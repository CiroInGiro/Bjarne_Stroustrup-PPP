/*
Capitolo 21 Esercizio 5
Cosa dovremmo fare se non possiamo restituire end() per indicare che non l'abbiamo trovato?
Ridisegna e reimplementa find() e count() per prendere iteratori del primo e dell'ultimo elemento.
Confronta il risultato con la versione standard.
*/

/*
In questo caso andremmo a lavorare su un range chiuso: [first, last]
Potremmo gestire il caso in cui l'elemento manca con una eccezione ma le eccezione rallentano e devono essere gestite
Potremmo restituire un puntatore dello stesso tipo anzicchè il tipo a valore e imporlo in modo che un puntatore nullo significherebbe non trovato
Potremmo far decidere all'utente cosa vuole essere restituito come alternativa in caso di insuccesso, in modo da controllare i valori e la funzione sarebbe sempre valida
Possiamo quindi prendere un parametro in più bool, occupa poco e indica i 2 casi possibili, trovato e non trovato.
Siccome però count restituisce le occorrenze possiamo usare 0 che indica 0 occorrenze e va comunque bene
Siccome find restituisce un iteratore al valore trovato potremmo semplicemente restituire un iteratore inzializzato vuoto, l'utente dovrà controllare la validità dell'iteratore
*/

#include <iostream>
#include <vector>

namespace es5 {
	template<class It, class T>
	// requires Input_iterator<IT>()
	int count(It first, It last, const T& val) {
		int retVal{ 0 }; // non trovato
		while (first != last) { // con questo confronto andrà bene anche per gli iteratori delle liste, non random al posto di usare (first < last)
			if (*first == val) ++retVal;
			++first;
		}
		if (*last == val) ++retVal; // controllo anche dell'ultimo valore
		return retVal;
	}

	template<class It, class T>
	It find(It first, It last, const T& val) {
		It retVal; // non riesco ad avere una valore di inizializzazione nullo
		while (first != last) {
			if (*first == val) return first;
			++first;
		}
		if (*first == val) return first; // first e last sono uguali 
		return ++first; // ritorno un fuori range che controlla l'utente a seconda del tipo di contenitore
	}
}

int main(int argc, char** argv) {
	std::vector<int> vi{ 2, 10, 9, 3, 6, 3, 76, 9, 6, 3, 2, 1, 10, 10, 10, 12 };
	std::cout << "Vettore vi: ";
	for (auto val : vi) std::cout << val << " ";
	std::cout << std::endl;
	int num3 = es5::count(vi.begin(), (vi.end()-1), 3);
	std::cout << "Il numero 3 è presente " << num3 << " volte\n";
	int num10 = es5::count(vi.begin(), (vi.end()-1), 10);
	std::cout << "Il numero 10 è presente " << num10 << " volte\n";
	std::vector<int>::iterator ii = es5::find(vi.begin(), (vi.end() - 1), 12);
	if (ii != vi.end()) std::cout << "\nIl numero 12 è stato trovato.\n"; else std::cout << "\nIl numero 12 manca.\n";
	ii = es5::find(vi.begin(), (vi.begin() + 4), 99);
	if (ii != (vi.begin() + 4 + 1)) std::cout << "\nIl numero 99 è stato trovato tra i primi 5.\n"; else std::cout << "\nIl numero 99 manca fra i primi 5.\n";
	ii = es5::find(vi.begin(), (vi.begin() + 1), 9);
	if (ii != (vi.begin() + 1 + 1)) std::cout << "\nIl numero 9 è stato trovato tra i primi 2.\n"; else std::cout << "\nIl numero 9 manca fra i primi 2.\n";

	return 0;
}

/*
Nello standard template library si usa un range aperto a destra e questo permette che il puntatore finale del range sia anche il puntatore di controllo per l'utente, un dato in comune;
diversamente l'utente della funzione dovrà crearsi un puntatore in più, specie per le liste o mappe che punta al successivo dell'ultimo nel range per poterlo confrontarlo con quello restituito dalla funzione.
*/