/*
 Capitolo 26 Paragrafo 26.1
 Scrivi una ricerca binaria: una ricerca in un insieme ordinato di elementi partendo dal mezzo.
 - Se l'elmento centrale è = all'elemeto cercato allora abbiamo finito;
 - se l'elemento centrale < dell'elemento cercato allora cerchiamo nella metà di elementi più a destra;
 - se l'elemento cerntrale > dell'elemento cercato allora cerchiamo nella metà di elementi più a sinistra;
 - usa < come comparatore.
*/

#include <iostream>
#include <vector>

// funzione di stampa vettore
void stampa_v(const std::vector<int>& v) {
	std::vector<int>::const_iterator start = v.begin();
	std::vector<int>::const_iterator end = v.end();
	
	std::cout << "Elementi: ";
	while (start != end) {
		std::cout << *start << "; ";
		++start;
	}
	std::cout << std::endl;
}

// funzione di ricerca binaria
bool ricerca_v(const std::vector<int>& v, const int& num, size_t& pos) {
	size_t start = 0;
	size_t end = (v.size() - 1);
	size_t middle = (end - start) / 2;

	// controlli preliminari: pos restituisce l'indice quando trovato o rimane invariato; la funzione ritorna true in caso di successo altrimenti false.
	if (v.size() == 0) return false; // nulla da cercare
	if (num < v[start] || num > v[end]) return false; // stiamo cercando un numero che si trova al di fuori del range di numeri contenuti.

	while (middle != start && middle != end) {
		if (v[middle] == num) {
			pos = middle;
			return true;
		}
		if (v[middle] < num) {
			// stiamo cercando in un range troppo piccolo, ci spostiamo più avanti
			start = middle;
		}
		else {
			// stiamo cercando in un range di numeri grandi, ci spostiamo più indietro
			end = middle;
		}
		middle = start + ((end - start) / 2);
	}
	
	// ultimo controllo nel caso middle sia uguale a start o end.
	if (v[middle] == num) {
		pos = middle;
		return true;
	}
	else if (v[start] == num) {
		pos = start;
		return true;
	}
	else if (v[end] == num) {
		pos = end;
		return true;
	}
	
	return false;
}


int main(int argc, char** argv) {
	std::vector<int> v(15);
	
	for (size_t i = 0; i < v.size(); ++i) v[i] = 3 + i * 1.4;
	
	stampa_v(v);
	int num{ 0 };
	size_t pos{ 0 };
	bool result{ false };

	num = 5;
	std::cout << "Ricerco l'elemento " << num << " nel vettore : ";
	result = ricerca_v(v, num, pos);
	
	if (!result) std::cout << "Elemento non trovato\n";
	else std::cout << "Elemento trovato all'indice " << pos << std::endl;

	num = 1;
	std::cout << "Ricerco l'elemento " << num << " nel vettore : ";
	result = ricerca_v(v, num, pos);

	if (!result) std::cout << "Elemento non trovato\n";
	else std::cout << "Elemento trovato all'indice " << pos << std::endl;

	num = 100;
	std::cout << "Ricerco l'elemento " << num << " nel vettore : ";
	result = ricerca_v(v, num, pos);

	if (!result) std::cout << "Elemento non trovato\n";
	else std::cout << "Elemento trovato all'indice " << pos << std::endl;

	num = 3;
	std::cout << "Ricerco l'elemento " << num << " nel vettore : ";
	result = ricerca_v(v, num, pos);

	if (!result) std::cout << "Elemento non trovato\n";
	else std::cout << "Elemento trovato all'indice " << pos << std::endl;

	num = 22;
	std::cout << "Ricerco l'elemento " << num << " nel vettore : ";
	result = ricerca_v(v, num, pos);

	if (!result) std::cout << "Elemento non trovato\n";
	else std::cout << "Elemento trovato all'indice " << pos << std::endl;

	num = 12;
	std::cout << "Ricerco l'elemento " << num << " nel vettore : ";
	result = ricerca_v(v, num, pos);

	if (!result) std::cout << "Elemento non trovato\n";
	else std::cout << "Elemento trovato all'indice " << pos << std::endl;

	num = 14;
	std::cout << "Ricerco l'elemento " << num << " nel vettore : ";
	result = ricerca_v(v, num, pos);

	if (!result) std::cout << "Elemento non trovato\n";
	else std::cout << "Elemento trovato all'indice " << pos << std::endl;

	return 0;
}