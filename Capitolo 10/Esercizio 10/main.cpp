/*
Capitolo 10 Esercizio 10
Aggiungi a calculator del capitolo 7 la possibilità di usare i comandi from x che legge l'input dal file x.
Aggiungi un comando to y per salvare l'output (sia output che error) nel file y.
Scrivi un insieme di test prendendo spunto dal paragrafo 7.3 e usalo per testare calculator.
Discuti come vorresti usare questi comandi per il testing.
*/

/*
- Voglio che il programma utilizzi in ogni caso l'output su console ma con l'attivazione del salvataggio
su file, i risultati saranno anche salvati su file.
Saranno preparati i test del paragrafo 7.3 più dei nuovi per le nuove funzioni
più gli stessi test con l'attivazione dell'output rediretto.
Una cosa interessante è dare in input da file il comando di leggere l'input da file,
prevdedo che il nuovo file venga aperto e si continua da lì, a meno che non si preveda una 
funzione ricorsiva che apra un nuovo stream e alla fine dello stesso si ritorna allo stream precedente.
- ho deciso di usare uno stream di output nella classe calculation e uno stream di input nella classe Toke_stream:
quando il file è in errore Token_stream torna a leggere dallo standard input.
- Se nel file si incontra la richiesta di aprire un altro file bisogna ritornare un errore che lo stream da file è già utilizzato.
*/

#include "Calculator.h"
#include <iostream>
#include <fstream>


int main(int argc, char* argv[]) {
	Calculation::Calculator calc;

	try {
		calc.stampa_guida();
		calc.calculate();
	}
	catch (Calculation::Error e) {
		std::cerr << "\n\n\nErrore: " << e.what() << "\n\n\n";
	}
	catch (...) {
		std::cerr << "Boh...";
	}

	return 0;
}