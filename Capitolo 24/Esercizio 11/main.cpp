/* Capitolo 24 Esercizio 11
* Scrivi uno swap_columns() per abbinare swap_rows() da §24.5.3.
* Ovviamente, per farlo devi leggere e comprendere parte del codice della libreria Matrix esistente.
* Non preoccuparti troppo dell'efficienza: non è possibile far funzionare swap_columns() alla stessa velocità di swap_rows().
*/

#include "../PPP2code/Matrix.h"
#include "../PPP2code/MatrixIO.h"
#include <iostream>

// aggiungo la classe Matrix sotto un namespace diverso ed eredito la classe Matrix per aggiungergi la funzione membro swap_columns con gli stessi templates
namespace Numeric_lib2 {
	template<class T = double, int D = 1>
	class Matrix : public Numeric_lib::Matrix<T, D> {
	private:
		Matrix();
	};

	template<class T>
	class Matrix<T, 1> : public Numeric_lib::Matrix<T, 1>
	{
	public:
		Matrix(Numeric_lib::Index dim) : Numeric_lib::Matrix<T>(dim) {}
		void swap_columns(Numeric_lib::Index c1, Numeric_lib::Index c2) {
			if (c1 == c2) return; // nulla da fare
			std::swap((*this)[c1], (*this)[c2]);
		}
		~Matrix() { }
	};

	template<class T>
	class Matrix<T, 2> : public Numeric_lib::Matrix<T, 2> {
		public:
			Matrix(Numeric_lib::Index dim1, Numeric_lib::Index dim2) : Numeric_lib::Matrix<T, 2>(dim1, dim2) {}
			void swap_columns(Numeric_lib::Index c1, Numeric_lib::Index c2) {
				if (c1 == c2) return;
				for (Numeric_lib::Index row = 0; row < Numeric_lib::Matrix<T, 2>::dim1(); ++row) std::swap((*this)(row, c1), (*this)(row, c2));
			}
			~Matrix() { }
	};
}


int main() {
	using namespace Numeric_lib2; // dove si trova la classe Matrix con la funzione membro aggiunta swap_columns()
	
	// test prima con una matrice di una sola riga
	Matrix<double> m2(5);

	for (int i = 0; i < m2.dim1(); ++i) m2[i] = (i + 1);

	std::cout << "Matrice prima di scambiare le colonne 2 con 4:\n\n";
	std::cout << m2 << std::endl;
	m2.swap_columns(1, 3);
	std::cout << "\n\nMatrice dopo lo scambio:\n\n";
	std::cout << m2 << std::endl;

	// test della matrice bidimensionale
	Matrix<double, 2> m32(3, 5);

	for (int i = 0; i < m32.dim1(); ++i)
		for (int j = 0; j < m32.dim2(); ++j) 
			m32[i][j] = (m32.dim2() * i) + (j + 1);

	std::cout << "Matrice prima di scambiare le colonne 2 con 4:\n\n";
	std::cout << m32 << std::endl;
	m32.swap_columns(1, 3);
	std::cout << "\n\nMatrice dopo lo scambio:\n\n";
	std::cout << m32 << std::endl;

	return 0;
}