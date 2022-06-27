/*
Capitolo 18 Esercizio 7
Modifica la cat_dot precedente per prendere delle stringhe c-style come parametro e restituire una stringa c-style allocato nello heap.
Non usare funzioni dello standard library.
Testa queste funzioni con molte stringhe.
Assicurati di deallocare tutta la memoria che è stata allocata utilizzando new()
Confronta lo sforzo voluto per questo esercizio con quello voluto per gli esercizi 5 e 6.
*/

#include <iostream>

int char_count(const char* p) {
	if (p == nullptr) return 0;
	int retVal{ 0 };
	while (*p) { ++retVal; ++p; }
	return retVal;
}

int str_copy(const char* sorgente, char* destinazione) {
	int count{ 0 };
	while (*sorgente) {
		*destinazione = *sorgente;
		++sorgente;
		++destinazione;
		++count;
	}
	return count;
}

char* cat_dot(const char* s1, const char* s2, const char* sep) {
	int lunghezza = char_count(s1);
	lunghezza += char_count(s2);
	lunghezza += char_count(sep);
	char* retVal = new char[(lunghezza + 1)];
	int copie = str_copy(s1, retVal);
	copie += str_copy(sep, (retVal + copie));
	copie += str_copy(s2, (retVal + copie));
	*(retVal + copie) = '\0';
	return retVal;
}

int main(int argc, char** argv) {
	const char* stringa1{ "Carne" };
	const char* stringa2{ "Pesce" };
	const char* separatore{ ":" };
	char* risultato = cat_dot(stringa1, stringa2, separatore);
	std::cout << "Concatenamente delle c-style stringhe " << stringa1 << " e " << stringa2 << " col separatore c-style " << separatore << std::endl;
	std::cout << "Risultato: " << risultato << std::endl;
	delete[] risultato;
	return 0;
}