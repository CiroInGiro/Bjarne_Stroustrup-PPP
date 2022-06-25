#pragma once

#include "../MyClass/Fct_class.h"
#include "../GUI/Window.h"
#include "../GUI/Point.h"
#include "../GUI/Graph.h"
#include "../GUI/GUI.h"

using namespace Graph_lib;

class WinGraph : public Window
{
public:
	WinGraph(Point pos, int width, int height, const std::string& titolo);
	//void move() const;

private:
	Text errore;
	In_box min;
	In_box max;
	In_box risoluzione;
	Fct_class func_graph;
	Axis* x{ nullptr };
	Axis* y{ nullptr };
	Point _pos;
	Button bt_sin;
	Button bt_cos;
	int _start;
	int _end;
	int _ris;
	double _zoom_x;
	double _zoom_y;
	Point _origine;
	void prepara();
	void action_sin();
	void action_cos();
	static double func_sin(double x, int precision);
	static double func_cos(double x, int precision = 0);
};

