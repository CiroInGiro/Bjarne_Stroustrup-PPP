#include "Test.h"

// utilizzo con un int
std::istream& operator>>(std::istream& is, Test<int>& t) {
	char token{ '\n' };
	//t.val = -7; // t.val accetta valori negativi, dobbiamo interpretare il carattere '-'

		// nuovo record
		is >> token;
		if (token != '{') return is;

		// label
		is >> t.label;

/* La versione 2 non serve, l'errore era nel file txt perché
*  era stato usato il carattere -106 '-' invece del segno - (CH 45)
* 
		// valore vers.2
		is >> token;
		int segno{ 1 };
		
		if (token == -106) {
			segno = -1;
			is >> token;
		}
		else segno = 1;

		if (std::isdigit(token)) {
			is.unget();
			is >> t.val;
			t.val *= segno;
		}
		else throw; // t.val non letto
	*/	
		is >> t.val; // *** vers.1 *** //

		// riempimento vettore
		// assicuriamoci che sia vuoto. Versione 2
		t.seq.clear();
		is >> token;
		if (token != '{') return is;
	
		int intero{ 0 };
		//is >> token;

		while (!is.eof() && token != '}') {
			is >> token;
			if (std::isdigit(token) || token == '-') {
				is.unget();
				is >> intero;
				t.seq.push_back(intero);
			}
		}

		// fine vettore
		//is >> token;
		if (token != '}') return is;

		// esito atteso
		is >> t.res;

		// fine record
		is >> token;
		if (token != '}') return is;

	return is;
}

// utilizzo con un float
std::istream& operator>>(std::istream& is, Test<float>& t) {
	char token{ '\n' };
	// nuovo record
	is >> token;
	if (token != '{') return is;

	// label
	is >> t.label;
	
	// val
	is >> t.val;

	// riempimento vettore
	// assicuriamoci che sia vuoto. Versione 2
	t.seq.clear();
	is >> token;
	if (token != '{') return is;

	float elemento{ 0 };

	while (!is.eof() && token != '}') {
		is >> token;
		if (std::isdigit(token) || token == '-' || token == '.') {
			is.unget();
			is >> elemento;
			t.seq.push_back(elemento);
		}
	}

	// fine vettore
	if (token != '}') return is;

	// esito atteso
	is >> t.res;

	// fine record
	is >> token;
	if (token != '}') return is;

	return is;
}

// utilizzo con una string
std::istream& operator>>(std::istream& is, Test<std::string>& t) {
	char token{ '\n' };
	// nuovo record
	is >> token;
	if (token != '{') return is;

	// label
	is >> t.label;

	// val
	is >> t.val;

	// riempimento vettore
	// assicuriamoci che sia vuoto. Versione 2
	t.seq.clear();
	is >> token;
	if (token != '{') return is;

	std::string elemento;

	while (!is.eof() && token != '}') {
		is >> token;
		if (token != '}') {
			is.unget();
			is >> elemento;
			t.seq.push_back(elemento);
		}
	}

	// fine vettore
	if (token != '}') return is;

	// esito atteso
	is >> t.res;

	// fine record
	is >> token;
	if (token != '}') return is;

	return is;
}
