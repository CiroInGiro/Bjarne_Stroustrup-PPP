/* Capitolo 25 Esercizio 06
Scrivi un ciclo infinito che sia difficile riconoscere come ciclo infinito.
È accettabile un ciclo che non è realmente infinito perché termina dopo aver consumato completamente alcune risorse. 
*/

#include <iostream>

int main() {
	
	// VS avvisa che il loop è infinito: cpu al 50%
	for (char c = 0; c < 150; ++c) {
		std::cout << "c = " << c << std::endl;
	}

	return 0;
}