/*
Capitolo 16 Esercizio 1
Crea una classe My_window come Simple_window, solo che oltre al tasto next ci sia il tasto quit.
*/
#include "../GUI/Graph.h"
#include "../GUI/GUI.h"

class My_window : public Graph_lib::Window {
public:
	My_window(Point pos, int width, int height, const std::string& titolo) : Window(pos, width, height, titolo),
		bt_quit(Point{ x_max() - 100, pos.y + 10 }, 70, 20, "Quit", [](Graph_lib::Address, Graph_lib::Address pw) { Graph_lib::reference_to<My_window>(pw).quit(); }),
		bt_next(Point{ x_max() - 200, pos.y + 10 }, 70, 20, "Next", [](Graph_lib::Address, Graph_lib::Address pw) { Graph_lib::reference_to<My_window>(pw).next(); })
	{
		attach(bt_quit);
		bt_quit.hide();
		attach(bt_next);
	}
private:
	Graph_lib::Button bt_next;
	Graph_lib::Button bt_quit;
	void next() {
		bt_next.hide();
		bt_quit.show();
		redraw();
	}
	void quit() {
		hide();
	}
};

int main() {
	My_window win(Point{ 0,0 }, 400, 400, "Capitolo 16 Esercizio 1");
	return Graph_lib::gui_main();
}