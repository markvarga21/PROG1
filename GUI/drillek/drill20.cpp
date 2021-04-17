#include<iostream>
#include<vector>
#include<list>

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

/*template<typename T>
void printout(T& t, int sz)
{
	for (int i = 0; i < sz, ++i) std::cout << T[i] << ' ';
}*/

int main()
{
	// initialization
	int arr[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
	const int arr_size = sizeof(arr)/sizeof(*arr);
	vector<int> vec = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
	list<int> ls = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

	// printing out the default containers
	cout << "Array def. elements: ";
	for (int i = 0; i < arr_size; ++i) cout << arr[i] << ' ';
	cout << endl;
	cout << "Vector def. elements: ";
	for (int i = 0; i < vec.size(); ++i) cout << vec[i] << ' ';
	cout << endl;
	cout << "List def. elements: ";
	for (auto p = ls.begin(); p!=ls.end(); ++p) cout << *p << ' ';
	cout << endl << endl;

	// copying
	vector<int>::iterator vector_in_array = sajat::copy(&arr[0], &arr[arr_size], vec.begin());
	int list_to_arr[ls.size()];
	sajat::copy(ls.begin(), ls.end(), &arr[0]);

	cout << "Copied array in vector: ";
	//for (auto p = vector_in_array.begin(); p!=vector_in_array.end(); ++p) cout << *p << ' ';
	cout << endl;
	cout << "Copied list in an array: ";
	for (int i = 0; i < ls.size(); ++i) cout << arr[i] << ' ';



	return 0;
}