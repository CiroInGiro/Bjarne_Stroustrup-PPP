#include "menu_action2.h"

message::message(Point xy, int width, int height, const std::string& titolo, const std::string& messaggio)
	: Graph_lib::Window(xy, width, height, titolo) {
	int x = (x_max() / 2) - messaggio.length();
	int y = (y_max() / 2);
	Graph_lib::Text *msg = new Graph_lib::Text(Point{ x, y }, messaggio);
	msg->set_color(Graph_lib::Color::blue);
	attach(*msg);
}