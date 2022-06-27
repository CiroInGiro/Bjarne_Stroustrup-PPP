/*
Capitolo 19 Esercizio 14
Fornisci una interfaccia grafica e un minimo di output grafico per "Hunt the Wumpus" del capitolo 18.
Prendi l'input in un input box e visualizza
una mappa della cava attualmente conosciuta al giocatore in una finestra.
*/

/*
Capitolo 19 Esercizio 15
Dai la possibilità all'utente di markare le stanze dove probabilmente ci siano pipistrelli, pozzi o mostro.
*/
// Potremmo inserire altri campi bool ad indicare per cosa sono markate le camere
// se la camera è visibile aggiunge le righe descrittive per tutti i campi bool
// altrimenti visualizza la camera ma solo con i marker.

#include "../MyClass/Wumpus.h"
//#include "WumpusGUI.h"

int main(int argc, char** argv) {
	Wumpus game;
	//game.debug();
	//game.guidebug();
	game.guiplay();
	return 0;
}