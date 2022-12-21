/* Capitolo 24 Drill 4
* Scrivi un programma che prende in input degli int e stampi la radice quadrata (sqrt) di essi o se è illegale quando non possibile.
* Controlla l'uscita di sqrt()
*/

#include <iostream>

int main() {
	using std::cout;
	using std::cin;
	using std::endl;

	int numero{ 0 };
	double result{ 0 };

	cout << "inserisci degli interi e io stampa la sua radice quadrata: ";
	while (cin >> numero) {
		result = sqrt(numero);
		if (!errno) cout << "\nLa radice quadrata di " << numero << " é " << result << endl;
		else cout << "\nNon posso calcolare la radice quadrata di " << numero << endl;
		errno = 0;
		cout << endl << "Altro numero: ";
	}
}