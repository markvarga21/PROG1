#include "../source/std_lib_facilities.h"

template<typename T>
struct S {
private:
	T val;
public:
	S(T vall = T()) : val(vall) {}

	T& get();
	T get() const { return val; }

	//T set(T newval) { val = newval; }

	T operator=(const T&);

};

template<typename T> T& S<T>::get() { return val; }

//template<typename T> T const S<T>::get() { return val; }

template<typename T> T S<T>::operator=(const T& newval) { val = newval; }

template<typename T>
istream& operator>>(istream& is, S<T>& tt){
	is >> tt.get();
	return is;
}

template<typename T> void read_val(T& v)
{
	cin >> v;
}

int main()
try {
	S<int> intt {5};
	S<char> charr {'c'};
	S<double> doublee {3.1415};
	S<string> stringg {"alma"};
	//S<vector<int>> vecc { {3, 4, 5, 6} };

	// 4-es feladat
	//cout << intt.val << " " << charr.val << " " << doublee.val << " " << stringg.val << endl;

	//cout << intt.get() << endl;

	// 8-as feladat
	//cout << intt.get() << " " << charr.get() << " " << doublee.get() << " " << stringg.get() << endl;
	//cout << vecc.get();

	// 9-es feladat
	/*cout << "Regi intt: " << intt.get() << endl;
	intt.set(10);
	cout << intt.get() << endl;
	*/
	
	// 10-es feladat
	/*S<int> masik {25};
	cout << "Regi intt: " << intt.get() << endl;
	intt = masik;
	cout << "Uj intt: " << intt.get() << endl;*/

	// 11-es teszt
	/*const S<int> a {36};
	cout << a.get() << endl;*/

	// 13-as feladat
	/*S<int> i;
	S<double> d;
	S<string> s;
	S<char> c;
	read_val(i); read_val(d); read_val(s); read_val(c);
	cout << i.get() << " " << d.get() << " " << s.get() << " " << c.get() << endl;
	*/


	return 0;
} catch (exception& e) {
	cerr << e.what() << endl;
	return 1;
} catch (...) {
	cerr << "Something went wrong!" << endl;
	return 2;
}