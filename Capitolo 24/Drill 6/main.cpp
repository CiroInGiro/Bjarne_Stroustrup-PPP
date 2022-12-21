/* Capitolo 24 Drill 6
* Calcola una tavola pitagorica per [0,n)*[0,m) e rappresentala come una matrice 2D.
* Prendi n e m da cin e stampa bene la tabella (supponiamo che m sia abbastanza piccolo da far stare i risultati su una riga).
*/

#include <iostream>
#include "../PPP2code/Matrix.h"

int main() {
	using Numeric_lib::Matrix;
	using std::cout;
	using std::cin;
	using std::endl;

	int n{ 0 }, m{ 0 };

	cout << "Inserisci i valori di riga e colonna:\n";
	
	std::cout << "\nInserisci il numero di righe: ";
	while (!(cin >> n) || (n <= 0)) {
		cout << "\nRiprova, un intero > 0: ";
		cin.clear();
		cin.ignore(120, '\n');
	}

	std::cout << "\nInserisci il numero di colonne: ";
	while (!(cin >> m) || (m <= 0)) {
		cout << "\nRiprova, un intero  > 0: ";
		cin.clear();
		cin.ignore(120, '\n');
	}

	Matrix<int, 2> tab(n, m);

	// Prepariamo l'intestazione di colonne
	for (int colonna = 0; colonna < tab.dim2(); ++colonna) {
		cout << "\t" << colonna;
	}

	// stampa i caporiga e i risultati delle moltiplicazioni
	for (int riga = 0; riga < tab.dim1(); ++riga) {
		cout << "\n" << riga;
		for (int colonna = 0; colonna < tab.dim2(); ++colonna) {
			cout << "\t" << (riga * colonna);
		}
	}
}