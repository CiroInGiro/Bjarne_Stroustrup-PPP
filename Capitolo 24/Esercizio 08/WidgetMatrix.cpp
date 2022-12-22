#include "WidgetMatrix.h"

WidgetMatrix::WidgetMatrix(Point position, Index row, Index column, const std::string& name, int margine = 5) {
	// calcolo dimensione del widget e costruzione matrice
	add(position);
	_name = name;
	_margine_celle = margine;
	_width = 0;
	_height = 0;
	_celle.resize(row);
	for (Index r = 0; r < _celle.size(); ++r) _celle[r].resize(column);
	
	for (Index r = 0; r < _celle.size(); ++r) {
		for (Index c = 0; c < _celle[r].size(); ++c) {
			_celle[r][c] = new Graph_lib::TBox(point(0), "");
		}
	}

	_riposiziona();
}

WidgetMatrix::~WidgetMatrix() {
	for (int r = 0; r < _celle.size(); ++r) {
		for (int c = 0; c < _celle[r].size(); ++c) {
			delete _celle[r][c];
			_celle[r][c] = nullptr;
		}
	}
}

void WidgetMatrix::draw_lines() const {
	for (auto w : _celle) {
		for (auto c : w) {
			c->draw_lines();
		}
	}
}

void WidgetMatrix::move(int dx, int dy) {
	for (auto w : _celle) {
		for (auto c : w) {
			c->move(dx, dy);
		}
	}
}

void WidgetMatrix::set_value(Index row, Index column, double value) {
	std::ostringstream oss{ "" };
	oss << value;
	_celle[row][column]->clear_line();
	_celle[row][column]->add_line(oss.str());
	// animazione di cella: lampeggia rosso e verde 2 volte ogni mezzo secondo
	int volte{ 2 };
	Graph_lib::Color old_color = _celle[row][column]->color();
	
	while (volte > 0) {
		_celle[row][column]->set_color(Graph_lib::Color::red);
		Fl::redraw();
		Fl::wait();
		_attesa(std::chrono::milliseconds(500));
		_celle[row][column]->set_color(Graph_lib::Color::green);
		Fl::redraw();
		Fl::wait();
		_attesa(std::chrono::milliseconds(500));
		--volte;
	}

	// imposto il vecchio colore
	_celle[row][column]->set_color(old_color);
	Fl::redraw();
	Fl::wait();
}

void WidgetMatrix::set_color(Graph_lib::Color c) {
	Shape::set_color(c);
	std::vector<std::vector<Graph_lib::TBox*>>::iterator irow = _celle.begin();
	while (irow != _celle.end()) {
		std::vector<Graph_lib::TBox*>::iterator icolumn = irow->begin();
		while (icolumn != irow->end()) {
			(*icolumn)->set_color(c);
			++icolumn;
		}
		++irow;
	}
}

void WidgetMatrix::swapRow(Index row1, Index row2) {
	// scambio celle tra 2 righe 5px ogni 250 ms
	int y1 = _celle[row1][0]->point(0).y;
	int y2 = _celle[row2][0]->point(0).y;
	Index num_cols = _celle[row1].size() - 1;
	
	int dy1, dy2;
	if (_celle[row1][0]->point(0).y < _celle[row2][0]->point(0).y) {
		dy1 = +5;
		dy2 = -5;
	}
	else {
		dy1 = -5;
		dy2 = 5;
	}

	while (_celle[row1][num_cols]->point(0).y != y2 || _celle[row2][num_cols]->point(0).y != y1) {
		// spostiamo le cella della prima riga
		for (Graph_lib::TBox* tb : _celle[row1]) {
			if (abs(y2 - tb->point(0).y) < abs(dy1)) dy1 = y2 - tb->point(0).y;
			tb->move(0, dy1);
		}
		// spostiamo le celle della seconda riga
		for (Graph_lib::TBox* tb : _celle[row2]) {
			if (abs(y1 - tb->point(0).y) < abs(dy2)) dy2 = y1 - tb->point(0).y;
			tb->move(0, dy2);
		}
		// attesa 250 ms
		Fl::redraw();
		Fl::wait();
		_attesa(std::chrono::milliseconds(250));
	}
}

void WidgetMatrix::_riposiziona() {
	int x = point(0).x;
	int y = point(0).y;

	for (Index r = 0; r < _celle.size(); ++r) {
		for (Index c = 0; c < _celle[r].size(); ++c) {
			if (_celle[r][c]) {
				int dx = x - _celle[r][c]->get_position().x;
				int dy = y - _celle[r][c]->get_position().y;
				_celle[r][c]->move(dx, dy);
			}
			
			// aggiorno lo spazio occuppato dal widget in orizzontale
			x += _celle[r][c]->get_width() + _margine_celle;
			if (_width < (x - point(0).x)) _width += _celle[r][c]->get_width() + _margine_celle;
		}
		x = point(0).x; // ritorno a capo rigo
		// aggiorno lo spazio occupato dal widget in verticale
		y += _celle[r][0]->get_height() + _margine_celle;
		if (_height < (y - point(0).y)) _height += _celle[r][0]->get_height() + _margine_celle; // ultimo utilizzato
	}
}

// timer
void WidgetMatrix::_attesa(std::chrono::milliseconds ritardo) {
	std::chrono::steady_clock::time_point start{ std::chrono::steady_clock::now() };
	std::chrono::steady_clock::time_point end{ std::chrono::steady_clock::now() };

	while (std::chrono::duration_cast<std::chrono::milliseconds>((end - start)) < ritardo) {
		end = std::chrono::steady_clock::now();
	}
}