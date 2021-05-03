// g++ vector_002.cpp -o vec002 -Wall
#include "std_lib_facilities.h"

class My_out_of_range{};

struct No_default { //legyen azert default konstruktor, ahol ez ertelmezve van
	No_default(int k) { a = k; }
	int a = 0;
	int b = 0;
};

template<typename T, typename A = allocator<T>> //'A' az T-re hivatkozo allokator
class My_vector
{
//reprezentacio
	A alloc;
	long unsigned int sz; //mennyit hasznalunk is fel ebbol a helybol
	T* elem;
	int space; //mennyinek foglaltunk helyet

	void debug(const string& str)
	{
		//irja ki az objektum cimet = this
		cerr << this << "->" << str << " elem ptr: "
			<< elem << endl;
	}
//interface
public:

	using size_type = unsigned long; //tipus aliasok
	using value_type = T; //adunk a tipusnak egy alternativ nevet
	using iterator = T*;
	using const_iterator = const T*;

	//BEGIN, END fuggvenyek, iteratorok
	iterator begin() { return elem; }
	const iterator begin() const { return elem; } //itt a return &elem[0] ugyan az mint a return elem;
	iterator end() { return elem+sz; } //mintha az elem pointert elleptetnenk sz-el
	const iterator end() const { return elem+sz; } //&elem[sz] == elem+sz; 
	iterator back() { return elem+sz-1; } //utolso elem cimet adja vissza

	My_vector(): sz{0}, elem{nullptr}, space{0} {} //szukseges es legyen default konstruktor

	//akkor foglalunk free soreban memoriat, ha azt akarjuk hogy az ott maradjon a lefoglalas, konstruktor utan is 
	explicit My_vector(int s): sz(s), elem{alloc.allocate(s)}, space(s)
	{ //ha nem mondjuk hogy explicit akkor siman csinalhatjuk hogy My_vector mv6 = 10
		for (int i = 0; i < s; ++i) alloc.construct(&elem[i], T());
		//debug("int constructor");
	}

	My_vector(initializer_list<T> lst): 
		sz(lst.size()), 
		elem{alloc.allocate(sz)},
		space(lst.size())
	{
		for (int i = 0; i < sz; ++i) alloc.construct(&elem[i], *(lst.begin()+i)); //hova es milyen erteket; *(...) wut this
	}

	My_vector(const My_vector& arg): 
		sz{arg.sz},
		elem{alloc.allocate(sz)},
		space{arg.sz}
	{
		for (int i = 0; i < sz; ++i) alloc.construct(&elem[i], arg[i]); //arg -> referenciat ad at
	}

	//operatorok self reference-t adnak at
	My_vector& operator=(const My_vector& arg)
	{
		if (this == &arg) return *this;
		// ha onmagat akarnank ertekul adni, masolni
		// v=v;
		// folosleges memoriamuveleteket ne vegezzunk

		if (arg.sz <= space)
		{
			for (int i = 0; i < arg.sz; ++i)
				alloc.construct(&elem[i], arg[i]);
			for (int i = arg.sz; i < sz; ++i)
				alloc.destroy(&elem[i]);
			sz = arg.sz;
			return *this;
		}

		T* p = alloc.allocate(arg.sz);
		//copy(arg.elem, arg.elem+arg.sz, p);
		for(int i = 0; i < arg.sz; ++i) alloc.construct(&p[i], arg[i]);
		alloc.deallocate(elem, space); //memoriat szabadit fel
		//delete[] elem;
		elem = p;
		sz = arg.sz;
		space = arg.space;
		//debug("copy assignment");
		return *this; 
	}

	//&& r-value referencia, ha valami mozgatast jelent, akkor ezt kell hasznalni
	My_vector(My_vector&& arg):
		sz{arg.sz}, elem{arg.elem}, space{arg.space}
	{
		arg.sz = 0;
		arg.space = 0;
		arg.elem = nullptr; //az miatt kell h ne legyen double delete
		//debug("move constructor");
	}

	My_vector& operator=(My_vector&& arg)
	{
		//delete[] elem;
		for(int i = 0; i < sz; ++i) alloc.destroy(&elem[i]);
		alloc.deallocate(elem, space);

		space = arg.space;
		sz = arg.sz;
		elem = arg.elem;
		arg.sz = 0;
		arg.space = 0;
		arg.elem = nullptr;
		//debug("move assignment");
		return *this;
	}

	~My_vector() { 
		//delete[] elem; 
		for (int i = 0; i < sz; ++i) alloc.destroy(&elem[i]); //destroy elemeket torol, deletel
		alloc.deallocate(elem, space);
	} 

	long unsigned int size() const { return sz; }
	int capacity() const { return space; }

	T& operator[](int n){ return elem[n]; }
	const T& operator[](int n) const { return elem[n]; }

