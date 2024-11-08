/*
* Capitolo 26 Esercizio 5
* Aggiungi un test al set di tests per binary_search per tentare di intercettare lo (improbabile) errore di
* binary_search che modifica la sequenza.
*/

/* 
* binary_search utilizza gli iteratori solo per scorrere la sequenza e li deferenzia per leggerne il valore.
* credo l'unico modo sia passare una funzione di confronto che crea il casino ma anche qui
* la funzione di predicato deve poter prendere dei riferimenti non const ai valori passati da binary_search.
*/

#include "../MyClass/Test2.h"
#include <algorithm>
#include <iostream>
#include <fstream>
#include <random>
#include <string>
#include <sstream>


/* 
* Ho provato a creare una classe derivata per poter passare un puntatore alla classe base e vedere cosa succede a scorrere una sequenza con formattazione diversa ma
* non ci sono riuscito perché le classi sono nel template della medesima classe Test2 e non c'è conversione. Non sono andato oltre.
*/

class Piccolo {
	int intero1{ 0 };
public:
	Piccolo(const int& parametro = 0) { intero1 = parametro; }
	friend std::ostream& operator<<(std::ostream& os, const Piccolo& piccolo) {
		os << piccolo.intero1;

		return os;
	}
	friend bool operator<(const Piccolo& a, const Piccolo& b) { return (a.intero1 < b.intero1); }
};

class Grande : public Piccolo {
	int intero2{ 0 };
public:
	Grande(const int& parametro = 0) : Piccolo(parametro) { intero2 = parametro; }
	friend std::ostream& operator<<(std::ostream& os, const Grande& grande) {
		os << grande.intero2;

		return os;
	}
	friend bool operator<(const Grande& a, const Grande& b) { return (a.intero2 < b.intero2); }
};


