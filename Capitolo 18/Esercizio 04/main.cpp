/*
Capitolo 18 Esercizio 4
Considera cosa succede se dai a strdup() findx() e strcmp() un oggetto che non sia un c-style string!
Per prima cosa scopri come ottenere un char* a un array zero terminato di caratteri e poi usalo (mai farlo nella realtà - non sperimentarlo).
Provalo con "false c-style string" allocate nello heap e nello stack.
Se i risultati sembrano ancora ragionevoli disattivate la modalità di debug.
Riprogettate queste 3 funzioni in modo che prendano un altro parametro che indica il numero massimo di elementi nelle stringhe da considerare.
Quindi provalo con stringhe c-style corrette e stringhe "cattive".
*/

#include <iostream>

char* my_strdup(const char* cs) {
	int size{ 0 };
	while (*(cs + size)) ++size;
	char* retVal = new char[size];
	for (char* ip = retVal; *cs; ++cs, ++ip) *ip = *cs;
	*(retVal + size) = '\0';
	return retVal;
}

char* my_strdup(const char* cs, int elem) {
	//int size{ 0 };
	//while (*(cs + size)) ++size;
	char* retVal = new char[(elem+1)];
	for (int ip = 0; ip <= elem; ++cs, ++ip) if (*cs == '\0') *(retVal + ip) = ' '; else *(retVal + ip) = *cs;
	*(retVal + elem + 1) = '\0';
	return retVal;
}

char* findx(const char* s, const char* x) {
	char* retVal{ nullptr };
	int is{ 0 }; // indice in s
	int ix{ 0 }; // indice in x
	int pos{ 0 };
	while (*(s + is)) {
		if (*(s + is) == *(x + ix)) {
			pos = is;
			while (*(x + ix) && *(s + is) == *(x + ix)) {
				++is;
				++ix;
			}
			if (*(x + ix)) {
				// stringa non corrispondente, reset
				ix = 0;
				pos = 0;
			}
			else {
				// stringa trovata, possiamo uscire
				// pos è l'indice della prima occorrenza
				// ix si trova ora alla fine e ci dice la lunghezza della stringa
				retVal = new char[(ix + 1)];
				// riempimento retVal
				for (int i = 0; i <= ix; ++i) {
					*(retVal + i) = *(s + pos + i);
				}
				*(retVal + ix + 1) = '\0';
				return retVal;
			}
		}
		++is;
	}
	return retVal;
}

char* findx(const char* s, const char* x, int elem) {
	char* retVal{ nullptr };
	int is{ 0 }; // indice in s
	int ix{ 0 }; // indice in x
	int pos{ 0 };
	while (is < elem) {
		if (*(s + is) == *(x + ix)) {
			pos = is;
			while (*(x + ix) && *(s + is) == *(x + ix)) {
				++is;
				++ix;
			}
			if (*(x + ix)) {
				// stringa non corrispondente, reset
				ix = 0;
				pos = 0;
			}
			else {
				// stringa trovata, possiamo uscire
				// pos è l'indice della prima occorrenza
				// ix si trova ora alla fine e ci dice la lunghezza della stringa
				retVal = new char[(ix + 1)];
				// riempimento retVal
				for (int i = 0; i <= ix; ++i) {
					*(retVal + i) = *(s + pos + i);
				}
				*(retVal + ix + 1) = '\0';
				return retVal;
			}
		}
		++is;
	}
	return retVal;
}

int strcmp(const char* s1, const char* s2) {
	int retVal{ 0 }; // presupposto che siano uguali
	while (*s1 && *s2) {
		if (*s1 < *s2) return -1;
		if (*s1 > *s2) return 1;
		// ancora uguali
		++s1;
		++s2;
	}
	// una delle due stringhe è più corta o uguali
	if (!*s1 && !*s2) return 0; // entrambe alla fine, quindi uguali
	if (!*s1) return -1; // s1 più corta
	return 1; // s2 più corta
}

int strcmp(const char* s1, const char* s2, int elem) {
	int retVal{ 0 }; // presupposto che siano uguali
	int count{ 0 };
	while (count < elem) {
		if (*s1 < *s2) return -1;
		if (*s1 > * s2) return 1;
		// ancora uguali
		++s1;
		++s2;
		++count;
	}
	// una delle due stringhe è più corta o uguali
	if (!*s1 && !*s2) return 0; // entrambe alla fine, quindi uguali
	if (!*s1) return -1; // s1 più corta
	return 1; // s2 più corta
}

// Oggetto TEST
class TEST {
public:
	TEST() {
		dato = 0;
	}
	int get() const { return dato; }
	void set(int i) { dato = i; }
private:
	int dato{ 0 };
};

