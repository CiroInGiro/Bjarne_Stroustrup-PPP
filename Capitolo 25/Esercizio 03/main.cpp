/* Esercizio 3 Capitolo 25
* Inizializza un intero 32 bit segnato con le bit patterns e stampa il risultato:
* tutti 0;
* tutti 1;
* alternando 1 e 0 partendo col più a sinistra 1;
* alternando 0 e 1 partendo col più a sinistra 0;
* pattern 110011001100...;
* pattern 001100110011...;
* pattern con byte tutti 1 poi tutti 0 partendo col byte di 1;
* pattern con byte tutti 1 poi tutti 0 partendo col byte di 0.
* Ripeti l'esercizio con un intero 32 bit non segnato.
*/

#include <iostream>
#include <assert.h>
#include <bitset>

int main() {
	using std::cout;
	using std::endl;
	signed int i32{ 0 };
	unsigned int ui32{ 0 };

	cout << "32 bit intero segnato:\n";

	assert(sizeof(i32) * 8 == 32, "int non è a 32 bit");
	
	// tutti bit 0
	cout << "tutti 0: " << std::bitset<sizeof(i32) * 8>(i32) << " dec: " << i32 << endl << endl;

	// tutti 1
	i32 = 0xFFFFFFFF;
	cout << "tutti 1: " << std::bitset<sizeof(i32) * 8>(i32) << " dec: " << i32 << endl << endl;

	// 1 e 0 partendo dal più significativo 1
	bool alterno = 1;
	i32 = 0;
	for (size_t i = 1; i < (sizeof(i32) * 8); ++i) {
		i32 |= alterno;
		i32 <<= 1;
		alterno = !alterno;
	}
	cout << "1 e 0 alternati: " << std::bitset<sizeof(i32) * 8>(i32) << " dec: " << i32 << endl << endl;

	// 0 e 1 partendo col più significativo a 0
	alterno = 0;
	i32 = 0;
	for (size_t i = 1; i < (sizeof(i32) * 8); ++i) {
		i32 <<= 1;
		alterno = !alterno;
		i32 |= alterno;
	}
	cout << "0 e 1 alternati: " << std::bitset<sizeof(i32) * 8>(i32) << " dec: " << i32 << endl << endl;

	// alternati 2 volte 1 e 2 volte 0 partendo dagli 11 (110011001100...)
	// 1100 sarebbe 12 in decimale che in esadecimale corrisonde alla C
	i32 = 0xCCCCCCCC;
	cout << "11001100...: " << std::bitset<sizeof(i32) * 8>(i32) << " dec: " << i32 << endl << endl;

	// alternati 2 volte 0 e 2 volte 1 partendo dagli 00 (001100110011...)
	// 0011 sarebbe 3 in decimale che in esadecimale corrisonde al 3
	i32 = 0x33333333;
	cout << "00110011...: " << std::bitset<sizeof(i32) * 8>(i32) << " dec: " << i32 << endl << endl;

	// dobbiamo alternare byte con bit a 1 e byte con bit a 0 iniziando dagli 1
	// 11111111 sarebbe 256 in decimale che in esadecimale corrisonde al 0xFF
	i32 = 0xFF00FF00;
	cout << "111100001111...: " << std::bitset<sizeof(i32) * 8>(i32) << " dec: " << i32 << endl << endl;

	// dobbiamo alternare byte con bit a 0 e byte con bit a 1 iniziando dagli 0
	// 11111111 sarebbe 256 in decimale che in esadecimale corrisonde al 0xFF
	i32 = 0x00FF00FF;
	cout << "000011110000...: " << std::bitset<sizeof(i32) * 8>(i32) << " dec: " << i32 << endl << endl;

	// con un intero non segnato
	cout << "\n\n\n32 bit intero non segnato:\n";

	// tutti bit 0
	cout << "tutti 0: " << std::bitset<sizeof(ui32) * 8>(ui32) << " dec: " << ui32 << endl << endl;

	// tutti 1
	ui32 = 0xFFFFFFFF;
	cout << "tutti 1: " << std::bitset<sizeof(ui32) * 8>(ui32) << " dec: " << ui32 << endl << endl;

	// 1 e 0 partendo dal più significativo 1
	alterno = 1;
	ui32 = 0;
	for (size_t i = 1; i < (sizeof(ui32) * 8); ++i) {
		ui32 |= alterno;
		ui32 <<= 1;
		alterno = !alterno;
	}
	cout << "1 e 0 alternati: " << std::bitset<sizeof(ui32) * 8>(ui32) << " dec: " << ui32 << endl << endl;

	// 0 e 1 partendo col più significativo a 0
	alterno = 0;
	ui32 = 0;
	for (size_t i = 1; i < (sizeof(ui32) * 8); ++i) {
		ui32 <<= 1;
		alterno = !alterno;
		ui32 |= alterno;
	}
	cout << "0 e 1 alternati: " << std::bitset<sizeof(ui32) * 8>(ui32) << " dec: " << ui32 << endl << endl;

	// alternati 2 volte 1 e 2 volte 0 partendo dagli 11 (110011001100...)
	// 1100 sarebbe 12 in decimale che in esadecimale corrisonde alla C
	ui32 = 0xCCCCCCCC;
	cout << "11001100...: " << std::bitset<sizeof(ui32) * 8>(ui32) << " dec: " << ui32 << endl << endl;

	// alternati 2 volte 0 e 2 volte 1 partendo dagli 00 (001100110011...)
	// 0011 sarebbe 3 in decimale che in esadecimale corrisonde al 3
	ui32 = 0x33333333;
	cout << "00110011...: " << std::bitset<sizeof(ui32) * 8>(ui32) << " dec: " << ui32 << endl << endl;

	// dobbiamo alternare byte con bit a 1 e byte con bit a 0 iniziando dagli 1
	// 11111111 sarebbe 256 in decimale che in esadecimale corrisonde al 0xFF
	ui32 = 0xFF00FF00;
	cout << "111100001111...: " << std::bitset<sizeof(ui32) * 8>(ui32) << " dec: " << ui32 << endl << endl;

	// dobbiamo alternare byte con bit a 0 e byte con bit a 1 iniziando dagli 0
	// 11111111 sarebbe 256 in decimale che in esadecimale corrisonde al 0xFF
	ui32 = 0x00FF00FF;
	cout << "000011110000...: " << std::bitset<sizeof(ui32) * 8>(ui32) << " dec: " << ui32 << endl << endl;

	return 0;
}