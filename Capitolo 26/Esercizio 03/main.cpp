/* 
* Capitolo 26 Esercizio 3
* Ripeti l'esercizio 1 con la versione di binary_search che prende un criterio di comparazione.
* Crea una lista di nuove opportunità di errori introdotti dal nuovo parametro extra.
*/

#include <vector>
#include "../MyClass/Test.h"
#include <iostream>
#include <fstream>
#include <random>
#include <string>
#include <sstream>
#include <algorithm>

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

/*
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
*/

bool predicate_int(const int& a, const int& b) { return (a < b); }

bool predicate_float(const float& a, const float& b) { return (a < b); }

bool predicate_str(const std::string& a, const std::string& b) {
	float num_a{ 0.0 }, num_b{ 0.0 };
	std::istringstream stream_a, stream_b;
	char token1{ ' ' }, token2{ ' ' };
	stream_a.str(a);
	stream_b.str(b);
	
	// Controlliamo la stringa a
	stream_a >> token1;
	
	if (token1 == '.' || token1 == '-') {
		stream_a >> token2;
		stream_a.putback(token1);
		stream_a.putback(token2);
		if (std::isdigit(token2)) stream_a >> num_a;
	}
	else if (std::isdigit(token1)) stream_a >> num_a; 
	else {
		stream_a.unget();
		return (a < b);
	}

	// controlliamo la stringa b
	stream_b >> token1;

	if (token1 == '.' || token1 == '-') {
		stream_b >> token2;
		stream_b.putback(token1);
		stream_b.putback(token2);
		if (std::isdigit(token2)) stream_b >> num_b;
	}
	else if (std::isdigit(token1)) stream_b >> num_b;
	else {
		stream_b.unget();
		return (a < b);
	}

	// abbiamo estratto 2 numeri iniziali alle stringhe
	return (num_a < num_b);
}

int main() {
	std::fstream file_test("Tests_03.txt", std::fstream::in | std::fstream::out | std::fstream::trunc);

	if (file_test.bad()) return 1;

	prepara_tests(file_test);
	file_test.seekg(0); // posiziona il puntatore di lettura

	// leggiamo i test per darli in pasto a binary_search
	for (Test<int> t; file_test >> t;) {
		bool esito = std::binary_search(t.seq.begin(), t.seq.end(), t.val, predicate_int);
		std::cout << t << std::endl;
		std::cout << "Cerchiamo " << t.val << " nella sequenza e binary_search(begin(), end(), value, predicate) restituisce " << esito;
		if (esito == t.res) std::cout << "." << std::endl; else std::cout << "// *** ERRORE *** //" << std::endl;
		std::cout << "****************************************" << std::endl << std::endl;
	}

	file_test.close();

	// Proviamo le stringhe
	Test<std::string> test_str;
	test_str.label = "string1";
	test_str.val = "10";
	test_str.seq = { "0", "2", "5", "7", "10", "12", "15", "17" };
	test_str.res = 1;

	// leggiamo i test<string> per darli in pasto a binary_search
	{ // lascio il blocco per comodità: si evita problemi con conflitti di variabili se già erano in uno scope nidificato
		//bool esito = std::binary_search(test_str.seq.begin(), test_str.seq.end(), test_str.val); // ordinamento di soli caratteri (std::less{})
		bool esito = std::binary_search(test_str.seq.begin(), test_str.seq.end(), test_str.val, predicate_str); // ordinamneto personalizzato Ok
		std::cout << test_str << std::endl;
		std::cout << "Cerchiamo " << test_str.val << " nella sequenza e binary_search(begin(), end(), value, predicate) restituisce " << esito;
		if (esito == test_str.res) std::cout << "." << std::endl; else std::cout << "\n// *** ERRORE *** //\n" << std::endl;
		std::cout << "****************************************" << std::endl << std::endl;
	}

	return 0;
}
