#include "MyStack.h"
#include <iostream>

int main(int argc, char** argv) {
	const size_t byte_use = 1 * 1024;

	MyStack<byte_use> pila;
	
	// dimensione di un char
	std::cout << "char occupa " << sizeof(char) << " byte.\n";

	// utilizzo tutta la memoria e la formatto col carattere 'O'
	char* p = (char*)pila.get(byte_use);

	if (!p) throw;

	for (size_t count = 0; count < byte_use; ++count) {
		*p = 'O';
		++p;
	}
	
	pila.free();
	p = nullptr;

	// riprendo il puntatore e stampo la pila
	p = (char*)pila.get(byte_use);
	if (!p) throw;

	for (size_t count = 0; count < byte_use; ++count) {
		std::cout << *p << ' ';
		++p;
		if (((count + 1) % 20) == 0) std::cout << std::endl;
	}
	
	pila.free();
	p = nullptr;
	std::cout << std::endl;

	return 0;
}