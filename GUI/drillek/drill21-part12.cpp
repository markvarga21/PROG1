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

bool sortByName(const Item& item1, const Item& item2)
{
	return item1.name < item2.name;
}

bool sortById(const Item& item1, const Item& item2)
{
	return item1.iid < item2.iid;
}

bool sortByValDesc(const Item& item1, const Item& item2)
{
	return item1.value > item2.value;
}

void format() { cout << "-----------------------------------------------------" << endl; }

int main()
try {
	list<Item> ls;
	string n;
	int id;
	double val;

	// file handling
	string filename = "p1_infile.txt";
	ifstream is {filename};
	if (!is) cout << "Can't open file!" << endl;

	// reading in datas
	while (is >> n >> id >> val) { ls.push_back(Item{n, id, val}); }

	
	// sortings
	ls.sort(sortByName); // sorting by name
	ls.sort(sortById); // sorting by id
	ls.sort(sortByValDesc); // sorting by value, descendent

	format();

	// printing out the elements after sorting
	cout << "### List elements after sorting ###" << endl;
	printout(ls.begin(), ls.end());

	// insertions
	ls.insert(ls.end(), Item{"horse shoe", 99, 12.34});
	ls.insert(ls.end(), Item{"Canon S400", 9988, 499.95});

	format();

	// printing out the elements after inserting
	cout << "### List elements after inserting ###" << endl; 
	printout(ls.begin(), ls.end());

	// erase by name
	auto name_erase = find_if(ls.begin(), ls.end(), compByName("ajto"));
	ls.erase(name_erase);
	// erase by id
	auto id_erase = find_if(ls.begin(), ls.end(), compById(1));
	ls.erase(id_erase);

	format();

	//printing out after erase
	cout << "### List elements after erasing ###" << endl; 
	printout(ls.begin(), ls.end());

	return 0;
} catch (exception& e) {
	cerr << e.what() << endl;
	return 1;
} catch (...) {
	cerr << "Something went wrong!" << endl;
	return 2;
}