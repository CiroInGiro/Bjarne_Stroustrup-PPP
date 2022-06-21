#pragma once

#include "../GUI/Graph.h"
#include "../GUI/Point.h"

namespace Graph_lib {
	struct Regular_Hexagon : Shape
	{
		Regular_Hexagon(Point centro, int raggio);
		void draw_lines() const;
	private:
		int _x, _y;
		int _R;
	};

}

