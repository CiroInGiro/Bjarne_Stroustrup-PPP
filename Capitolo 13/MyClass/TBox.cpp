#include "TBox.h"

Graph_lib::TBox::TBox(Point xy, const string& titolo) : Box({ 0,0 }, 0, 0) {
	set_label(titolo);
	_titolo.set_color(Box::color());
	int riga_w = titolo.length() * (_titolo.font_size() / 2);
	int riga_height = _titolo.font_size();
	_titolo.move((xy.x + 5), (xy.y + riga_height));
	Box::move(xy.x, (xy.y + riga_height + 5));
}

void Graph_lib::TBox::move(int dx, int dy) {
	_titolo.move(dx, dy);
	Box::move(dx, dy);
}

void Graph_lib::TBox::add_line(const std::string& riga) {
	_linee.push_back(riga);
	resize();
	draw_lines();
}

void Graph_lib::TBox::set_label(const std::string& titolo) {
	_titolo.set_label(titolo);
	resize();
}

void Graph_lib::TBox::draw_lines() const {
	_titolo.draw_lines();
	Box::draw_lines();
	
	for (unsigned int indice = 0; indice < _linee.size(); ++indice) {
		int x = Box::point(0).x + 5;
		int y = Box::point(0).y + 5 + (_titolo.font_size() * (indice + 1));
		Graph_lib::Text testo{ Point{x,y}, _linee[indice] };
		testo.set_color(Box::color());
		testo.set_font(_titolo.font());
		testo.set_font_size(_titolo.font_size());
		testo.draw();
	}
}

void Graph_lib::TBox::resize() {
	int riga_width{ 0 };
	int riga_height = _titolo.font_size();
	if (max() > _titolo.label().length()) riga_width = max() * (_titolo.font_size() / 2);
	else riga_width = _titolo.label().length() * (_titolo.font_size() / 2);
	Box::set_width((riga_width + 10));
	// altezza considerata con almeno l'altezza di una riga + l'altezza di tutte le righe nel box + un margine di 5px per ogni riga nel box
	Box::set_height( (riga_height + (riga_height * _linee.size()) + (5 * _linee.size())) );
}

int Graph_lib::TBox::max() {
	int retVal{ 0 };
	for (std::string riga : _linee) {
		if (riga.length() > retVal) retVal = riga.length();
	}
	return retVal;
}