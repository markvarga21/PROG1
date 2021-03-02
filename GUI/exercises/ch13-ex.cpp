/*
    g++ drill13.cpp ../source/Graph.cpp ../source/Window.cpp ../source/GUI.cpp ../source/Simple_window.cpp -o drill13 `fltk-config --ldflags --use-images`
*/
#include "../source/Simple_window.h"
#include "../source/Graph.h"
#include<exception>
#include "../source/std_lib_facilities.h"

int main()
try {
    using namespace Graph_lib;

    Point tl{100,100};

    Simple_window win{Point{100, 100}, 600, 400, "Arcos"};

    Arc arc{tl, 50, 0, 90};

    Round_box boxx{Point{200,200}, 300, 100, 15};
    //Mark m1{Point{100, 100}, 'x'};

    Arrow arr{Point{100, 100}, Point{200, 200}, false, true, 10};

    //win.attach(m1);
    win.attach(arr);
    win.attach(arc);
    win.attach(boxx);
    win.wait_for_button();
    return 0;
} catch (exception& e){
    cerr << e.what() << endl;
    return 1;
} catch (...){
    cerr << "Something went wrong!" << endl;
    return 2;
}
