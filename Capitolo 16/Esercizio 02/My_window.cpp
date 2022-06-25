#include "My_window.h"

	My_window::My_window(Point pos, int width, int height, const std::string& titolo) : Window(pos, width, height, titolo),
		bt_quit(Point{ x_max() - 100, pos.y + 10 }, 70, 20, "Quit", [](Graph_lib::Address, Graph_lib::Address pw) { Graph_lib::reference_to<My_window>(pw).quit(); }),
		bt_next(Point{ x_max() - 200, pos.y + 10 }, 70, 20, "Next", [](Graph_lib::Address, Graph_lib::Address pw) { Graph_lib::reference_to<My_window>(pw).next(); })
	{
		attach(bt_quit);
		bt_quit.hide();
		attach(bt_next);
	}

	void My_window::next() {
		bt_next.hide();
		bt_quit.show();
		redraw();
	}

	void My_window::quit() {
		hide();
	}