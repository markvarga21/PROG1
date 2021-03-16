#include "Lines_window.h"

Lines_window::Lines_window(Point xy, int w, int h, const string& title)
	:Window{xy, w, h, title},
	next_button{Point{x_max()-300, 0}, 150, 40, "Next point",
		[](Address, Address pw) { reference_to<Lines_window>(pw).next(); }}, //callback-ek megadasa lambdaval
	quit_button{Point{x_max()-150, 0}, 150, 40, "Quit",
		[](Address, Address pw) { reference_to<Lines_window>(pw).quit(); }}, //callback-ek megadasa lambdaval
	next_x{Point{300, 0}, 50, 40, "next x:"},
	next_y{Point{450, 0}, 50, 40, "next y:"},
	xy_out{Point{100, 0}, 100, 40, "Current (x,y):"},
	color_menu{Point{x_max()-150, 40}, 150, 40, Menu::vertical, "color"},
	menu_button{Point{x_max()-150, 40}, 150, 40, "color menu", cb_menu},
	line_style_menu{Point{x_max()-300, 40}, 150, 40, Menu::vertical, "line style"},
	line_style_menu_button{Point{x_max()-300, 40}, 150, 40, "style_menu", cb_line_style_menu}
{
	//Next+Quit attacholasa
	attach(next_button);
	attach(quit_button);
	//In/Out boxok attacholasa
	attach(next_x);
	attach(next_y);
	attach(xy_out);


	//Menu attaches
	//Color menu
	color_menu.attach(new Button{Point{0, 0}, 0, 0, "red", cb_red});
	color_menu.attach(new Button{Point{0, 0}, 0, 0, "blue", cb_blue});
	color_menu.attach(new Button{Point{0, 0}, 0, 0, "black", cb_black});
	//Line style attach
	line_style_menu.attach(new Button{Point{0,0},0,0,"solid", cb_solid});
	line_style_menu.attach(new Button{Point{0,0},0,0,"dash", cb_dash});
	line_style_menu.attach(new Button{Point{0,0},0,0,"dot", cb_dot});
	//Masik ket fo menu attacholasa
	attach(color_menu);
	attach(line_style_menu);

	color_menu.hide(); //alapvetoen hideolva vannak a menuk, csak a buttonok latszodnak
	line_style_menu.hide(); //alapvetoen hideolva vannak a menuk, csak a buttonok latszodnak

	//Gombok felrakasa, menu es line style
	attach(menu_button);
	attach(line_style_menu_button);
	//open poly vonaljainak felrakasa
	attach(lines);
}	

void Lines_window::quit()
{
	hide(); //a kilepes megfeleloje az FLTK-ban
}

void Lines_window::next()
{
	// A  next rubrikak, IN boxok tartalma, a get_int() tagfuggvennyel elkerve
	int x = next_x.get_int();
	int y = next_y.get_int();

	//Pont hozzaadasa az open polihoz
	lines.add(Point{x,y});

	//kiiras outputra
	ostringstream ss;
	ss << '(' << x << ',' << y << ')';
	xy_out.put(ss.str()); //rendes stringge alakitas, convertion

	//ablak ujrarajzolasa
	redraw();
}

//milyen action(ok) hivodjon/triggerelodjon a gomb(ok) megnyomasakor
void Lines_window::cb_red(Address, Address pw)
{
	reference_to<Lines_window>(pw).red_pressed(); 
}

void Lines_window::cb_blue(Address, Address pw)
{
	reference_to<Lines_window>(pw).blue_pressed();
}

void Lines_window::cb_black(Address, Address pw)
{
	reference_to<Lines_window>(pw).black_pressed();
}

void Lines_window::cb_menu(Address, Address pw)
{
	reference_to<Lines_window>(pw).menu_pressed();
}

void Lines_window::cb_solid(Address, Address pw)
{
	reference_to<Lines_window>(pw).solid_pressed();
}

void Lines_window::cb_dash(Address, Address pw)
{
	reference_to<Lines_window>(pw).dash_pressed();
}

void Lines_window::cb_dot(Address, Address pw)
{
	reference_to<Lines_window>(pw).dotted_pressed();
}

void Lines_window::cb_line_style_menu(Address, Address pw)
{
	reference_to<Lines_window>(pw).line_style_menu_pressed();
}