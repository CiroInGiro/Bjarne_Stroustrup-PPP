#pragma once

#include "../GUI/Graph.h"
#include <math.h>

/*
* Capitolo 22: aggiungo la possibilità di passare 2 puntda dove deve iniziare la freccia e dove finire.
*/

namespace Graph_lib {
	struct Arrow : Shape
	{
		Arrow(Point xy1, int lunghezza, int rotazione);
		Arrow(Point start, Point end);
		void draw_lines() const;
		//~Arrow() { std::cout << "\nDistruttore per Arrow chiamatao...\n"; }
	private:
		int _l; // lunghezza della freccia
		int _a; // rotazione antioraria della freccia (0° a ore 3)
	};
}
