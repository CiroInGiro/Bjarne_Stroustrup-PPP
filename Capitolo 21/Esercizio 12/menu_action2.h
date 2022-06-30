#pragma once
#include "../GUI/Window.h"
#include "../GUI/Graph.h"
#include "../GUI/GUI.h"

class message : Graph_lib::Window {
public:
	message(Point xy, int width, int height, const std::string& titolo, const std::string& messaggio);
private:
};