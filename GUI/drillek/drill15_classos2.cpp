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

	Person(string first = "Gipsz", string second = "Jakab", int c_age = 63) : first_name(first), second_name(second), age(c_age) 
	{
		if (age <= min_age || age > max_age) throw Invalid_input{};
		for (int i = 0; i < first_name.size(); ++i) if (!isalpha(first_name[i])) throw Invalid_input{}; 
		for (int i = 0; i < second_name.size(); ++i) if (!isalpha(second_name[i])) throw Invalid_input{}; 
	}

	string get_first_name() const { return first_name; }
	string get_second_name() const { return second_name; }
	int get_age() const { return age; }

	void set_first_name(string n) 
	{
		for (int i = 0; i < n.size(); ++i) if (!isalpha(n[i])) throw Invalid_input{}; 
		first_name = n; 
	}

	void set_second_name(string n) 
	{
		for (int i = 0; i < n.size(); ++i) if (!isalpha(n[i])) throw Invalid_input{}; 
		second_name = n; 
	}

	void set_age(int nb) 
	{
		if (nb <= min_age || nb > max_age) throw Invalid_input{}; 
		age = nb; 
	}
private:
	string first_name;
	string second_name;
	int age;
};

ostream& operator<<(ostream& os, const Person& p){
	return os << p.get_first_name() << " " << p.get_second_name() << " " << p.get_age();
}

istream& operator>>(istream& is, Person& p){
	string str1;
	string str2;
	int a;

	is >> str1 >> str2 >> a;
	
	if (a <= p.min_age || a > p.max_age) throw Invalid_input{};  
	for (int i = 0; i < str1.size(); ++i) if (!isalpha(str1[i])) throw Invalid_input{};
	for (int i = 0; i < str2.size(); ++i) if (!isalpha(str2[i])) throw Invalid_input{};
	p.set_first_name(str1);
	p.set_second_name(str2);
	p.set_age(a);
}

int main()
try {
	vector<Person> persons;
	
	cout << "Kerem irja be a neveket egy '|' jellel befejezoleg a legvegen" << endl;
	string vezeteknev;
	string keresztnev;
	int kor;
	string trigger = "|";
	while (cin){
		cin >> vezeteknev;
		if (vezeteknev == trigger) break;
		cin >> keresztnev;
		cin >> kor;
		persons.push_back(Person{vezeteknev, keresztnev, kor});
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
