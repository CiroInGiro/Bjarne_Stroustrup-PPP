/* Disegna i bit su un pezzo di carta.
* Usando la carta poi figura quale sarebbe la risposta per si = 128.
* Quindi esegui il programma per vedere se la macchina è d'accordo.
*/

#include <iostream>
#include <bitset>

void print(int i) {
	std::cout << "int i: " << int(i) << " == " << std::bitset<8*sizeof(int)>(i) << '\n';
}

int main() {
	int si = 128;
	print(si);
	char c = si;
	print(c);
	unsigned char uc = si;
	print(uc);
	signed char sc = si;
	print(sc);

	return 0;
}

/*
* int si = 128; 00000000 00000000 00000000 10000000
* char c = si;  10000000 // -127 complementare di tutti 1 <- ho dimenticato che è il corrispondente del positivo + 1, quindi -128
* unsigned char uc = si; 10000000 // 128 8 bit per i valori positivi
* signed char sc = si; 10000000 // -127 come char <- anche qui -128
*/