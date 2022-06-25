/*
Capitolo 16 Esercizio 9
Modifica la calcolatrice del capitolo 7 per prendere i suoi input da una input box
e ritornare i suoi risultati in una output box.
*/

#include "WinCalc.h"
#include <exception>

int main(int argc, char* argv[]) {
	try {
		WinCalc c(Point{ 0,0 }, 800, 800, "Capitolo 16 Esercizio 9");
		c.color(Color::white);
		gui_main();
	}
	catch (std::exception e) {
		using std::cerr;
		using std::endl;
		cerr << "Errore: " << e.what() << endl;
	}
	catch (...) {
		using std::cerr;
		using std::endl;
		cerr << "Errore non gestito..." << endl;
	}
	return 0;
}