/* Capitolo 26 Esercizio 7
* Testa "editor di testo semplice" dal capitolo 20.6
*/

/* 
* Ho chiuso le funzioni nella classe Document. Il file preso è quello modificato all'esercizio 10 del Capitolo 20.
* Sono riscritte cambiando qualche nome ma le funzioni sono quelle dell'esempio del libro.
* 1. Guardando il codice credo che ci sia un bug quando si passa alla funzione count_words_white
* una stringa di caratteri bianchi che contiene uno o più caratteri uguali: dovrebbe contare in più le parole quanti i caratteri duplicati.
* 2. La funzione find_and_replace era incompleta e anche da controllare, ad esempio p non viene usato.
* 3. quando isalnum e isalpha controllano un carattere deve essere nel range -1 e 255 (in count_words_white)
*/

#include "Document.h"
#include <fstream>

int main() {
	// Iniziamo col caricare un file di testo su cui lavorare: main.cpp ad esempio
	std::ifstream file_cpp("main.cpp");
	//std::ifstream file_cpp("file_test.txt");
	Document main;

	if (!file_cpp.good()) return 1;

	while (!file_cpp.eof()) file_cpp >> main;

	// stampo il file caricato come primo test
	std::cout << "*** File letto: ***\n\n";
	main.print();
	std::cout << std::endl << "*** *** ***" << std::endl << std::endl;
	// OK

	// conto quanti caratteri ci sono
	std::cout << "*** Caratteri nel documento ***\n";
	std::cout << "Il documento contiene " << main.count_chars() << " caratteri compresi quelli speciali.";
	std::cout << std::endl << "*** *** ***\n\n";
	// non sono contati i caratteri Carrier Return ma perché non usati OK
	
	// conto quante parole tra spazi ci sono
	std::cout << "*** Parole nel documento ***\n";
	std::cout << "Il documento contiene " << main.count_words_white() << " parole di caratteri alfanumerici.";
	std::cout << std::endl << "*** *** ***\n\n";
	// Prende i caratteri alfanumerici e scarta il resto ma count_words_white diventano 3 parole. OK
	// Se alla parola non segue un carattere bianco non viene contata KO

	// conto quante parole tra spazi definiti ci sono
	std::cout << "*** Parole nel documento ***\n";
	std::cout << "Il documento contiene " << main.count_words_white(" \n\n") << " parole tra i caratteri ' ' e '\\n'.";
	std::cout << std::endl << "*** *** ***\n\n";
	// Se non ci sono caratteri bianchi non conta l'unica parola che c'è KO

	// conto quante parole tra spazi ci sono formate da soli caratteri dell'alfabeto
	std::cout << "*** Parole nel documento ***\n";
	std::cout << "Il documento contiene " << main.count_words_alpha() << " parole di sole lettere.";
	std::cout << std::endl << "*** *** ***\n\n";
	// Se non ci sono caratteri bianchi non conta l'unica parola che c'è KO

	// cancello le prime due righe
	std::cout << "*** cancello le prime 2 righe ***\n";
	main.erase_line(0);
	main.erase_line(0);
	main.print();
	std::cout << std::endl << "*** *** ***" << std::endl << std::endl;
	// OK

	std::cout << "*** cerco la parola erase ***\n";
	Text_Iterator t = main.find_text(main.begin(), main.end(), "erase");
	if (t != main.end()) std::cout << "erase trovato." << std::endl;
	else std::cout << "erase non trovato.\n";
	std::cout << std::endl << "*** *** ***" << std::endl << std::endl;
	// OK

	std::cout << "*** sostituisco erase con 5 '-' ***\n";
	t = main.find_and_replace(main.begin(), main.end(), "erase", "-----");
	if (t != main.end()) std::cout << "erase trovato." << std::endl;
	else std::cout << "erase non trovato.\n";
	std::cout << "Ristampo il documento:\n";
	main.print();
	std::cout << std::endl << "*** *** ***" << std::endl << std::endl;
	// Avviene la sostituzione solo alla prima occorrenza ma va bene se vogliamo chiedere conferma di sostituzione
	// ad ogni riscontro OK
	// La funzione è comunque incompleta, bisogna prevedere quando la stringa da sostituire e la nuova sono di dimensioni diverse.
	
	return 0;
}