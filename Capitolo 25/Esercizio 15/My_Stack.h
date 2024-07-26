#pragma once

typedef char* Address;

template<size_t dim>
class My_Stack
{
private:
	// size di stack in bytes
	size_t sz;
	// indirizzo dello stack
	char* inizio_stack;
	// Array di puntatori che contengono gli indirizzi rilasciati nello stack
	Address* array_ptr;
	size_t address_index;
public:
	// costruttore
	My_Stack() { 
		sz = dim;
		inizio_stack = new char[dim];
		array_ptr = new Address[dim]; // massimo numero di allocazione uguale al numero di bytes alllocati
		address_index = 0;
		array_ptr[address_index] = inizio_stack; // primo indirizzo da rilasciare
	}

	// get per ricevere il puntatore alla memoria di tot bytes
	void* get(int dimensione) {
		// se vogliamo allocare più spazio di quanto ne abbiamo
		if ((array_ptr[address_index] + dimensione) > (inizio_stack + sz)) return 0;
		void* retVal = array_ptr[address_index];
		++address_index;
		array_ptr[address_index] = (char*)retVal + dimensione;
		return retVal;
	}

	// libera l'ultima allocazione
	void free() {
		// se sono in testa non ho nulla da liberare
		if (address_index == 0) return;
		--address_index; // ritorno al precedente indirizzo rilasciato
	}

	// spazio ancora libero in bytes
	size_t available() const {
		size_t retVal = (size_t)((inizio_stack + sz) - array_ptr[address_index]);
		return retVal;
	}

	// dimensione dello stack
	size_t size() const {
		return sz;
	}
};
