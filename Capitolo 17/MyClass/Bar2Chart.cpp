#include "Bar2Chart.h"

namespace Graph_lib {

	Bar2Chart::Bar2Chart(Point posizione, int width, int height) {
		add(posizione);
		_width = width;
		_height = height;
		/*if (_max_valori < 0) _max_valori = 0; else _max_valori = num_valori;
		for (int indice = 0; indice < _max_valori; ++indice) {
			_valori.push_back(0);
			_barre.push_back({ Color::black, Color::black, nullptr });
		}
		if (_max_valori > _width) error("Troppo poco spazio per disegnare le barre");*/
	}

	void Bar2Chart::add_value(double valore, Serie yy) {
		//if (indice < 0 || indice >= _max_valori) error("valore non registrabile, barra mancante.");
		StyleBar barra;
		barra.border_color = color();
		barra.fill_color = fill_color();
		std::ostringstream oss;
		oss << valore;
		barra.label = new Text(point(0), oss.str());
		barra.x_label = new Text(point(0), "");
		switch (yy) {
		case Serie::y1:
			_valori_y1.push_back(valore);
			_barre_y1.push_back(barra);
			break;
		case Serie::y2:
			_valori_y2.push_back(valore);
			_barre_y2.push_back(barra);
			break;
		}
		_valori_y1.size() > _valori_y2.size() ? _max_valori = _valori_y1.size() : _max_valori = _valori_y2.size();
	}

	double Bar2Chart::value(int indice, Serie yy) const {
		//if (indice < 0 || indice >= _max_valori) error("valore non accessibile");
		switch (yy) {
		case Serie::y1:
			if (indice < 0 || indice >= _valori_y1.size()) error("valore non accessibile");
			return _valori_y1[indice];
			break;
		case Serie::y2:
			if (indice < 0 || indice >= _valori_y2.size()) error("valore non accessibile");
			return _valori_y2[indice];
			break;
		default:
			return 0.0;
		}
	}

	void Bar2Chart::draw_lines() const {
		int barra_width = ((_width / _max_valori) * 0.8) / 2;
		int barra_margine = (_width / _max_valori) * 0.1;
		double yscale = _height / _max();

		int x = point(0).x + barra_margine;

		fl_color(color().as_int());
		fl_line(point(0).x, point(0).y, (point(0).x + _width), point(0).y);
		fl_line(point(0).x, point(0).y, point(0).x, (point(0).y - _height));

		for (int indice = 0; indice < _max_valori; ++indice) {
			if (indice < _valori_y1.size()) {
				int h = _valori_y1[indice] * yscale;
				int y = point(0).y - h;
				if (_barre_y1[indice].fill_color.visibility()) {
					fl_color(_barre_y1[indice].fill_color.as_int());
					fl_rectf(x, y, barra_width, h);
				}
				if (_barre_y1[indice].border_color.visibility()) {
					fl_color(_barre_y1[indice].border_color.as_int());
					fl_rect(x, y, barra_width, h);
				}
				if (_barre_y1[indice].label) {
					Point pbar = _barre_y1[indice].label->point(0);
					int newx = x - pbar.x;
					int newy = (y - 5) - pbar.y;
					_barre_y1[indice].label->move(newx, newy);
					_barre_y1[indice].label->set_color(_barre_y1[indice].border_color);
					_barre_y1[indice].label->draw();
				}
				if (_barre_y1[indice].x_label) {
					Point pbar = _barre_y1[indice].x_label->point(0);
					int newx = x - pbar.x;
					int newy = point(0).y + 15 - pbar.y;
					_barre_y1[indice].x_label->move(newx, newy);
					_barre_y1[indice].x_label->set_color(_barre_y1[indice].border_color);
					_barre_y1[indice].x_label->draw();
				}
			}
			if (indice < _valori_y2.size()) {
				x += barra_width;
				int h = _valori_y2[indice] * yscale;
				int y = point(0).y - h;
				if (_barre_y2[indice].fill_color.visibility()) {
					fl_color(_barre_y2[indice].fill_color.as_int());
					fl_rectf(x, y, barra_width, h);
				}
				if (_barre_y2[indice].border_color.visibility()) {
					fl_color(_barre_y2[indice].border_color.as_int());
					fl_rect(x, y, barra_width, h);
				}
				if (_barre_y2[indice].label) {
					Point pbar = _barre_y2[indice].label->point(0);
					int newx = x - pbar.x;
					int newy = (y - 5) - pbar.y;
					_barre_y2[indice].label->move(newx, newy);
					_barre_y2[indice].label->set_color(_barre_y2[indice].border_color);
					_barre_y2[indice].label->draw();
				}
				if (_barre_y2[indice].x_label) {
					Point pbar = _barre_y2[indice].x_label->point(0);
					int newx = x - pbar.x;
					int newy = point(0).y + 35 - pbar.y;
					_barre_y2[indice].x_label->move(newx, newy);
					_barre_y2[indice].x_label->set_color(_barre_y2[indice].border_color);
					_barre_y2[indice].x_label->draw();
				}
				x -= barra_width;
			}
			x += (barra_width * 2) + (barra_margine * 2);
		}

		if (_etichetta) {
			_etichetta->set_color(color());
			_etichetta->draw();
		}
	}

