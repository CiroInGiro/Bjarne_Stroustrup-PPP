/* Capitolo 24 Drill 5
* Chiedi 10 valori in virgola mobile in input e riempi una matrice di 10 double.
* Matrix non ha push_back() quindi attenzionne a gestire un numero sbagliato di double.
* Stampa la matrice.
*/

#include <iostream>
#include "../PPP2code/Matrix.h"

int main() {
	using Numeric_lib::Matrix;
	using std::cout;
	using std::cin;
	using std::endl;

	Matrix<double> md(10);

	cout << "Dammi 10 numeri in virgola mobile per riempire la matrice:\n";
	int i = 0;
	while (i < md.dim1()) {
		cout << endl << "Inserisci l'elemento " << (i + 1) << " di 10: ";
		if ((cin >> md[i])) {
			++i;
		}
		else {
			cin.clear();
			cin.ignore(120, '\n');
			cout << "\nRiprova: ";
		}
	}

	cout << "\n\nStampo la matrice inserita:\n";

	for (int i = 0; i < md.dim1(); ++i) {
		cout << "Elemento alla posizione " << i << " vale " << md[i] << endl;
	}
}