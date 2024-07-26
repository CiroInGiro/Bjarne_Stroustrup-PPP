/* Capitolo 25 Esercizio 7
Scrivi i valori esadecimali da 0 a 400;
scrivi i valori esadecimali da -200 a 200.
*/

#include <iostream>

int main() {
	std::cout << "Numeri esadecimanli da 0 a 400:\n";

	for (unsigned int i = 0; i <= 400; ++i) {
		std::cout << std::showbase << std::hex << i << std::endl;
	}

	std::cout << "\n\n\n\nNumeri esadecimanli da -200 a 200:\n";

	for (signed int i = -200; i <= 200; ++i) {
		std::cout << std::showbase << std::hex << i << std::endl;
	}

	return 0;
}

// per i numeri negativi, esendo complementari dei numeri positivi, più sono piccoli
// più bit significativi saranno utilizzati.