/* Capitolo 24 Esercizio 8
* Anima l'eliminazione Gaussiana
*/

// l'idea è di creare un widget matrix che forma una 'matrice' di output textbox e delle funzioni per animare un cambio di valore nella matrice o lo scambio righe.
// Se creiamo una window con il widget in questione, dobbiamo creare dei metodi per gestire le animazioni
// gli indici della matrice e la matrice di widget nella window dovranno corrispondere
// bisogna lanciare al posto di Fl::run() un Fl::wait() per lanciare la grafica in un thread a parte, e metterla in attesa.
// successivamente possiamo reimpostare la grafica e aggiornarla con Fl::redraw()
// a questo punto lanciare un altro Fl::wait() o Fl::flush() per aggiornare.

#include <iostream>
//#include <sstream>
#include <vector>
//#include "../GUI/Graph.h"
//#include "../GUI/Window.h"
#include "../GUI/Point.h"
#include "WinMatrix.h"

using Matrix = std::vector<std::vector<double>>;
using Vector = std::vector<double>;
using Index = long;

const std::string MATRIXNAME{ "A" };
const std::string VECTORNAME{ "b" };

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

void elim_with_partial_pivot(Matrix& A, Vector& b, WinMatrix& win) {
	const Index n = A.size(); // sappiamo che la matrice è quadrata

	for (Index j = 0; j < n; ++j) {
		Index pivot_row = j;

		// guardiamo per un pivot migliore
		for (Index k = j + 1; k < n; ++k) {
			if (abs(A[k][j]) > abs(A[pivot_row][j])) pivot_row = k;
		}

		// scambio le righe se ci sono pivot migliori
		if (pivot_row != j) {
			for (Index i = 0; i < A.size(); ++i) {
				std::swap(A[j][i], A[pivot_row][i]);
			}
			win.swapRow(MATRIXNAME, j, pivot_row); // animazione
			std::swap(b[j], b[pivot_row]);
			win.swapRow(VECTORNAME, j, pivot_row); // animazione
		}

		// eliminazione
		for (Index i = j + 1; i < n; ++i) {
			const double pivot = A[j][j];
			if (pivot == 0) throw Elim_failure(j);
			const double mult = A[i][j] / pivot;
			// ciclo che sostituisce scale_and_add
			for (Index s = j; s < A[j].size(); ++s) {
				A[i][s] = A[i][s] * (-mult) + A[i][s];
				// impostazioni valori nella matrice grafica
				win.setMatrix(MATRIXNAME, i, s, A[i][s]);
			}
			b[j] -= mult * (b[j]);
			// aggiornamento vettore grafico
			win.setVector(VECTORNAME, j, b[j]);
		}
	}
}

Vector back_substitution(const Matrix& A, const Vector& b) {
	const Index n = A.size();
	Vector x(n);

	for (Index i = n - 1; i >= 0; --i) {
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

// classical Gaussian eliination
Vector classical_gaussian_elimination(Matrix A, Vector b, WinMatrix& win) {
	elim_with_partial_pivot(A, b, win);
	return back_substitution(A, b);
}

int main() {
	Matrix A(2);
	WinMatrix win(Point{ 200, 200 }, 350, 300, "Eliminazione Gaussiana");
	win.set_win_color(Graph_lib::Color::white);
	// aggiungi matrice alla finestra
	win.set_matrix_color(Graph_lib::Color::dark_blue);
	win.addMatrix(MATRIXNAME, 2, 2);

	for (Index i = 0; i < A.size(); ++i) {
		A[i].resize(2);
	}
	Vector b(2);
	// aggiungi vettore alla finestra
	win.set_matrix_color(Graph_lib::Color::dark_green);
	win.addVector(VECTORNAME, 2);
	win.show();
	A[0][0] = 0;
	A[0][1] = 1;
	b[0] = 5;
	A[1][0] = 1;
	A[1][1] = 0;
	b[1] = 6;
	// imposta valori nella matrice grafica
	win.setMatrix(MATRIXNAME, 0, 0, 0);
	win.setMatrix(MATRIXNAME, 0, 1, 1);
	win.setVector(VECTORNAME, 0, 5);
	win.setMatrix(MATRIXNAME, 1, 0, 1);
	win.setMatrix(MATRIXNAME, 1, 1, 0);
	win.setVector(VECTORNAME, 1, 6);

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
		std::cout << "\n\nVettore b:\n";
		std::cout << "{";
		for (double d : b) {
			std::cout << " " << d;
		}
		std::cout << " }\n";

		// passiamo la GUI per controllare le animazioni
		Vector result = classical_gaussian_elimination(A, b, win);
		win.set_matrix_color(Graph_lib::Color::dark_green);
		win.addVector("Result", 2);
		std::cout << "Operazione riuscita, risultato:\n";
		std::cout << "{";
		for (Index i = 0; i < result.size(); ++i) {
			std::cout << " " << result[i];
			win.setVector("Result", i, result[i]);
		}
		std::cout << " }\n";
	}
	catch (Elim_failure e) {
		std::cerr << "\n\n\nErrore di eliminazione all'indice " << e.what();
	}
	catch (Back_subst_failure e) {
		std::cerr << "\n\n\nErrore di sostituzione all'indice " << e.what();
	}

	return Fl::run();
}