// inserimento ordinato di un elemento nella sequenza di un test
template<class T>
void inserimento_ordinato(Test2<T>& t, T& valore) {
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

// Per l'inserimento ordinato di stringhe servirebbe usare la funzione predicate personalizzata che tiene conto dei numeri.

// Preparazione dei tests
void prepara_tests_int(std::ostream& out) {
	Test2<int> test;
	std::random_device rnd_device;
	std::mt19937 rnd_generatore(rnd_device());
	std::uniform_int_distribution<int> lunghezza_sequenza(0, 10);
	std::numeric_limits<int> interi;
	constexpr int max = interi.max();
	std::uniform_int_distribution<int> elemento_casuale(0, max);

	// una sequenza ordinaria
	test.label = "a.1";
	test.val.push_back(8);
	test.val.push_back(4);
	int precedente1{ 1 }, precedente2{ 2 };
	test.seq.push_back(1);
	test.seq.push_back(2);

	for (int elemento = 2; elemento < 10; ++elemento) {
		test.seq.push_back((precedente1 + precedente2));
		precedente1 = test.seq[(elemento - 1)];
		precedente2 = test.seq[(elemento)];
	}

	test.res.push_back(1);
	test.res.push_back(0);
	out << test << std::endl;

	// sequenza vuota
	test.clear();
	test.label = "b.1";
	test.val.push_back(8);
	test.res.push_back(0);
	out << test << std::endl;

	// sequenza di un elemento
	test.clear();
	test.label = "c.1";
	test.val.push_back(1);
	test.seq.push_back(1);
	test.res.push_back(1);
	out << test << std::endl;

	// sequenza di un numero pari di elementi
	test.clear();
	test.label = "d.1";
	test.val.push_back(5);

	for (int elemento = 1; elemento < 5; ++elemento) {
		test.seq.push_back(elemento);
	}

	test.res.push_back(0);
	out << test << std::endl;

	// sequenza di un numero dispari di elementi
	test.clear();
	test.label = "d.2";
	test.val.push_back(5);

	for (int elemento = 1; elemento < 6; ++elemento) {
		test.seq.push_back(elemento);
	}

	test.res.push_back(1);
	out << test << std::endl;

	// tutti gli elementi uguali
	test.clear();
	test.label = "uguali";
	test.val.push_back(2);

	for (int indice = 0; indice < 7; ++indice) test.seq.push_back(1);

	test.res.push_back(0);
	out << test << std::endl;

	// elemento iniziale differente
	test.clear();
	test.label = "differente.1";
	test.val.push_back(2);
	test.seq.push_back(1);

	for (int indice = 0; indice < 7; ++indice) test.seq.push_back(2);

	test.res.push_back(1);
	out << test << std::endl;

	// elemento finale differente
	test.clear();
	test.label = "differente.last";
	test.val.push_back(8);

	for (int indice = 0; indice < 7; ++indice) test.seq.push_back(1);

	test.seq.push_back(8);

	test.res.push_back(1);
	out << test << std::endl;

	// sequenza con molti elementi.
	test.clear();
	test.label = "large.1";
	test.val.push_back(2000);
	test.seq.clear();

	for (int elemento = 0; elemento < 2001; ++elemento) test.seq.push_back(elemento);

	test.res.push_back(1);
	out << test << std::endl;

	// alcune sequenze di lunghezza casuale
	// utilizziamo lunghezza_sequenza

	for (int sequenza = 0; sequenza < 10; ++sequenza) {
		test.clear();
		test.label = "rnd_seq.";
		test.label += std::to_string((sequenza + 1));
		int num_elems = lunghezza_sequenza(rnd_generatore);

		for (int indice = 0; indice < num_elems; ++indice) {
			test.seq.push_back((indice * 5 / 2));
		}

		if (num_elems) { // sequenza non di zero elementi
			test.val.push_back((test.seq[(num_elems / 2)]));
			test.res.push_back(1);
		}
		else { // sequenza zero
			test.val.push_back(0);
			test.res.push_back(0);
		}

		out << test << std::endl;
	}

	// alcune sequenze ordinate di numeri casuali
	// utilizziamo elemento_casuale
	for (int sequenza = 0; sequenza < 10; ++sequenza) {
		test.clear();
		test.label = "rnd_num.";
		test.label += std::to_string((sequenza + 1));

		for (int indice = 0; indice < 500; ++indice) {
			int val_elem = elemento_casuale(rnd_generatore);
			// inserimento ordinato
			inserimento_ordinato(test, val_elem);
		}

		test.val.push_back((test.seq[(test.seq.size() / 2)]));
		test.res.push_back(1);
		out << test << std::endl;
	}
}

// dichiarazione di predicate()
template<class T>
//bool predicate(const T& a, T& b) { return (a < b++); } // come volevasi dimostrare, binary_search passa valori costanti che la funzione predicate non potrà cambiare.
bool predicate(const T& a, const T& b) { return (a < b); }

// definizione di predicate che usa string
bool predicate(std::string& a, std::string& b) {
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

template<class T>
void report_test(std::istream& file_test) {
	bool risultato{ 0 };

	for (Test2<T> test2; file_test >> test2;) {
		std::cout << "*** Test " << test2.label << " ***\n";

		if (test2.val.size() != test2.res.size()) {
			std::cerr << "\n\n\nErrore: Numero di test diffrente dal numero di risultati attesi.\n\n\n";
			return;
		}

		for (size_t indice_val = 0; indice_val < test2.val.size(); ++indice_val) {
			std::cout << "Cerco " << test2.val[indice_val] << " nella sequenza { ";
			for (size_t indice_seq = 1; indice_seq < test2.seq.size(); ++indice_seq) std::cout << test2.seq[(indice_seq - 1)] << ", ";
			if (test2.seq.size()) std::cout << *(test2.seq.end() - 1);
			std::cout << " }. Risultato atteso: " << test2.res[indice_val] << "; binary_search restituisce: ";
			risultato = binary_search(test2.seq.begin(), test2.seq.end(), test2.val[indice_val]);
			std::cout << risultato;
			if (risultato == test2.res[indice_val]) std::cout << ".\n\n"; else std::cout << ".\n*** ERRORE ***\n\n\n\n";
		}

		test2.clear();
	}
}

template<class T>
void report_test(const Test2<T>& test2) {
	bool risultato{ 0 };
	
		if (test2.val.size() != test2.res.size()) {
			std::cerr << "\n\n\nErrore: Numero di test diffrente dal numero di risultati attesi.\n\n\n";
			return;
		}

		for (size_t indice_val = 0; indice_val < test2.val.size(); ++indice_val) {
			std::cout << "Cerco " << test2.val[indice_val] << " nella sequenza { ";
			for (size_t indice_seq = 1; indice_seq < test2.seq.size(); ++indice_seq) std::cout << test2.seq[(indice_seq - 1)] << ", ";
			if (test2.seq.size()) std::cout << *(test2.seq.end() - 1);
			std::cout << " }. Risultato atteso: " << test2.res[indice_val] << "; binary_search restituisce: ";
			risultato = binary_search(test2.seq.begin(), test2.seq.end(), test2.val[indice_val]);
			std::cout << risultato;
			if (risultato == test2.res[indice_val]) std::cout << ".\n\n"; else std::cout << ".\n*** ERRORE ***\n\n\n\n";
		}
}

void report_test(const Test2<Grande>* testp) {
	bool risultato{ 0 };
	Test2<Grande> test2 = *testp;

	if (test2.val.size() != test2.res.size()) {
		std::cerr << "\n\n\nErrore: Numero di test diffrente dal numero di risultati attesi.\n\n\n";
		return;
	}

	for (size_t indice_val = 0; indice_val < test2.val.size(); ++indice_val) {
		std::cout << "Cerco " << test2.val[indice_val] << " nella sequenza { ";
		for (size_t indice_seq = 1; indice_seq < test2.seq.size(); ++indice_seq) std::cout << test2.seq[(indice_seq - 1)] << ", ";
		if (test2.seq.size()) std::cout << *(test2.seq.end() - 1);
		std::cout << " }. Risultato atteso: " << test2.res[indice_val] << "; binary_search restituisce: ";
		risultato = binary_search(test2.seq.begin(), test2.seq.end(), test2.val[indice_val]);
		std::cout << risultato;
		if (risultato == test2.res[indice_val]) std::cout << ".\n\n"; else std::cout << ".\n*** ERRORE ***\n\n\n\n";
	}
}

void report_test_predicate(const Test2<int> test2) {
	bool risultato{ 0 };

	if (test2.val.size() != test2.res.size()) {
		std::cerr << "\n\n\nErrore: Numero di test diffrente dal numero di risultati attesi.\n\n\n";
		return;
	}

	for (size_t indice_val = 0; indice_val < test2.val.size(); ++indice_val) {
		std::cout << "Cerco " << test2.val[indice_val] << " nella sequenza { ";
		for (size_t indice_seq = 1; indice_seq < test2.seq.size(); ++indice_seq) std::cout << test2.seq[(indice_seq - 1)] << ", ";
		if (test2.seq.size()) std::cout << *(test2.seq.end() - 1);
		std::cout << " }. Risultato atteso: " << test2.res[indice_val] << "; binary_search restituisce: ";
		risultato = binary_search(test2.seq.begin(), test2.seq.end(), test2.val[indice_val], predicate<int>);
		std::cout << risultato;
		if (risultato == test2.res[indice_val]) std::cout << ".\n\n"; else std::cout << ".\n*** ERRORE ***\n\n\n\n";
	}
}

int main() {
	// *** Test2 con int *** //
	std::fstream file_test("Tests_01.txt", std::fstream::trunc | std::fstream::in | std::fstream::out);

	if (!file_test.is_open()) return 1;

	prepara_tests_int(file_test);
	file_test.seekg(0); // posiziona il puntatore di lettura
	std::cout << "\n\n*** Esito Test con int ***\n\n";
	report_test<int>(file_test);
	file_test.close();

	// Proviamo con un cast implicito dove si perdono dati.
	Test2<Grande> test_grande;
	test_grande.label = "grandi.1";
	test_grande.val.push_back(Grande(5));
	test_grande.val.push_back(Grande(2));
	test_grande.seq.push_back(Grande(1));
	test_grande.seq.push_back(Grande(3)); 
	test_grande.seq.push_back(Grande(5));
	test_grande.seq.push_back(Grande(7));
	test_grande.res.push_back(1);
	test_grande.res.push_back(0);
	std::cout << "\n\n*** Esito Test con Grande ***\n\n";
	//report_test<Grande>(test_grande);
	//Test2<Grande>* test2_pg = new Test2<Grande>;
	//Test2<Piccolo> test_piccolo;
	Test2<Grande>* test2_pg = &test_grande;
	report_test(test2_pg);

	// utilizza la funzione predicate che incrementa il valore da confrontare.
	Test2<int> test2_int;
	test2_int.label = "Test2_INT.1";
	test2_int.val.push_back(3);
	test2_int.seq = { 1, 3, 5, 7, 9 };
	test2_int.res.push_back(1);

	report_test_predicate(test2_int);

	//delete test2_pg;

	return 0;
}