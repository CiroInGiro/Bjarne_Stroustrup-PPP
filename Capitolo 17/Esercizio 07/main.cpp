/*
Capitolo 17 Esercizio 7
Scrivi un programa che legge caratteri da cin e li metta in un vettore allocato nello heap.
Leggi gli individuali caratteri fino al punto esclamativo '!'
Non usare std::string
Non preoccuparti di esaurire la memoria.
*/

#include <iostream>

int main(int argc, char** argv) {
	unsigned int num_char{ 0 };
	const int blocco{ 10 };
	unsigned int asize{ blocco };
	char* ach = new char[asize];
	std::cout << "Scrivi quello che vuoti, per terminare inserisci il '!'" << std::endl;
	while (std::cin.get(ach[num_char]) && ach[num_char] != '!') {
		if (num_char == (asize - 1)) {
			asize += blocco;
			char* old = ach;
			ach = new char[asize];
			for (unsigned int i = 0; i <= num_char; ++i) {
				ach[i] = old[i];
			}
			delete[] old;
		}
		++num_char;
	}
	ach[num_char] = '\0';
	std::cout << std::endl;
	std::cout << "Bene, hai terminato col '!'" << std::endl;
	std::cout << "Hai digitato: " << ach << std::endl;
	delete[] ach;
	return 0;
}