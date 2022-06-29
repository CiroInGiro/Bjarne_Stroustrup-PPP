/*
Capitolo 20 Esercizio 20
Esegui un piccolo esperimento di temporizazione per confrontare i costi nell'usare un vettore e una lista.
Puoi trovare una spiegazione di come cronometrare un programma nel paragrafo 26.6.1
Generare N valori int casuali nel range [0:N) 
Ad ogni int generato inseriscilo in un vector<int> che cresce di un elemento alla volta. Tieni il vettore ordinato.
Cioè un valore è inserito dopo ogni valore che è minore o uguale ad esso e prima di ogni valore che è maggiore di esso.
Ora rifai l'esperimento con un list<int>.
Per quale N la lista diventa più veloce del vettore?
Prova a spiegare i risultati.
Questo esperimento fu prima suggerito da John Bentley.
*/

/*
sicuramente il vettore risulterà più lento negli inserimenti sopratutto con N grandi e a tratti perché succede quando la classe vector dovrà allocare un nuovo blocco di memoria e spostare i dati dal vecchio blocco al nuovo.
*/
// riesco a misurare fino a cifre con 5 zeri e non c'è differenza forse perché anche la lista ha il suo contro che sarebbe lo scorrimento per la ricerca degli elementi: è veloce nell'inserimento ma non lavora su blocchi contigui di memoria.

#include <vector>
#include <list>
#include <iostream>
#include <chrono>
#include <random>

unsigned long power(const unsigned int base, unsigned int potenza) {
	unsigned long retVal{ 1 };
	while (potenza > 0) { retVal *= base; --potenza; }
	return retVal;
}
template<typename Iter, typename T>
// requires Input_Iterator<Iter>;
// requires T()
Iter insert_ordered(Iter from, Iter to, T val) {
	while (from != to) {
		if (val > *from) ++from;
		else return from;
	}
	return to;
}

int main(int argc, char** argv) {
	std::vector<int> vi;
	std::list<int> li;
	// Provo con diversi N
	for (unsigned int multiplo = 1; multiplo <= 5; ++multiplo) {
		unsigned long N = power(10, multiplo);
		std::srand(N);
		// prendo il tempo prima della prova vector
		auto start = std::chrono::system_clock::now();
		for (unsigned long prove = 1; prove < N; ++prove) {
			int val = std::rand() % N;
			std::vector<int>::iterator to = insert_ordered(vi.begin(), vi.end(), val);
			vi.insert(to, val);
		}
		// prendo il tempo dopo la prova vector
		std::chrono::time_point<std::chrono::system_clock> stop = std::chrono::system_clock::now();
		std::cout << "Vettore riempito con " << N << " valori casuali in maniera ordinata in " << std::chrono::duration_cast<std::chrono::milliseconds>(stop-start).count() << " ms;" << std::endl;

		// prendo il tempo per la prova list
		start = std::chrono::system_clock::now();
		for (unsigned long prove = 1; prove < N; ++prove) {
			int val = std::rand() % N;
			std::list<int>::iterator to = insert_ordered(li.begin(), li.end(), val);
			li.insert(to, val);
		}
		// prendo il tempo dopo la prova list
		stop = std::chrono::system_clock::now();
		std::cout << "Lista riempito con " << N << " valori casuali in maniera ordinata in " << std::chrono::duration_cast<std::chrono::milliseconds>(stop - start).count() << " ms;" << std::endl;
		vi.resize(0);
		li.resize(0);
	}
	return 0;
}