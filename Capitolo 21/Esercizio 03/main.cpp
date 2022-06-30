/*
Capitolo 21 Esercizio 3
Implementa da solo la funzione count() e testala.

Capitolo 21 esercizio 4
Implementa da solo la funzione count_if() e testala.
*/

#include <iostream>
#include <vector>

/*
count e count_if
count prende 2 iteratore di inpunt random e un valore e ne conta le occorrenze nell'intervallo [iteratore, iteratore)
count_if prende 2 iteratore di inpunt random e un predicato conta le occorrenze quando il predicato(valore testato) nell'intervallo [iteratore, iteratore) gli restituisce vero
*/

namespace esercizio3 {
	template<class It, class T>
	// requires Input_iterator<It>()
	int count(It first, It last, const T& val) {
		if (first > last) return 0; // errore range
		int retVal{ 0 };
		// Range [start, end) // quindi esclude end: range aperto a destra
		while (first != last) { if (*first == val) retVal++; ++first; }
		return retVal;
	}

	template<class It, class P>
	// requires Input_iterator<It>() && Predicate<P>
	int count_if(It first, It last, P pred) {
		if (first > last) return 0;
		int retVal{ 0 };
		while (first != last) { if (pred(*first)) ++retVal; ++first; }
		return retVal;
	}
}

bool divisibili_per_3(const int& val) {
	return !(val - (val / 3) * 3);
}

int main(int argc, char** argv) {
	std::vector<int> vi{ 2, 10, 9, 3, 6, 3, 76, 9, 6, 3, 2, 1, 10, 10, 10, 12 };
	std::cout << "Vettore vi: ";
	for (auto val : vi) std::cout << val << " ";
	std::cout << std::endl;
	int num3 = esercizio3::count(vi.begin(), vi.end(), 3);
	std::cout << "Il numero 3 è presente " << num3 << " volte\n";
	int num10 = esercizio3::count(vi.begin(), vi.end(), 10);
	std::cout << "Il numero 10 è presente " << num10 << " volte\n";
	int divisibili3 = esercizio3::count_if(vi.begin(), vi.end(), divisibili_per_3);
	std::cout << "\nI numeri divisibili per 3 ne sono: " << divisibili3 << std::endl;
	// test range
	int primi = esercizio3::count_if(vi.begin(), (vi.begin() + 3), [](const int& val) {return true; });
	std::cout << "\nI primi 3 numeri, ne conto " << primi << std::endl;

	return 0;
}