	// a simaban is (std lib-be) is at-al van megoldva
	T& at(int n) //ha rossz indexet adunk at
	{
		if (n < 0 || n >= sz) throw My_out_of_range();
		return elem[n];
	}

	const double& at(int n) const //ha rossz indexet adunk at
	{
		if (n < 0 || n >= sz) throw My_out_of_range();
		return elem[n];
	}

	void reserve(int newalloc)
	{
		if (newalloc <= space) return;
		//T* p = new T[newalloc];
		//T* p = alloc.allocate(newalloc);
		unique_ptr<T[]> p { alloc.allocate(newalloc) }; //levedi az ezalatt levo reszt, ahol egy hiba keletkezhet
		// T[] -> tobb elemnek foglalunk helyet, hasonlo mint a delete[]
		//for (int i = 0; i < sz; ++i) p[i] = elem[i];
		for (int i = 0; i < sz; ++i) alloc.construct(&p[i], elem[i]);
		for (int i = 0; i < sz; ++i) alloc.destroy(&elem[i]);
		alloc.deallocate(elem, space); //memoria felszabaditasa
		//delete[] elem;
		elem = p.release();
		space = newalloc;
	}

	void resize(int newsize, T val = T()) //utobbival opcionalis lesz ez a megadasi mod, vagyis a defaultra lesz beallitva ami altalaban 0
	{
		reserve(newsize);
		for (int i = sz; i < newsize; ++i) alloc.construct(&elem[i], val);
		for (int i = newsize; i < sz; ++i) alloc.destroy(&elem[i]);
		
		sz = newsize;
	}

	void push_back(const T d)
	{
		if (space == 0)
			reserve(8); //nincs jelentosege hogy most 8
		else if (sz == space) //ha elfogyik a terulet akkor duplazom
			reserve(2*space);
		//elem[sz] = d;
		alloc.construct(&elem[sz], d);
		++sz;
	}

	//insert is es az erase is konvenciok szerint egy-egy iteratort ad vissza

	iterator erase(iterator p) //mutatunk valahova es azt kell kitorolni, amire ez a 'p' iterator mutat
	{
		if (p == end()) return p; //ha a vegere mutat
		//ellenben ha nem a vege
		for (auto pos = p+1; pos != end(); ++pos)
			*(pos-1) = *pos; //mindig az elozore ramasoljuk az aktualisat, elore mozgatunk onnantol kezdve amit ki akarunk torolni

		//fel kell szabaditani az utolso
		alloc.destroy(&*(end()-1)); //az adott erteknek a cime = &*(end()-1); az end() az utolso utani elemre mutat mindig
		//dereferencialas (hogy meglegyen a konkret elem, hiszen ez meg egy iterator) => *(end()-1)
		--sz;
		return p;
	}

	iterator insert(iterator p, const T& val)
	{
		int index = p-begin(); //hany hely vna a kezdet es a 'p' kozott, ahova be akarjuk tenni
		if (size() == capacity()) //nem lenne muszaj a tagfiggvenyeket hasznalni
			reserve(size()==0?8:2*capacity());
		alloc.construct(elem+sz, *back()); //legutolso elemet kimasoljuk a vegere
		++sz;
		iterator pp = begin()+index;
		for (auto pos = end()-1; pos != pp; --pos) 
			*pos = *(pos-1); //toljuk eggyel
		*(begin()+index) = val;
		return pp; //mi tortenne ha nem adnank vissza az iteratort? vagyis ha nem lenne a 'return pp' resz
	}	

};

int main()
try {
	/*My_vector<double> dmv {10.5, 10.3, 10.7};

	for(int i = 0; i < dmv.size(); ++i)
		cout << dmv.at(i) << " ";
	cout << endl;

	dmv.resize(5, 0.0);
	for(int i = 0; i < dmv.size(); ++i)
		cout << dmv.at(i) << " ";
	cout << endl;*/


	My_vector<string> smv {"Jack", "Jill", "John", "Jenny", "Bela"};

	for(int i = 0; i < smv.size(); ++i)
		cout << smv.at(i) << " ";
	cout << endl << endl;

	auto p = find(smv.begin(), smv.end(), "Jill"); //find() standard library-s cucc, amivel containerben tudunk keresni
	//a find iteratorral ter vissza (talan pointer?)
	//'p' iterator

	smv.erase(p);

	smv.insert(p, "Joseph");

	for (const auto& e : smv) //mit irtunk hozza hogy mostmar mukodik s eddig nem ment?
		cout << e << endl;
	//a range-for loopok iteratorokkal mukodnek (maybe ezert is megyek mar, hiszen megirtuk hozza ezt a reszt)

	return 0;
} catch(exception& e){
	cerr << e.what() << endl;
	return 1;
} catch(...){
	cerr << "Something went wrong!" << endl;
	return 2;
}
