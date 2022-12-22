#pragma once
#include "../GUI/Window.h"
#include "../GUI/Point.h"
#include <vector> // vettore di widget
#include "WidgetMatrix.h"

// definisco i stessi tipi per le matrici
using Matrix = std::vector<std::vector<double>>;
using Vector = std::vector<double>;
using Index = long;

class WinMatrix : public Graph_lib::Window
{
public:
	WinMatrix(int width, int height, const std::string& titolo);
	WinMatrix(Point position, int width, int height, const std::string& titolo);
	~WinMatrix() override;
	void addMatrix(const std::string& name, Index row, Index column);
	void addVector(const std::string& name, Index size) { addMatrix(name, size, 1); }
	void setMatrix(const std::string& name, Index row, Index column, double value);
	void setVector(const std::string& name, Index index, double value) { setMatrix(name, index, 0, value); }
	void swapRow(const std::string& name, Index row1, Index row2);
	void set_win_color(Graph_lib::Color c);
	void set_matrix_color(Graph_lib::Color c);
private:
	Graph_lib::Color* _color{ nullptr };
	std::vector<WidgetMatrix*> _matrici;
	const int _margine_matrici{ 35 }; // pixel, spazio tra le matrici
	const int _margine_celle{ 30 }; // pixel, spazio tra le cele
};

