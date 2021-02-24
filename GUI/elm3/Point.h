#ifndef POINT_GUARD //ez arra szolgal hogy egy headert nem tudjunk tobbszor beincludeolni
#define POINT_GUARD

namespace Graph_lib{

struct Point{
	int x, y;
	Point(): x(0), y(0) {}
	Point(int xx, int yy): x(xx), y(yy) {}
};

inline bool operator==(Point a, Point b) { return a.x==b.x && a.y==b.y; } // inline = ha ezeket hasznaljuk akkor nem fog odaugrani sehova, a fuggvenyhez pl.

inline bool operator!=(Point a, Point b){ return !(a==b); }

}

#endif