/*
    g++ drill13.cpp ../source/Graph.cpp ../source/Window.cpp ../source/GUI.cpp ../source/Simple_window.cpp -o drill13 `fltk-config --ldflags --use-images`
*/
#include "../source/Simple_window.h"
#include "../source/Graph.h"
#include "../source/std_lib_facilities.h"

double one(double x) { return 1; }

double slope(double x) { return x/2; }

double square(double x) { return x*x; }

double sloping_cos(double x) { return cos(x)+slope(x); }

int main()
try {
    using namespace Graph_lib;


    //------------------------ Function graphing drill ---------------------------
    //feladat 1
    const int w_width = 600;
    const int w_heigth = 600;

    Simple_window win{Point{100, 100}, w_width, w_heigth, "Function graphs."};
    //1 vege

    //feladat 4
    const int axis_length = 400;
    const int notch = 20;
    const int eltolas = 200;
    Axis ax{Axis::x, Point{300-eltolas, 300}, axis_length, notch, "1 == 20 pixels"};
    Axis ay{Axis::y, Point{300, 300+eltolas}, axis_length, notch};
    //4 vege

    //feladat 5
    ax.set_color(Color::red);
    ay.set_color(Color::red);
    //5 vege1
    //--------------------------------- PART 1 VEGE ----------------------------------

    //----------------------- Fuggvenyes part 2 -----------------------------
    const int lrange = 10;
    const int rrange = 11;
    const int n_points = 400;
    const int x_scale = 20;
    const int y_scale = 20;
    Function egyseg_f{one, lrange, rrange, Point{300, 300}, n_points, x_scale, y_scale};
   
    Function slope_f{slope, lrange, rrange, Point{300, 300}, n_points, x_scale, y_scale};
    Text lab2{Point{475, 200}, "x/2"};

    Function square_f{square, lrange, rrange, Point{300, 300}, n_points, x_scale, y_scale}; //mivel a feladat azt kerte, hogy a range, notch stb. mindegyiknel ugyan azok legyenek, ezert az x^2 fuggveny joval az ablakon kivul van

    //fuggveny megadasa lambda segitsegevel
    Function cos_f{[] (double x) {return cos(x); }, lrange, rrange, Point{300, 300}, n_points, x_scale, y_scale};
    cos_f.set_color(Color::blue);

    Function cos_slope{sloping_cos, lrange, rrange, Point{300, 300}, n_points, x_scale, y_scale};
    //---------------------------------- PART 2 VEGE ----------------------------------------

    win.attach(egyseg_f);
    win.attach(ax); win.attach(ay);
    win.attach(slope_f); win.attach(lab2);
    win.attach(square_f);
    win.attach(cos_f);
    win.attach(cos_slope);
    win.wait_for_button();
    return 0;
} catch (exception& e){
    cerr << e.what() << endl;
    return 1;
} catch (...){
    cerr << "Something went wrong!" << endl;
    return 2;
}
