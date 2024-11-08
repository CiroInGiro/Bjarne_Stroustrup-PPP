#include "TriangoloRettangolo.h"
#include <math.h>

Graph_lib::TriangoloRettangolo::TriangoloRettangolo(Point vertice, double base, double altezza, int angolo) {
	if (base == 0) error("Base del triangolo rettangolo mancante");
	_base = base;

	if (altezza == 0) error("Altezza del triangolo rettangolo mancante");
	_altezza = altezza;

	if (angolo > 360 || angolo < -360) _angolo = angolo % 360;
	else _angolo = angolo;

	x_vertice = vertice.x;
	y_vertice = vertice.y;

	// il vertice corrisponde al fulcro di rotazione
	add(vertice);
	// ruota sul vertice, il punto p0
	double newx, newy; // nuova posizione del punto
	const double pi = 3.14159265; // costante pi greco
	double rad; // gradi in radianti
	rad = _angolo * pi / 180;
	// partiamo dal triancolo coricato perché a 0° corrispondente a destra sullo schermo
	double x = x_vertice + _altezza; 
	double y = y_vertice;
	newx = (x - x_vertice) * cos(rad) - (y - y_vertice) * sin(rad);
	newy = (x - x_vertice) * sin(rad) + (y - y_vertice) * cos(rad);
	add(Point{ (int)(newx + point(0).x), (int)(-newy + point(0).y) });
	x = x_vertice + _altezza;
	y = y_vertice + _base;
	newx = (x - x_vertice) * cos(rad) - (y - y_vertice) * sin(rad);
	newy = (x - x_vertice) * sin(rad) + (y - y_vertice) * cos(rad);
	add(Point{ (int)(newx + point(0).x), (int)(-newy + point(0).y) });
}

void Graph_lib::TriangoloRettangolo::draw_lines() const {
	if (color().visibility()) {
		fl_color(color().as_int());
		fl_line(point(0).x, point(0).y, point(1).x, point(1).y);
		fl_line(point(1).x, point(1).y, point(2).x, point(2).y);
		fl_line(point(2).x, point(2).y, point(0).x, point(0).y);
	}
}