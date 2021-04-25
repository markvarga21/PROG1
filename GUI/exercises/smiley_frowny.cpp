#include "../source/Simple_window.h"
#include "../source/Graph.h"

int main()
{
	Simple_window win{Point{50, 50}, 600, 600, "Binary tree"};

	Smiley sm {Point{200, 200}, 50};
	Smiley_hat sm_h {Point{100, 100}, 50};
	sm.set_color(Color::blue);

	Frowny fr {Point{300,300}, 70};
	Frowny_hat fr_h {Point{450,450}, 70};

	win.attach(sm); win.attach(sm_h);
	win.attach(fr); win.attach(fr_h); 
	win.wait_for_button();
	return 0;
}