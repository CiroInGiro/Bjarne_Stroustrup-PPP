/*
Capitolo 17 Esercizio 8
Ripeti l'esercizio 7 ma questa volata usa std::string invece dello heap.
std::string sa come utilizzare lo heap.
*/

#include <iostream>

int main(int argc, char** argv) {
	char ch{ ' ' };
	std::string testo{ "" };
	std::cout << "Scrivi quello che vuoti, per terminare inserisci il '!'" << std::endl;
	while (std::cin.get(ch) && ch != '!') { testo += ch; }
	std::cout << std::endl;
	std::cout << "Bene, hai terminato col '!'" << std::endl;
	std::cout << "Hai digitato: " << testo << std::endl;
	return 0;
}