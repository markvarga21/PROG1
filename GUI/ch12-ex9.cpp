#include "Simple_window.h"
#include "Graph.h"

int main()
try {
	Simple_window win{Point{100, 100}, 1280, 720, "Pepe"}; 
	Image fr{Point{50, 50}, "pepe.jpg"};

	Text t{Point{150, 500}, "Pepe the frog"};

	win.attach(fr);
	win.attach(t);
	win.wait_for_button();
	return 0;
} catch (exception& e){
	cerr << e.what() << endl;
	return 1;
} catch (...){
	cerr << "Something went wrong!" << endl;
	return 2;
}