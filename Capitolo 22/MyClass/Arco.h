#pragma once

#include "../GUI/Graph.h"
#include "../GUI/Point.h"

namespace Graph_lib {
	struct Arco : Shape {
	public:
		Arco(Point xy, int w, int h, double a1, double a2);
		void draw_lines() const;
	private:
		int _w, _h; // punto min e max distante dal centro
		double _start, _end; // angolo di partenza e finale
	};
}