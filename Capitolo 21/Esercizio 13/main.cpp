/*
Capitolo 21 Esercizio 13
Scrivi un programma per pulire un file di testo da utilizzare in un programma di interrogazioni parole;
questo sostituisce la punteggiatura con spazi bianchi, metti le parole tutte in caratteri minuscoli,
sostituisci don't con do not ecc... e rimuovi i plurali, ad esempio ships con ship.
Non essere ambizioso nel togliere i plurali, limitati a togliere le 's' finali.
Testa il programma in un vero file di testo di almeno 5000 parole.
*/

/*
1. eliminare la punteggiatura (bisogna crearsi una funzione per questo)
2. uso tolower() per mettere i caratteri in minuscolo funzione di std::cctype
3. sostituire le abbreviazioni: don't con do not
4. togliere i plurari con le 's finali
Per velocizzare il programma e ridurre le chiamate a funzioni o alla risorsa file, invece di leggere ed elaborare i singoli
caratteri per poi legarli in stringhe tenterò questo approccio:
1. leggo dallo stream file le stringhe separate dal carattere bianco come di default
2. tolgo la punteggiatura se presente
3. modifico la stringa se sono abbreviate
4. modifico la stringa se sono plurali
5. metto i caratteri in minuscolo
6. inserisco la stringa in un set<std::string> se mancante
*/

#include <iostream>
#include <fstream>
#include <set>
#include "pulitore.h"

int main(int argc, char* argv) {
	std::ifstream ifs{ "" };
	std::string nomefile{ "" };
	std::set<std::string>* set_di_parole;
	using std::cin;
	using std::cout;
	using std::endl;
	try {
		cout << "Capitolo 21 Esercizio 13:" << endl;
		cout << "Leggo le parole da un file di testo e le restituisco in minuscolo, senza punteggiatura;" << endl;
		cout << "cambio i plurali in singolari e tolgo le abbreviazioni." << endl;
		cout << "Dammi il nome del file da cui prendere il testo:" << endl;
		while (!ifs) {
			cout << "File formato testo (.txt): "; // ho usato ..\host_centralino.txt
			cin >> nomefile;
			cout << endl;
			ifs.open(nomefile);
		}
		// la classe pulitore deve prendere un input file stream e restituire un puntatore ad un set di stringhe.
		set_di_parole = pulitore(ifs).get_set();
		ifs.close();
		cout << "Elenco Parole in std::set<std::string>: " << endl;
		//auto inizio = set_di_parole->begin();
		//auto fine = set_di_parole->end();
		for (std::string s : *set_di_parole)
		{
			cout << s << endl;
		}
	}
	catch (...) {
		std::cout << "\n\nErrore non gestito.\n";
	}
}