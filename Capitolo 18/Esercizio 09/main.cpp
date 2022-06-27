/*
Capitolo 18 Esercizio 9
Considera il layout di emmoria nel paragrafo 17.4
Scrivi un programma che indichi l'ordine della memoria statica, dello stack e dello heap nella RAM.
In che direzione cresce lo stack, con indirizzi verso il basso o verso l'alto?
In un array allocato nello heap gli indici più alti sono allocati in indirizzi più alti o più bassi?
*/

#include <iostream>

// la memoria statica contiene il programma e le variabili globali
const int dim_arr{ 10 };
double global_double1{ 0 };
double global_double2{ 0 };
double global_double3{ 0 };
double global_array_double1[dim_arr]{ 0.0 };
double global_array_double2[dim_arr]{ 0.0 };
double global_array_double3[dim_arr]{ 0.0 };

// funzione per stampare gli indirizzi di un array e dei suoi indici
// array di double
void stampa_array(const double* p, int dim) {
	using std::cout;
	using std::endl;
	std::cout.setf(std::ios::hex, std::ios::basefield);
	std::cout.setf(std::ios::showbase);
	for (int indice = 0; indice < dim; ++indice) {
		cout << "Indice: " << indice << " all'indirizzo: " << p << endl;
		++p;
	}
	std::cout.unsetf(std::ios::hex);
	std::cout.unsetf(std::ios::showbase);
}

// array di int
void stampa_array(const int* p, int dim) {
	using std::cout;
	using std::endl;
	std::cout.setf(std::ios::hex, std::ios::basefield);
	std::cout.setf(std::ios::showbase);
	for (int indice = 0; indice < dim; ++indice) {
		cout << "Indice: " << indice << " all'indirizzo: " << p << endl;
		++p;
	}
	std::cout.unsetf(std::ios::hex);
	std::cout.unsetf(std::ios::showbase);
}

// array di char
void stampa_array(const char* p, int dim) {
	using std::cout;
	using std::endl;
	std::cout.setf(std::ios::hex, std::ios::basefield);
	std::cout.setf(std::ios::showbase);
	for (int indice = 0; indice < dim; ++indice) {
		cout << "Indice: " << indice << " all'indirizzo: " << &p << endl;
		++p;
	}
	std::cout.unsetf(std::ios::hex);
	std::cout.unsetf(std::ios::showbase);
}

int main(int argc, char** argv) {

	// lo stack contiene tutte le variabili del programma dopo la sua esecuzione
	// c'è un puntatore this anche per main o solo per gli oggetti?
	//void* prg = this; // solo all'interno di una funzione membro non statica

	// nello heap invece (memoria libera) va a finire tutte le allocazioni dinamiche che facciamo con new()

	// Test memoria statica
	using std::cout;
	using std::endl;
	using std::cin;
	cout << "STATICA:\n\n";
	cout << "Allocato un const int globale:\n";
	stampa_array(&dim_arr, 1);
	cout << "\n\nAllocati 3 double consecutivi globali assieme a tre arrey di 10 elementi globali:\n";
	cout << "global double 1: ";
	stampa_array(&global_double1, 1);
	cout << "\nglobal double 2:";
	stampa_array(&global_double2, 1);
	cout << "\nglobal double 3:";
	stampa_array(&global_double3, 1);
	cout << "\nprimo global array di 10 double: ";
	stampa_array(global_array_double1, 10);
	cout << "\nsecondo global array di 10 double: ";
	stampa_array(global_array_double2, 10);
	cout << "\nterzo global array di 10 double: ";
	stampa_array(global_array_double3, 10);

	// Test memoria stack
	cout << "STACK:\n\n";
	const int costante{ 0 };
	char carattere{ ' ' };
	cout << "\n\nCostante int assegnata nel blocco main(): ";
	stampa_array(&costante, 1);
	cout << "\n\nVariabile char assegnata nel blocco main(): ";
	stampa_array(&carattere, 1);

	// Test Heap
	cout << "HEAP:\n\n";
	double* dinamic_double1 = new double{ 0 };
	double* dinamic_double2 = new double{ 0 };
	double* dinamic_double3 = new double{ 0 };
	int* dinamic_array1 = new int[dim_arr] {0};
	int* dinamic_array2 = new int[dim_arr] {0};
	int* dinamic_array3 = new int[dim_arr] {0};
	cout << "Allocati dinamicamente 3 double e 3 array di " << dim_arr << " int:\n";
	cout << "double 1: ";
	stampa_array(dinamic_double1, 1);
	cout << "\ndouble 2: ";
	stampa_array(dinamic_double2, 1);
	cout << "\ndouble 3 :";
	stampa_array(dinamic_double3, 1);
	cout << "\n\nArray di int n°1:\n";
	stampa_array(dinamic_array1, dim_arr);
	cout << "\nArray di int n°2:\n";
	stampa_array(dinamic_array2, dim_arr);
	cout << "\nArray di int n°3:\n";
	stampa_array(dinamic_array3, dim_arr);
	delete dinamic_double1;
	delete dinamic_double2;
	delete dinamic_double3;
	delete[] dinamic_array1;
	delete[] dinamic_array2;
	delete[] dinamic_array3;
	// attesa uscita
	std::cout << "\n\nDigita qualcosa seguito da invio per continuare...\n";
	std::cin >> carattere;
	return 0;
}

// La memoria statica è il blocco di indirizzi più bassi che il sistema utilizza. gli indirizzo nella memoria statica vengono assegnati dal basso verso l'alto e anche gli indici degli array vanno verso l'alto. Gli indirizzo sono assegnati consecutivamente.
// I primi ad essere utilizzati sono gli indirizzo per le variabili globali.

// Nello stack ci vanno le variabili e costanti del main. Gli indirizzi sono anche qui crescenti e scelti in un blocco dopo la statica ma comunque nel basso.

// Nello Heap invece gli indirizzi sono crescente, anche negli array ma sono assegnati molto alti, lontano dal fine memoria assendo dello spazio che dovrà occupare una variabile o array. Gli indirizzi vengono pescati quindi tra quelli libero dall'alto verso il basso.
