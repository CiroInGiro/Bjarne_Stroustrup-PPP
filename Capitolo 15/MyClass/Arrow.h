#pragma once

#include "../GUI/Graph.h"
#include <math.h>

namespace Graph_lib {
	struct Arrow : Shape
	{
		Arrow(Point xy1, int lunghezza, int rotazione);
		void draw_lines() const;
	private:
		int _l; // lunghezza della freccia
		int _a; // rotazione antioraria della freccia (0° a ore 3)
	};
}
