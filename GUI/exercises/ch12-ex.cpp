#include "../source/Simple_window.h"
#include "../source/Graph.h"

int main()
try {
	using namespace Graph_lib;

	const int w_width = 1280;
	const int w_height = 720;
	Simple_window win{Point{100,100}, w_width, w_height, "Exercises from chapter 12"};

	// 1.
	const int rect_w = 60;
	const int rect_h = 30;
	Rectangle rect{Point{50, 200}, rect_w, rect_h};
	rect.set_color(Color::blue);

	Polygon poly_rect;
	poly_rect.add(Point{100, 50});
    poly_rect.add(Point{200, 50});
    poly_rect.add(Point{200, 100});
    poly_rect.add(Point{100, 100});
	poly_rect.set_color(Color::red);
	// end of 1.

	// 2.
	Rectangle rect2{Point{200, 200}, 100, 30};
	Text t2{Point{220, 218}, "Howdy!"};
	// end of 2.

	// 3.
	Text initV{Point{50, w_height-150}, "V"};
	Text initM{Point{75, w_height-150}, "M"};
	initV.set_color(Color::blue);
	initV.set_font(Font::times_bold);
	initV.set_font_size(30);

	initM.set_color(Color::green);
	initV.set_font(Font::times_bold);	
	initM.set_font_size(30);
	//end of 3.

	// 4.
	const int sq_w = 50;
	const int tic_x = 200;
	const int tic_y = 450;
	//1st row
	Rectangle sq1{Point{tic_x, tic_y}, sq_w, sq_w};
	sq1.set_fill_color(Color::red);

	Rectangle sq2{Point{tic_x + sq_w, tic_y}, sq_w, sq_w};
	sq2.set_fill_color(Color::white);

	Rectangle sq3{Point{tic_x + (2 * sq_w), tic_y}, sq_w, sq_w};
	sq3.set_fill_color(Color::red);

	//2nd row
	Rectangle sq4{Point{tic_x, tic_y + sq_w}, sq_w, sq_w};
	sq4.set_fill_color(Color::white);

	Rectangle sq5{Point{tic_x + sq_w, tic_y + sq_w}, sq_w, sq_w};
	sq5.set_fill_color(Color::red);

	Rectangle sq6{Point{tic_x + (2 * sq_w), tic_y + sq_w}, sq_w, sq_w};
	sq6.set_fill_color(Color::white);

	//3rd row
	Rectangle sq7{Point{tic_x, tic_y + (2 * sq_w)}, sq_w, sq_w};
	sq7.set_fill_color(Color::red);

	Rectangle sq8{Point{tic_x + sq_w, tic_y + (2 * sq_w)}, sq_w, sq_w};
	sq8.set_fill_color(Color::white);

	Rectangle sq9{Point{tic_x + (2 * sq_w), tic_y + (2 * sq_w)}, sq_w, sq_w};
	sq9.set_fill_color(Color::red);
	// end of 4.

	// 5.
	// 1 in = 72 pt
	Rectangle rect3{Point{420, 50}, (2 * w_width)/3, (3 * w_height)/4};
	rect3.set_style(Line_style(Line_style::solid, 0.25*72));
	//end of 5.

	// 7. 
	Rectangle hs_base{Point{700, 250}, 200, 300};
	
	Polygon hs_roof;
	hs_roof.add(Point{700, 250});
	hs_roof.add(Point{900, 250});
	hs_roof.add(Point{800, 100});

	Polygon chimney;
	chimney.add(Point{850, 175});
	chimney.add(Point{875, 213});
	chimney.add(Point{880, 138});
	chimney.add(Point{850, 138});

	Rectangle door{Point{770, 370}, 100, 180};

	Rectangle window{Point{720, 270}, 150, 75};

	Lines l{Point{795, 270}, Point{795, 345}};
	
	// end of 7.

	// 8.
	Circle c1{Point{100, 300}, 50};
	Circle c2{Point{150, 350}, 50};
	Circle c3{Point{220, 300}, 50};
	Circle c4{Point{270, 350}, 50};
	Circle c5{Point{340, 300}, 50};

	const int cicrcle_w = 8;
	c1.set_style(Line_style(Line_style::solid, cicrcle_w));
	c1.set_color(Color::blue);

	c2.set_style(Line_style(Line_style::solid, cicrcle_w));
	c2.set_color(Color::yellow);

	c3.set_style(Line_style(Line_style::solid, cicrcle_w));
	c3.set_color(Color::black);

	c4.set_style(Line_style(Line_style::solid, cicrcle_w));
	c4.set_color(Color::green);

	c5.set_style(Line_style(Line_style::solid, cicrcle_w));
	c5.set_color(Color::red);
	// end of 8.


	win.attach(rect); win.attach(poly_rect); //1
	win.attach(rect2); win.attach(t2); //2
	win.attach(initV); win.attach(initM); //3
	win.attach(sq1); win.attach(sq2); win.attach(sq3); win.attach(sq4); win.attach(sq5); win.attach(sq6); win.attach(sq7); win.attach(sq8); win.attach(sq9); //4
	win.attach(rect3); //5
	//6-os kulon fajlokban, ex12-6a.cpp es ex12-6b.cpp neven
	win.attach(hs_base); win.attach(hs_roof); win.attach(chimney); win.attach(door); win.attach(window); win.attach(l);//7
	win.attach(c1); win.attach(c2); win.attach(c3); win.attach(c4); win.attach(c5); //8
	//9-es kulon fajlban, ch12-ex9.cpp neven

	win.wait_for_button();
	return 0;
} catch (exception& e){
	cerr << e.what() << endl;
	return 1;
} catch (...){
	cerr << "Something went wrong!" << endl;
	return 2;
}
