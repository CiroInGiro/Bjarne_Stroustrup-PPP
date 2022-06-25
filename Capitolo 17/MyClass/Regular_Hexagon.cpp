#include "Regular_Hexagon.h"

Graph_lib::Regular_Hexagon::Regular_Hexagon(Point centro, int R) : _R{ R }, _x{ centro.x }, _y{ centro.y } {
	const double pi = 3.14159265;
	const int step = 360 / 6;
	int gradi{ 0 };
	for (int num_angolo = 1; num_angolo <= 6; ++num_angolo) {
		double rad_angolo = gradi * pi / 180;
		int x = centro.x + R * cos(rad_angolo);
		int y = centro.y - R * sin(rad_angolo);
		add(Point{ x, y });
		gradi += step;
	}
}

void Graph_lib::Regular_Hexagon::draw_lines() const {
	if (color().visibility()) {
		for (unsigned int indice = 1; indice < number_of_points(); ++indice) {
			fl_color(color().as_int());
			int x1 = point((indice - 1)).x;
			int y1 = point((indice - 1)).y;
			int x2 = point(indice).x;
			int y2 = point(indice).y;
			fl_line(x1, y1, x2, y2);
		}
		fl_line(point(0).x, point(0).y, point((number_of_points() - 1)).x, point((number_of_points() - 1)).y);
	}
}