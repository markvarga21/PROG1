/*
    g++ main.cpp Graph.cpp Window.cpp GUI.cpp Simple_window.cpp -o main `fltk-config --ldflags --use-images`
*/
#include "Simple_window.h"
#include "Graph.h"
#include<exception>
#include "std_lib_facilities.h"

int main()
try {
    using namespace Graph_lib;

    // 1. feladat
    const int width = 800;
    const int heigth = 1000;
    Simple_window win{Point{100,100}, width, heigth, "Drill 13 window"};   
    // 1. feladat vege

    // 2. feladat
    const int x_size = win.x_max();  
    const int y_size = win.y_max();
    const int grid_x = 100;
    const int grid_y = 100;
    Lines grid;
    //vertical
    for (int i = 0; i <= width; i+=grid_x)
        grid.add(Point{i,0}, Point{i, heigth});
    //horizontal
    for (int i = 0; i <= heigth; i+=grid_x)
        grid.add(Point{0,i}, Point{width, i});
    // 2. feladat vege

    //a constot tudjuk valtoztatni pl const int image = valtoz(a);
    // a constexpr ismernunk kell forditasi idoben az erteket

    // 3. feladat
    /*
    Rectangle rect1{Point{0, 0}, grid_x, grid_y};
    rect1.set_fill_color(Color::red);

    Rectangle rect2{Point{grid_x, grid_y}, grid_x, grid_y};
    rect2.set_fill_color(Color::red);

    Rectangle rect3{Point{2*grid_x, 2*grid_y}, grid_x, grid_y};
    rect3.set_fill_color(Color::red);

    Rectangle rect4{Point{3*grid_x, 3*grid_y}, grid_x, grid_y};
    rect4.set_fill_color(Color::red);

    Rectangle rect5{Point{4*grid_x, 4*grid_y}, grid_x, grid_y};
    rect5.set_fill_color(Color::red);

    Rectangle rect6{Point{5*grid_x, 5*grid_y}, grid_x, grid_y};
    rect6.set_fill_color(Color::red);

    Rectangle rect7{Point{6*grid_x, 6*grid_y}, grid_x, grid_y};
    rect7.set_fill_color(Color::red);

    Rectangle rect8{Point{7*grid_x, 7*grid_y}, grid_x, grid_y};
    rect8.set_fill_color(Color::red);
    */
    // 3. feladat vege
    /*
    vector<Rectangle> rect(8);
    for (int i = 0; i <= 8; i++){
        rect[i]{Point{i*grid_x, i*grid_y}, grid_x, grid_y};
        rect[i].set_fill_color(Color::red);
        win.attach(rect[i]);
    }*/

    // 4. feladat
    Image i1{Point{0, 0}, "kep200.jpg"};
    Image i2{Point{200, 200}, "kep200.jpg"};
    Image i3{Point{400,400}, "kep200.jpg"};

    win.attach(i1); win.attach(i2); win.attach(i3); //4
    win.attach(grid); //2
    //win.attach(rect1); win.attach(rect2); win.attach(rect3); win.attach(rect4); win.attach(rect5); win.attach(rect6); win.attach(rect7); win.attach(rect8);//3
    win.wait_for_button();
    return 0;
} catch (exception& e){
    cerr << e.what() << endl;
    return 1;
} catch (...){
    cerr << "Something went wrong!" << endl;
    return 2;
}
