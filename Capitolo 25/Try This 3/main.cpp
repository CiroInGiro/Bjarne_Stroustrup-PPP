/* Il seguente esempio sembra innocente
// ma è un loop infinito
*/

#include <iostream>

void infinite() {
	unsigned char max = 160; // very large 

	// sono utilizzati 7 bit che danno un valore massimo di 127
	for (signed char i = 0; i < max; ++i) std::cout << int(i) << '\n';
}

int main() {
	// ora chiamo la funzione che genera un loop infinito
	// questo perché max utilizza il bit 8 e i che al bit 8 utilizza il segno diventerà negativo non appena il contatore superi 127
	// a quel punto servirà impostare il bit 8 ad 1 per avere un valore > di 127 ma per un signed significa un valore negativo
	// e il ciclo continua perché i sarà ancora minore di max
	infinite();
}

/* si infatti stampa i numeri da 0 a 127
*  poi inizia a stampare -128 fino a 0
*  da qui si ricomincia.
*/