/* Capitolo 24 Esercizio 1
* Gli argomenti di funzione f per a.apply() e apply(f, a) sono differenti.
* Scrivi una funzione triple() per ognuna e usa ognuna per triplicare gli elementi di un array { 1 2 3 4 5 }.
* Definisci un singolo triple() che può essere usata per entrambi a.apply(triple) e apply(triple, a).
* Spiega perché dovrebbe essere una cattiva idea scrivere ogni funzione usata da apply() in questo modo.
*/

#include "../PPP2code/Matrix.h"
#include <iostream>
#include "../PPP2code/MatrixIO.h"

// funzione da passare ad a.apply() alla funzione sarà passato il valore della matrice per riferimento e quello sarà modificato.
void f1(int& val) { 
	val *= 3; // utilizzato da a.apply(f)
}

// funziona da passare a apply() alla funzione viene passato il valore della matrice e utilizzato il valore di ritorno
int f2(const int& val) { return (val * 3); }

int triple(int& val) {
	int retVal = val * 3; // calcolo prima il valore moltiplicato x 3
	val *= 3; // modifico direttamente val in caso si sia utilizzato a.apply() e quindi non è utilizzato il valore di ritorno
	return retVal; // se invece viene usato apply() allora sarà usato il valore di ritorno che sovrascriverà di nuovo val precedentemente modificato.
}

int main() {
	Numeric_lib::Matrix<int> a(6);

	std::cout << "Memorizzo i seguenti valori in Matrix<int, 1>:\n";
	for (int i = 0; i < a.dim1(); ++i) {
		a[i] = (i + 1);
		std::cout << "Valore nella posizione " << i << ": " << a[i] << std::endl;
	}
	Numeric_lib::Matrix<int> a_copy = a;

	std::cout << "uso Matrix<int, 1>.apply(f) per far triplicare i valori nella matrice da f e la ristampo: \n";
	//a.apply(f1);
	a.apply(triple);
	std::cout << "\n\n" << a << "\n";

	//Numeric_lib::Matrix<int> b = apply(f2, a_copy);
	Numeric_lib::Matrix<int> b = apply(triple, a_copy);
	std::cout << "uso apply(f, Matrix<int, 1>) per riempire una nuova matrice coi valori triplicati:\n";
	std::cout << "\n\n" << b << "\n";
}

/* Un unica funzione ci puo dare il risultato sperato ma compromette la sicurezza dei dati nella matrice e crea confusione nel suo utilizzo.
* Inoltre la funzione esegue un operazione in memoria in più quando si chiama apply() e un operazioni in più per il calcolo e copia del valore di ritorno in caso si chiami a.apply()
*/
