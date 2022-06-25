/*
Capitolo 16 Esercizio 10
Peovvedi a un programma in cui è possibile scegliere tra un set di funzioni (ad es. sin() e log()).
Fornire i parametri per queste funzioni e quindi rappresentarle graficamente.
*/

#include <iostream>
#include "WinGraph.h"

int main() {
	try {
		WinGraph win(Point{ 0,0 }, 800, 800, "Capitolo 16 Esercizio 10");
		win.color(Color::white);
		gui_main();
	}
	catch (exception e) {
		std::cerr << "Eccezione: " << e.what() << std::endl;
	}
	catch (...) {
		std::cerr << "Errore non gestito :-o" << std::endl;
	}
	return 0;
}