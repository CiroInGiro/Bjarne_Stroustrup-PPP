/*
Capitolo 18 Esercizio 8
Riscrivi tutte le funzioni del paragrafo 18.7 per usare come approccio il rovescio della stringa e il suo confronto.
Ad esempio prendi home, diventa emoh; confronta se le due sono uguali per capire se home è una stringa polindrome.
*/

#include <iostream>

int count_chars(const char* s1) {
	int retVal{ 0 };
	if (s1 == nullptr) return 0;
	while (*s1) {
		++retVal;
		++s1;
	}
	return retVal;
}

bool str_compare(const char* s1, const char* s2) {
	while (*s1 && *s2) {
		if (*s1 != *s2) return false;
		++s1;
		++s2;
	}
	if (*s1 || *s2) return false;
	return true;
}

bool is_polydrome_reverse(const char* word) {
	int index_reverse = count_chars(word);
	char* reverse = new char[index_reverse];
	*(reverse + index_reverse) = '\0';
	const char* index_word = word;
	while (*index_word) {
		--index_reverse;
		*(reverse + index_reverse) = *index_word;
		++index_word;
		if (index_reverse == 0) break; // non dovrebbe mai capitare, solo debug.
	}
	return str_compare(word, reverse);
}

bool is_polydrome_compare(const char* word) {
	const char* start = word;
	const char* end = start + (count_chars(word) - 1);
	while (start < end) {
		if (*start != *end) return false;
		++start;
		--end;
	}
	return true;
}

int main(int argc, char** argv) {
	// test parola Home con reverse
	const char* word_home{ "Home" };
	using std::cout;
	cout << "Parola testata col metodo reverse: " << word_home << ";\n";
	cout << "Esito: ";
	if (is_polydrome_reverse(word_home)) cout << "E' polindrome.\n"; else cout << "Non è polindrome.\n";
	char ch{ ' ' };
	std::cin >> ch;

	// test parola HomemoH con reverse
	const char* word_homemoh{ "HomemoH" };
	cout << "Parola testata col metodo reverse: " << word_homemoh << ";\n";
	cout << "Esito: ";
	if (is_polydrome_reverse(word_homemoh)) cout << "E' polindrome.\n"; else cout << "Non è polindrome.\n";
	ch = { ' ' };
	std::cin >> ch;

	// test parola Home con compare
	using std::cout;
	cout << "Parola testata col metodo compare: " << word_home << ";\n";
	cout << "Esito: ";
	if (is_polydrome_compare(word_home)) cout << "E' polindrome.\n"; else cout << "Non è polindrome.\n";
	ch = { ' ' };
	std::cin >> ch;

	// test parola HomemoH con compare
	cout << "Parola testata col metodo compare: " << word_homemoh << ";\n";
	cout << "Esito: ";
	if (is_polydrome_compare(word_homemoh)) cout << "E' polindrome.\n"; else cout << "Non è polindrome.\n";
	ch = { ' ' };
	std::cin >> ch;

	return 0;
}

// Col metodo compare è stato utilizzato meno codice perché è bastato creare due indice che lavorano su un dato che già abbiamo.
// mentre col reverse abbiamo dovuto crearci il codice per girare la parola in un nuovo dato e poi creare il codice per il confronto.