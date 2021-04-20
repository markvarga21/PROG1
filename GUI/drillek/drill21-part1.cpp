#include<iostream>
#include<vector>
#include<exception>
#include<fstream>
#include<algorithm>
#include<list>

using namespace std;

struct Item
{
	Item(string n, int i, double v): name(n), iid(i), value(v) {}
	string name;
	int iid;
	double value;

	//bool operator==(const Item& i1) { return name == i1.name; }
};

ostream& operator<<(ostream& os, const Item& i)
{
	os << i.name << ' ' << i.iid << ' ' << i.value;
	return os;
}

template<typename Iter>
void printout(const Iter& first, const Iter& last)
{
	for (auto p = first; p != last; ++p)
		cout << *p << ' ' << endl;
}

class compByName
{
private:
	string name;
public:
	compByName(const string& s): name{s} {}
	bool operator()(const Item& i) const { return i.name == name; }
};

class compById
{
private:
	int id;
public:
	compById(const int& idd): id(idd) {}
	bool operator()(const Item& i) const { return i.iid == id; }
};

void format() { cout << "-----------------------------------------------------" << endl; }

int main()
try {
	vector<Item> vi;
	string n;
	int id;
	double val;

	// file handling
	string filename = "p1_infile.txt";
	ifstream is {filename};
	if (!is) cout << "Can't open file!" << endl;

	// reading in datas
	while (is >> n >> id >> val) { vi.push_back(Item{n, id, val}); }

	// sortings
	// sorting by name
	sort(vi.begin(), vi.end(), 
		[] (const Item& i1, const Item& i2) { return i1.name < i2.name; });
	// sorting by id
	sort(vi.begin(), vi.end(), 
		[] (const Item& i1, const Item& i2) { return i1.iid < i2.iid; });
	// sorting by value, descendent
	sort(vi.begin(), vi.end(), 
		[] (const Item& i1, const Item& i2) { return i1.value > i2.value; });

	format();

	// printing out the elements after sorting
	cout << "### Vector elements after sorting ###" << endl;
	printout(vi.begin(), vi.end());

	// insertions
	vi.insert(vi.end(), Item{"horse shoe", 99, 12.34});
	vi.insert(vi.end(), Item{"Canon S400", 9988, 499.95});

	format();

	// printing out the elements after inserting
	cout << "### Vector elements after inserting ###" << endl; 
	printout(vi.begin(), vi.end());

	// erase by name
	auto name_erase = find_if(vi.begin(), vi.end(), compByName("ajto"));
	vi.erase(name_erase);
	// erase by id
	auto id_erase = find_if(vi.begin(), vi.end(), compById(1));
	vi.erase(id_erase);

	format();

	//printing out after erase
	cout << "### Vector elements after erasing ###" << endl; 
	printout(vi.begin(), vi.end());

	return 0;
} catch (exception& e) {
	cerr << e.what() << endl;
	return 1;
} catch (...) {
	cerr << "Something went wrong!" << endl;
	return 2;
}