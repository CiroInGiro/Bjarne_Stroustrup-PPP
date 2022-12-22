/* Capitolo 24 Esercizio 7
* Riscrivi il programma eliminazione Gaussiana senza l'uso della libreria di Matrici.
* dunque usa gli array incorporati o vettori al posto delle matrici.
*/

#include <iostream>
#include <sstream>
//#include "../PPP2code/Matrix.h"
//#include "../PPP2code/MatrixIO.h"
#include <vector>

//using Matrix = Numeric_lib::Matrix<double, 2>;
//using Vector = Numeric_lib::Matrix<double, 1>;
//using Numeric_lib::Index;

using Matrix = std::vector<std::vector<double>>;
using Vector = std::vector<double>;
using Index = long;

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

void elim_with_partial_pivot(Matrix& A, Vector& b) {
	const Index n = A.size(); // sappiamo che la matrice è quadrata

	for (Index j = 0; j < n; ++j) {
		Index pivot_row = j;

		// guardiamo per un pivot migliore
		for (Index k = j + 1; k < n; ++k) {
			if (abs(A[k][j]) > abs(A[pivot_row][j])) pivot_row = k;
		}

		// scambio le righe se ci sono pivot migliori
		if (pivot_row != j) {
			//A.swap_rows(j, pivot_row);
			for (Index i = 0; i < A.size(); ++i) {
				std::swap(A[j][i], A[pivot_row][i]);
			}
			std::swap(b[j], b[pivot_row]);
		}

		// eliminazione
		for (Index i = j + 1; i < n; ++i) {
			const double pivot = A[j][j];
			if (pivot == 0) throw Elim_failure(j);
			const double mult = A[i][j] / pivot;
			//A[i].slice(j) = Numeric_lib::scale_and_add(A[j].slice(j), -mult, A[i].slice(j));
			// ciclo che sostituisce scale_and_add
			for (Index s = j; s < A[j].size(); ++s) {
				A[i][s] = A[i][s] * (-mult) + A[i][s];
			}
			b[j] -= mult * (b[j]);
		}
	}
}

Vector back_substitution(const Matrix& A, const Vector& b) {
	const Index n = A.size();
	Vector x(n);

	for (Index i = n - 1; i >= 0; --i) {
		//double s = b(i) - Numeric_lib::dot_product(A[i].slice(i + 1), x.slice(i + 1));
		// sostutuisce dot_product
		double dot{ 0 };
		for (Index s = (i + 1); s < A[i].size(); ++s) {
			dot += (A[i][s] * x[s]);
		}
		double s = b[i] - dot;
		if (double m = A[i][i]) x[i] = s / m;
		else throw Back_subst_failure(i);
	}
	return x;
}

Vector classical_gaussian_elimination(Matrix A, Vector b) {
	//classical_elimination(A, b);
	elim_with_partial_pivot(A, b);
	return back_substitution(A, b);
}

int main() {
	Matrix A(2);
	for (Index i = 0; i < A.size(); ++i) {
		A[i].resize(2);
	}
	Vector b(2);

	A[0][0] = 0;
	A[0][1] = 1;
	b[0] = 5;
	A[1][0] = 1;
	A[1][1] = 0;
	b[1] = 6;

	try {
		std::cout << "Matrice A:\n";
		std::cout << "{\n";
		for (Vector R : A) {
			std::cout << " {";
			for (double c : R) {
				std::cout << " " << c;
			}
			std::cout << " }\n";
		}
		std::cout << "}\n";
		std::cout << "Vettore b:\n";
		std::cout << "{";
		for (double d : b) {
			std::cout << " " << d;
		}
		std::cout << " }\n";

		Vector result = classical_gaussian_elimination(A, b);
		std::cout << "Operazione riuscita, risultato:\n";
		std::cout << "{";
		for (double d : result) {
			std::cout << " " << d;
		}
		std::cout << " }\n";
	}
	catch (Elim_failure e) {
		std::cerr << "\n\n\nErrore di eliminazione all'indice " << e.what();
	}
	catch (Back_subst_failure e) {
		std::cerr << "\n\n\nErrore di sostituzione all'indice " << e.what();
	}

	return 0;
}