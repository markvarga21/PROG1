/*
	g++ drill15_classos.cpp -o drill15class
*/ 
#include "../source/std_lib_facilities.h"

class Invalid_input {};

struct Person
{
public:
	const int max_age = 150;
	const int min_age = 1;

	Person(string c_name = "Goofy", int c_age = 63) : name(c_name), age(c_age) 
	{
		if (age <= min_age || age > max_age) throw Invalid_input{};
		for (int i = 0; i < name.size(); ++i) if (!isalpha(name[i])) throw Invalid_input{}; 
	}

	string get_name() const { return name; } //ide nem tudtam a konyv altalal kert name() elnevezest adni, mert maskepp nevutkozes lenne
	int get_age() const { return age; }

	void set_name(string n) { name = n; }
	void set_age(int nb) { age = nb; }
private:
	string name;
	int age;
};

ostream& operator<<(ostream& os, const Person& p){
	return os << p.get_name() << " " << p.get_age();
}

istream& operator>>(istream& is, Person& p){
	string str;
	int a;

	cin >> str >> a;
	
	if (a <= p.min_age || a > p.max_age) throw Invalid_input{};
	for (int i = 0; i < str.size(); ++i) if (!isalpha(str[i])) throw Invalid_input{}; 
	
	p.set_name(str);
	p.set_age(a);
}

int main()
try {
	vector<Person> persons;
	
	cout << "Kerem irja be a neveket egy '|' jellel befejezoleg a legvegen" << endl;
	string nev;
	int kor;
	string trigger = "|";
	while (cin){
		cin >> nev;
		if (nev == trigger) break;
		cin >> kor;
		persons.push_back(Person{nev, kor});
	}
	
	
	for (Person n : persons) cout << n << endl;
	
	return 0;
} catch (Invalid_input){
	cerr << "Incorrect name or age!" << endl;
	return 1;
} catch (exception& e){
	cerr << e.what() << endl;
	return 2;
} catch (...){
	cerr << "Something went wrong!" << endl;
	return 3;
}
