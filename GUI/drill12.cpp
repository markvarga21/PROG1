/*
    g++ main.cpp Graph.cpp Window.cpp GUI.cpp Simple_window.cpp -o main `fltk-config --ldflags --use-images`
*/
#include "Simple_window.h"
#include "Graph.h"
#include<math.h>

double sq(double x) { return x*x; }

class Negative_number{};

int main()
try {
    using namespace Graph_lib;
    
    const int w_width = 600;
    const int w_lenght = 400;

    const int ax_lenght = 300;
    const int notch = 20;

    //window felrajzolasa/megjelenitese
    Simple_window win {Point{100, 100}, w_width, w_lenght, "My window"};

    // tengelyek
    Axis xa {Axis::x, Point{20,350}, ax_lenght, notch, "X"};
    Axis ya {Axis::y, Point{20,350}, ax_lenght, notch, "Y"};
    xa.set_color(Color::blue);
    xa.label.set_color(Color::black);
    ya.set_color(Color::blue);
    ya.label.set_color(Color::black);
    // Origo szoveg
    Text t {Point{7, 365}, "0"};

    // haromszog poligon
    Polygon poly;
    poly.add(Point{100, 300});
    poly.add(Point{150, 200});
    poly.add(Point{200, 300});
    poly.set_color(Color::red);
    poly.set_style(Line_style(Line_style::dash, 5));

    // fuggvenyek
    const int l_interval = 0;
    const int r_interval = 5 * M_PI;
    const int smoothness = 8000;
    const int sin_scale_x = 20;
    const int sin_scale_y = 20;
    Function sine(sin, l_interval, r_interval, Point{20, 150}, smoothness, sin_scale_x, sin_scale_y);
    sine.set_color(Color::yellow);

    // rectangle
    const int rect_width = 100;
    const int rect_heigh = 50;
    Rectangle rect{Point{200, 200}, rect_width, rect_heigh};
    rect.set_fill_color(Color::cyan);

    // closed poly
    Closed_polyline poly_rect;
    poly_rect.add(Point{100, 50});
    poly_rect.add(Point{200, 50});
    poly_rect.add(Point{200, 100});
    poly_rect.add(Point{100, 100});
    poly_rect.add(Point{50, 75});
    poly_rect.set_color(Color::dark_cyan);
    poly_rect.set_style(Line_style(Line_style::dash, 2));
    poly_rect.set_fill_color(Color::green);

    // text 
    const int font_size = 20;
    Text txt{Point{70, 25}, "Hello graphical world!"};
    txt.set_font(Font::times_bold);
    txt.set_font_size(font_size);

    // kep
    Image img{Point{100, 50}, "pepe.jpg"};
    // img.move(10, 10); miert nem megy?

    // kor
    const int crl_rad = 50;
    const int crl_line_width = 3;
    Circle crl{Point{520, 200}, crl_rad};
    crl.set_style(Line_style(Line_style::dot, crl_line_width));
    crl.set_fill_color(Color::dark_cyan);

    // markok
    Mark m{Point{520, 200}, 'x'};

    // sizes
    ostringstream oss;
    oss << "screen size: " << x_max() << "x" << y_max()
        << "; window size: " << win.x_max() << "x" << win.y_max() << ";";
    Text sizes{Point{250, 48}, oss.str()};

    // x^2 fuggveny kirajzolasa
    Point origo{20, 350};
    const int range_min = 0;
    const int range_max = 8;
    const int sq_scl_x = 10;
    const int sq_scl_y = 10;
    Function xnegyzet{sq, range_min, range_max, origo, smoothness, sq_scl_x, sq_scl_y};
    xnegyzet.set_color(Color::dark_red);

    // gyok x fuggveny
    const int rng_min = 0;
    const int rng_max = 25;
    Function gyokx{ [] (double x) { if (x < 0) throw Negative_number{}; return sqrt(x); }, rng_min, rng_max, origo, smoothness, sq_scl_x, sq_scl_y };
    gyokx.set_style(Line_style::dashdot);

    // attach-ek
    win.attach(img);
    win.attach(xa); win.attach(ya); win.attach(t);
    win.attach(poly);
    win.attach(sine);
    win.attach(rect);
    win.attach(poly_rect);
    win.attach(txt);
    win.attach(crl);
    win.attach(m);
    win.attach(sizes);
    win.attach(xnegyzet);
    win.attach(gyokx);

    win.wait_for_button();
    return 0;

// hibakezeles
} catch (Negative_number){
    cerr << "Gyok alatt nem lehet negativ!" << endl;
    return 1;
} catch (exception& e){
    cerr << e.what() << endl;
    return 2;
} catch (...){
    cerr << "Something went wrong!" << endl;
    return 3;
}
