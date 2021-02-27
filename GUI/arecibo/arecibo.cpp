/*
    g++ arecibo.cpp ../source/Graph.cpp ../source/Window.cpp ../source/GUI.cpp ../source/Simple_window.cpp -o arecibo `fltk-config --ldflags --use-images`
*/
#include "../source/Simple_window.h"
#include "../source/Graph.h"
#include "../source/std_lib_facilities.h"
#include<math.h>

int main()
try {
    using namespace Graph_lib;
    
    constexpr int rsize = 9;
    constexpr int w_width = 23*rsize;
    constexpr int w_heigth = 73*rsize;
    Simple_window win{Point{100,0}, w_width, w_heigth, "Arecibo message"};

    vector<char> c(1679);

    for (int i = 0; i < c.size(); ++i) cin >> c[i];

    Vector_ref<Rectangle> rect;

    int y = 0, x = 0;
    for (int i = 0; i < c.size(); ++i){
        if (c[i] == '1'){ 
            if (i % 23 == 0 && i != 0) { x = 0; y+=rsize; }
            rect.push_back(new Rectangle(Point{x, y}, rsize, rsize));
            rect[i].set_fill_color(Color::white);
            win.attach(rect[i]);
            x+=rsize;
        }
        if (c[i] == '0'){
            if (i % 23 == 0 && i != 0) { x = 0; y+=rsize; } 
            rect.push_back(new Rectangle(Point{x, y}, rsize, rsize));
            rect[i].set_fill_color(Color::black);
            win.attach(rect[i]);
            x+=rsize;
        }
    }

    win.wait_for_button();
    return 0;

// hibakezeles
} catch (exception& e){
    cerr << e.what() << endl;
    return 1;
} catch (...){
    cerr << "Something went wrong!" << endl;
    return 2;
}
