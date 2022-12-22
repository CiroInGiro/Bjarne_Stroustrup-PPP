/* Capitolo 24 ercizio 6
* Nell'esempio dell'eliminazione Gaussiana, sostituisci le oprtazioni sui vettori dot_product() e scale_and_add() con dei cicli.
* Testa e commenta la chiarezza del codice.
*/

// i cicli e le operazioni che fanno le funzioni scale_and_add() e dot_product() creano sicuramente confusione,
// sopratutto perché si trovano nidificati in un altro ciclo e poi per gli indici che si ripetono nei vettori assieme al for più esterno.
// tutti questi indici non aiutano a spiegare in maniera lineare l'operazione che si vuole compiere.

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

void elim_with_partial_pivot(Matrix& A, Vector& b) {
	const Index n = A.dim1();

	for (Index j = 0; j < n; ++j) {
		Index pivot_row = j;

		// guardiamo per un pivot migliore
		for (Index k = j + 1; k < n; ++k) {
			if (abs(A(k, j)) > abs(A(pivot_row, j))) pivot_row = k;
		}

		// scambio le righe se ci sono pivot migliori
		if (pivot_row != j) {
			A.swap_rows(j, pivot_row);
			std::swap(b(j), b(pivot_row));
		}

		// eliminazione
		for (Index i = j + 1; i < n; ++i) {
			const double pivot = A(j, j);
			if (pivot == 0) Numeric_lib::error("Non si può risolvere: pivot==0");
			const double mult = A(i, j) / pivot;
			//A[i].slice(j) = Numeric_lib::scale_and_add(A[j].slice(j), -mult, A[i].slice(j));
			// ciclo che sostituisce scale_and_add
			for (Index s = j; s < A[j].dim1(); ++s) {
				A(i, s) = A(i, s) * (-mult) + A(i, s);
			}
			b(j) -= mult * (b(j));
		}
	}
}

Vector back_substitution(const Matrix& A, const Vector& b) {
	const Index n = A.dim1();
	Vector x(n);

	for (Index i = n - 1; i >= 0; --i) {
		//double s = b(i) - Numeric_lib::dot_product(A[i].slice(i + 1), x.slice(i + 1));
		// sostutuisce dot_product
		double dot{ 0 };
		for (Index s = (i + 1); s < A[i].dim1(); ++s) {
			dot += (A(i, s) * x(s));
		}
		double s = b(i) - dot;
		if (double m = A(i, i)) x(i) = s / m;
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
	Matrix A(2, 2);
	Vector b(2);

	A(0, 0) = 0;
	A(0, 1) = 1;
	b(0) = 5;
	A(1, 0) = 1;
	A(1, 1) = 0;
	b(1) = 6;

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