/*
Capitolo 18 Eserciizo 5
Scrivi una funzione string cat_dot(const string& s1, const string& s2) che concatena due stringhe con un punto.
As esempio cat_dot("Niels", "Bohr") restituisce "Niels.Bohr"
*/

#include <iostream>

std::string cat_dot(const std::string& s1, const std::string& s2) {
	return s1 + "." + s2;
}

int main(int argc, char** argv) {
	std::string risultato = cat_dot("Mani", "Piedi");
	std::cout << "Concatenzazione di Mani e Piedi, risultato: " << risultato << std::endl;
	return 0;
}