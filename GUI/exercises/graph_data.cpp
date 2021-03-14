/*
    g++ graph_data.cpp ../source/Graph.cpp ../source/Window.cpp ../source/GUI.cpp ../source/Simple_window.cpp -o graph `fltk-config --ldflags --use-images`
*/
#include "../source/Simple_window.h"
#include "../source/Graph.h"
#include "../source/std_lib_facilities.h"

class Scale
{
    int cbase;
    int vbase;
    double scale;
public:
    Scale(int b, int vb, double s) : cbase(b), vbase(vb), scale(s) {}
    int operator()(int v) const { return cbase + (v-vbase)*scale; }
};  

struct Distribution
{
    int year, young, middle, old;
};

istream& operator>>(istream& is, Distribution& d)
{
    char c1 = 0;
    char c2 = 0;
    char c3 = 0;
    Distribution dd;

    if (is >> c1 >> dd.year >> c2 >> dd.young >> dd.middle >> dd.old >> c3)
    {
        if (c1 != '(' || c2 != ':' || c3 != ')') { is.clear(ios_base::failbit); return is; }
    }
    else {
        return is;
    }
    d = dd;
    return is;
}

int main()
try {
    using namespace Graph_lib;

    constexpr int xmax = 600;
    constexpr int ymax = 400;

    constexpr int xoffset = 100;
    constexpr int yoffset = 60;

    constexpr int xspace = 40;
    constexpr int yspace = 40;

    constexpr int xlength = xmax-xoffset-xspace;
    constexpr int ylength = ymax-yoffset-yspace;

    constexpr int base_year = 1960;
    constexpr int end_year = 2040;

    constexpr double xscale = double(xlength)/(end_year-base_year);
    constexpr double yscale = double(ylength)/100;      

    Scale xs{xoffset, base_year, xscale};
    Scale ys{ymax-yoffset, 0, -yscale};

    Simple_window win {Point{100, 100}, xmax, ymax, "Aging Japan"};

    Axis x{Axis::x, Point{xoffset, ymax-yoffset}, xlength, (end_year-base_year)/10, 
        "year   1960    1970    1980    1990    "
        "2000   2010    2020    2030    2040"};
    x.label.move(-100, 0);

    Axis y{Axis::y, Point{xoffset, ymax-yoffset}, ylength, 10, "perc. of population"};

    Line current_year{Point{xs(2021), ys(0)}, Point{xs(2021), ys(100)}};
    current_year.set_style(Line_style::dash);

    Open_polyline children;
    Open_polyline adults;
    Open_polyline aged;

    string file_name = "age_date.txt";
    ifstream ifs(file_name);
    if (!ifs) error("Cant open file!");

    for (Distribution d; ifs >> d; )
    {
        if (d.year < base_year || end_year < d.year) error("Year out of range!");
        if (d.young+d.middle+d.old != 100) error("Percentages do not add up!");

        const int x = xs(d.year);
        children.add(Point{x, ys(d.young)});
        adults.add(Point{x, ys(d.middle)});
        aged.add(Point{x, ys(d.old)});
    }

    Text children_label{Point{20, children.point(0).y}, "Age 0-14"};
    children.set_color(Color::red);
    children_label.set_color(Color::red);

    Text adults_label{Point{20, adults.point(0).y}, "Age 15-64"};
    adults.set_color(Color::blue);
    adults_label.set_color(Color::blue);

    Text aged_label{Point{20, aged.point(0).y}, "Age 65+"};
    aged.set_color(Color::dark_green);
    aged_label.set_color(Color::dark_green);

    win.attach(children);
    win.attach(adults);
    win.attach(aged);

    win.attach(children_label);
    win.attach(adults_label);
    win.attach(aged_label);

    win.attach(x);
    win.attach(y);

    win.attach(current_year);

    win.wait_for_button();
    return 0;
} catch (exception& e){
    cerr << e.what() << endl;
    return 1;
} catch (...){
    cerr << "Something went wrong!" << endl;
    return 2;
}
