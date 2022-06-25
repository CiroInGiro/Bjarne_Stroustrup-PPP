#pragma once

#include "../GUI/Graph.h"
#include "../GUI/GUI.h"

// finestra col pulsante quit aggiuntivo e next
class My_window : public Graph_lib::Window {
public:
	My_window(Point pos, int width, int height, const std::string& titolo);
private:
	Graph_lib::Button bt_next;
	Graph_lib::Button bt_quit;
	void next();
	void quit();
};

