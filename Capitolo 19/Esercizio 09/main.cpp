/*
Capitolo 19 Esercizio 9
Reimplemeta vector::operator=() (19.2.5) utilizzando Allocator (19.3.7) per gestire la memoria.
*/

#include "MyVector.h"
#include <iostream>

#include <string>
#include "MySize.h"
#include <memory>

template<typename T>
// requires (Container<T>())
void print(const T& v) {
	using std::cout;
	for (int i = 0; i < v.size(); ++i) {
		cout << "Elemento " << i << ": " << v[i] << "\n";
	}
}

int main(int argc, char** argv) {
	MyVector<int, MyAllocator<int>> vi1(3);
	vi1[0] = 2;
	vi1[1] = 3;
	vi1[2] = 1;
	MyVector<int, MyAllocator<int>> vi2;
	vi2 = vi1;
	print(vi2);

	/*
	// il motivo per cui myallocator non funziona con le stringhe, non considera che il tipo stringa ha una dimensione variabile e crea un blocco sbagliato di memoria.
	// Allocator nello standard library invece funziona anche con string
	void* pv = malloc(MySize<std::string>());
	std::string* ps = reinterpret_cast<std::string*>(pv);
	*ps = "ciao";
	*/

	return 0;
}