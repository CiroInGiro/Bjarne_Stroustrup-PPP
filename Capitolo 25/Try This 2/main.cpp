/*
* Fai funzionare l'esempio dei bit e prova alcuni valori per sviluppare un'idea delle rappresentazioni binarie ed esadecimali.
* Se ti confondi sulla rappresentazione dei valori negativi, riprova dopo aver letto §25.5.3. 
*/

#include <iostream>
#include <bitset>

int main(int argc, char** argv) {
	for (unsigned i; std::cin >> i;) {
		std::cout << std::dec << i
			<< " == " << std::hex << " 0x" << i
			<< " == " << std::bitset<8 * sizeof(unsigned)>{i} << '\n';
	}
	return 0;
}

/* In pratica i numeri negativi sono il risultato matematico di togliere 1 unità
* e fare il complementare dei bit risultanti.
* Quindi si può moltiplicare prima per tutti i bit a 1 tranne il meno significativo per togliere l'unità
* e poi invertire i bit.
*/
