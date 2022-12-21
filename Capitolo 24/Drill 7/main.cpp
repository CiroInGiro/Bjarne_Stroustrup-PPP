/* Capitolo 24 Drill 7
* Leggi 10 complex<double> da cin (si, cin supporta >> per complex) e mettili in un Matrix.
* Calcola e stampa la somma dei 10 numeri complessi.
*/

#include <iostream>
#include "../PPP2code/Matrix.h"
#include <complex>

int main() {
	using std::cin;
	using std::cout;
	using Numeric_lib::Matrix;

	Matrix<std::complex<double>, 1> mc(10);
	
	cout << "Mi servono 10 numeri complessi di cui calcolare la somma: ";

	for (int i = 0; i < mc.dim1(); ++i) {
		while (!(cin >> mc[i])) {
			cin.ignore(120, '\n');
			cin.clear();
			cout << "\nNumero complesso: ";
		}
	}

	std::complex<double> somma;

	for (int i = 0; i < mc.dim1(); ++i) {
		somma += mc[i];
	}

	cout << "\nLa somma dei numeri complessi inseriti: " << somma << std::endl;
}