/*
Capitolo 17 Esercizio 9
In quale modo la pila cresce: su (verso indirizzi più alti) o giù (verso indirizzi più bassi)?
In che modo lo heap inizialmente cresce (cioè prima di utilizzare delete[])?
Scrivi un programma per determinare le risposte.
*/

#include <iostream>

int main(int argc, char** argv) {
	const std::string testo{ "Questa è una frase." };
	unsigned int dim{ (testo.size() + 1) };
	char* ach = new char[dim];
	unsigned int idx{ 0 };
	for (char ch : testo) {
		ach[idx] = ch;
		++idx;
	}
	ach[idx] = '\0';
	std::cout << "Vediamo gli indirizzi consecutivi assegnati per l'array: " << std::endl;
	idx = 0;
	while (ach[idx] != '\0') {
		char* pc;
		pc = &ach[0] + idx; // così sappiamo che incrementare l'indice sull'indirizzo copprisponde al valore successivo
		std::cout << "Array[" << idx << "] = " << ach[idx] << " all'indirizzo " << &ach + idx << " contiene: " << *pc << std::endl;
		++idx;
	}
	std::cout << "\nOra allochiamo la stessa frase di nuovo e vediamo a quale indirizzo assegna, più alto o più basso del precedente:" << std::endl;
	char* ach2 = new char[(dim*2)];
	idx = 0;
	for (char ch : testo) {
		ach2[idx] = ch;
		++idx;
	}
	ach2[idx] = '\0';
	std::cout << "Vediamo gli indirizzi consecutivi assegnati per il secondo array: " << std::endl;
	idx = 0;
	while (ach2[idx] != '\0') {
		std::cout << "Array2[" << idx << "] = " << ach2[idx] << " all'indirizzo " << &ach2 + idx << std::endl;
		++idx;
	}
	std::cout << "\nAdesso dealloco il primo array e ne creo un'altro, vediamo dove viene creato:" << std::endl;
	delete[] ach;
	ach = new char[dim];
	std::cout << "Il nuovo array di identica dimensione è stato ricreato all'indirizzo: " << &ach << std::endl;
	return 0;
}
// In conclusione il sistema cerca memoria libera negli indirizzi più alti e alloca blocchi contigui con indirizzi dal più basso al più alto.
// Alcune volte la deallocazione e la riallocazione per lo stesso spazio di memoria avviene al medesimo indirizzo.