#include "../source/std_lib_facilities.h"

using namespace std;
using Line = vector<char>; // a line is a vector of characters, this is an alias for shortcutting

class Text_iterator
{
private:
	list<Line>::iterator ln; // ln == line
	Line::iterator pos; // adott character pozicioja egy adott sorban/lineban
public:
	// start the iterator at line ll's character position pp
	// ll -> adott sor; pp -> adott sor adott eleme/char-ja
	Text_iterator(list<Line>::iterator ll, Line::iterator pp): ln{ll}, pos{pp} {}

	char& operator*() { return *pos; }
	Text_iterator& operator++(); 

	bool operator==(const Text_iterator& other) const
		{ return ln == other.ln && pos == other.pos; }
	bool operator!=(const Text_iterator& other) const
		{ return !(*this == other); } // azert lehet itt hasznalni, mivel mar definialva van
									  // *this == megnezzuk ezt: ln == other.ln && pos == other.pos; 

	Line& get_line() const { return *ln; }
    Line::iterator get_pos() const { return pos; }
};

namespace std { // ez az miatt kell hogy megfeleljen az iterator stl formajanak
	template<>
	struct iterator_traits<Text_iterator> 
	{
    	typedef ptrdiff_t          difference_type;
        typedef char               value_type;
        typedef char*              pointer;
        typedef char&              reference;
        typedef input_iterator_tag iterator_category;
	};
}

Text_iterator& Text_iterator::operator++()
{
	++pos;
	if (pos == (*ln).end()) // vagyis egy adott sor vegen vagyok, az utolso karakternel; 
	{						// kiertekelesi sorrendre (mivel elobb az end() ertekelodne ki s nem a *) figyelve, hogy elkerjuk az adott sort
		++ln; // sor count novelese
		pos = (*ln).begin(); // pozicio visszahozasa az elejere
	}
	return *this;
}

struct Document
{
	list<Line> line; // a document is a list of lines
	Document() { line.push_back(Line{}); }

	Text_iterator begin() // az adott sor elso karaktere
		{ return Text_iterator(line.begin(), line.begin()->begin()); } // karaktervektor iterator; line.begin()->begin() == (*line.begin().begin()) 
	Text_iterator end() // az utolso karakter utani iterator/helyzet	
	{
		auto last = line.end();
		--last; // tudjuk hogy a dokumentum nem ures;// -> mindez az miatt kell, mivel a dokumentem vegere mindig berakunk egy ures sort
		return Text_iterator(last, last->end()); // mivel a dokumentem vegere mindig berakunk egy ures sort, es ugye nekunk meg pont az utolso nem ures sor kell
	}
};

istream& operator>>(istream& is, Document& d)
{
	if (!is) return is; //hibakezeles
	for (char ch; is.get(ch); ) // mivel get van itt, a whitespacek is be lesznek olvasva, sima is >> -el nem, mivel ez atugorja a karaktereket
	{
		d.line.back().push_back(ch); // character hozzaadasa, hozzafuzese az adott sor elejtol kezdve
		if (ch == '\n')
			d.line.push_back(Line{}); // uj sor beszurasa
	}
	if (d.line.back().size()) // utolso ures sor hozzaadasa, ha esetleg nem vegzodne uj sorra; ha az utolso sor  nem ures
		d.line.push_back(Line{}); // akkor adjunk hozza egy ures sort
	return is; // konvencio es chaining miatt
}

template<typename Iter>
void sajat_advance(Iter& p, int n)
{
	while (0 < n) { ++p; --n; }
	while (n < 0) { --p; ++n; }
}

void erase_line(Document& d, int n)
{
	if (n < 0 || d.line.size()-1 <= n) return; // hibakezeles rossz input eseten
	auto p = d.line.begin();
	sajat_advance(p, n); // ez csak siman ellepteti a p-t n-el, STL beli
	d.line.erase(p); // STL beli
}

bool match(Text_iterator p, Text_iterator last, const string& s)
{
	for (auto q = s.begin(); q != s.end(); ++q) // vegig ellenorzi az adott substringet
	{
		if (*q != *p || p == last) return false;
		++p;
	}
	return true;
}

Text_iterator find_text(Text_iterator first, Text_iterator last, const string& s)
{
	if (s.size() == 0) return last; // ures string keresese nem ertelmezett
	char first_char = s[0];
	while (true)
	{
		auto p = find(first, last, first_char);
		if (p == last || match(p, last, s)) return p;
		first = ++p; // kovetkezo karakter megnezese
	}
}

void find_replace(Text_iterator first, Text_iterator last, const string& to_replace_str, const string& replace_str)
{
	Text_iterator p = find_text(first, last, to_replace_str); // iterator a cserelendo szovegre
	if (p == last) return; // nincs benne a cserelendo string

	Line& li = p.get_line(); // melyik sorban van a cserelendo szo; itt megkapom magat a line-t

	// van-e a li-nek elegendo helye hogy cserelhessunk?
	const int diff = replace_str.size()-to_replace_str.size();
	// ha nem ferne el a string, foglalunk neki helyet
	if (diff > 0 && li.size()+diff > li.capacity()) // mint a vektornal, amikor duplaztunk, van a size es a capacity (hogy mennyi fer meg el)
	{
		li.reserve(li.size()+diff); // memoriafoglalas
	}

	p = find_text(first, last, to_replace_str); // ujra megkeresem az allokalas miatt

	auto q = p.get_pos(); // adott pozicio lekerese

	q = li.erase(q, q+to_replace_str.size()); // a cserelendo string kitorlese

	// crbegin() -> egy constant reverse iteratort terit vissza ami a string vegere mutat
	// crend() -> elso elottire mutat
	for (auto r = replace_str.crbegin(); r != replace_str.crend(); ++r) 
		q = li.insert(q, *r); // karakterenkent valo beszuras az adott sorba, mivel vektorok eseten az insert az adott pozicio ele szurja be
}							  // ez miatt kell a vegerol haladni, beszuras utan pedig noveli a container nagysagat 1-el

int char_count(Document& d)
{
	int count = 0;
	for (const auto& p : d)
	{
		if (!isspace(p)) // ha nem egy space karakter van ott akkor noveli a szamlalo erteket
			++count;
	}
	return count;
}

void print(Document& d)
{
	for (const auto& p : d) cout << p;
}

int main()
try {
	Document my_doc;
	string filename = "text_editor_input.txt";
	ifstream iss {filename};

	if (!iss) 
	{
		cout << "File not found!" << endl;
		return 1;
	}

    iss >> my_doc;

    print(my_doc);

    find_replace(my_doc.begin(), my_doc.end(), "volt", "LESZ");

    print(my_doc);

    cout << endl << "A karekterek szama a dokumentumban: " << char_count(my_doc) << endl;
	return 0;
} catch (exception& e) {
	cerr << e.what() << endl;
	return 1;
} catch (...) {
	cerr << "Something went wrong!" << endl;
	return 2;
}