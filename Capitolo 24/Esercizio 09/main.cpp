/* Capitolo 24 Esercizio 9
* Riscrivi la funzione non membro apply() che ritorna un matrix del tipo ritornato dalla funzione applicata;
* cioè apply(f, a) dovrebbe ritornare un Matrix<R> dove R è il tipo ritornato da f.
* Attenzione: la soluzione richiede informazioni sui templates non incluse in questo libro.
*/

#include "../PPP2code/Matrix.h"
#include "../PPP2code/MatrixIO.h"
#include <iostream>

namespace my {
	template<class R>
	Numeric_lib::Matrix<R> apply(R f(R), Numeric_lib::Matrix<R>& m) {
		Numeric_lib::Matrix<R> retVal(m.dim1());

		for (int i = 0; i < m.dim1(); ++i) {
			retVal[i] = f(m[i]);
		}

		return retVal;
	}
}

int f(int p) {
	return (p + 10);
}

int main() {
	Numeric_lib::Matrix<int> dm(5);
	Numeric_lib::Matrix<int> rm(5);

	for (int i = 0; i < dm.dim1(); ++i) {
		dm[i] = i * 2 - 1;
	}

	std::cout << "Stampo la matrice di esempio:" << std::endl;
	std::cout << dm << std::endl << std::endl;

	rm = my::apply(f, dm);

	std::cout << "Stampo la matrice di ritorno, la funzione f aggiunge 10 al parametro passato:\n\n";
	std::cout << rm << std::endl;

	return 0;
}