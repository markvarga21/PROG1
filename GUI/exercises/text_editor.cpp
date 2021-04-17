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
		{ return ln == other.ln && pos == other.pos; } // itt lehetne-e *this self-reference-el vajon?
	bool operator!=(const Text_iterator& other) const
		{ return !(*this == other); }

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
	if (pos == (*ln).end()) // vagyis egy adott sor vegen vagyok, az utolso karakternel
	{
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
		{ return Text_iterator(line.begin(), line.begin()->begin()); }
	Text_iterator end() // az utolso karakter utani iterator/helyzet
	{
		auto last = line.end();
		--last; // tudjuk hogy a dokumentum nem ures
		return Text_iterator(last, last->end());
	}
};

istream& operator>>(istream& is, Document& d)
{
	if (!is) return is; //hibakezeles
	for (char ch; is.get(ch); )
	{
		d.line.back().push_back(ch); // character hozzaadasa, hozzafuzese az adott sor elejtol kezdve
		if (ch == '\n')
			d.line.push_back(Line{}); // uj sor beszurasa
	}
	if (d.line.back().size()) d.line.push_back(Line{}); // utolso ures sor hozzaadasa
	return is;
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

    istringstream iss 
    	{"Egyszer volt\nhol nem volt\nhetedhet orszagon\nis tul\n"};
    iss >> my_doc;

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