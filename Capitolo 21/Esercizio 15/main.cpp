/*
* Capitolo 21 esercizio 15
* Fornisci una GUI all'esercizio precedente.
*/

/*
* Dobbiamo rappresentare graficamente i seguenti step:
* 1. Quante occorrenze ci sono di ship nel file? <- sostituisco con 'host'
* 2. Quale parola si ripete più spesso?
* 3. Qual'è la parola più lunga nel file?
* 4. Quale la più corta?
* 5. Lista di tutte le parole che iniziano con 's'
* 6. Lista di tutte le parole di 4 lettere
*/

#include <iostream>
#include <fstream>
#include "pulitore.h"
#include <map>
#include "Cap21Es15GUI.h"

int main() try {
	// creiamo la main finestra e passiamogli la mappa delle parole
	std::ifstream ifs{ "" };
	std::string nomefile{ "" };
	while (!ifs) {
		std::cout << "Nome del file di parole: ";
		std::cin >> nomefile;
		std::cout << std::endl;
		ifs.open(nomefile);
	}
	std::map<std::string, int>* mappa_di_parole = pulitore(ifs).get_map();
	ifs.close();
	// ora la main finestra avrà un tasto per gestire le pagine per mostrare i vari step di indagini nella mappa.
	Cap21Es15GUI win{ Point{10, 10}, 800, 600, "Capitolo 21 Esercizio 15", *mappa_di_parole };
	Fl::run();
	return 0;
}
catch (std::exception e) {
	std::cout << "\n\nEccezione: " << e.what() << std::endl;
}
catch (...) {
	std::cout << "\n\nErrore non gestito." << std::endl;
} 