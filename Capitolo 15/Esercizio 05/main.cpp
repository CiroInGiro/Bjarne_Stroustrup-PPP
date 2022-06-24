/*
Capitolo 15 Esercizio 5
Anima (come nel paragrafo 15.5) la serie 1-1/3+1/5-1/7...
E' conosciuta come la serie di Leibniz e converge verso pi/4
*/

#include "../GUI/Simple_window.h"
#include "../MyClass/Fct_class.h"

double pi_quarti(double x, int step) {
	double retVal = 1;
	// operando 0 per - e 1 per +
	bool operando{ 0 };
	double dividendo = 3;
	int ciclo = 1;
	while (ciclo < step) {
		switch (operando) {
		case 0:
			retVal -= 1 / dividendo;
			break;
		case 1:
			retVal += 1 / dividendo;
			break;
		default:
			retVal = 1;
		}
		operando != operando;
		dividendo += 2;
		++ciclo;
	}
	return retVal;
}

int main() {
	const string titolo{ "Capitolo 15 Esercizio 5" };

	Simple_window win(Point{ 0, 0 }, 600, 600, titolo);
	win.color(Color::white);

	Axis x(Axis::x, Point{ 100, 300 }, 400, 20, "Asse x: 1 a 20");
	Axis y(Axis::y, Point{ 300, 500 }, 400, 20, "Asse y: 1 a 20");
	x.set_color(Color::red);
	y.set_color(Color::red);
	win.attach(x);
	win.attach(y);

	Fct_class piQuarter(pi_quarti, -10, 11, Point{ 300, 300 }, 400, 20, 20, 1);
	piQuarter.set_color(Color::blue);
	piQuarter.start();
	win.attach(piQuarter);

	for (int p = 2; p < 7; ++p) {
		piQuarter.reset();
		piQuarter.parametri(pi_quarti, -10, 11, Point{ 300, 300 }, 400, 20, 20, p);
		piQuarter.start();
		win.wait_for_button();
	}
}