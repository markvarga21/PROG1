#include "../source/Lines_window.h"
#include "../source/Graph.h"
#include "../source/std_lib_facilities.h"

/*
g++ drill16.cpp ../source/Graph.cpp ../source/Window.cpp ../source/GUI.cpp ../source/Simple_window.cpp ../source/Lines_window.cpp -o drill16 `fltk-config --ldflags --use-images`
*/

int main()
try {

	Lines_window win{Point{100, 100}, 1280, 720, "Lines"};
	
	return gui_main();
} catch (exception& e){
	cerr << e.what() << endl;
	return 1;
} catch (...){
	cerr << "Something went wrong!" << endl;
	return 2;
}