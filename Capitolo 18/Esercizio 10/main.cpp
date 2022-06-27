/*
Capitolo 18 Esercizio 10
Guarda la soluzione con array sul problema del polandrome del paragrafo 18.7.2
Risolvi la gestione delle stringhe troppo lunghe 
(a) segnalando quando la stringa è troppo lunga
(b) consentendo una stringa arbitriariamente lunga
Commenta la complessività delle 2 versioni
*/

#include <iostream>

bool is_polandrome(const char a[], int dim) {
	int first{ 0 };
	int last = dim - 1;
	while (first < last) {
		if (a[first] != a[last]) return false;
		++first;
		--last;
	}
	return true;
}

// diversamente se vogliamo gestire stringhe più lunghe dobbiamo per forza occupare più memoria
// unica alternativa è avere allocazione dinamica che, come per string e vector, quando servirà più spazio, questo sarà allocato.
std::istream& read_word(std::istream& is, char* a, int max) {
	//is.width(max);
	//is >> a;
	char c{ ' ' };
	int count{ 0 };
	while (is.get(c) && c != '\0' && !isspace(c)) {
		if (count < max) a[count] = c;
		else {
			is.unget();
			std::cout << "\nLimite di " << max << " caratteri raggiunto.\n";
			break;
		}
		++count;
	}
	a[count] = '\0';
	return is;
}

int main(int argc, char** argv) {
	constexpr int dim_arr{ 10 };
	using std::cout;
	cout << "scrivi una parola e invio per controllarla.\n";
	for (char caratteri[dim_arr]; read_word(std::cin, caratteri, dim_arr);) {
		cout << caratteri;
		if (!is_polandrome(caratteri, strlen(caratteri))) cout << " non";
		cout << " e' una parola polandrome\n\n";
	}
	return 0;
}