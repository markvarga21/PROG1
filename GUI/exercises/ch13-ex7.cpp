/*
    g++ ch13-ex.cpp ../source/Graph.cpp ../source/Window.cpp ../source/GUI.cpp ../source/Simple_window.cpp -o ch13-ex `fltk-config --ldflags --use-images`
*/
#include "../source/Simple_window.h"
#include "../source/Graph.h"
#include<exception>
#include "../source/std_lib_facilities.h"

int main()
try {
    using namespace Graph_lib;

    Simple_window win{Point{100, 100}, 720, 400, "ch13-ex7"};
    Vector_ref<Rectangle> rect;
    const int cell_size = 15;

    for (int i = 0; i < 6; ++i)
    for (int j = 0; j < 6; ++j)
    for (int k = 0; k < 6; ++k){
        rect.push_back(new Rectangle{Point{i*6*cell_size + j*cell_size, k*cell_size}, cell_size, cell_size});
        rect[rect.size()-1].set_fill_color(fl_rgb_color(51*i, 51*j, 51*k));
        win.attach(rect[rect.size()-1]);
    }


    win.wait_for_button();
    return 0;
} catch (exception& e){
    cerr << e.what() << endl;
    return 1;
} catch (...){
    cerr << "Something went wrong!" << endl;
    return 2;
}
