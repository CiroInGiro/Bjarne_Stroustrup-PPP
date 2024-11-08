/*
* Capitolo 26 Esercizio 9
* Aggiungi un output formattato basato sul testo alla libreria di inerfaccia grafica.
* Per esempio, quando avviene una chiamata Circle{Point{0,1},15} 
* potrebbe essere stampato in uscita sullo stream.
*/

#include "Lavagna.h"

int main(int argc, char** argv) {
	Lavagna lavagna(Point{ 0, 0 }, 500, 500, "Disegno - Esercizio 9");
	lavagna.color(Color::white);

	// indirizzare l'input all'interprete della finestra
	std::istringstream iss{ "Color{ black } Rectangle{ 100, 150, 300, 350 } Line{ 100, 150, 250, 0 } Line{ 250, 0, 400, 150 } Color{ green } Circle{ 250, 85, 40 } Rectangle{ 225, 400, 50, 100 } Rectangle{ 125, 200, 100, 100 } Rectangle{ 300, 200, 75, 100 }" };
	while (!iss.eof() && iss >> lavagna) {}

	// Ora reinderizziamo i disegni verso uno strream
	std::ostringstream oss;
	oss << lavagna;
	std::cout << "\n\n\nOutput stream:\n" << oss.str() << "\n\n\n";
	// se iss e oss sono diversi il test fallisce.
	
	// Solo per vedere il disegno.
	lavagna.run();

	return 0;
}