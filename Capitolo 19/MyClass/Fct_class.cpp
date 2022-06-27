#include "Fct_class.h"

using namespace Graph_lib;

Fct_class::Fct_class(Fp2 funzione, double min, double max, Point origine, int count, double xscale, double yscale, int precisione) {
	parametri(funzione, min, max, origine, count, xscale, yscale, precisione);
}

void Graph_lib::Fct_class::reset() {
	//func = nullptr;
	_funzione = nullptr;
	_min = 0;
	_max = 0;
	_origine.x = 0;
	_origine.y = 0;
	_count = 100;
	_xscale = 25;
	_yscale = 25;
	_precisione = 1;
	for (int i = 0; i < number_of_points(); ++i) {
		set_point(i, _origine);
	}
}

void Fct_class::parametri(Fp2 funzione, double min, double max, Point origine, int count, double xscale, double yscale, int precisione) {
	//func = nullptr;
	_funzione = funzione;
	_min = min;
	_max = max;
	if (max - min <= 0) error("Range di valori troppo stretto.");
	_origine = origine;
	_count = count;
	if (count <= 0) error("Serve almeno un calcolo per avere un valore");
	_xscale = xscale;
	_yscale = yscale;
	if (xscale < 0 || xscale > 100) error("Percentuale della scala x non corretta");
	if (yscale < 0 || yscale > 100) error("Percentuale della scala y non corretta");
	_precisione = precisione;
	if (precisione < 0) error("Valore di precisione negativo");
}

void Fct_class::start() {
	if (_funzione == nullptr) error("start(): parametro funzione da eseguire mancante");

	/*if (func == nullptr) {
		func = new Function(_funzione, _min, _max, _origine, _count, _xscale, _yscale);
	}*/

	int num_points = number_of_points();
	double step = (_max - _min) / _count;
	double x = _min;
	for (int i = 0; i < _count; ++i) {
		double y = _funzione(x, _precisione);
		int xpoint = _origine.x + (int)(x * _xscale);
		int ypoint = _origine.y - (int)(y * _yscale);
		if (i < num_points) set_point(i, Point{ xpoint, ypoint });
		else add(Point{ xpoint, ypoint });
		x += step;
	}
	/*
	// dovrebbe averlo fatto già reset comunque.
	if (_count < num_points) {
		for (int i = _count; i < num_points; ++i) {
			set_point(i, _origine);
		}
	}*/
}

void Fct_class::stop() {
	//func = nullptr;

}

/*void Fct_class::draw_lines() const {
	if (func != nullptr) func->draw();
}
void Fct_class::move(int dx, int dy) {
	if (func != nullptr) func->move(dx, dy);
}
*/