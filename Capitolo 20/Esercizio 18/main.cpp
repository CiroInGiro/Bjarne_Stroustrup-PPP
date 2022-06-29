/*
Capitolo 20 Esercizio 18
Definisci un iteratore range controllore per vector (un random access iterator).
*/

#include "../MyClass/MyVector.h"
#include <iostream>

int main(int argc, char** argv) {
	try {
		MyVector<int> mv;
		mv.push_back(1);
		mv.push_back(2);
		MyVector<int>::safe_iterator si = mv.begin();
		std::cout << "Elemento 1: " << *si << std::endl;
		++si;
		std::cout << "Elemento 2: " << *si << std::endl;
		std::cout << "Ora porto l'iteratore fuori dal range consentito..." << std::endl;
		++si; // end()
		++si; // errore
	}
	catch (MyError e) {
		std::cerr << "Eccezione: " << e.what() << std::endl;
		return 1;
	}
	

	return 0;
}