/* Capitolo 24 Esercizio 12
* Implementa
* Matrix<double> operator*(Matrix<double, 2>&, Matrix<double>&)
* e
* Matrix<double, N> operator+(Matrix<double, N>&, Matrix<double, N>&)
* se ne hai bisogno, cerca la definizione matematica in un libro.
*/

/*
* operator* : Forse possiamo utilizzarla per la combinazione lineare, significa che il numero di righe della matrice dovrà essere uguale al numero di colonne della matrice 1 dimensione.
* Ogni valore della matrice 1d serve a scalare un vettore contenuto nella matrice 2d.
*/

/*
* operator+ : Dovrà sommare due matrici e restituire la matrice che ha la somma degli elementi di ogni matrice con stessi indici, le 3 matrici saranno di uguale dimensione.
*/

#include "../PPP2code/Matrix.h"
#include "../PPP2code/MatrixIO.h"
#include <iostream>
#include <random>

using namespace Numeric_lib;

Matrix<double> operator*(Matrix<double, 2>& matrix_2d, Matrix<double>& matrix_1d);

template<int N>
Matrix<double, N> operator+(Matrix<double, N>& A, Matrix<double, N>& B);

int main() {
	Matrix<double, 2> m2d(3, 5); // contiene 3 vettori da 5 elementi
	Matrix<double> m1d(3); // contiene 3 valori da scalare ognuno per un vettore
	Matrix<double> r1d(5); // vettore ricavato dalla somma di tutti i vettori contenuti nella matrice e scalati coi valori della matrice ad 1 dimensione.
	std::default_random_engine rnd_engine; // motore per generare un insieme di numeri
	std::uniform_real_distribution<double> rnd_distr(0.00, 5.99); // funzione per la distribusione di numeri double
	
	// riempo le matrici con numeri casuali
	for (int r = 0; r < m2d.dim1(); ++r)
		for (int c = 0; c < m2d.dim2(); ++c)
			m2d(r, c) = rnd_distr(rnd_engine);

	for (int i = 0; i < m1d.dim1(); ++i) m1d(i) = rnd_distr(rnd_engine);

	std::cout << "Matrice di vettori (1 vettore di valori per riga):\n";
	std::cout << m2d << std::endl;
	std::cout << "Vettore dei valori scalari:\n";
	std::cout << m1d << std::endl;

	r1d = m2d * m1d;
	std::cout << "Combinazione tra matrice e vettore:\n";
	std::cout << r1d << std::endl;

	std::cout << "\n\n\nOra proviamo l'operatore+, ho queste 2 matrici:\n";
	Matrix<double, 2> a(4, 4);
	Matrix<double, 2> b(4, 4);

	// riempo sempre con numeri casuali
	for (int r = 0; r < a.dim1(); ++r)
		for (int c = 0; c < a.dim2(); ++c) {
			a(r, c) = rnd_distr(rnd_engine);
			b(r, c) = rnd_distr(rnd_engine);
		}
	std::cout << "Matrice a:\n";
	std::cout << a << std::endl;
	std::cout << "\n\nMatrice b:\n";
	std::cout << b << std::endl;

	std::cout << "\n\nQuesta la matrice somma:\n";
	Matrix<double, 2> somma(4, 4);
	somma = a + b;
	std::cout << somma << std::endl;

	return 0;
}

Matrix<double> operator*(Matrix<double, 2>& matrix_2d, Matrix<double>& matrix_1d) {
	// la matrice a 2 o più dimmensioni è considerata un insieme di vettori.
	// la matrice a 1 dimensione (vettore) è l'insieme dei valori da scalare:
	// Ogni elemento del vettore sarà moltiplicato per il suo scalare.
	// Gli elementi di ogni vettore scalato saranno sommati di volta in volta al vettore risultante.
	
	Matrix<double> result(matrix_2d.dim2());

	if (matrix_2d.dim1() != matrix_1d.dim1()) return result; // combinazione non possibile: i valori da scalare non sono uguali al numero di vettori presenti in matrice

	// inizializzo la matrice risultante
	for (int i = 0; i < result.dim1(); ++i) result(i) = 0.00;

	// iv: indice dei vettori
	for (int iv = 0; iv < matrix_2d.dim1(); ++iv) {
		// ic: indice degli elementi di un vettore
		for (int ic = 0; ic < matrix_2d.dim2(); ++ic) {
			// iv è anche l'indice degli scalari perché ogni vettore ne ha uno
			result(ic) += (matrix_2d(iv, ic) * matrix_1d(iv));
		}
	}
	
	return result;
}

template<int N>
Matrix<double, N> operator+(Matrix<double, N>& A, Matrix<double, N>& B) {
	// primo creo la matrice di ritorno copiandola da una dei parametri (così avrò lo stesso numero di righe e colonne).
	Matrix<double, N> retVal(A);

	// ora sommo i valori della seconda matrice
	for (int r = 0; r < retVal.dim1(); ++r)
		for (int c = 0; c < retVal.dim2(); ++c)
			retVal(r, c) += B(r, c);

	return retVal;
}