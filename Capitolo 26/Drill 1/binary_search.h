#pragma once

#include<vector>

// funzione di ricerca binaria
template<class It, class T>
bool binary_search(It start, It end, T& num) {
	//size_t start = 0;
	//size_t end = (v.size() - 1);
	//size_t middle = (end - start) / 2;

	// contreolli preliminari: pos restituisce l'indice quando trovato o rimane invariato; la funzione ritorna true in caso di successo altrimenti false.
	//if (v.size() == 0) return false; // nulla da cercare
	if (start == end) return false;

	//if (num < v[start] || num > v[end]) return false; // stiamo cercando un numero che si trova al di fuori del range di numeri contenuti.
	if (num < *start || num > *(end - 1)) return false;

	It middle = start + ((end - start) / 2);

	while (middle != start && middle != end) {

		//if (v[middle] == num) {
		if (*middle == num)
			//pos = middle;
			return true;
		//}

		//if (v[middle] < num) {
		if (*middle < num)
			// stiamo cercando in un range troppo piccolo, ci spostiamo più avanti
			start = middle;
		//}
		else {
			// stiamo cercando in un range di numeri grandi, ci spostiamo più indietro
			end = middle;
		}
		middle = start + ((end - start) / 2);
	}

	// ultimo controllo nel caso middle sia uguale a start o end.
	//if (v[middle] == num) {
	if (*middle == num)
		//pos = middle;
		return true;
	//}
	//else if (v[start] == num) {
	else if (*start == num)
		//pos = start;
		return true;
	//}
	//else if (v[end] == num) {
	else if (*(end - 1) == num)
		//pos = end;
		return true;
	//}

	return false;
}

