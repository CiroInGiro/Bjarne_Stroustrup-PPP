/* Capitolo 26 Drill 1
* Implementa l'operatore di Input '<' per Test del Paragrafo 26.3.2.2 
*/

/* Test 1.5: t.val viene letto in input come 0 invece di -7; abbiamo un falso riscontro.
* Il problema era nel file txt, col copia e incolla il carattere '-' era il -106 invece del segno matematico 45.
* Ho aggiunto 2 righe di test con label 0.x per i numeri negativi.
*/

/* Capitolo 26 Drill 2
* Completare un file di test per le sequenze del §26.3:

a. { 1 2 3 5 8 13 21 }                            // an “ordinary sequence”
b. { }
c. { 1 }
d. { 1 2 3 4 }                                         // even number of elements
e. { 1 2 3 4 5 }                                       // odd number of elements
f. { 1 1 1 1 1 1 1 }                                 // all elements equal
g. { 0 1 1 1 1 1 1 1 1 1 1 1 1 }              // different element at beginning
h. { 0 0 0 0 0 0 0 0 0 0 0 0 0 1 }           // different element at end

*/

/* Aggiunti allo stesso file di tests con label dalla a alla h.
*/

#include "Test.h"
#include "binary_search.h"
#include <iostream>
#include <fstream>

int test_all(std::istream& is) {
	int error_count{ 0 };
	for (Test t; is >> t;) {
		bool r = binary_search(t.seq.begin(), t.seq.end(), t.val);
		if (r != t.res) {
			std::cout << "Fallimento: test " << t.label << " binary_search: "
				<< t.seq.size() << " elementi, val==" << t.val << " -> " << t.res << std::endl;
			++error_count;
		}
	}
	return error_count;
}

int main() {
	std::ifstream is = std::ifstream("my_tests.txt");
	if (is.fail()) throw;
	int errors = test_all(is);
	std::cout << std::endl << std::endl;
	std::cout << "Numero di errori: " << errors << std::endl;
	is.close();
}