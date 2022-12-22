/* Capitolo 24 esercizio 4
* Rendi il programma Eliminazione Gaussian funzionante;
* ovvero completalo, farlo compilare e testalo con un semplice esempio.
*/

#include <iostream>
#include <sstream>
#include "../PPP2code/Matrix.h"
#include "../PPP2code/MatrixIO.h"

using Matrix = Numeric_lib::Matrix<double, 2>;
using Vector = Numeric_lib::Matrix<double, 1>;
using Numeric_lib::Index;

class Elim_failure {
public:
	Elim_failure() : err{ 0 } {}
	Elim_failure(Index& i) : err{ i } {}
	Index what() { return err; }
private:
	Index err;
};

class Back_subst_failure {
public:
	Back_subst_failure() : err{ 0 } {}
	Back_subst_failure(const Index& i) : err{ i } {}
	Index what() { return err; }
private:
	Index err;
};

void classical_elimination(Matrix& A, Vector& b) {
	const Index n = A.dim1();

	// attraversa dalla 1a colonna alla successiva dopo l'ultima
	// riempendo di zero tutti gli elementi lungo la diagonale
	for (Index j = 0; j < n - 1; ++j) {
		const double pivot = A(j, j);
		
		if (pivot == 0) throw Elim_failure(j);

		// riempo con zeri gli elementi sotto la diagonale sulla i-esima riga
		for (Index i = j + 1; i < n; ++i) {
			const double mult = A(i, j) / pivot;
			A[i].slice(j) = scale_and_add(A[j].slice(j), -mult, A[i].slice(j));
			b(i) -= mult * b(j); // applichiamo la corrispondente modifica anche in b
		}
	}
}

Vector back_substitution(const Matrix& A, const Vector& b) {
	const Index n = A.dim1();
	Vector x(n);

	for (Index i = n - 1; i >= 0; --i) {
		double s = b(i) - Numeric_lib::dot_product(A[i].slice(i + 1), x.slice(i+1));
		
		if (double m = A(i, i)) x(i) = s / m;
		else throw Back_subst_failure(i);
	}
	return x;
}

Vector classical_gaussian_elimination(Matrix A, Vector b) {
	classical_elimination(A, b);
	return back_substitution(A, b);
}

int main() {
	Matrix A(2,2);
	Vector b(2);

	A(0, 0) = 9;
	A(0, 1) = 3;
	b(0) = 60;
	A(1, 0) = 3;
	A(1, 1) = 18;
	b(1) = 9;

	try {
		std::cout << "Matrice A:\n";
		std::cout << A << std::endl;
		std::cout << "Vettore b:\n";
		std::cout << b << std::endl;

		Vector result = classical_gaussian_elimination(A, b);
		std::cout << "Operazione riuscita, risultato:\n";
		std::cout << result << std::endl;
	}
	catch (Elim_failure e) {
		std::cerr << "\n\n\nErrore di eliminazione all'indice " << e.what();
	}
	catch (Back_subst_failure e) {
		std::cerr << "\n\n\nErrore di sostituzione all'indice " << e.what();
	}

	return 0;
}