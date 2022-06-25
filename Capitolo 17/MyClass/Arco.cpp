#include "Arco.h"

Graph_lib::Arco::Arco(Point xy, int w, int h, double a1, double a2) : _w{ w }, _h{ h } {
	_start = a1;
	_end = a2;
	if (a1 < 0) _start = 0;
	if (a2 < 0) _end = 0;
	if (a1 > 360) _start = (int)a1 % 360;
	if (a2 > 360) _end = (int)a2 % 360;
	if (_start > _end) {
		double temp = _start;
		_start = _end;
		_end = temp;
	}
	Point spigolo{ (xy.x - w), (xy.y - h) };
	add(spigolo);
}

void Graph_lib::Arco::draw_lines() const {
	if (fill_color().visibility()) {
		fl_color(fill_color().as_int());
		fl_pie(point(0).x, point(0).y, (_w + _w), (_h + _h), _start, _end);
	}
	if (color().visibility())
	{
		fl_color(color().as_int());
		fl_arc(point(0).x, point(0).y, (_w + _w), (_h + _h), _start, _end);
	}
}
