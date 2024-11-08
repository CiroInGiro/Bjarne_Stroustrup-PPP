/*
* Capitolo 26 Drill 4
* Ripetere questi test per sequenze di stringhe, come { Bohr Darwin Einstein Lavoisier Newton Turing }.
*/

#include "../MyClass/Test.h"
#include <fstream>
#include <limits>
#include <random>
#include <string>

// inserisce un elemento nel vettore in modo da rimanere ordinato il vettore
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

template <class T>
bool ricerca_sequenziale(Test<T>& t, T& valore) {

	for (T elemento : t.seq) if (elemento == valore) return true;

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
	// Prepariamo un insieme di stringhe in cui ricercare e un insieme di stringhe campione per la ricerca.
	std::vector<std::string> dominio_stringhe{ "Tower", "CPU", "GPU", "APU", "MotherBoard", "Mouse", "Tastiera", "Elettrone", "Quantum" };
	std::vector<std::string> stringhe_ricerca{ "Mouse", "ALU", "MiddleTower", "Guanto", "Moto", "CPU" };
	Test<std::string> t; // Test che lavora sulle stringhe
	std::ofstream file_test("Drill4_Test.txt");
	std::random_device rnd_device;
	std::mt19937_64 rnd_generatore(rnd_device());
	std::uniform_int_distribution<int> numero_di_elementi_a_caso(0, 1000);
	std::uniform_int_distribution<int> indici_a_caso(0, (dominio_stringhe.size() - 1));
	std::uniform_int_distribution<int> scelta_campione(0, (stringhe_ricerca.size() - 1));

	/*
	* Preparazione del test a.
	* Inizialmente ho considerato tutti i numeri positivi interi che l'architettura hardware consentisse ma contare fino a 2 migliardi portava via troppo tempo,
	* allora ho scelto gli ultimi 10000 numeri di questo range.
	*/

	t.label = "a.1";
	t.val = stringhe_ricerca[(scelta_campione(rnd_generatore))];

	for (int numero = 0; numero < 10000; ++numero) {
		t.seq.push_back(dominio_stringhe[indici_a_caso(rnd_generatore)]);
	}

	t.res = ricerca_sequenziale(t, t.val);
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
		t.val = stringhe_ricerca[scelta_campione(rnd_generatore)];
		t.seq.clear();

		// preparazione del test
		int numero_di_elementi = numero_di_elementi_a_caso(rnd_generatore);

		for (int index = 0; index < numero_di_elementi; ++index) {
			std::string elemento = dominio_stringhe[indici_a_caso(rnd_generatore)];
			// inserisci in seq elemento
			inserimento_ordinato(t, elemento);
		}

		// Esito atteso del test
		t.res = ricerca_sequenziale(t, t.val);

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
		t.val = stringhe_ricerca[scelta_campione(rnd_generatore)];
		t.seq.clear();

		for (int index = 0; index < (test - 1); ++index) {
			std::string elemento = dominio_stringhe[indici_a_caso(rnd_generatore)];
			// inserisci in seq elemento
			inserimento_ordinato(t, elemento);
		}

		// cerca t.val in t.seq in maniera sicura e aggiorna t.res
		t.res = ricerca_sequenziale(t, t.val);

		// esporta t nel file dei test
		file_test << t << std::endl;
	}

	file_test.close();

	return 0;
}