/* Using hexadecimal literals, define short unsigned ints with:
* a. Every bit set;
* b. The lowest (least significant bit) set;
* c. The haighest (most significant bit) set;
* d. The lowest byte set;
* e. The highest byte set;
* f. Every second bit set (and the lowest bit 1);
* g. Every second bit set (and the lowest bit 0).
*/

#include <iostream>
#include <bitset>
#include <iomanip>

void stampa(const std::string pref, const short unsigned int& var) {
	std::cout << pref << ": " << std::setw(5) << var << " == " << std::bitset<sizeof(var) * 8>(var) << std::endl;
}

int main() {
	short unsigned int var{ 0 };

	// a.
	var = 0xFFFF;
	std::cout << "a: " << std::setw(5) << var << " == " << std::bitset<sizeof(var) * 8>(var) << std::endl;

	// b.
	var = 0x0001;
	std::cout << "b: " << std::setw(5) << var << " == " << std::bitset<sizeof(var) * 8>(var) << std::endl;

	// c. ogni cifra hex sono 4 bit quindi la prima cifra deve rappresentare 1000 binario che corrsisponde al valore 8
	var = 0x8000;
	//std::cout << "c: " << std::setw(5) << var << " == " << std::bitset<sizeof(var) * 8>(var) << std::endl;
	stampa("c", var);

	// d. 1 byte sono 8 bit
	var = 0x00FF;
	stampa("d", var);

	// e. il contrario del precedente
	var = 0xFF00;
	stampa("e", var);

	// f. i secondi bit di ogni cifra hex?
	var = 0x2223;
	stampa("f", var);

	// g. come il precedente
	var = 0x2222;
	stampa("g", var);

	return 0;
}