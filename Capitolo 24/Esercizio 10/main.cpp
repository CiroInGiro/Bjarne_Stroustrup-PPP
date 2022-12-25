/* Capitolo 24 Esercizio 10
* Quanto è casuale il tuo default_random_engine? 
* Scrivete un programma che prenda due numeri interi n e d come input e chiami randint(n) d volte, registrando il risultato.
* Emetti il numero di estrazioni per ciascuno di [0:n) e "eyeball" quanto sono simili i conteggi. 
* Prova con valori bassi per n e con valori bassi per d per vedere se disegnare solo pochi numeri casuali provoca evidenti distorsioni.
*/

#include <iostream>
#include <random>

int main(int argc, char** argv) {
	// creo il motore (engine)
	std::default_random_engine rnde{};
	// creo il generatore di numeri
	std::normal_distribution<double> rnd_gen{ 15, 4.0 };
	std::vector<int> righe(30);

	for (int i = 0; i < 30; ++i) {
		// uso l'engine col generatore per riempire il vettore
		righe[i] = rnd_gen(rnde);
	}

	// stampo graficamente i numeri generati
	for (int r : righe) {
		for (int i = 0; i < r; ++i) std::cout << "*";
		std::cout << std::endl;
	}

	return 0;
}