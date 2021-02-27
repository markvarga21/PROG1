#include <png++/png.hpp>
#include <iostream>
#include<complex>
#include<exception>

// g++ mandelbrot-set.cpp `libpng-config --cflags` -o mandel -lpng

using namespace std;
using namespace png;

constexpr float width = 600;
constexpr float height = 600;

int value (int x, int y){
	constexpr float x_eltolas = 0.8;
	constexpr float y_eltolas = 0.5;
	constexpr float scale = 2.5;
	constexpr float intensity = 25; //minnel kisebb annal intenzivebb

	complex<float> point(((float)x/width-x_eltolas)*scale, ((float)y/height-y_eltolas)*scale); //azert kell osztani hogy a szam [0, 1] intervallumban legyen
	
	complex<float> z(0, 0);
		unsigned int nb_iter = 0; //ez azt jelenti hogy hanyszor/mennyire nezi meg ezt
		while (abs(z) < 2 && nb_iter <= 50){ //akkor lep ki a while-bol ha az adott komplex szam kilep a 2 sugaru korbol, vagy miutan megnezte mindd a 34 iteraciot
			z = z * z + point;
			nb_iter++;
		}
		if (nb_iter < 50) return (255*nb_iter)/intensity; // szin visszateritese
		else return 0; //minnel kesobb lep ki az iteratiobol annal sotetebb
		// minnel kisebb az iteracio, akkor mivel annyival kevesebbet nez meg, ellenoriz le, ezert tobb resz lesz fekete(feketes piros) szinu
}


int main()
try {
    image<rgb_pixel> image(width, height); //kep inicializalasa

    for (int x = 0; x < image.get_width(); ++x) //vegig megy a kepernyo osszes pixelen/koordinatajan
    	for (int y = 0; y < image.get_height(); ++y) //vegig megy a kepernyo osszes pixelen/koordinatajan
    	{
    		int val = value(x, y); //szinertek kiszmaolasa
    		image[y][x] = rgb_pixel(val, 0, 0); //itt azert van megforditva az x es az y hogy horizontalis legyen a megjelenites
    	}

    image.write("mandelbrot_render.png"); //kep ,,kiirasa,,
    
    return 0;
}catch (exception& e){
	cerr << e.what() << endl;
	return 1;
} catch (...){
	cerr << "Something went wrong!" << endl;
	return 2;
}