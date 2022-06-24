/*
C'è un altro modo per calcolare il fattoriale di un numero ed è questo:
int fact(int n) { n > 1? n*fact(n-1) : 1; }
essa controlla prima se n>1 e per fact(4) calcola prima 4*fact(3), poi ovviamente diventa 4*3*fact(2) fino a 4*3*2*fact(1) che sarebbe 4*3*2*1, prova a vedere se funziona.
Una funzione che chiama se stessa si chiama ricorsiva.
L'alternativa che abbiamo visto al paragrafo 15.5 si chiama iterativa perché itera attraverso i valori (ciclo while).
Verifica che la fact() ricorsiva funzioni dando gli stessi risultati della fact() iterativa, calcolando il fattoriale dei valori 0,1,2,3,4 fino ad includere 20.
Quale implementazione preferisci e perché?
*/

/*
con entrambe riusciamo a calcolare il fattoriale fino al numero 15 ma questo lo sapevamo dagli esercizi precedenti, dovuto al limite di bit per un intero.
la funzione ricorsiva è più elegante e usa meno codice, la preferisco.
Bisogna però stare attenti perché ogni chiamata ricorsiva crea un nuovo record nella tabella virtuale dell'elenco funzioni, la quale potrebbe raggiungere il suo limite.
Quindi per piccoli cicli la preferenza va sicuramente alla ricorsiva, per grandissime ricorsioni allora è meglio andare sul sicuro e scegliere di iterare.
*/

#include <iostream>

int fact_ricorsivo(int n) {
	return n > 1 ? n * fact_ricorsivo(n - 1) : 1;
}

int fact_iterattivo(int n) {
	int retVal{ 1 };
	int fatt{ n };
	while (fatt > 1) {
		retVal *= fatt;
		--fatt;
	}
	return retVal;
}

int main(int argc, char** argv) {
	using std::cout;
	using std::endl;
	for (int fattoriale = 0; fattoriale <= 20; ++fattoriale) {
		cout << "Calcoliamo il fattoriale di " << fattoriale << ":" << endl;
		cout << "con la funzione iterattiva, risultato: " << fact_iterattivo(fattoriale) << ";" << endl;
		cout << "con la funzione ricorsiva, risultato:  " << fact_ricorsivo(fattoriale) << ";" << endl;
		cout << endl;
	}
	std::cin.get();
	return 0;
}