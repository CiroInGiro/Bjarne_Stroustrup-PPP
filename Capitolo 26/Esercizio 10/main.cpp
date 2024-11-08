/* 
* Capitolo 26 Esercizio 10
* Usa l'interfaccia testuale dell'esercizio 9 per scrivere un test migliore per l'interfaccia della libreria grafica.
*/

#include "../MyClass/Lavagna.h"

int main(int argc, char** argv) {
	Lavagna* lavagna = new Lavagna(Point{ 0, 0 }, 500, 500, "Disegno - Esercizio 10 - Test Cerchio");
	lavagna->color(Color::white);

	// indirizzare l'input all'interprete della finestra
	std::istringstream iss; // { "Color{ black } Rectangle{ 100, 150, 300, 350 } Line{ 100, 150, 250, 0 } Line{ 250, 0, 400, 150 } Color{ green } Circle{ 250, 85, 40 } Rectangle{ 225, 400, 50, 100 } Rectangle{ 125, 200, 100, 100 } Rectangle{ 300, 200, 75, 100 }" };
	//while (!iss.eof() && iss >> lavagna) {}

	// Ora reinderizziamo i disegni verso uno strream
	std::ostringstream oss;
	//oss << lavagna;
	//std::cout << "\n\n\nOutput stream:\n" << oss.str() << "\n\n\n";
	// se iss e oss sono diversi il test fallisce.

	// Test Cerchio blu
	iss.str("Color{blue} Circle{Point{250,250},50}");
	while (!iss.eof() && iss >> *lavagna) {}
	oss << *lavagna;
	std::cout << "\n\n\nTest creazione di un cerchio blue:\n";
	std::cout << "Stringa in input:\n" << iss.str() << "\n\n";
	std::cout << "Stringa in output:\n" << oss.str() << "\n\n";
	if (iss.str() == oss.str()) std::cout << "Esito positivo\n\n";
	else std::cout << "Esito negativo\n\n\n\n";
	// *** Il test falliva perché quando creiamo il cerchio indichiamo il suo centro
	// *** ma la struttura memorizza un Point con le coordinate dell'angolo superiore sinistro
	// *** del quadrato immaginario che lo contiene. Modificato nell'operatore<< di Disegno

	// Test Rettangolo verde
	delete lavagna;
	lavagna = new Lavagna(Point{ 0, 0 }, 500, 500, "Disegno - Esercizio 10 - Test Rettangolo");
	lavagna->color(Color::white);
	iss.clear(); oss.clear();
	iss.str("Color{green} Rectangle{Point{200,200},100,100}");
	oss.str("");
	while (!iss.eof() && iss >> *lavagna) {}
	oss << *lavagna;
	std::cout << "\n\n\nTest creazione di un rettangolo green:\n";
	std::cout << "Stringa in input:\n" << iss.str() << "\n\n";
	std::cout << "Stringa in output:\n" << oss.str() << "\n\n";
	if (iss.str() == oss.str()) std::cout << "Esito positivo\n\n";
	else std::cout << "Esito negativo\n\n\n\n";

	// Test Linea rossa
	delete lavagna;
	lavagna = new Lavagna(Point{ 0, 0 }, 500, 500, "Disegno - Esercizio 10 - Test Rettangolo");
	lavagna->color(Color::white);
	iss.clear(); oss.clear();
	iss.str("Color{red} Line{Point{0,500},Point{500,0}}");
	oss.str("");
	while (!iss.eof() && iss >> *lavagna) {}
	oss << *lavagna;
	std::cout << "\n\n\nTest creazione di una linea rossa:\n";
	std::cout << "Stringa in input:\n" << iss.str() << "\n\n";
	std::cout << "Stringa in output:\n" << oss.str() << "\n\n";
	if (iss.str() == oss.str()) std::cout << "Esito positivo\n\n";
	else std::cout << "Esito negativo\n\n\n\n";

	// Solo per vedere il disegno.
	//lavagna->run();

	return 0;
}