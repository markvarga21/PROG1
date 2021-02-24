#include "../source/Simple_window.h"
#include "../source/Graph.h"

int main()
try {
	Simple_window win{Point{100, 100}, 2000, 1100, "6b"}; //1366x768-as screenen van leprogramozva, ezert a 2000x1100 biztosan nagyobb lesz es nem fer ki
	
	win.wait_for_button();
	return 0;
} catch (exception& e){
	cerr << e.what() << endl;
	return 1;
} catch (...){
	cerr << "Something went wrong!" << endl;
	return 2;
}
