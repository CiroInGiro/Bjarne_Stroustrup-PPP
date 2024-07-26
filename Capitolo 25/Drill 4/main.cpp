/* 
* Print each as a decimal and as a hexidecimal.
*/

#include <iostream>
#include <iomanip>

void stampa(const std::string pref, const short unsigned int& var) {
	std::cout << pref << ": " << std::setw(5);
	std::cout << std::dec << var << " == ";
	std::cout << std::showbase << std::hex << var << std::endl;
}

int main() {
	short unsigned int var{ 0 };

	// a.
	var = 0xFFFF;
	stampa("a", var);

	// b.
	var = 0x0001;
	stampa("b", var);

	// c. ogni cifra hex sono 4 bit quindi la prima cifra deve rappresentare 1000 binario che corrsisponde al valore 8
	var = 0x8000;
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