#pragma once

#include "../GUI/Graph.h"

namespace Graph_lib {
	struct Regular_Polygon : Shape
	{
		Regular_Polygon(Point centro, int raggio, int lati);
		void draw_lines() const;
	private:
		Point* _centro;
		int _R; // raggio
		int _lati;
	};
}