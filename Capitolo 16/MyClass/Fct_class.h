#pragma once

#include "../GUI/Graph.h"

typedef double Fp(double);

typedef double Fp2(double, int);

namespace Graph_lib {
	class Fct_class :public Shape {
	public:
		Fct_class(Fp2 funzione, double min, double max, Point origine, int count = 100, double xscale = 25, double yscale = 25, int precisione = 0);
		void reset();
		void parametri(Fp2 funzione, double min, double max, Point origine, int count = 100, double xscale = 25, double yscale = 25, int precisione = 0);
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
		int _precisione;
	};
}


