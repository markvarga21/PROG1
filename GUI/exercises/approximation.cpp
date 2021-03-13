/*
    g++ approximation.cpp ../source/Graph.cpp ../source/Window.cpp ../source/GUI.cpp ../source/Simple_window.cpp -o approx `fltk-config --ldflags --use-images`
*/
#include "../source/Simple_window.h"
#include "../source/Graph.h"
#include "../source/std_lib_facilities.h"

int NN = 10;

double fac(int n)
{
    int r = 1;
    while (n > 1)
    {
        r *= n;
        n--;
    }
    return r;
}

double term(double x, int n) { return pow(x,n)/fac(n); }

double exp_f(double x, int n)
{
    double sum = 0;
    for (int i = 0; i < n; ++i) sum += term(x, i);
    return sum;
}

double expN(double x)
{
    return exp_f(x, NN);
}

int main()
try {
    using namespace Graph_lib;

    constexpr int sc_width = 400;
    constexpr int sc_heigth = 400;
    Simple_window win{Point{50, 50}, sc_width, sc_heigth, "Approximation"};

    const int notch = 20;
    Axis ax{Axis::x, Point{10, sc_heigth/2}, sc_width-20, notch};
    Axis ay{Axis::y, Point{sc_width/2, sc_heigth-10}, sc_heigth-20, notch};

    Point orig{200, 200};
    const int nrOfPoints = 200;
    const double r_min = -5;
    const double r_max = 5;
    const double x_scale = 10;
    const double y_scale = 10;
    Function real_exp{exp, r_min, r_max, orig, nrOfPoints, x_scale, y_scale};
    real_exp.set_color(Color::red);

    win.attach(ax); win.attach(ay);
    win.attach(real_exp);

    for (int n = 0; n < 20; ++n)
    {
        NN = n;
        Function e{expN, r_min, r_max, orig, nrOfPoints, x_scale, y_scale};
        win.attach(e);
        win.wait_for_button();
        win.detach(e);
    }
    return 0;
} catch (exception& e){
    cerr << e.what() << endl;
    return 1;
} catch (...){
    cerr << "Something went wrong!" << endl;
    return 2;
}
