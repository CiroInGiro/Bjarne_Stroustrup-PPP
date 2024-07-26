/*
* Do 3 and 4 using bit manipolation operations (|, &, <<) and only the literals 1 and 0.
*/

#include <iostream>
#include <iomanip>
#include <bitset>

void stampa(const std::string pref, const short unsigned int& var) {
	std::cout << pref << ": " << std::setw(5);
	std::cout << std::dec << var << " == ";
	std::cout << std::bitset<sizeof(var) * 8>(var) << " == ";
	std::cout << std::showbase << std::hex << var << std::endl;
}

int main() {
	short unsigned int var{ 0 };

	// a.
	//var = 0xFFFF;
	var = 1;
	for (size_t pos = 1; pos < (sizeof(var) * 8); ++pos) {
		var <<= 1; // sposto i bit di 1 a sx e assegno il nuovo valore a var
		var |= 1; // sommo con i bit del valore 1
	}
	stampa("a", var);

	// b.
	//var = 0x0001;
	var &= 0; // azzero i bit per iniziare da capo
	var |= 1;
	stampa("b", var);

	// c. ogni cifra hex sono 4 bit quindi la prima cifra deve rappresentare 1000 binario che corrsisponde al valore 8
	//var = 0x8000;
	var &= 0;
	var |= 1;
	var <<= 15;
	stampa("c", var);

	// d. 1 byte sono 8 bit
	//var = 0x00FF;
	var = 1;
	for (size_t pos = 1; pos < ((sizeof(var) * 8) / 2); ++pos) {
		var <<= 1;
		var |= 1;
	}
	stampa("d", var);

	// e. il contrario del precedente
	//var = 0xFF00;
	var &= 0;
	for (size_t pos = 0; pos < (sizeof(var) * 8); ++pos) {
		if (pos <= ((sizeof(var) * 8) / 2)) var |= 1; // metà dei bit
		var <<= 1;
	}
	stampa("e", var);

	// f. i secondi bit di ogni cifra hex?
	//var = 0x2223;
	var &= 0;
	for (size_t bit4 = 0; bit4 < ((sizeof(var) * 8) / 2); ++bit4) {
		var |= 1;
		var <<= 4; // va al byte successivo, un altro spostamento è stato già fatto
	}
	var |= 1;
	var <<= 1;
	var |= 1;
	stampa("f", var);

	// g. come il precedente
	//var = 0x2222;
	var &= 0;
	for (size_t bit4 = 0; bit4 < ((sizeof(var) * 8) / 2); ++bit4) {
		var |= 1;
		var <<= 4; // potrei anche slittare di 8 e non mi trovo
	}
	var |= 1;
	var <<= 1;
	stampa("g", var);

	return 0;
}