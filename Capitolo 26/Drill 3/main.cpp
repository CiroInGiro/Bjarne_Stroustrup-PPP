/* 
* Capitolo 26 Drill 3
* Basato sul paragrafo 26.3.1-3, completa un programma che genera:
* a. Una sequenza molto grande (come consideresti molto grande, e perché?);
* b. 10 sequenze con un numero casuale di elementi;
* c. 10 sequenze con 0,1,2...9 elementi casuali (ma rimanendo in ordine).
*/

/* 
* Ci serve una costante per il limite della sequenza molto grande.
* Ci serve un generatore di numeri casuali nel dominio dei numeri interi.
* Ci serve la possibilità di inserire in un contenitore i numeri in maniera ordinata velocemente.
* Ci serve la classe Test di Drill 1 a cui aggiungeremo l'operatore<< di output per creare il file.
*/

#include "../MyClass/Test.h"
#include <fstream>
#include <limits>
#include <random>
#include <string>

// inserisce un elemento nel vettore in modo da rimanere ordinato il vettore
void inserimento_ordinato(Test<int>& t, int& valore) {
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

bool ricerca_sequenziale(Test<int>& t, int& valore) {

	for (int elemento : t.seq) if (elemento == valore) return true;

	return false;
}

void aggiorna_val(Test<int>& t, bool esito_richiesto) {
	std::random_device rnd_device;
	std::mt19937 rnd_generatore(rnd_device());
	std::uniform_int_distribution<int> scelta_index(0, 0);
	std::uniform_int_distribution<int>::param_type parametri;
	std::uniform_int_distribution<int> interi_a_caso(0, INT_MAX);

	if (t.seq.size() == 0) {
		t.val = 0;
		t.res = 0;
		return;
	}

	if (esito_richiesto) {
		parametri = scelta_index.param();
		parametri._Init(0, (t.seq.size() - 1));
		scelta_index.param(parametri);
		int indice = scelta_index(rnd_generatore);
		t.val = t.seq[indice];
		t.res = 1;
	}
	else {
		t.res = 0;

		if (!ricerca_sequenziale(t, t.val)) {
			// valore già inesistemte
			return;
		}

		t.val = interi_a_caso(rnd_generatore);
		int sgancio_di_sicurezza = t.seq.size();

		while (ricerca_sequenziale(t, t.val) && sgancio_di_sicurezza) {
			t.val = interi_a_caso(rnd_generatore);
			--sgancio_di_sicurezza;
		}

		if (!sgancio_di_sicurezza) {
			t.res = 1;
		}
	}
}

int main() {
	Test<int> t;
	std::ofstream file_test("Drill3_Test.txt");
	constexpr int max_int = INT_MAX;
	//int max_int = 10; // Test su range ristretto OK
	//std::cout << max_int << std::endl; // test utilizzo intero più grande. OK
	//std::cout << (max_int * -1) << std::endl; // test utilizzo intero negativo più piccolo OK
	//return 1;

	std::random_device rnd_device;
	std::mt19937_64 rnd_generatore(rnd_device());
	std::uniform_int_distribution<int> interi_a_caso(0, max_int);
	std::uniform_int_distribution<int> numero_di_elementi_a_caso(0, 100);
	std::uniform_int_distribution<int> esito_casuale(0, 1);

	/*
	* Preparazione del test a.
	* Inizialmente ho considerato tutti i numeri positivi interi che l'architettura hardware consentisse ma contare fino a 2 migliardi portava via troppo tempo,
	* allora ho scelto gli ultimi 10000 numeri di questo range.
	*/

	t.label = "a.1";
	t.val = max_int;
	t.res = 1;

	//for (int numero = 0; numero <= max_int; ++numero) { // ciclo infinito perché per essere falso il confronto numero dovrebbe essere > INT_MAX
	for (int numero = (max_int - 10000); numero < max_int; ++numero) {
		//std::cout << numero << std::endl; // Test ciclo ci vuole molto tempo già per arrivare a 500K !
		t.seq.push_back(numero);
	}
	t.seq.push_back(max_int); // ultimo numero che volevamo utilizzare
	
	file_test << t << std::endl;

	/*
	* Preparazione del test b.
	* In un loop di 10 cicli generiamo un numero casuale [0, 10000) che indica il numero di elementi in una serie.
	* Un ciclo nidificato genera numeri casuali e riempe la sequenza.
	* Ci serve una funzione da chiamare che inserisca gli elementi casuali in ordine, senza doverli ordinare tutti alla fine.
	*/

	
	for (int test = 1; test <= 10; ++test) {
		// resetta t ai valori di default
		t.label = "b.";
		t.label += std::to_string(test);
		t.val = interi_a_caso(rnd_generatore);
		t.seq.clear();

		// preparazione del test
		int numero_di_elementi = numero_di_elementi_a_caso(rnd_generatore);

		for (int index = 0; index < numero_di_elementi; ++index) {
			int elemento = interi_a_caso(rnd_generatore);
			// inserisci in seq elemento
			inserimento_ordinato(t, elemento);
		}

		// cerca t.val in t.seq in maniera sicura e aggiorna t.res
		//if (ricerca_sequenziale(t, t.val)) t.res = 1; else t.res = 0; // vers.1: più è ampio il range dei numeri casuali e più è difficile indovinare un numero presente nella sequenza.

		// scelta a caso dell'esito del test
		bool esito = esito_casuale(rnd_generatore);
		aggiorna_val(t, esito);


		// esporta t nel file dei test
		file_test << t << std::endl;
	}
	
	/*
	* Preparazione del test c.
	* In un loop che va da 0 a 9 generiamo una sequenza con lo stesso numerodi elementi del loop riempita con numeri casuali [0, 10000).
	* Il ciclo nidificato quindi genera i numeri casuali e riempe la sequenza.
	* Utilizziamo la funzione che inserisca gli elementi casuali in ordine, senza doverli ordinare tutti alla fine.
	*/

	for (int test = 1; test <= 10; ++test) {
		// resetta t ai valori di default
		t.label = "c.";
		t.label += std::to_string(test);
		t.val = interi_a_caso(rnd_generatore);
		t.seq.clear();

		for (int index = 0; index < (test - 1); ++index) {
			int elemento = interi_a_caso(rnd_generatore);
			// inserisci in seq elemento
			inserimento_ordinato(t, elemento);
		}

		// cerca t.val in t.seq in maniera sicura e aggiorna t.res
		//if (ricerca_sequenziale(t, t.val)) t.res = 1; else t.res = 0;

		// scelta a caso dell'esito del test
		bool esito = esito_casuale(rnd_generatore);
		aggiorna_val(t, esito);

		// esporta t nel file dei test
		file_test << t << std::endl;
	}

	file_test.close();

	return 0;
}