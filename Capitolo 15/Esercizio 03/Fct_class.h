#pragma once

#include "../GUI/Graph.h"
#include "../GUI/Point.h"

typedef double Fp(double);

typedef double Fp2(double, int);

namespace Graph_lib {
	template<typename T>	
	class Fct_class :public Graph_lib::Shape {
	public:
		Fct_class(Fp2 funzione, double min, double max, Point origine, int count = 100, double xscale = 25, double yscale = 25, T precisione = 0);
		void reset();
		void parametri(Fp2 funzione, double min, double max, Point origine, int count = 100, double xscale = 25, double yscale = 25, T precisione = 0);
		void start();
		void stop();
		//void draw_lines() const;
		//void move(int dx, int dy);
	private:
		//Function* func{ nullptr };
		Fp2* _funzione{ nullptr };
		double _min, _max;
		Point _origine;
		int _count;
		double _xscale, _yscale;
		T _precisione;
	};

	template<typename T>
	Fct_class<T>::Fct_class(Fp2 funzione, double min, double max, Point origine, int count, double xscale, double yscale, T precisione) {
		parametri(funzione, min, max, origine, count, xscale, yscale, precisione);
	};

	template<typename T>
	void Fct_class<T>::reset() {
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
	};

	template<typename T>
	void Fct_class<T>::parametri(Fp2 funzione, double min, double max, Point origine, int count, double xscale, double yscale, T precisione) {
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
	};

	template<typename T>
	void Fct_class<T>::start() {
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
	};

	template<typename T>
	void Fct_class<T>::stop() {
		//func = nullptr;

	};
}
