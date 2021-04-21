#include<isotream>
#include<vector>

using namespace std;

template<typename Elem>
struct Link {
	Link* prev; // elozo
	Link* succ; // kovetkezo
	Elem val; // maga az ertek
};

template<typename Elem>
class List {
private:
	Link<Elem>* first;
	Link<Elem>* last; // utolso utanira mutat
public:
	class iterator; // member type: iterator

	iterator begin(); // iterator ami az elso elemre mutat
	iterator end(); // iterator ami az utolso utanira mutat

	iterator insert(iterator p, const Elem& v); // insert v into list after p
	iterator erase(iterator p); // remove p from list

	void push_back(const Elem& v); // insert v at end
	void push_front(const Elem& v); // insert v at front
	void pop_front(); // remove the first element
	void pop_back(); // remove the last element;

	Elem& front(); // the first element
	Elem& back(); // the last element
};

template<typename ELem>
class list<Elem>::iterator {
private:
	Link<Elem>* curr; // current link
public:
	iterator(Link<Elem>* p) : curr(p) {}

	iterator& operator++() { curr = curr->succ; return *this; } // elore
	iterator& operator--() { curr = curr->prev; return *this; } // visszafele
	Elem& operator*() { return curr->val; } // get the value; dereference

	bool operator==(const iterator& b) const { return cur == b.curr; }
	bool operator!=(const iterator& b) const { return cur != b.curr; }
};

template<typename Iter>
Iterator high(Iter first, Iter last) // return an iterator to the element in [first, last), that has the highest value
{
	Iterator high = first;
	for (Iterator p; p != last; ++p)
	{
		if (*high < *p) high = p;
	}
	return high;
}

int main()
try {


	return 0;
} catch(exception& e) {
	cerr << e.what() << endl;
	return 1;
} catch(...) {
	cerr << "Something went wrong!" << endl;
	return 2;
}