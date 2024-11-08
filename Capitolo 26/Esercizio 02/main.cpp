/*
*  Capitolo 26 Esercizio 2
* Modifica il test di binary_search per lavorare con tipi arbitrary di elementi.
* Dunque, testala con sequenze di string e numeri in virgola mobile.
*/

#include "../MyClass/Test.h"
#include <iostream>
#include <fstream>
#include <string>
#include <limits>
#include <random>
#include <sstream>

// funzione di ricerca binaria scritta al paragrafo 26.1 versione template
template<class T>
bool ricerca_v(const std::vector<T>& v, const T& num, size_t& pos) {
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
// funzione che lavora con int
void prepara_tests_int(std::ostream& out) {
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

// Funzione come float
void prepara_tests_float(std::ostream& out) {
	Test<float> test;
	std::random_device rnd_device;
	std::mt19937 rnd_generatore(rnd_device());
	std::uniform_int_distribution<int> lunghezza_sequenza(0, 10);
	std::numeric_limits<float> virgola;
	constexpr float max = virgola.max();
	std::uniform_real_distribution<float> elemento_casuale(0.0, max);

	// una sequenza ordinaria
	test.label = "a.1";
	test.val = 8.0;
	float precedente1{ 1.0 }, precedente2{ 2.0 };
	test.seq.push_back(precedente1);
	test.seq.push_back(precedente2);

	for (int elemento = 2; elemento < 10; ++elemento) {
		test.seq.push_back((precedente1 + precedente2));
		precedente1 = test.seq[(elemento - 1)];
		precedente2 = test.seq[(elemento)];
	}

	test.res = 1;
	out << test << std::endl;

	// sequenza vuota
	test.label = "b.1";
	test.val = 8.0;
	test.seq.clear();
	test.res = 0;
	out << test << std::endl;

	// sequenza di un elemento
	test.label = "c.1";
	test.val = 1.0;
	test.seq.push_back(1.0);
	test.res = 1;
	out << test << std::endl;

	// sequenza di un numero pari di elementi
	test.label = "d.1";
	test.val = 5.0;
	test.seq.clear();

	for (int elemento = 1; elemento < 5; ++elemento) {
		test.seq.push_back(elemento);
	}

	test.res = 0;
	out << test << std::endl;

	// sequenza di un numero dispari di elementi
	test.label = "d.2";
	test.val = 5.0;
	test.seq.clear();

	for (int elemento = 1; elemento < 6; ++elemento) {
		test.seq.push_back(elemento);
	}

	test.res = 1;
	out << test << std::endl;

	// tutti gli elementi uguali
	test.label = "uguali";
	test.val = 2.0;
	test.seq.clear();

	for (int indice = 0; indice < 7; ++indice) test.seq.push_back(1.0);

	test.res = 0;
	out << test << std::endl;

	// elemento iniziale differente
	test.label = "differente.1";
	test.val = 2.0;
	test.seq.clear();
	test.seq.push_back(1.0);

	for (int indice = 0; indice < 7; ++indice) test.seq.push_back(2.0);

	test.res = 1;
	out << test << std::endl;

	// elemento finale differente
	test.label = "differente.last";
	test.val = 8.2;
	test.seq.clear();

	for (int indice = 0; indice < 7; ++indice) test.seq.push_back(1.0);

	test.seq.push_back(8.2);

	test.res = 1;
	out << test << std::endl;

	// sequenza con molti elementi.
	test.label = "large.1";
	test.val = 2000.0;
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
			test.val = 0.0;
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
			float val_elem = elemento_casuale(rnd_generatore);
			// inserimento ordinato
			inserimento_ordinato(test, val_elem);
		}

		test.val = test.seq[(test.seq.size() / 2)];
		test.res = 1;
		out << test << std::endl;
	}
}