int main(int argc, char** argv) {
	// Per prima cosa utilizziamo reinterpret_cast<T> che reinterpreta un puntatore di un tipo in un altro.
	// Passando il puntatore compatibili con le funzioni:
	// tutte hanno un controllo sulla terminazione di stringa col valore nullo, quindi leggeranno dati dalla memoria finché non ci sarà un '\0' (NULL) casuale.
	// strdup è la più pericolosa in quando scriverà questi dati in un altra locazione di memoria e allo stesso modo questa memoria potrebbe corrispondere persino ad un file aperto sul disco.
	// nel nostro caso my_strdup crea una locazione della memoria di quella dimensione e ci sopia i dati fino al primo '\0' causale che legge, quindi utilizzerà sempre memoria sicura.

	TEST* intero = new TEST;
	char* stringa;
	char* stringa_copiata;
	int esito{ 0 };

	const char* parola1{ "Cane" }; // 4 byte come un intero
	const char* parola2{ "cane" };
	const char* parola3{ "casa" };
	using std::cout;
	using std::endl;
	
	// Test 1
	cout << "TEST 1 my_strdup(stringa) con stringa impostata a parola1:" << endl << endl;
	cout << "parola1 è " << parola1 << endl;
	stringa = const_cast<char*>(parola1);
	cout << "stringa vale " << stringa << endl;
	 stringa_copiata = my_strdup(stringa);
	cout << "stringa copiata: " << stringa_copiata << endl << endl;
	char ch{ ' ' }; std::cin >> ch;

	// Test 2
	cout << "TEST 2 my_strdup(stringa) con stringa impostata a TEST:" << endl << endl;
	cout << "TEST è " << intero->get() << endl;
	stringa = reinterpret_cast<char*>(intero);
	cout << "stringa vale " << stringa << endl;
	stringa_copiata = my_strdup(stringa);
	cout << "stringa copiata: " << stringa_copiata << endl << endl;
	ch = ' '; std::cin >> ch;

	// Test 3
	cout << "TEST 3 my_strdup(stringa) con stringa impostata a TEST non 0:" << endl << endl;
	intero->set(INT32_MAX);
	cout << "TEST è " << intero->get() << endl;
	stringa = reinterpret_cast<char*>(intero);
	cout << "stringa vale " << stringa << endl;
	stringa_copiata = my_strdup(stringa);
	cout << "stringa copiata: " << stringa_copiata << endl << endl;
	ch = ' '; std::cin >> ch;

	// Test 4
	cout << "TEST 4 findx(stringa, stringa) con stringa impostata a TEST non 0:" << endl << endl;
	intero->set(INT32_MAX);
	cout << "TEST è " << intero->get() << endl;
	stringa = reinterpret_cast<char*>(intero);
	cout << "stringa vale " << stringa << endl;
	stringa_copiata = findx(stringa, stringa);
	cout << "stringa trovata: " << stringa_copiata << endl << endl;
	ch = ' '; std::cin >> ch;

	// Test 5
	cout << "TEST 5 strcmp(parola1, stringa) con stringa impostata a TEST non 0:" << endl << endl;
	intero->set(INT32_MAX);
	cout << "parola1 vale " << parola1 << endl;
	stringa = reinterpret_cast<char*>(intero);
	cout << "stringa vale " << stringa << endl;
	esito = strcmp(parola1, stringa);
	cout << "Esito vale (-1 se parola1 è più piccola, 1 se è più grande e 0 se = a stringa): " << esito << endl << endl;
	ch = ' '; std::cin >> ch;

	// Test 6
	cout << "TEST 6 my_strdup(stringa, 20) con stringa impostata a TEST non 0:" << endl << endl;
	intero->set(INT32_MAX);
	cout << "TEST è " << intero->get() << endl;
	stringa = reinterpret_cast<char*>(intero);
	cout << "stringa vale " << stringa << endl;
	stringa_copiata = my_strdup(stringa, 20);
	cout << "stringa copiata: " << stringa_copiata << endl << endl;
	ch = ' '; std::cin >> ch;

	// Test 7
	const char* frase{ "Testo in cui la parola can è presente." };
	cout << "TEST 7 findx(frase, parola2, 100):" << endl << endl;
	cout << "La frase è " << frase << endl;
	stringa = const_cast<char*>(frase);
	cout << "stringa vale " << stringa << endl;
	stringa_copiata = findx(stringa, parola2, 100);
	cout << "stringa copiata: ";
	if (stringa_copiata) cout << stringa_copiata; else cout << " ";
	cout << endl << endl;
	ch = ' '; std::cin >> ch;

	// Test 8
	cout << "TEST 8 strcmp(parola1, parola2, 100):" << endl << endl;
	cout << "parola1 vale " << parola1 << endl;
	cout << "parola2 vale " << parola2 << endl;
	esito = strcmp(parola1, parola2, 100);
	cout << parola1 << " risulta ";
	if (esito < 0) cout << "più piccola di "; else if (esito > 0) cout << "più grande di "; else cout << "uguale a";
	cout << parola2;
	cout << endl << endl;
	ch = ' '; std::cin >> ch;

	return 0;
}