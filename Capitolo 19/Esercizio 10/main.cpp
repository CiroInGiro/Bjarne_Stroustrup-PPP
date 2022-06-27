/*
Capitolo 9 Esercizio 10
Implementa un semplice unique_ptr supportando solo un costruttore, distruttore, ->, * e release().
In particolare non provare a implementare un costruttore di copia e di assegnazione.
*/

#include <iostream>

template<typename T>
class unique_ptr {
	T* _punt;
public:
	unique_ptr(T* p) : _punt { p } { }
	~unique_ptr() { 
		if (_punt) free(_punt);
		_punt = 0;
	}
	T& operator->() {
		return *_punt;
	}
	T& operator*() {
		return *_punt;
	}
	T* release() {
		T* retVal = _punt;
		_punt = 0;
		return retVal;
	}
};

int main(int argc, char** argv) {
	unique_ptr<int> upi(new int);
	*upi = 10;
	int* pi = upi.release();
	std::cout << "Ho creato il unique_ptr e gli ho assegnato il valore 10 che riporto di seguito dopo averlo rilasciato in un puntatore int: " << *pi << "\n\n";
	return 0;
}