// Funzione come string
void prepara_tests_str(std::ostream& out) {
	Test<std::string> test;
	std::random_device rnd_device;
	std::mt19937 rnd_generatore(rnd_device());
	std::uniform_int_distribution<int> lunghezza_sequenza(0, 10);
	std::numeric_limits<int> interi;
	constexpr int max = interi.max();
	std::uniform_int_distribution<int> elemento_casuale(0, max);
	//std::uniform_int_distribution<int>::param_type indice_parametri;

	// una sequenza ordinaria
	test.label = "a.1";
	test.val = "8";
	int precedente1{ 1 }, precedente2{ 2 };
	test.seq.push_back("1");
	test.seq.push_back("2");

	for (int elemento = 2; elemento < 10; ++elemento) {
		int totale = (precedente1 + precedente2);
		test.seq.push_back(std::to_string(totale));
		precedente1 = atoi(test.seq[(elemento - 1)].c_str());
		precedente2 = atoi(test.seq[(elemento)].c_str());
	}

	test.res = 1;
	out << test << std::endl;

	// sequenza vuota
	test.label = "b.1";
	test.val = "8";
	test.seq.clear();
	test.res = 0;
	out << test << std::endl;

	// sequenza di un elemento
	test.label = "c.1";
	test.val = "1";
	test.seq.push_back("1");
	test.res = 1;
	out << test << std::endl;

	// sequenza di un numero pari di elementi
	test.label = "d.1";
	test.val = "5";
	test.seq.clear();

	for (int elemento = 1; elemento < 5; ++elemento) {
		test.seq.push_back(std::to_string(elemento));
	}

	test.res = 0;
	out << test << std::endl;

	// sequenza di un numero dispari di elementi
	test.label = "d.2";
	test.val = "5";
	test.seq.clear();

	for (int elemento = 1; elemento < 6; ++elemento) {
		test.seq.push_back(std::to_string(elemento));
	}

	test.res = 1;
	out << test << std::endl;

	// tutti gli elementi uguali
	test.label = "uguali";
	test.val = "2";
	test.seq.clear();

	for (int indice = 0; indice < 7; ++indice) test.seq.push_back("1");

	test.res = 0;
	out << test << std::endl;

	// elemento iniziale differente
	test.label = "differente.1";
	test.val = "2";
	test.seq.clear();
	test.seq.push_back("1");

	for (int indice = 0; indice < 7; ++indice) test.seq.push_back("2");

	test.res = 1;
	out << test << std::endl;

	// elemento finale differente
	test.label = "differente.last";
	test.val = "8";
	test.seq.clear();

	for (int indice = 0; indice < 7; ++indice) test.seq.push_back("1");

	test.seq.push_back("8");

	test.res = 1;
	out << test << std::endl;

	// sequenza con molti elementi.
	test.label = "large.1";
	test.val = "2000";
	test.seq.clear();

	for (int elemento = 0; elemento < 2001; ++elemento) test.seq.push_back(std::to_string(elemento));

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
			test.seq.push_back(std::to_string((indice * 5 / 2)));
		}

		if (num_elems) { // sequenza non di zero elementi
			test.val = test.seq[(num_elems / 2)];
			test.res = 1;
		}
		else { // sequenza con almeno 1 elemento
			test.val = "0";
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
			std::string val_elem = std::to_string(elemento_casuale(rnd_generatore));
			// inserimento ordinato
			inserimento_ordinato(test, val_elem);
		}

		test.val = test.seq[(test.seq.size() / 2)];
		test.res = 1;
		out << test << std::endl;
	}
}

template<class T>
void report_test(std::istream& file_test) {
	// leggiamo i test per darli in pasto a binary_search
	for (Test<T> t; file_test >> t;) {
		size_t indice{ 0 };
		bool esito = ricerca_v(t.seq, t.val, indice);
		std::cout << t << std::endl;
		std::cout << "Cerchiamo " << t.val << " nella sequenza e ricerca_v restituisce " << esito;
		if (esito) std::cout << " e aggiorna indice a " << indice << " che corrisponde nella sequenza a " << t.seq[indice];
		std::cout << std::endl;
		std::cout << "****************************************" << std::endl << std::endl;
	}
}

