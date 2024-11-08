/*
* Capitolo 26 Esercizio 8
* Aggiungere un'interfaccia basata su testo alla libreria dell'interfaccia grafica dei capitoli 12 - 15.
* Ad esempio, la stringa Circle{ Point{0,1},15 } dovrebbe generare una chiamata Circle{ Point{0,1},15 }.
* Utilizzare questa interfaccia di testo per creare un "disegno per bambini"
* di una casa bidimensionale con un tetto, due finestre e una porta.
*/

/* 
* Creo una finestra che sarà la superficie da disegno.
* La finestra avrà un loop che legge da un input stream
* e interpreterà i comandi, chiamando le dovute classi.
* 
* NB: in Graph.h è stata modificato il tipo per il costruttore di Color perché, diversamente da C++11
* C++14 controlla il cast implicito con perdita di dati rendendo l'avviso bloccante.
*/

#include "Lavagna.h";

int main(int argc, char** argv) {
	// Generare la finestra
	Lavagna lavagna(Point{ 0, 0 }, 500, 500, "Disegno");
	lavagna.color(Color::white);

	// indirizzare l'input all'interprete della finestra
	std::istringstream iss{ "Color{ black } Rectangle{ 100, 150, 300, 350 } Line{ 100, 150, 250, 0 } Line{ 250, 0, 400, 150 } Color{ green } Circle{ 250, 85, 40 } Rectangle{ 225, 400, 50, 100 } Rectangle{ 125, 200, 100, 100 } Rectangle{ 300, 200, 75, 100 }" };
	while (!iss.eof() && iss >> lavagna) {}

	// Far partire la libreria grafica che gira fino alla chiusura della finestra.
	//Fl::run();

	// Fa partire il loop che alterna il disegno della finestra al prompt dei comandi
	lavagna.run();

	return 0;
}
