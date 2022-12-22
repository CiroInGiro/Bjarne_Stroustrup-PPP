#pragma once
// Shape per disegnare una matrice di TBox

#include "../GUI/Graph.h" // per shape
#include "../MyClass/TBox.h" // per il box e il valore della cella
#include "../GUI/Point.h"
#include <sstream>
#include <chrono>
#include <math.h> // per abs()

using Index = long;

class WidgetMatrix : public Graph_lib::Shape
{
public:
	WidgetMatrix(Point position, Index row, Index column, const std::string& name, int _margine_celle);
	~WidgetMatrix();
	void draw_lines() const override;
	void move(int dx, int dy);
	int get_width() const { return _width; }
	int get_height() const { return _height; }
	std::string get_name() const { return _name; }
	void set_value(Index row, Index column, double value);
	void set_color(Graph_lib::Color c);
	void swapRow(Index row1, Index row2);
private:
	int _margine_celle, _width, _height;
	std::string _name;
	std::vector<std::vector<Graph_lib::TBox*>> _celle;
	void _riposiziona();
	void _attesa(std::chrono::milliseconds); // esce dalla funzione allo scadere del tempo
};

