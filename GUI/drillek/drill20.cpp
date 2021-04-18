#include<iostream>
#include<vector>
#include<list>
#include<algorithm>

using namespace std;

namespace sajat {
template<typename Iter1, typename Iter2>
Iter2 copy(Iter1 f1, Iter1 e1, Iter2 f2)
{
	//if (f1==e1) return *this;
	while (f1 != e1) {
		*f2 = *f1;
		++f1;
		++f2;
	}
	return f2;
}

} //end of namespace

template<typename Iter>
void printout(Iter first, Iter last, string name)
{
	cout << name << endl;
	for (auto p = first; p != last; ++p){ cout << *p << ' '; }
	cout << endl;
}

int main()
try {
	// initialization
	int arr[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
	const int arr_size = sizeof(arr)/sizeof(*arr);
	vector<int> vec = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
	list<int> ls = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

	// writing out the default starting datas
	/*printout(&arr[0], &arr[0]+arr_size, "Kezdo array elemek: ");
	printout(vec.begin(), vec.end(), "Kezdo vektor elemek: ");
	printout(ls.begin(), ls.end(), "Kezdo lista elemek: ");
	*/

	// copying default containers
	int arr_copy[arr_size];
	sajat::copy(&arr[0], &arr[0]+arr_size, &arr_copy[0]);
	vector<int> vec_copy = vec;
	list<int> ls_copy = ls;
	
	// writing out the copied versions of starting containers
	/*printout(&arr_copy[0], &arr_copy[0]+arr_size, "Masolt kezdo array elemek: ");
	printout(vec_copy.begin(), vec_copy.end(), "Masolt kezdo vektor elemek: ");
	printout(ls_copy.begin(), ls_copy.end(), "Masolt kezdo lista elemek: ");
	*/

	// modofing container values
	for (int i = 0; i < arr_size; ++i) { arr_copy[i] += 2; }
	for (auto p : vec_copy) { p += 3; }
	for (auto p = ls_copy.begin(); p != ls_copy.end(); ++p) { *p += 5; }

	// printing out modified container values
	printout(&arr_copy[0], &arr_copy[0]+arr_size, "Masolt+novelt array elemek: ");
	printout(vec_copy.begin(), vec_copy.end(), "Masolt+novelt kezdo vektor elemek: ");
	printout(ls_copy.begin(), ls_copy.end(), "Masolt+novelt kezdo lista elemek: ");

	// formatting
	cout <<  endl;

	// copying different containers into each other
	copy(&arr_copy[0], &arr_copy[0]+arr_size, vec_copy.begin());
	copy(ls_copy.begin(), ls_copy.end(), &arr_copy[0]);

	// writing out these values
	printout(vec_copy.begin(), vec_copy.end(), "Array elemek vektorban: ");
	printout(&arr_copy[0], &arr_copy[0]+arr_size, "Lista elemek arrayben: ");

	cout << endl;

	// existences
	// in vector
	const int vec_val = 3;
    auto vec_p = find(vec_copy.begin(), vec_copy.end(), vec_val);
    if (vec_p != vec_copy.end())
    	cout << "Found the number " << vec_val << ", on position " << distance(vec_copy.begin(), vec_p) << "." << endl;
    else cout << "The number " << vec_val << " could not be found!" << endl;

    // in list
    const int ls_val = 27;
    auto ls_p = find(ls_copy.begin(), ls_copy.end(), ls_val);
    if (ls_p != ls_copy.end())
    	cout << "Found the number " << ls_val << ", on position " << distance(ls_copy.begin(), ls_p) << "!" << endl;
    else cout << "The number " << ls_val << " could not be found!" << endl;

	return 0;
} catch (exception& e) {
	cerr << e.what() << endl;
	return 1;
} catch (...) {
	cerr << "Something went wrong!" << endl;
	return 2;
}