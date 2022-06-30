/*
Capitolo 21 Esercizio 7
Scrivi una funzione di ricerca binaria per un vector<int>, senza usare quello standard.
Puoi scegliere ogni interfaccia che ti piace.
Testa.
Quanto sei sicuro che la tua funzione di ricerca funzioni?
Ora scrivi una funzione di ricerca binaria per list<string>.
Testa.
Quando si somigliano le due funzioni di ricerca binaria?
Quando pensi che si sarebbero somigliate se non avresti saputo dello standard template library?
*/

#include <vector>
#include <list>
#include <iostream>

template<class It, class T>
// requires Input_iterator<It>()
It bsearch(It first, It last, const T& val) {
	// pensiamo prima alla lista perché è più complicato senza poter usare l'accesso random dell'iteratore
	unsigned long dist{ 0 }; // distanza tra first e last
	for (It navetta{ first }; navetta != last; ++navetta) ++dist; // sostituibile con std::count(first, last) definita in algorithm
	It middle{ first };
	unsigned long pos = dist / 2;
	// avanza fino a metà
	for (unsigned long p{ 0 }; p < pos; ++p) ++middle;
	while (middle != last && middle != first && *middle != val) {
		dist -= pos; // dimezza il range di ricerca
		pos = dist / 2; // prossimo range
		if (*middle < val) {
			first = middle;
			//d = d - pos;
			//pos = d / 2;
			for (unsigned long p{ 0 }; p < pos; ++p) ++middle; // sostituibile con la funzione std::forwsrd(iterator, count) definita in algorithm
		}
		else if (*middle > val) {
			last = middle;
			//d = d - pos;
			//pos = d / 2;
			for (unsigned long p{ 0 }; p < pos; ++p) --middle; // sostituibile con la funzione std::backward(iterator, count) definita in algorithm
		}
	}
	return middle;
}

int main(int argc, char** argv) {
	std::vector<int> vi{ 2, 4, 5, 7, 8, 9, 12, 34, 35, 90, 99 };
	std::cout << "Ho il seguente vettore di interi:\n";
	for (int i : vi) std::cout << i << ", ";
	std::cout << std::endl;
	std::cout << "Cerco il valore 90 in esso,";
	std::vector<int>::iterator ii = bsearch(vi.begin(), vi.end(), 90);
	if (*ii == 90) std::cout << " il valore 90 è presente!\n"; else std::cout << " non lo trovo...\n";
	std::cout << std::endl;
	std::cout << "Cerco il valore 35 in esso,";
	ii = bsearch(vi.begin(), vi.end(), 35);
	if (*ii == 35) std::cout << " il valore 35 è presente!\n"; else std::cout << " non lo trovo...\n";
	std::cout << std::endl;
	std::cout << "Cerco il valore 101 in esso,";
	ii = bsearch(vi.begin(), vi.end(), 101);
	if (*ii == 101) std::cout << " il valore 101 è presente!\n"; else std::cout << " non lo trovo...\n";
	std::cout << std::endl;
	std::cout << "Cerco il valore 1 in esso,";
	ii = bsearch(vi.begin(), vi.end(), 1);
	if (*ii == 1) std::cout << " il valore 1 è presente!\n"; else std::cout << " non lo trovo...\n";
	std::cout << std::endl;
	std::cout << "Cerco il valore 2 in esso,";
	ii = bsearch(vi.begin(), vi.end(), 2);
	if (*ii == 2) std::cout << " il valore 2 è presente!\n"; else std::cout << " non lo trovo...\n";
	std::cout << std::endl;
	std::cout << "Cerco il valore 99 in esso,";
	ii = bsearch(vi.begin(), vi.end(), 99);
	if (*ii == 99) std::cout << " il valore 99 è presente!\n"; else std::cout << " non lo trovo...\n";

	return 0;
}

/*
La funzine creata sfrutta solo l'operatore di incremento dell'iteratore in modo da andar bene anche con le liste dove l'accesso non è random.
Si potrebbe creare un test sull'iteratore con un accesso random e se si solleva un eccezione si gestisce passando a questa tecnica altrimenti il contenitore sarà sequenziale con il vettore e quindi si può utilizzare l'accesso random.
Se non avessi conosciuto lo stl avrei commesso sicuramente molti più errori sugli iteratori per le liste ma superabile, anche le funzioni da algorithm non sono state usate volutamente ma sono nello stl.
*/