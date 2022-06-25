#pragma once

#include "../GUI/Graph.h"
#include "../GUI/Point.h"
#include "../MyClass/Arco.h"

// Box con angoli arrotondati
namespace Graph_lib {
	struct Box : Shape
	{
		Box(Point xy, int w, int h);
		void draw_lines() const;
		void set_width(int width);
		void set_height(int height);
	private:
		int _w;
		int _h;
		void draw_border(const Point& xy, const int& w, const int& h) const;
	};
}
