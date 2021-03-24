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

    // 1. feladat
    const int width = 1000;
    const int heigth = 800;
    Simple_window win{Point{10,10}, width, heigth, "Drill 13 window"};   
    // 1. feladat vege

    // 2. feladat
    const int x_size = win.x_max();  
    const int y_size = win.y_max();
    const int grid_x = 100;
    const int grid_y = 100;
    Lines grid;
    //--------------------- GRID -------------------
    //vertical
    for (int i = 0; i <= heigth; i+=grid_x)
        grid.add(Point{i,0}, Point{i, heigth});
    //horizontal
    for (int i = 0; i <= heigth; i+=grid_x)
        grid.add(Point{0,i}, Point{heigth, i});
    // 2. feladat vege

    // 3. feladat
    //Nevtelen objektumok segitsegevel letrehozott grid kitoltes
    Vector_ref<Rectangle> rect;
    for (int i = 0; i < 8; ++i){
        rect.push_back(new Rectangle({i*grid_x, i*grid_y}, grid_x, grid_y));
        rect[i].set_fill_color(Color::red);
        rect[i].set_color(Color::invisible);
        win.attach(rect[i]);
    }
    // 3. feladat vege
    
    // 4. feladat
    Image i1{Point{0, 200}, "kep200.jpg"};
    Image i2{Point{200, 400}, "kep200.jpg"};
    Image i3{Point{400,200}, "kep200.jpg"};
    // 4. feladat vege

    win.attach(grid); //2
    win.attach(i1); win.attach(i2); win.attach(i3); //4

    //5. feladat
    Image kicsikep{Point{0, 0}, "100as.jpg"};
    win.attach(kicsikep);

    int cnt = 1;
    while (cnt < 64){
        win.wait_for_button();
        if (cnt % 8 == 0) kicsikep.move(-800, 100);   
        kicsikep.move(100, 0);
        cnt++;
    }
    //5. feladat vege

    return 0;
} catch (exception& e){
    cerr << e.what() << endl;
    return 1;
} catch (...){
    cerr << "Something went wrong!" << endl;
    return 2;
}
