#pragma once

#include "../GUI/Graph.h"

namespace Graph_lib {
	struct TriangoloRettangolo : Shape {
		TriangoloRettangolo(Point vertice_90, double base, double altezza, int angolo);
		void draw_lines() const;
	private:
		double x_vertice;
		double y_vertice;
		int _angolo;
		double _base;
		double _altezza;
	};
}