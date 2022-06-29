/*
Capitolo 20 Esercizio 7
Trova l'ultima lessico grafico-logica stringa in un vettore disordinato di string
*/

#include <vector>
#include <string>
#include <iostream>

template<typename Iter>
// requires Input_Iterator<Iter>()
Iter trova_ultima(Iter first, Iter last, const std::string& s) {
	Iter retVal{ last }; // se la fine viene restituita non è stato trovato nulla
	while (first != last) {
		if (*first == s) {
			retVal = first;
			// debug info
			std::cout << "\nTrovata...\n";
		}
		++first;
	}
	return retVal;
}

int main() {
	std::vector<std::string> vs{ "casa", "Bob", "Tetto", "cortile", "casa", "paint", "polo" };
	std::string cerco{ "casa" };
	std::vector<std::string>::iterator p = trova_ultima(vs.begin(), vs.end(), cerco);
	using std::cout;
	using std::endl;
	cout << "Cerco la stringa '" << cerco << "' in un vettore di stringhe disordinato";
	if (p == vs.end()) cout << " ma non l'ho trovata.\n"; else cout << " e l'ho trovata: " << *p << endl;
	return 0;
}