/* Capitolo 25 Esercizio 2
* Make a list of words that can be spelled with hexadecimal notation.Read 0 as o, read 1 as l, read 2 as to, etc.;
	for example, Foo1 and Beef.Kindly eliminate vulgarities from the list before submitting it for grading.
*/

/*
* cifre esadecimali: 0 1  2  3   4   5 6 7 8 9 A B C D E F
* lettere:           O i to  E  FOR  S    
* 1. ABAC0
* 2. B1C1
* 3. FEDE
* 4. BAC1
* 5. C0DA
*/

#include <iostream>

int main() {
	using std::cout;
	using std::endl;
	cout << "1. ABAC0" << endl;
	cout << "2. B1C1" << endl;
	cout << "3. FEDE" << endl;
	cout << "4. BAC1" << endl;
	cout << "5. C0DA" << endl;

	return 0;
}