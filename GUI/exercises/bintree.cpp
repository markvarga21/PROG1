#include "../source/Simple_window.h"
#include "../source/Graph.h"

int main()
{
	Simple_window win{Point{50, 50}, 600, 600, "Binary tree"};
	Binary_tree tr{Point{300, 100}, 4, "ad"};
	tr.set_node_label("lrl", "Alma");


	win.attach(tr);
	win.wait_for_button();
	return 0;
}