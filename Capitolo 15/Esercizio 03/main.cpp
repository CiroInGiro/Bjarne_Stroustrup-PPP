/*
Capitolo 15 Esercizio 3
Modifica Fct in modo che prenda un parametro aggiuntivo per controllare la precisione o altro.
Rendi il tipo di questo parametro un Template per avere una maggiore flessibilità.
*/

#include "Fct_class.h"
#include "../GUI/Simple_window.h"

double q(double x, int p = 0) { return x * x; }

double coseno(double x, int p = 0) { return cos(x); }

int fact(int n) {
	int count = n;
	int retVal{ 1 };
	while (count > 0) {
		retVal *= count;
		--count;
	}
	return retVal;
}

double e(double x, int precision = 0) {
	// per il membro 0 abbiamo 1
	double retVal = 1;
	for (int p = 1; p < precision; ++p) {
		retVal += (pow(x, p)) / fact(p);
	}
	return retVal;
}

int main() {
	try {
		const string titolo{ "Capitolo 15 Esercizio 3" };
		Simple_window win(Point{ 0, 0 }, 600, 600, titolo);
		win.color(Color::white);

		Axis x(Axis::x, Point{ 100, 300 }, 400, 20, "1 a 20");
		Axis y(Axis::y, Point{ 300, 500 }, 400, 20, "1 a 20");
		x.set_color(Color::red);
		y.set_color(Color::red);
		win.attach(x);
		win.attach(y);

		Fct_class<int> multifunc(q, -10.0, 11.0, Point{ 300, 300 }, 400, 20.0, 20.0, 0);
		multifunc.start();
		win.attach(multifunc);
		win.wait_for_button();
		
		multifunc.reset();
		win.wait_for_button(); // visualizzo il grafico resettato.
		
		multifunc.parametri(coseno, -10.0, 11.0, Point{ 300, 300 }, 400, 20.0, 20.0, 0);
		multifunc.start();
		win.wait_for_button();

		multifunc.parametri(e, -10.0, 11.0, Point{ 300, 300 }, 400, 20.0, 20.0, 4);
		multifunc.start();
		win.wait_for_button();

	}
	catch (exception e) {

	}

	return 0;
}