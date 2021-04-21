#include<iostream>
#include<map>
#include<vector>
#include<algorithm>
#include<exception>

using namespace std;

void read_val(map<string, int>& m)
{
	string s;
	int val;
	cin >> s >> val;
	m.insert({s, val});
}

template<typename T1, typename T2>
void print_map(const map<T1, T2> mapp, const string& str)
{
	cout << str << endl;
	for (const auto& e : mapp) cout << e.first << ' ' << e.second << endl;
}

void format() { cout << "-----------------------------------------------------" << endl; }

double map_int_sum(const map<string, int>& mapp)
{
	int sum = 0;
	for (const auto& e : mapp) sum += e.second;
	return sum;
}

int main()
try {
	map<string, int> msi;

	// inserting 10 elements into the map
	msi.insert({"prog", 21});
	msi.insert({"lecture", 11});
	msi.insert({"info", 31});
	msi.insert({"magyar", 12});
	msi.insert({"diszkmat", 22});
	msi.insert({"oprendszer", 23});
	msi.insert({"kalkulus", 24});
	msi.insert({"terinfo", 25});
	msi.insert({"halozati", 22});
	msi.insert({"adatbazis", 20});

	print_map(msi, "MSI elements: ");

	format();

	// erasing
	msi.erase(msi.begin(), msi.end());

	// reading value pairs
	cout << "Please enter 10 pairs of 'string' and 'int': " << endl;
	constexpr int how_many = 10;
	for (int i = 0; i < how_many; ++i) read_val(msi);
	format();
	// printing out these elements
	print_map(msi, "New read values of msi: ");

	format();

	// sum of map's elements
	cout << "Sum of map's 'int' elements: " << map_int_sum(msi) << endl;

	format();

	// reversed pairs of 'msi'
	map<int, string> mis;
	for (const auto& m : msi) mis.insert({m.second, m.first});
	print_map(mis, "Data pairs of 'mis': ");

	return 0;
} catch (exception& e) {
	cerr << e.what() << endl;
	return 1;
} catch (...) {
	cerr << "Something went wrong!" << endl;
	return 2;
}
