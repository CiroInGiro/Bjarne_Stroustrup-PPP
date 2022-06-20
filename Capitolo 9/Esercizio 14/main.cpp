/*
Capitolo 9 Esercizio 14
Crea e implementa una classe Money per i calcoli con dollari e centesimi utilizzando l'arrotondamento 4/5 (da .5 cent si arrotondo per eccesso mentre per valori inferiori per troncamento).
Rappresenta un importo monetario sotto forma di centesimi in un long int ma gli input e output in dollari e centesimi, ad esempio $ 123.45.
Non preoccuparti se l'ammontare non entra in un long int.
*/
// bug: letto la prima digit in operator>> non è stata considerata, aggiunto cin.putback(carattere)
// bug: in arrotondamento() è stata tolta la parte sinistra della virgola senza considerare lo slittamento, aggiunti i 2 zero occupati dai decimali
// bug: in print() per riportare i centesimi in dollari si è diviso per 100 che è un intero, questo taglia i decimali, si è diviso allora per 100.0 che è un double.

/*
Capitolo 9 Esercizio 15
Affina la classe Money aggiungendo la valuta (aggiungilo al costruttore).
Accetta una inizializzazione a virgola mobile come long in modo che può essere rappresentato proprio come un long int.
Non accettare operazioni illegali.
Ad esempio Money*Money non ha senso, mentre USD1.23+DKK5.00 ha senso solo se provvedi ad una tabella di conversione per le conversioni tra USD (US Dollar) e DKK (Danish Kroner).
*/
// Mi è venuto il dubbio che l'esercizio 14 intendesse la classe Money tipo Calculator, che esegua i calcoli di tipo finanziario, aggiungo allora la funzione membro calcola()
// bug: anche per l'operatore << è stato eseguito il calcolo di divisione per 100 che è un intero e veniva fatta una conversione implicita ad int trocando i decimali, è stato diviso per 100.0

/*
Capitolo 9 Esercizio 16
Definisci un operatore>> che legga l'ammontare con la valuta, come USD12.3 nella variabile Money.
Definisci anche il corrispondente operatore di output <<.
*/
// E' stato già impostato cos' dall'inizio e nell'esercizio precedente è stata aggiunta la valuta.

/*
Capitolo 9 Esercizio 17
Fornisci un esempio di calcolo in cui un Rational dia un risultato migliore di Money
*/
// Ad esempio 0.75 dollari o 0.50 euro possono essere rappresentati come 3/4 di dollaro o 1/2 euro.

/*
Capitolo 9 Esercizio 18
Fornisci un esempio dove un rational può dare un risultato migliore di un double
*/
// Forse per un double con molti decimali e prossimo ad una frazione nota come 2/3.

#include "Money.h"

int main(int argc, char* argv) {
	try {
		Money banca, contanti;

		std::cout << "Saldo iniziale del C/C Bancario nella forma VVV0 (3 lettere per la valuta tra EUR, USD e DDK e il valore)? ";
		std::cin >> banca;
		std::cout << "\nSoldi attuali che hai in tasca nella forma VVV0 (3 lettere per la valuta tra EUR, USD e DDK e il valore)? ";
		std::cin >> contanti;
		std::cout << "\nHai " << banca << " sul C/C mentre in tasca hai: \n";
		contanti.print();
		Money conto_estero("DDK", 0);
		std::cout << "\n\ntrasferisco tutto sul nuovo conto in DDK:\n";
		conto_estero = conto_estero + banca + contanti; // ho sommato anche se stesso per far capire la valuta che voglio come conversione finale, quella più a sinistra.
		std::cout << "Bene, ora sul nuovo conto ho: " << conto_estero << std::endl;
	}
	catch (Money::Error errore) {
		std::cout << "Ahia!";
	}

	return 0;
}