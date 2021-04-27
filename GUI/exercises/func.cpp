#include "../source/Simple_window.h"
#include "../source/Graph.h"
#include <exception>

double xnegyzet(double x) { return x*x; }

int main()
try {
	using namespace Graph_lib;

	Simple_window win{Point{100, 100}, 300, 300, "Factorial and my function"};
	
	const int rmin = -10;
	const int rmax = 10;
	Point origin(150, 250);
	const int count = 100;
	const int xscale = 25;
	const int yscale = 25;
	double precision = 1.0;

	My_function<double> MF(xnegyzet, rmin, rmax, origin, count, xscale, yscale, precision);

	int n = 0;
	const int max_n = 50;
	const int leptek = 5;

	while (n < max_n) {
		win.attach(MF);
		win.wait_for_button();
		win.detach(MF);
		MF.reset_precision(precision+n);
		n += leptek;
	}

} catch(exception& e) {
	cerr << e.what() << endl;
	return 1;
} catch (...) {
	cerr << "Something went wrong!" << endl;
	return 2;
}