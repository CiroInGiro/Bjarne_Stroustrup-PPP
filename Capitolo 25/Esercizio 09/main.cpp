/* Capitolo 25 Esercizio 9
Senza utilizzare intestazioni standard (come<limits> ) o documentazione, 
calcola il numero di bit in un int e determina se char è firmato o non firmato nella tua implementazione. 
*/

// ad indicare il numero di bit c'è il fatto che arrivati al limite una unità in più
// ci darà zero per un intero non segnato e meno di zero se segnato

#include <iostream>

template<class A>
signed short bitcount(A t) {
	signed short count{ 0 };

	while (t > 1) {
		t /= 2;
		++count;
	}

	if (t % 2 == 1) ++count;

	return ++count;
}
/*
signed short bitcount(int i) {
	signed short count{ 0 };

	while (i > 1) {
		i /= 2;
		++count;
	}

	if (i % 2 == 1) ++count;

	return ++count;
}
*/

int main() {
	char c = 0;
	int i = 0;

	--c;
	if (c > 0) std::cout << "Char è un tipo non segnato, valore massimo di bit " << bitcount<char>(c) << std::endl;
	if (c < 0) std::cout << "Char è un tipo segnato, valore massimo di bit ";
	while (c < 0) --c;
	std::cout << bitcount<char>(c) << std::endl;

	--i;
	if (i > 0) std::cout << "Int è un tipo non segnato, valore massimo di bit " << bitcount<int>(i) << std::endl;
	if (i < 0) std::cout << "Int è un tipo segnato, valore massimo di bit ";
	while (i < 0) --i;
	std::cout << bitcount<int>(i) << std::endl;

	return 0;
}