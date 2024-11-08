/*
* Capitolo 26 Esercizio 1
* Fai girare binary_search del paragrafo 26.1 con i test presentati al paragrafo 26.3.2.1
*/

#include <vector>
#include "../MyClass/Test.h"
#include <iostream>
#include <fstream>
#include <random>
#include <string>

// inserimento ordinato di un elemento nella sequenza di un test
template<class T>
void inserimento_ordinato(Test<T>& t, T& valore) {
	auto start = t.seq.begin();
	auto end = t.seq.end();

	// se la sequenza è ancora vuota bisogna solo aggiungerlo senza cercare.
	if (t.seq.size() == 0) {
		t.seq.push_back(valore);
		return;
	}

	// se il valore da aggiungere è più grande o uguale all'ultimo allora non serve scorrere il contenitore
	if (valore >= *(end - 1)) {
		t.seq.push_back(valore);
		return;
	}

	// cerchiamo la posizione corretta per valore
	while (start != end) {
		if (valore <= *start) {
			t.seq.insert(start, valore);
			return;
		}
		++start;
	}

	// se siamo arrivati alla fine è strano perché è la seconda condizione prevista
	throw; // per avere una allert nel caso si verifichi questo caso.
}

// Preparazione dei tests
void prepara_tests(std::ostream& out) {
	Test<int> test;
	std::random_device rnd_device;
	std::mt19937 rnd_generatore(rnd_device());
	std::uniform_int_distribution<int> lunghezza_sequenza(0, 10);
	std::numeric_limits<int> interi;
	constexpr int max = interi.max();
	std::uniform_int_distribution<int> elemento_casuale(0, max);

	// una sequenza ordinaria
	test.label = "a.1";
	test.val = 8;
	int precedente1{ 1 }, precedente2{ 2 };
	test.seq.push_back(1);
	test.seq.push_back(2);

	for (int elemento = 2; elemento < 10; ++elemento) {
		test.seq.push_back((precedente1 + precedente2));
		precedente1 = test.seq[(elemento - 1)];
		precedente2 = test.seq[(elemento)];
	}

	test.res = 1;
	out << test << std::endl;

	// sequenza vuota
	test.label = "b.1";
	test.val = 8;
	test.seq.clear();
	test.res = 0;
	out << test << std::endl;

	// sequenza di un elemento
	test.label = "c.1";
	test.val = 1;
	test.seq.push_back(1);
	test.res = 1;
	out << test << std::endl;

	// sequenza di un numero pari di elementi
	test.label = "d.1";
	test.val = 5;
	test.seq.clear();

	for (int elemento = 1; elemento < 5; ++elemento) {
		test.seq.push_back(elemento);
	}

	test.res = 0;
	out << test << std::endl;

	// sequenza di un numero dispari di elementi
	test.label = "d.2";
	test.val = 5;
	test.seq.clear();

	for (int elemento = 1; elemento < 6; ++elemento) {
		test.seq.push_back(elemento);
	}

	test.res = 1;
	out << test << std::endl;

	// tutti gli elementi uguali
	test.label = "uguali";
	test.val = 2;
	test.seq.clear();
	
	for (int indice = 0; indice < 7; ++indice) test.seq.push_back(1);

	test.res = 0;
	out << test << std::endl;

	// elemento iniziale differente
	test.label = "differente.1";
	test.val = 2;
	test.seq.clear();
	test.seq.push_back(1);

	for (int indice = 0; indice < 7; ++indice) test.seq.push_back(2);

	test.res = 1;
	out << test << std::endl;

	// elemento finale differente
	test.label = "differente.last";
	test.val = 8;
	test.seq.clear();

	for (int indice = 0; indice < 7; ++indice) test.seq.push_back(1);

	test.seq.push_back(8);

	test.res = 1;
	out << test << std::endl;

	// sequenza con molti elementi.
	test.label = "large.1";
	test.val = 2000;
	test.seq.clear();

	for (int elemento = 0; elemento < 2001; ++elemento) test.seq.push_back(elemento);

	test.res = 1;
	out << test << std::endl;

	// alcune sequenze di lunghezza casuale
	// utilizziamo lunghezza_sequenza
	for (int sequenza = 0; sequenza < 10; ++sequenza) {
		test.label = "rnd_seq.";
		test.label += std::to_string((sequenza + 1));
		test.seq.clear();
		int num_elems = lunghezza_sequenza(rnd_generatore);

		for (int indice = 0; indice < num_elems; ++indice) {
			test.seq.push_back((indice * 5 / 2));
		}

		if (num_elems) { // sequenza non di zero elementi
			test.val = test.seq[(num_elems / 2)];
			test.res = 1;
		}
		else { // sequenza con almeno 1 elemento
			test.val = 0;
			test.res = 0;
		}

		out << test << std::endl;
	}

	// alcune sequenze ordinate di numeri casuali
	// utilizziamo elemento_casuale
	for (int sequenza = 0; sequenza < 10; ++sequenza) {
		test.label = "rnd_num.";
		test.label += std::to_string((sequenza + 1));
		test.seq.clear();

		for (int indice = 0; indice < 500; ++indice) {
			int val_elem = elemento_casuale(rnd_generatore);
			// inserimento ordinato
			inserimento_ordinato(test, val_elem);
		}

		test.val = test.seq[(test.seq.size() / 2)];
		test.res = 1;
		out << test << std::endl;
	}

}

// funzione di ricerca binaria scritta al paragrafo 26.1
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

int main() {
	std::fstream file_test("Tests_01.txt");

	if (file_test.bad()) return 1;

	prepara_tests(file_test);
	file_test.seekg(0); // posiziona il puntatore di lettura

	// leggiamo i test per darli in pasto a binary_search
	for (Test<int> t; file_test >> t;) {
		size_t indice{ 0 };
		bool esito = ricerca_v(t.seq, t.val, indice);
		std::cout << t << std::endl;
		std::cout << "Cerchiamo " << t.val << " nella sequenza e ricerca_v restituisce " << esito;
		if (esito) std::cout << " e aggiorna indice a " << indice << " che corrisponde nella sequenza a " << t.seq[indice];
		std::cout << std::endl;
		std::cout << "****************************************" << std::endl << std::endl;
	}

	file_test.close();

	return 0;
}

/*
* Il test differente.1 non restituisce il primo 2 in sequenza ma spezzettando la sequenza in metà lo trova
* sull'estremo (che controlla per primo) del primo segmento.
* 
* Tutti i test sono superati !
*/