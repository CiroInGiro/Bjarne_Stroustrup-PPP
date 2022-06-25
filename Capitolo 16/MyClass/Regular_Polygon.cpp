#include "Regular_Polygon.h"

Graph_lib::Regular_Polygon::Regular_Polygon(Point centro, int R, int num_lati) {
	this->_centro = new Point{ centro.x,centro.y };
	_R = R;
	_lati = num_lati;
	const double pi = 3.14159265;
	const double step = 360 / _lati;
	double gradi{ 0.0 };
	for (int num_angolo = 1; num_angolo <= _lati; ++num_angolo) {
		double rad = gradi * pi / 180;
		double x = _centro->x + _R * cos(rad);
		double y = _centro->y - _R * sin(rad);
		add(Point{ (int)x, (int)y });
		gradi += step;
	}
}

void Graph_lib::Regular_Polygon::draw_lines() const {
	if (color().visibility()) {
		fl_color(color().as_int());
		for (int num_lato = 1; num_lato < number_of_points(); ++num_lato) {
			int x1 = point((num_lato - 1)).x;
			int y1 = point((num_lato - 1)).y;
			int x2 = point(num_lato).x;
			int y2 = point(num_lato).y;
			fl_line(x1, y1, x2, y2);
		}
		int x1 = point((number_of_points() - 1)).x;
		int y1 = point((number_of_points() - 1)).y;
		int x2 = point(0).x;
		int y2 = point(0).y;
		fl_line(x1, y1, x2, y2);
	}
}