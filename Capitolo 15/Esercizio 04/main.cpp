/*
Capitolo 15 Esercizio 4
Traccia un seno (sin(x)), un coseno (cos(x)), la somma di questi (sin(x) + cos(x)) e la somma del quadrato di questi (sin(x)*sin(x) + cos(x)*cos(x)) su un singolo grafico.
Provvedere agli assi ed etichette.
*/

#include <math.h>
#include "../GUI/Simple_window.h"
#include "../MyClass/Fct_class.h"

double seno(double x, int p) {
	return sin(x);
}

double coseno(double x, int p) {
	return cos(x);
}

double seno_plus_coseno(double x, int p) {
	return sin(x) + cos(x);
}

double qseno_plus_qcoseno(double x, int p) {
	return pow(sin(x), 2) + pow(cos(x), 2);
}

int main() {
	const string titolo{ "Capitolo 15 Esercizio 4" };
	
	Simple_window win(Point{ 0, 0 }, 600, 600, titolo);
	win.color(Color::white);
	
	Axis x(Axis::x, Point{ 100, 300 }, 400, 20, "Asse x: 1 a 20");
	Axis y(Axis::y, Point{ 300, 500 }, 400, 20, "Asse y: 1 a 20");
	x.set_color(Color::red);
	y.set_color(Color::red);
	win.attach(x);
	win.attach(y);

	Fct_class gseno(seno, -10, 11, Point{ 300, 300 }, 400, 20, 20, 0);
	gseno.set_color(Color::yellow);
	gseno.start();
	win.attach(gseno);

	Fct_class gcoseno(coseno, -10, 11, Point{ 300, 300 }, 400, 20, 20, 0);
	gcoseno.set_color(Color::blue);
	gcoseno.start();
	win.attach(gcoseno);

	Fct_class gsenopluscoseno(seno_plus_coseno, -10, 11, Point{ 300, 300 }, 400, 20, 20, 0);
	gsenopluscoseno.set_color(Color::green);
	gsenopluscoseno.start();
	win.attach(gsenopluscoseno);

	Fct_class gqsenoplusqcoseno(qseno_plus_qcoseno, -10, 11, Point{ 300, 300 }, 400, 20, 20, 0);
	gqsenoplusqcoseno.set_color(Color::dark_green);
	gqsenoplusqcoseno.start();
	win.attach(gqsenoplusqcoseno);

	win.wait_for_button();

	return 0;
}