/*
Scrivi una funzione char* findx(const char* s, const char* x) che trova la prima occorrenza della c-style stringa x nella c-style stringa s
*/

#include <iostream>

char* findx(const char* s, const char* x) {
	int num_char{ 0 };
	while (x[num_char]) ++num_char;
	++num_char;
	char* retVal = new char[num_char];
	int is{ 0 }, ix{ 0 };
	while (s[is]) {
		while (s[is] == x[ix] && ix < (num_char-1)) {
			retVal[ix] = s[is];
			++is;
			++ix;
		}
		if (ix == num_char-1) {
			retVal[ix] = '\0';
			return retVal;
		}
		else ix = 0;
		++is;
	}
	return nullptr;
}

int main(int argc, char** argv) {
	char testo[]{ "Questa frase contiene la parola cane nella variabile testo." };
	char trova[]{ "cane" };
	char* dove = findx(testo, trova);
	std::cout << "Testo in cui cercare: " << testo << std::endl;
	std::cout << "Parola da cercare: " << trova << std::endl;
	if (dove) std::cout << "Ho trovato: " << dove << std::endl;
	else std::cout << "Non ho trovato nessuna occorrenza." << std::endl;
	return 0;
}