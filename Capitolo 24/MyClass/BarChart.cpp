#include "BarChart.h"

namespace Graph_lib {

	BarChart::BarChart(Point posizione, int width, int height, int num_valori) {
		add(posizione);
		_width = width;
		_height = height;
		if (_max_valori < 0) _max_valori = 0; else _max_valori = num_valori;
		for (int indice = 0; indice < _max_valori; ++indice) {
			_valori.push_back(0);
			_barre.push_back({ Color::black, Color::black, nullptr });
		}
		if (_max_valori > _width) error("Troppo poco spazio per disegnare le barre");
	}

	void BarChart::set_value(double valore, int indice) {
		if (indice < 0 || indice >= _max_valori) error("valore non registrabile, barra mancante.");
		_valori[indice] = valore;
	}

	double BarChart::value(int indice) const {
		if (indice < 0 || indice >= _max_valori) error("valore non accessibile");
		return _valori[indice];
	}

	void BarChart::draw_lines() const {
		int barra_width = (_width / _max_valori) * 0.8;
		int barra_margine = (_width / _max_valori) * 0.2;
		double yscale = _height / _max();

		int x = point(0).x + 1;

		fl_color(color().as_int());
		fl_line(point(0).x, point(0).y, (point(0).x + _width), point(0).y);
		fl_line(point(0).x, point(0).y, point(0).x, (point(0).y - _height));

		for (int indice = 0; indice < _valori.size(); ++indice) {
			int h = _valori[indice] * yscale;
			int y = point(0).y - h;
			if (_barre[indice].fill_color.visibility()) {
				fl_color(_barre[indice].fill_color.as_int());
				fl_rectf(x, y, barra_width, h);
			}
			if (_barre[indice].border_color.visibility()) {
				fl_color(_barre[indice].border_color.as_int());
				fl_rect(x, y, barra_width, h);
			}
			if (_barre[indice].label) {
				Point pbar = _barre[indice].label->point(0);
				int newy = (y - 5) - pbar.y;
				_barre[indice].label->move(1, newy);
				_barre[indice].label->set_color(_barre[indice].border_color);
				_barre[indice].label->draw();
			}
			if (_barre[indice].x_label) {
				_barre[indice].x_label->set_color(_barre[indice].border_color);
				_barre[indice].x_label->draw();
			}
			x += barra_width + barra_margine;
		}

		if (_etichetta) {
			_etichetta->set_color(color());
			_etichetta->draw();
		}
	}

	void BarChart::set_label(const string& etichetta) {
		_etichetta = new Text(Point{ (point(0).x + (_width / 2)), (point(0).y - _height - 30) }, etichetta);
	}

	void BarChart::set_bar_label(const string& etichetta, int indice) {
		int barra_width = (_width / _max_valori) * 0.8;
		int barra_margine = (_width / _max_valori) * 0.2;
		double yscale = _height / _max();
		int y = point(0).y - (int)(_valori[indice] * yscale) - 5;
		int x = point(0).x + (barra_margine * indice) + (barra_width * indice);
		_barre[indice].label = new Text(Point{ x, y }, etichetta);
		//_barre[indice].label->set_color(_barre[indice].border_color);
	}
	
	void BarChart::set_bar_x_label(const string& etichetta, int indice) {
		int barra_width = (_width / _max_valori) * 0.8;
		int barra_margine = (_width / _max_valori) * 0.2;
		int y = point(0).y + 15;
		int x = point(0).x + (barra_margine * indice) + (barra_width * indice);
		_barre[indice].x_label = new Text(Point{ x, y }, etichetta);
	}

	void BarChart::set_bar_color(Color colore, int indice) {
		_barre[indice].border_color = colore;
	}

	void BarChart::set_bar_fill_color(Color colore, int indice) {
		_barre[indice].fill_color = colore;
	}

	double BarChart::_max() const {
		double retVal{ 0 };
		for (double valore : _valori) {
			if (valore > retVal) retVal = valore;
		}
		return retVal;
	}
}