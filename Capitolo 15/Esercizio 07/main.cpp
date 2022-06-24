/*
Capitolo 15 Esercizio 7
Modifica la classe GraphBar in modo da consentire l'etichetta di se stesso e delle sue barre.
Accetta l'uso di colore.
*/

#include "BarChart.h"
#include "../GUI/Simple_window.h"
#include <iostream>

int main() {
	const string titolo{ "Capitolo 15 Esercizio 7" };
	Simple_window win(Point{ 0, 0 }, 800, 600, titolo);
	win.color(Color::white);

	BarChart grafico(Point{ 50, 500 }, 700, 400, 20);
	grafico.set_color(Color::dark_red);
	grafico.set_fill_color(Color::blue);
	grafico.set_label("Grafico a barre");

	Color rgb[11] = { Color::blue, Color::cyan, Color::dark_blue, Color::dark_cyan, Color::dark_green, Color::dark_magenta, Color::dark_red, Color::dark_yellow, Color::green, Color::magenta, Color::red };
	int rgb_ind{ 0 };

	for (int rif = 0; rif < 20; ++rif) {
		int rif2{ 0 };
		if (rif > 0) rif2 = rif - 1;
		double valore_etichetta = (1 + rif + (grafico.value(rif2) * 1.3));
		grafico.set_value(valore_etichetta, rif);
		grafico.set_bar_color(rgb[rgb_ind], rif);
		grafico.set_bar_fill_color(rgb[rgb_ind], rif);
		ostringstream olabel;
		olabel << valore_etichetta;
		grafico.set_bar_label(olabel.str(), rif);
		++rgb_ind;
		if (rgb_ind > 10) rgb_ind = 0;
	}

	win.attach(grafico);
	win.wait_for_button();
}