/*
Capitolo 18 Esercizio 6
Modifica il precedente esercizio in modo che cat_dot prenda un terzo parametro come stringa di separazione oltre al punto.
*/

#include <iostream>

std::string cat_dot(const std::string& s1, const std::string& s2, const std::string& sep = ".") {
	return s1 + sep + s2;
}

int main(int argc, char** argv) {
	const std::string stringa1{ "Carne" };
	const std::string stringa2{"Pesce"};
	const std::string separatore{ "-" };
	std::string risultato = cat_dot(stringa1, stringa2, separatore);
	std::cout << "Concatenamento di " << stringa1 << " e " << stringa2 << " utilizzando " << separatore << " : " << risultato << std::endl;
	return 0;
}