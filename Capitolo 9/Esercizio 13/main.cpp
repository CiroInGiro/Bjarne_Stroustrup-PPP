/*
Capitolo 9 Esercizio 13
Disegna e implementa una classe di numeri razionali, Rational.
Un numero razionale ha 2 numeri, un numeratore e un denominatore, ad esempio 5/6 (5 sesti, anche conosciuto come circa .83333).
Gradati la definizione se ne hai bisogno.
Provvedi all'assegnazione, addizione, sottrazione, moltiplicazione, divisione e all'operatore di uguaglianza.
Provvedi anche alla conversione in double.
Perché qualcuno dovrebbe usare una classe per i numeri razionali?
*/
// Una classe che gestisca i numeri razionali è sicuramente utile in un programma matematico per il calcolo di numeri razionali o semplificazioni nelle equazioni, lo potremmo integrare in calculator ad esempio.
// Potrebbe anche servire per la rappresentazione di alcuni numeri più vicino alla realtà, come le dimensioni in pollici dei diametri in rubinetteria, (3/4 di pollice).

#include "Rational.h"
#include <iostream>

int main(int argc, char* argv) {
	Rational TreMezzi{ 3, 2 };
	Rational QuattroNoni{ 4, 9 };
	Rational OttoNoni{ 8, 9 };
	Rational Due(2);

	Rational risultato = TreMezzi * QuattroNoni / OttoNoni * Due;

	std::cout << "Frazioni:" << std::endl;
	std::cout << "3/4 * 4/9 / 8/9 * 2 = " << risultato.frazione();

	return 0;
}