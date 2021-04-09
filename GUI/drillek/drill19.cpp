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

template<typename T> void read_val(T& v) { cin >> v; }

int main()
try {
	S<int> intt {5};
	S<char> charr {'c'};
	S<double> doublee {3.1415};
	S<string> stringg {"alma"};
	S<vector<int>> vecc { {3, 4, 5, 6} };

	// 4-es feladat
	//cout << intt.val << " " << charr.val << " " << doublee.val << " " << stringg.val << endl;

	//cout << intt.get() << endl;

	cout << "8-as feladat" << endl;
	cout << intt.get() << " " << charr.get() << " " << doublee.get() << " " << stringg.get() << endl;
	vector<int> local = vecc.get();
	for (auto n : local) cout << n << " ";
	cout << endl;

	/*
	cout << "9-es feladat" << endl;
	cout << "Regi intt: " << intt.get() << endl;
	intt.set(10);
	cout << intt.get() << endl;
	*/

	cout << "10-es feladat" << endl;
	S<int> masik {25};
	cout << "Regi intt: " << intt.get() << endl;
	intt = masik;
	cout << "Uj intt: " << intt.get() << endl;

	cout << "11-es teszt" << endl;
	const S<int> a {36};
	cout << a.get() << endl;

	cout << "13-as feladat" << endl;
	S<int> i;
	S<double> d;
	S<string> s;
	S<char> c;
	cout << "Kerem irja be a tipusnak megfelelo ertekeket (int, double, string, char): " << endl;
	read_val(i); read_val(d); read_val(s); read_val(c);
	cout << i.get() << " " << d.get() << " " << s.get() << " " << c.get() << endl;

	return 0;
} catch (exception& e) {
	cerr << e.what() << endl;
	return 1;
} catch (...) {
	cerr << "Something went wrong!" << endl;
	return 2;
}