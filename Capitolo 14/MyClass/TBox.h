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
		void draw_lines() const;
	private:
		Graph_lib::Text _titolo{ Point{0,0}, "" };
		vector<std::string> _linee;
		void resize();
		int max();
	};
}