/* Capitolo 24 Esercizio 2
* Rifai l'esercizio 1 ma con una funzione oggetto invece della funzione.
* Suggerimento: Matrix.h contiene degli esempi.
*/

#include "../PPP2code/Matrix.h"
#include <iostream>
#include "../PPP2code/MatrixIO.h"

// sostituisce triple() del precedente esercizio
class fobj {
public:
	fobj() : molt{ 1 } {}
	fobj(const int& m) : molt{ m } {};
	int operator()(int& i) {
		int retVal = i * molt; // apply()
		i *= molt; // per Matrix.apply()
		return retVal;
	}
private:
	int molt;
};

int main() {
	Numeric_lib::Matrix<int> a(6);

	std::cout << "Memorizzo i seguenti valori in Matrix<int, 1>:\n";
	for (int i = 0; i < a.dim1(); ++i) {
		a[i] = (i + 1);
		std::cout << "Valore nella posizione " << i << ": " << a[i] << std::endl;
	}
	Numeric_lib::Matrix<int> a_copy = a;

	std::cout << "uso Matrix<int, 1>.apply(f) per far triplicare i valori nella matrice da f e la ristampo: \n";
	//a.apply(f1);
	a.apply(fobj(3));
	std::cout << "\n\n" << a << "\n";

	//Numeric_lib::Matrix<int> b = apply(f2, a_copy);
	Numeric_lib::Matrix<int> b = apply(fobj(3), a_copy);
	std::cout << "uso apply(f, Matrix<int, 1>) per riempire una nuova matrice coi valori triplicati:\n";
	std::cout << "\n\n" << b << "\n";
}
