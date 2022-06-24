/*
Capitolo 15 Esercizio 2
Definisci una classe Fct che è come Function tranne che memorizza i parametri del suo costruttore.
Fornisci a Fct un operazione di reset, in modo che puoi riutilizzarla per diverse funzioni, range ecc.
*/

#include "../GUI/Graph.h"
#include "../GUI/Simple_window.h"

typedef double Fp(double);

class Fct_class :public Shape{
public:
	Fct_class(Fp funzione, double min, double max, Point origine, int count = 100, double xscale = 25, int yscale = 25) {
		parametri(funzione, min, max, origine, count, xscale, yscale);
	}
	void reset() {
		func = nullptr;
		_funzione = nullptr;
		_min = 0;
		_max = 0;
		_origine.x = 0;
		_origine.y = 0;
		_count = 100;
		_xscale = 25;
		_yscale = 25;
		for (int i = 0; i < number_of_points(); ++i) {
			point(i) = _origine;
		}
	}
	void parametri(Fp funzione, double min, double max, Point origine, int count = 100, double xscale = 25, double yscale = 25) {
		func = nullptr;
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
	}
	void start() {
		if (_funzione == nullptr) error("start(): parametro funzione da eseguire mancante");

		if (func == nullptr) {
			func = new Function(_funzione, _min, _max, _origine, _count, _xscale, _yscale);
		}
	}
	void stop() {
		func = nullptr;
	}
	void draw_lines() const {
		if (func != nullptr) func->draw();
	}
	void move(int dx, int dy) {
		if (func != nullptr) func->move(dx, dy);
	}
private:
	Function* func{ nullptr };
	Fp* _funzione{ nullptr };
	double _min, _max;
	Point _origine;
	int _count;
	double _xscale, _yscale;
};

double q(double x) { return x * x; }

double coseno(double x) { return cos(x); }

int main(int argc, char** argv) {
	try {
		const string titolo{ "Capitolo 15 Esercizio 2" };
		Simple_window win(Point{ 0, 0 }, 600, 600, titolo);
		win.color(Color::white);

		Axis x(Axis::x, Point{ 100, 300 }, 400, 20, "1 a 20");
		Axis y(Axis::y, Point{ 300, 500 }, 400, 20, "1 a 20");
		x.set_color(Color::red);
		y.set_color(Color::red);
		win.attach(x);
		win.attach(y);

		Fct_class multifunc(q, -10, 11, Point{ 300, 300 }, 400, 25, 25);
		multifunc.start();
		win.attach(multifunc);

		win.wait_for_button();
		multifunc.reset();
		win.wait_for_button();
		multifunc.parametri(coseno, -10, 11, Point{ 300, 300 }, 400, 25, 25);
		multifunc.start();
		win.wait_for_button();

	}
	catch (exception e) {

	}
	
	return 0;
}