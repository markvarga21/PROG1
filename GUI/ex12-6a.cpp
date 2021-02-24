#include "Simple_window.h"
#include "Graph.h"

int main()
try {
	Simple_window win{Point{100, 100}, 200, 200, "6a"};
	Rectangle rec{Point{100, 100}, 300, 300};


	win.attach(rec);
	win.wait_for_button();
	return 0;
} catch (exception& e){
	cerr << e.what() << endl;
	return 1;
} catch (...){
	cerr << "Something went wrong!" << endl;
	return 2;
}