/* Capitolo 25 Esercizio 8
Scrivi i valori numerici di ogni carattere della tua tastiera.
*/

#include <iostream>

int main() {

	for (unsigned int i = 0; i < 255; ++i) {
		std::cout << "Carattere '" << char(i) << "' = valore " << i << std::endl;
	}

	return 0;
}