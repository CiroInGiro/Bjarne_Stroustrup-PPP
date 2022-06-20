/*
Capitolo 9 Esercizio 13
Disegna e implementa una classe di numeri razionali, Rational.
Un numero razionale ha 2 numeri, un numeratore e un denominatore, ad esempio 5/6 (5 sesti, anche conosciuto come circa .83333).
Guardati la definizione se ne hai bisogno.
Provvedi all'assegnazione, addizione, sottrazione, moltiplicazione, divisione e all'operatore di uguaglianza.
Provvedi anche alla conversione in double.
Perché qualcuno dovrebbe usare una classe per i numeri razionali?
*/
// Una classe che gestisca i numeri razionali è sicuramente utile in un programma matematico per il calcolo di numeri razionali o semplificazioni nelle equazioni, lo potremmo integrare in calculator ad esempio.
// Potrebbe anche servire per la rappresentazione di alcuni numeri più vicino alla realtà, come le dimensioni in pollici dei diametri in rubinetteria, (3/4 di pollice).

// PS: all'epoca che fu fatto l'esercizio  non è stato testato e vi avviso che da proprio i numeri, solo che non sono quelli giusti!
// Ad esempio il minimo comune multiplo è calcolato ma i numeratori non vengono adattati.

#include "Rational.h"
#include <iostream>

int main(int argc, char* argv) {
	Rational TreMezzi{ 3, 2 };
	Rational QuattroNoni{ 4, 9 };
	Rational OttoNoni{ 8, 9 };
	Rational Due(2);

	Rational risultato = (TreMezzi * QuattroNoni) / (OttoNoni * Due); // le parentesi servono per dare precedenza all'operatore *

	std::cout << "Frazioni:" << std::endl;
	std::cout << "3/2 * 4/9 / 8/9 * 2 = " << risultato.frazione();

	return 0;
}