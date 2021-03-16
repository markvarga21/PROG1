#include "../source/Lines_window.h"
#include "../source/Graph.h"
#include "../source/std_lib_facilities.h"

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