	void Bar2Chart::set_label(const string& etichetta) {
		_etichetta = new Text(Point{ (point(0).x + 10), (point(0).y - _height - 30) }, etichetta);
	}

	void Bar2Chart::set_bar_label(const string& etichetta, int indice, Serie yy) {
		switch (yy) {
		case Serie::y1:
		{
			//int barra_width = ((_width / _max_valori) * 0.8) / 2;
			//int barra_margine = (_width / _max_valori) * 0.1;
			//double yscale = _height / _max();
			//int y = point(0).y - (int)(_valori_y1[indice] * yscale) - 5;
			//int x = point(0).x + (barra_margine * indice) + (barra_width * indice);
			_barre_y1[indice].label = new Text(point(0), etichetta);
		}
			break;
		case Serie::y2:
		{
			//int barra_width = (_width / _max_valori) * 0.2;
			//int barra_margine = (_width / _max_valori) * 0.2;
			//double yscale = _height / _max();
			//int y = point(0).y - (int)(_valori_y2[indice] * yscale) - 5;
			//int x = point(0).x + (barra_margine * indice * 2) + (barra_width * indice * 2);
			_barre_y2[indice].label = new Text(point(0), etichetta);
		}
			break;
		}
	}
	
	void Bar2Chart::set_bar_x_label(const string& etichetta, int indice, Serie yy) {
		//int barra_width = (_width / _max_valori) * 0.2;
		//int barra_margine = (_width / _max_valori) * 0.2;
		//int x{ 0 };
		//int y = point(0).y + 15;
		switch (yy) {
		case Serie::y1:
			//x = point(0).x + (barra_margine * indice) + (barra_width * indice);
			_barre_y1[indice].x_label = new Text(point(0), etichetta);
			break;
		case Serie::y2:
			//x = point(0).x + (barra_margine * indice * 2) + (barra_width * indice * 2);
			_barre_y2[indice].x_label = new Text(point(0), etichetta);
			break;
		}
	}

	void Bar2Chart::set_bar_color(Color colore, int indice, Serie yy) {
		switch (yy) {
		case Serie::y1:
			_barre_y1[indice].border_color = colore;
			break;
		case Serie::y2:
			_barre_y2[indice].border_color = colore;
			break;
		}
	}

	void Bar2Chart::set_bar_fill_color(Color colore, int indice, Serie yy) {
		switch (yy) {
		case Serie::y1:
			_barre_y1[indice].fill_color = colore;
			break;
		case Serie::y2:
			_barre_y2[indice].fill_color = colore;
			break;
		}
	}

	double Bar2Chart::_max() const {
		double retVal{ 0 };
		for (double valore : _valori_y1) {
			if (valore > retVal) retVal = valore;
		}
		for (double valore : _valori_y2) {
			if (valore > retVal) retVal = valore;
		}
		return retVal;
	}
}