void debug() {
	// *** Debug rnd_seq.1 *** //
	std::istringstream debug_iss{ "{ rnd_seq.1 10 { 0 2 5 7 10 12 15 17 } 1 }" };
	Test<std::string> rnd_seq1;
	debug_iss >> rnd_seq1;
	size_t debug_indice{ 0 };
	bool debug_esito = ricerca_v(rnd_seq1.seq, rnd_seq1.val, debug_indice);
	
	/* 
	* Il confronto tra le stringhe "7" e "10" con operatore < da falso perché si inizia il confronto col primo carattere
	* quindi l'esito "7" < "1" false.
	*/

	// *** Debug rnd_seq.6 *** //
	debug_iss.str("{ rnd_seq.6 10 { 0 2 5 7 10 12 15 17 20 } 1 }");
	Test<std::string> rnd_seq6;
	debug_iss >> rnd_seq6;
	debug_esito = ricerca_v(rnd_seq6.seq, rnd_seq6.val, debug_indice);

	/*
	* In questo caso funziona perché capita nel confronto di ugualianza con la stringa "10"
	* che si trova su uno degli estremi: start, middle o end.
	* In questo esempio si confronta "10" == *middle che corrisponde a "10"
	*/

	// *** Debug rnd_seq.4 *** //
	debug_iss.str("{ rnd_seq.4 7 { 0 2 5 7 10 12 } 1 }");
	Test<std::string> rnd_seq4;
	debug_iss >> rnd_seq4;
	debug_esito = ricerca_v(rnd_seq4.seq, rnd_seq4.val, debug_indice);

	/*
	* Al confronto, prima partizione, di "7" con *end che corrisponde a "12" con operatore <
	* ancora risulta falso perché il carattere '7' non è minore del carattere '1'
	*/

	// *** Debug rnd_seq.10 *** //
	debug_iss.str("{ rnd_seq.10 5 { 0 2 5 7 10 } 1 }");
	Test<std::string> rnd_seq10;
	debug_iss >> rnd_seq10;
	debug_esito = ricerca_v(rnd_seq10.seq, rnd_seq10.val, debug_indice);

	/* 
	* Anche in questo caso la condizione "5" < "10" (che si trova su *(end - 1)) risulta falso
	* perché il carattere '5' è maggiore del '1' come valore intero.
	*/
}

int main() {
	// *** debug ***
	//debug(); return 99;

	// *** Test con int *** //
	std::fstream file_test("Tests_01.txt", std::fstream::trunc | std::fstream::in | std::fstream::out);

	if (!file_test.is_open()) return 1;

	prepara_tests_int(file_test);
	file_test.seekg(0); // posiziona il puntatore di lettura
	std::cout << "\n\n*** Esito Test con int ***\n\n";
	report_test<int>(file_test);
	file_test.close();

	// *** Test con float ***//
	file_test.open("Tests_02.txt", std::fstream::trunc | std::fstream::in | std::fstream::out);

	if (!file_test.is_open()) return 2;

	prepara_tests_float(file_test);
	file_test.seekg(0);
	std::cout << "\n\n*** Esito Test con float ***\n\n";
	report_test<float>(file_test);
	file_test.close();

	// *** Test con string ***//
	file_test.open("Tests_03.txt", std::fstream::trunc | std::fstream::in | std::fstream::out);

	if (!file_test.is_open()) return 3;

	prepara_tests_str(file_test);
	file_test.seekg(0);
	std::cout << "\n\n*** Esito Test con string ***\n\n";
	report_test<std::string>(file_test);
	file_test.close();

	return 0;
}

/*
* { rnd_seq.1 10 { 0 2 5 7 10 12 15 17 } 1 }
* Cerchiamo 10 nella sequenza e ricerca_v restituisce 0
* Dovrebbe restituire 1 ma il confronto con stringhe controlla il valore intero assegnato a quel carattere e non il valore che rappresenta.
* Eseguo il debug...
* 
* { rnd_seq.6 10 { 0 2 5 7 10 12 15 17 20 } 1 }
* Cerchiamo 10 nella sequenza e ricerca_v restituisce 1 e aggiorna indice a 4 che corrisponde nella sequenza a 10
* In questa sequenza col 10 ma più lunga ha funzionato
* Eseguo il debug...
*
* { rnd_seq.4 7 { 0 2 5 7 10 12 } 1 }
* Cerchiamo 7 nella sequenza e ricerca_v restituisce 0
* Ci dovremmo trovare 7 in start alla seconda partizione
* Eseguo il debug...
*
* { rnd_seq.10 5 { 0 2 5 7 10 } 1 }
* Cerchiamo 5 nella sequenza e ricerca_v restituisce 0
* 
* Dovrò controllare il comportamento sul partizionamento in caso di stringhe.
*/