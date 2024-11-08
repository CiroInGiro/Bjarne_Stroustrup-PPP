#pragma once
#include <string>
#include <vector>
#include <iostream>

// Creo la struttura come classe
// Test è la struttura che contiene il test da eseguire e legge da stream
template<class T=int>
class Test
{
public:
	std::string label;
	T val;
	std::vector<T> seq;
	bool res;
	// operatore di input
	friend std::istream& operator>>(std::istream& is, Test<T>& t);
	friend std::ostream& operator<<(std::ostream& os, Test<T>& t) {
		// nuovo record
		os << "{ ";

		// label
		os << t.label << " ";

		// valore test
		os << t.val << " ";

		// scaricamento vettore
		os << "{ ";

		for (T elemento : t.seq) {
			os << elemento << " ";
		}

		// fine vettore
		os << "} ";

		// esito atteso
		os << t.res << " ";

		// fine record
		os << "} ";

		return os;
	}
};
