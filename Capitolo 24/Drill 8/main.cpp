/* Capitolo 24 Drill 8
* Leggi 6 int in un Matrix<int, 2> m(2,3) e stampali.
*/

#include <iostream>
#include "../PPP2code/Matrix.h"
#include "../PPP2code/MatrixIO.h"

int main() {
	using Numeric_lib::Matrix;
	using std::cin;
	using std::cout;

	Matrix<int, 2> m(2, 3);

	cout << "Dammi 6 interi per riempire la matrice " << m.dim1() << "x" << m.dim2() << ":\n";

	for (int r = 0; r < m.dim1(); ++r) {
		for (int c = 0; c < m.dim2(); ++c) {
			cout << "\nInserisci il valore da memorizzare alla posizione " << r << "x" << c << ": ";
			while (!(cin >> m[r][c])) {
				cout << "\nValore " << r << "x" << c << ": ";
				cin.ignore(120, '\n');
				cin.clear();
			}
		}
	}

	cout << "\n\nOra stampo la matrice di interi inseriti:\n";

	cout << m;
}