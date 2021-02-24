#include "Simple_window.h"
#include "Graph.h"

int main(){
	int max_width = 600;
	int max_height = 400;

	Simple_window win{Point{100, 100}, max_width, max_height, "Graphics classes"};

	Line l (Point{200,200}, Point{300,300});

	Lines lines = {
		Point{100, 100}, Point{200, 100}, Point{150, 50}, Point{150, 150}
	};

	lines.add(Point{400,300}, Point{450, 250});

	lines.set_color(Color::red);

	win.attach(lines);

	win.wait_for_button();
	return 0;
}