#include "Box.h"

Graph_lib::Box::Box(Point xy, int w, int h) : _w{ w }, _h{ h } {
	add(xy);
}

void Graph_lib::Box::draw_border(const Point& xy, const int& w, const int& h) const {
	int d, r, x, y, x2, y2;
	if (w > h) d = h / 10;
	else d = w / 10;
	if (d < 2) d = 2;
	r = d / 2;
	x = xy.x;
	y = xy.y;
	fl_arc(x, y, d, d, 90, 180);
	// lato sinistro
	y = (xy.y + r);
	x2 = x;
	y2 = xy.y + h - r;
	fl_line(x, y, x2, y2);
	// angolo inferiore sinistro
	y = xy.y + h - d;
	fl_arc(x, y, d, d, 180, 270);
	// lato inferiore
	x = xy.x + r;
	y = xy.y + h;
	x2 = xy.x + w - r;
	y2 = y;
	fl_line(x, y, x2, y2);
	// angolo destro inferiore
	x = xy.x + w - d;
	y = y2 - d;
	fl_arc(x, y, d, d, 270, 360);
	// lato destro
	x = xy.x + w;
	y = xy.y + h - r;
	x2 = x;
	y2 = xy.y + r;
	fl_line(x, y, x2, y2);
	// angolo superiore destro
	x = xy.x + w - d;
	y = xy.y;
	fl_arc(x, y, d, d, 0, 90);
	// lato superiore
	x = xy.x + w - r;
	x2 = xy.x + r;
	y2 = y;
	fl_line(x, y, x2, y2);
}

void Graph_lib::Box::draw_lines() const {
	if (color().visibility()) {
		fl_color(color().as_int());
		draw_border(point(0), _w, _h);
	}
	if (fill_color().visibility()) {
		fl_color(fill_color().as_int());
		// riempo gli angoli
		int d, r, x, y, x2, y2;
		int spessore_bordo = style().width() / 2;
		if (spessore_bordo < 1) spessore_bordo = 1;
		x = point(0).x + spessore_bordo;
		y = point(0).y + spessore_bordo;
		if (_w > _h) d = _h / 10;
		else d = _w / 10;
		r = d / 2;
		fl_pie(x, y, d, d, 0, 360);
		x = point(0).x + spessore_bordo;
		y = point(0).y + _h - d - spessore_bordo;
		fl_pie(x, y, d, d, 0, 360);
		x = point(0).x + _w - d - spessore_bordo;
		y = point(0).y + _h - d - spessore_bordo;
		fl_pie(x, y, d, d, 0, 360);
		x = point(0).x + _w - d - spessore_bordo;
		y = point(0).y + spessore_bordo;
		fl_pie(x, y, d, d, 0, 360);
		x = point(0).x + r + spessore_bordo;
		x2 = point(0).x + _w - r - spessore_bordo;
		// striscione verticale
		for (int righe = (point(0).y + spessore_bordo); righe < (point(0).y + _h - spessore_bordo); ++righe) {
			fl_line(x, righe, x2, righe);
		}
		// striscione orizzontale
		y = point(0).y + r + spessore_bordo;
		y2 = point(0).y + _h - r - spessore_bordo;
		for (int colonne = (point(0).x + spessore_bordo); colonne < (point(0).x + _w - spessore_bordo); ++colonne) {
			fl_line(colonne, y, colonne, y2);
		}
	}
}

void Graph_lib::Box::set_width(int width) {
	if (width > 0) _w = width;
	move(0, 0);
}

void Graph_lib::Box::set_height(int height) {
	if (height > 0) _h = height;
	move(0, 0);
}

void Graph_lib::Box::set_color(Graph_lib::Color c) {
	Shape::set_color(c);
}