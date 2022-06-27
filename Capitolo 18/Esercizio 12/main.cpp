/*
Capitolo 18 Esercizio 12
Implementa una versione del gioco "Hunt the Wumpus" o anche Wump.
E' un gioco non grafico inventato da Gregory Yob.
Alla base del gioco c'è un mostro puzzolente che vive in una caverna formata da stanze collegate.
Il tuo lavoro è uccidere il mostro utilizzando arco e frecce.
In più la caverna nasconde altre trappole oltre al mostro, pozzi senza fondo e pipistrelli giganti.
Se enmtri in una stanza con un pozzo il gioco finisce per te.
Se entri in una stanza coi pipistrelli, questi ti portano in un'altra stanza.
Se entri in una stanza dove c'è il mostro o il mostro entra nella tua ti mangia.
Quando entri in una stanza avviserai un pericolo nelle vicinanze:
- "Sento il mostro": esso è in una stanza adiacente.
- "Sento una brezza": c'è un pozzo in una stanza adiacente.
- "Sento i pipistrelli": ci sono pipistrelli in una stanza adiacente.
Per tua convenienza le stanze sono numerate.
Ogni stanza è collegata da tunnel ad altre 3 stanze.
Quando entri in una stanza avrai un messaggio tipo: "Sei nella stanza 12, ci sono tunnel per 1, 13 e 4; muovi o spari?"
Le possibili risposte sono m13 per muovi in 13 e s13-4-3 per sparare una freccia nelle stanze 13, 4 e 3.
La portata di una freccia è di 3 stanze
All'inizio del gioco hai 5 freccie a disposizione
L'inconveniente della freccia è che sveglia il mostro e lui si sposta in una stanza adiacente che potrebbe essere la tua!
Probabilmente la parte più difficile dell'esercizio è creare la grotta selezionando quali camere sono collegate con le altre.
Probabilmente vorresti usare un generatore di numeri casuali, come randint() di std_lib_facilities.h
che crea giochi diversi con diverse stanze per spostarsi tra pozzi, mostri e pipistrelli.
Suggerimento: assicurati di avere un modo per produrre in output lo stato della caverna per il debug.
*/

// con una lista che si muove in quattro direzioni configuriamo la caverna ma non è una Skip List dal momento che non servono le ricerche
// Inizialmente creo la prima stanza e devo scegliere tre camere a cui collegarmi, verifico la loro esistenza e se sono già completi i collegamenti oppure ne creo ancora un'altra e così via
// quindi ho bisogno di creare prima una lista di stanze non ancora collegate fra le quali scegliere e man mano che sono completamente collegate vengono tolte dalle possibili scelte future
// per questo motivo mi sembra più pratico creare un arrai di tipo "nodo" o "camera" e randomizzare l'indice nel range dell'array per scegliere le camere, man mano che esse sono complete il range scenderà.

#include <iostream>
#include "Wumpus.h"

int main(int argc, char** argv) {
	try {
		Wumpus game;
		//game.debug();
		game.play();
	}
	catch (std::exception e) {
		std::cerr << "\n\n\nErrore: " << e.what() << "\n\n\n";
	}
	return 0;
}
