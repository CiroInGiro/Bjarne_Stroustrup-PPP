#include "Test2.h"

// utilizzo con un int
std::istream& operator>>(std::istream& is, Test2<int>& t) {
	char token{ '\n' };
	int intero{ 0 };

	// nuovo record
	is >> token;
	if (token != '{') return is;

	// label
	is >> t.label;

	// azzeramento e letture valori da testare
	t.val.clear();
	is >> token;
	if (token != '{') return is;

	while (!is.eof() && token != '}') {
		is >> token;
		if (std::isdigit(token) || token == '-') {
			is.unget();
			is >> intero;
			t.val.push_back(intero);
		}
	}

	if (token != '}') return is;

	// riempimento vettore
	// assicuriamoci che sia vuoto.
	t.seq.clear();
	is >> token;
	if (token != '{') return is;

	while (!is.eof() && token != '}') {
		is >> token;
		if (std::isdigit(token) || token == '-') {
			is.unget();
			is >> intero;
			t.seq.push_back(intero);
		}
	}

	if (token != '}') return is;

	// lettura degli esiti attesi
	t.res.clear();
	is >> token;
	if (token != '{') return is;

	while (!is.eof() && token != '}') {
		is >> token;
		if (token == '1') t.res.push_back(true);
		if (token == '0') t.res.push_back(false);
	}

	if (token != '}') return is;

	// fine record
	is >> token;
	if (token != '}') return is;

	return is;
}

// utilizzo con un float
std::istream& operator>>(std::istream& is, Test2<float>& t) {
	char token{ '\n' };
	float elemento{ 0 };

	// nuovo record
	is >> token;
	if (token != '{') return is;

	// label
	is >> t.label;

	// val
	t.val.clear();
	is >> token;
	if (token != '{') return is;

	while (!is.eof() && token != '}') {
		is >> token;
		if (std::isdigit(token) || token == '-' || token == '.') {
			is.unget();
			is >> elemento;
			t.val.push_back(elemento);
		}
	}

	if (token != '}') return is;

	// riempimento vettore
	// assicuriamoci che sia vuoto.
	t.seq.clear();
	is >> token;
	if (token != '{') return is;

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
	t.res.clear();
	is >> token;
	if (token != '{') return is;

	while (!is.eof() && token != '}') {
		is >> token;
		if (token == '1') t.res.push_back(true);
		if (token == '0') t.res.push_back(false);
	}

	if (token != '}') return is;

	// fine record
	is >> token;
	if (token != '}') return is;

	return is;
}

// utilizzo con una string
std::istream& operator>>(std::istream& is, Test2<std::string>& t) {
	char token{ '\n' };
	std::string elemento;

	// nuovo record
	is >> token;
	if (token != '{') return is;

	// label
	is >> t.label;

	// val
	t.val.clear();
	is >> token;
	if (token != '{') return is;

	while (!is.eof() && token != '}') {
		is >> token;
		if (token != '}') {
			is.unget();
			is >> elemento;
			t.val.push_back(elemento);
		}
	}
	if (token != '}') return is;

	// riempimento vettore
	// assicuriamoci che sia vuoto. Versione 2
	t.seq.clear();
	is >> token;
	if (token != '{') return is;

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
	t.res.clear();
	is >> token;
	
	if (token != '{') return is;
	
	while (!is.eof() && token != '}') {
		is >> token;
		if (token == '1') t.res.push_back(true);
		if (token == '0') t.res.push_back(false);
	}

	if (token != '}') return is;


	// fine record
	is >> token;
	if (token != '}') return is;

	return is;
}
