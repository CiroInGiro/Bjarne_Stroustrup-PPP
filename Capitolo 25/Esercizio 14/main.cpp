/* Capitolo 25 Esercizio 14
Implementa un semplice vettore che può memorizzare al massimo N elementi allocati da un pool.
Testalo per N==1000 e con elementi interi.
*/

#include "MyVector_Pool.h"
#include <iostream>
#include <vector>
#include <random>

int main() {
	// Un pò di ripasso: 
	int* test_pi = 0;
	int test_i{ 0 };
	std::cout << "Size of point to int: " << sizeof(test_pi) << std::endl;
	std::cout << "Size of int: " << sizeof(test_i) << std::endl;
	test_pi = &test_i;
	std::cout << std::endl << "Size of pi that point to i: " << sizeof(test_pi) << std::endl;
	bool test_b{ false };
	std::cout << std::endl << "Size of a bool : " << sizeof(test_b) << std::endl;
	//return 0;

	/*
	Gli indirizzi di memoria sono numeri molto grandi e occupano memoria.
	Il Pool non può nè sprecare nè variare la memoria occupata durante l'utilizzo
	e il tempo di impegno e rilascio della sua memoria dovrà essere il più prevedibile possibile.
	*/

	MyVector_Pool<int, 1000> test_pool;
	std::cout << "Stampa del Pool vuoto:\n\n";
	test_pool.stampa();
	int* a = test_pool.get();
	int* b = test_pool.get();
	int* c = test_pool.get();
	*a = 10;
	*b = 12;
	*c = *a + *b;
	std::cout << "A: " << *a << std::endl;
	std::cout << "B: " << *b << std::endl;
	std::cout << "A + B = " << *c << std::endl;
	test_pool.del(c);
	std::cout << "C cancellato: " << *c << " ma il suo indirizzo esiste ancora nel pool!" << std::endl;
	
	// Proviamo a mettere i puntatori in un vettore.
	std::vector<int*> vettore_pi;
	for (int i = 0; i < 10; ++i) {
		int* pget = test_pool.get();
		if (pget) {
			*pget = (i * 2 + i);
			vettore_pi.push_back(pget);
		}
	}
	std::cout << "Elementi vettore: ";
	for (int* p : vettore_pi) {
		std::cout << *p << "; ";
	}
	std::cout << std::endl;

	// stampa del pool pieno
	std::cout << "Stampa del Pool pieno:\n\n";
	test_pool.stampa();

	// svuoto il pool dagli elemeti nel vettore
	std::cout << "\n\n\nSvuoto il Pool e lo stampo:\n";
	for (size_t i = 0; i < vettore_pi.size(); ++i) {
		test_pool.del(vettore_pi[i]);

	}
	std::cout << "Stampa del Pool dopo lo svuotamento dai puntatori del vettore:\n\n";
	test_pool.stampa();

	// provo di nuovo in maniera disordinata
	bool push_pop{ false }; // indica se inseriamo o cancelliamo un elemento
	std::random_device rnd_device;
	std::default_random_engine rnd_distro(rnd_device());
	std::uniform_int_distribution<int> rnd_scelta(0, 1);
	std::uniform_int_distribution<int> rnd_valori(1, 1000);
	// azzero il vettore dei puntatori e gli ultimi dati nel pool
	vettore_pi.clear();
	test_pool.del(a);
	test_pool.del(b);
	std::cout << "Stampa del Pool dopo la cancellazione dei puntatori A e B:\n\n";
	test_pool.stampa();

	// ciclo di riempimento
	const int del_max = 200; // massimo numero di cancellazioni nel pool da eseguire
	int del_count{ 0 }; // numero di cancellazioni eseguite nel pool
	while (test_pool.size() < test_pool.capacity()) {
		if ((test_pool.size() == 0) || (del_count == del_max)) push_pop = true; else push_pop = rnd_scelta(rnd_distro);
		if (push_pop) {
			// aggiungi un nuovo elemento al pool e conserviamo il puntatore
			int* p = test_pool.get();
			if (!p) {
				if (test_pool.size() == test_pool.capacity()) throw; // se sei pieno perché mi trovo qui?
				throw; // se c'è spazio perché non hai un puntatore?
			}
			*p = rnd_valori(rnd_distro);
			vettore_pi.push_back(p);
			std::cout << std::dec << "Aggiunto il valore " << *p << " nel vettore; dimensione del pool: " << test_pool.size() << "; indirizzo: " << std::hex << p << std::endl;
		}
		else {
			// togliamo un elemento a caso dal pool
			++del_count;
			std::uniform_int_distribution<size_t> rnd_indice(0, (vettore_pi.size() - 1));
			size_t indice = rnd_indice(rnd_distro);
			std::cout << std::dec << "Cancellato elemento " << *vettore_pi[indice] << " dal pool; indirizzo: " << std::hex << vettore_pi[indice] << std::dec << " numero di cancellazioni : " << del_count << std::endl;
			test_pool.del(vettore_pi[indice]);
			vettore_pi.erase((vettore_pi.begin() + indice));
		}
	}

	std::cout << "Stampa del Pool dopo aggiunte e cancellazioni fino al suo riempimento:\n\n";
	test_pool.stampa();

	std::cout << "Cancello un elemento dal Pool pieno e ristampo il Pool:\n\n";
	test_pool.del(vettore_pi[0]);
	test_pool.stampa();

	return 0;
}