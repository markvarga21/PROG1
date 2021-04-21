#include<iostream>
#include<vector>

using namespace std;

template<typename Elem>
struct Link {
	Link(const Elem& v = Elem(), Link* p = 0, Link* s = 0) :prev(p), succ(s), val(v) {}

	Link* prev; // elozo
	Link* succ; // kovetkezo
	Elem val; // maga az ertek
};

template<typename Elem>
struct my_list {
	Link<Elem>* first;
	Link<Elem>* last; // utolso utanira mutat

	my_list(): first(new Link<Elem>()), last(first) {}

	class iterator; // member type: iterator

	iterator begin() { return iterator(first); } // iterator ami az elso elemre mutat
	iterator end() { return iterator(last); } // iterator ami az utolso utanira mutat

	iterator insert(iterator p, const Elem& v); // insert v into list after p
	iterator erase(iterator p); // remove p from list

	void push_back(const Elem& v); // insert v at end
	void push_front(const Elem& v); // insert v at front
	void pop_front(); // remove the first element
	void pop_back(); // remove the last element;

	Elem& front() { return *first; } // the first element
	Elem& back(); // the last element
};

template<typename Elem>
class my_list<Elem>::iterator {
private:
	Link<Elem>* curr; // current link
public:
	iterator(Link<Elem>* p) : curr(p) {}

	iterator& operator++() { curr = curr->succ; return *this; } // elore
	iterator& operator--() { curr = curr->prev; return *this; } // visszafele
	Elem& operator*() { return curr->val; } // get the value; dereference

	bool operator==(const iterator& b) const { return curr == b.curr; }
	bool operator!=(const iterator& b) const { return curr != b.curr; }
};

template<typename Elem>
void my_list<Elem>::push_front(const Elem& v)
{
	first = new Link<Elem>(v, 0, first); 
}

template<typename Iterator>
Iterator high(Iterator first, Iterator last) // return an iterator to the element in [first, last), that has the highest value
{
	Iterator high = first;
	for (Iterator p = first; p != last; ++p)
	{
		if (*high < *p) high = p;
	}
	return high;
}

int main()
try {
	my_list<int> ls;
	for (int i = 0; cin >> i; )
		ls.push_front(i);

	my_list<int>::iterator highest = high(ls.begin(), ls.end());

	cout << "Highest value: " << *highest << endl;

	return 0;
} catch(exception& e) {
	cerr << e.what() << endl;
	return 1;
} catch(...) {
	cerr << "Something went wrong!" << endl;
	return 2;
}