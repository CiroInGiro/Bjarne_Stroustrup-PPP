#pragma once

#include "../MyClass/Box.h"
#include <vector>

namespace Graph_lib {
	struct TBox : Box
	{
		TBox(Point xy, const std::string& titolo);  // Crea una etichetta sopra una box che usa Arco.h per smussare i bordi
		void move(int dx, int dy);
		void set_label(const std::string& titolo);
		void add_line(const std::string& riga);
		void clear_line();
		void draw_lines() const;
		void set_color(Graph_lib::Color c);
		// aggiunti nel capitolo 24 per esercizio 8
		int get_width() const { return _width; }
		int get_height() const { return _height; }
		Point get_position() { return _xy; };
	private:
		Graph_lib::Text _titolo{ Point{0,0}, "" };
		vector<std::string> _linee;
		void resize();
		int max();
		// aggiunti nel capitolo 24 per esercizio 8
		int _width{ 0 };
		int _height{ 0 };
		Point _xy;
	};
}