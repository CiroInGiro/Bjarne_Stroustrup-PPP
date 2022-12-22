#include "WinMatrix.h"

WinMatrix::WinMatrix(int width, int height, const std::string& titolo) : Window(width, height, titolo) { }

WinMatrix::WinMatrix(Point position, int width, int height, const std::string& titolo) : Window(position, width, height, titolo) { }

WinMatrix::~WinMatrix() {
	for (WidgetMatrix* wmx : _matrici) {
		delete wmx;
		wmx = nullptr;
	}

	delete _color;
	_color = nullptr;
}

void WinMatrix::addMatrix(const std::string& name, Index row, Index column) {
	// calcolo posizione in spazio vuoto
	int x{ _margine_matrici };
	int y{ _margine_matrici };
	for (WidgetMatrix* wmx : _matrici) x += wmx->get_width() + _margine_matrici;
	WidgetMatrix* wmx = new WidgetMatrix(Point{ x, y }, row, column, name, _margine_celle);
	wmx->set_color(*_color);
	attach(*wmx);
	_matrici.push_back(wmx);
}

void WinMatrix::setMatrix(const std::string& name, Index row, Index column, double value) {
	for (WidgetMatrix* wmx : _matrici) {
		// dobbiamo cercare la matrice name
		if (wmx->get_name() == name) {
			// impostiamo il valore
			wmx->set_value(row, column, value);
			return;
		}
	}
}

void WinMatrix::swapRow(const std::string& name, Index row1, Index row2) {
	// cerchiamo la matrice
	for (WidgetMatrix* wmx : _matrici) {
		if (wmx->get_name() == name) {
			// scambiamo le righe
			wmx->swapRow(row1, row2);
		}
	}
}

void WinMatrix::set_win_color(Graph_lib::Color c) {
	Window::color(c.as_int());
}

void WinMatrix::set_matrix_color(Graph_lib::Color c) {
	if (_color) { delete _color; _color = nullptr; }
	_color = new Graph_lib::Color(c);
}