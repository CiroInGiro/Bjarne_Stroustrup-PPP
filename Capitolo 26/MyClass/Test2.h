#pragma once
#include <string>
#include <vector>
#include <iostream>

// Creo la struttura come classe
// Test2 è la struttura che contiene i test da eseguire e legge da stream
template<class T>
class Test2
{
public:
	std::string label;
	std::vector<T> val;
	std::vector<T> seq;
	std::vector<bool> res;
	Test2() { clear(); }
	void clear() {
		label = "";
		val.clear();
		seq.clear();
		res.clear();
	}
	// operatore di input
	friend std::istream& operator>>(std::istream& is, Test2<T>& t);
	friend std::ostream& operator<<(std::ostream& os, Test2<T>& t) {
		// nuovo record
		os << "{ ";

		// label
		os << t.label << " ";

		// valori da testare
		os << "{ ";
		for (T elemento : t.val) os << elemento << " ";
		os << "} ";

		// scaricamento vettore
		os << "{ ";

		for (T elemento : t.seq) {
			os << elemento << " ";
		}

		// fine vettore
		os << "} ";

		// esiti attesi
		os << "{ ";
		for (bool elemento : t.res) os << elemento << " ";
		os << "} ";

		// fine record
		os << "} ";

		return os;
	}
	//friend bool operator<(const Test2<T>& a, const Test2<T>& b) { return (a.seq.size() < b.seq.size()); }
	friend void operator++(Test2<T>& a) { for (T elemento : a.seq) ++elemento; }
};