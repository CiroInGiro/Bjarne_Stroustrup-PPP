/*
Capitolo 13 Esercizio 17
Modifica l'esercizio precedente per usare esagoni di diverso colore.
*/

#include "../GUI/Simple_window.h"
#include "../GUI/Graph.h"
#include "../MyClass/Regular_Hexagon.h"

int main() {
	Simple_window win(Point{ 0,0 }, 800, 800, "Esercizio 15");
	win.color(Color::white);
	const int raggio = 120;
	const int distanza = raggio * 2;
	const int angolazione = 270;
	const int num_orizzontali = win.x_max() / distanza;
	const int space_orizzontale = (win.x_max() % distanza) / num_orizzontali;
	const int num_verticali = (win.y_max() - 20) / distanza;
	const int space_verticale = ((win.y_max() - 20) % distanza) / num_verticali;
	Vector_ref<Graph_lib::Regular_Hexagon> esagoni;

	for (int riga = 0; riga < num_verticali; ++riga) {
		for (int colonna = 0; colonna < num_orizzontali; ++colonna) {
			int x = raggio + (colonna * distanza) + (colonna * space_orizzontale);
			int y = raggio + 20 + (riga * distanza) + (riga * space_verticale);
			esagoni.push_back(new Graph_lib::Regular_Hexagon(Point{ x, y }, raggio));
			esagoni[(esagoni.size() - 1)].set_color((rand() % 255));
			win.attach(esagoni[(esagoni.size() - 1)]);
		}
	}

	win.wait_for_button();

	return 0;
}