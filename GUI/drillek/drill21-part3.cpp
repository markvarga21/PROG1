#include<iostream>
#include<vector>
#include<exception>
#include<fstream>
#include<algorithm>

using namespace std;

template<typename Iter>
void printout(const Iter& first, const Iter& last, const string& s)
{
	cout << s << endl;
	for (auto p = first; p != last; ++p)
		cout << *p << ' ';
	cout << endl;
}

template<typename InputIt, typename T, class BinaryOperation>
T my_accumulate(InputIt first, InputIt last, T init, BinaryOperation op)
{
	while(first != last) 
	{
		init = op(init, *first);
		++first;
	}
	return init;
}

template<typename InputIt>
double my_mean(InputIt first, InputIt last)
{
	double sum = my_accumulate(first, last, 0.0, plus<double>());
	int elem_nb = distance(first, last);
	return sum/elem_nb;
}

void format() { cout << "-----------------------------------------------------" << endl; }

int main()
try {
	vector<double> vd;

	// file handling
	string filename = "p3_infile.txt";
	ifstream is {filename};
	if (!is) cout << "Can't open file!" << endl;

	// reading in datas
	double data;
	while (is >> data) { vd.push_back(data); }

	// printing out the default datas
	printout(vd.begin(), vd.end(), "VD datas: ");

	format();

	// copying 'vd' into 'vi'
	vector<int> vi(vd.size());
	copy(vd.begin(), vd.end(), vi.begin());

	// writing out 'vi'
	printout(vi.begin(), vi.end(), "VI copied datas: ");

	format();

	// printing out the pairs
	cout << "Element pairs: " << endl;
	for (int i = 0; i < vi.size(); ++i) cout << vd[i] << ' ' << vi[i] << endl; 

	format();

	// summing and outputting
	double vd_sum = my_accumulate(vd.begin(), vd.end(), 0.0, plus<double>());
	cout << "Sum of vd's elements: " << vd_sum << endl;

	format();

	// diff between sum of vd's elements and of vi's elements
	int vi_sum = my_accumulate(vi.begin(), vi.end(), 0, plus<int>());
	cout << "Diff between vd's elem. and of vi's elem.: " << vd_sum-vi_sum << endl;

	format();

	// reversing
	reverse(vd.begin(), vd.end());
	printout(vd.begin(), vd.end(), "Reversed 'vd': ");

	format();

	// mean/avg of 'vd'
	double avg = my_mean(vd.begin(), vd.end());
	cout << "VD mean: " << avg << endl;

	format();

	// copying elements which are less than vd's mean
	vector<double> vd2;
	copy_if(vd.begin(), vd.end(), back_inserter(vd2), [avg] (const double& val) { return val < avg; });
	printout(vd2.begin(), vd2.end(), "Elements of vd which are less than its average: ");


	return 0;
} catch (exception& e) {
	cerr << e.what() << endl;
	return 1;
} catch (...) {
	cerr << "Something went wrong!" << endl;
	return 2;
}