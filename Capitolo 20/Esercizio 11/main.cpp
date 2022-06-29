/*
Capitolo 20 esercizio 11
Data un list<int> come parametro passato per riferimento, costruisci un vector<double> e copia la lista in esso.
Verifica che la copia è completa e corretta.
Stampa gli elementi ordinati in modo crescente.
*/

#include <list>
#include <vector>
#include <iostream>



void riempi(std::list<int>& l) {
	l.push_back(8);
	l.push_back(2);
	l.push_back(16);
	l.push_back(1);
	l.push_back(3);
	l.push_back(23);
}

void travasa(std::list<int>& l, std::vector<double>& v) {
	for (int i : l) v.push_back(i);
}

template<typename Iter>
void stampa(Iter first, Iter last) {
	int count{ 0 };
	while (first != last) {
		std::cout << "Address: " << &(*first) << " -> " << *first << std::endl;
		++first;
		++count;
	}
	std::cout << "Elementi totali: " << count << std::endl;
}

void ordina(std::vector<double>& v) {
	double tmp{ 0.0 };
	for (int i = 0; i < v.size() - 2; ++i) {
		for (int j = i; j < v.size(); ++j) {
			if (v[i] > v[j]) {
				// scambio
				tmp = v[i];
				v[i] = v[j];
				v[j] = tmp;
			}
		}
	}
}

int main(int argc, char** argv) {
	std::list<int> li;
	std::vector<double> vd;
	riempi(li);
	travasa(li, vd);
	std::cout << "Stampo i dati nella lista:" << std::endl;
	stampa(li.begin(), li.end());
	std::cout << std::endl;
	std::cout << "Stampo i dati nel vettore:" << std::endl;
	stampa(vd.begin(), vd.end());
	std::cout << std::endl;
	ordina(vd);
	std::cout << "Stampo i dati ordinati del vettore:" << std::endl;
	stampa(vd.begin(), vd.end());
	return 0;
}