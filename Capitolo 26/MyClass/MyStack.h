#pragma once

// Soluzione 1: creo una struttura che mi contiene l'indirizzo nella memoria allocata. In pratica l'array di strutture è un indice per gli indirizzi agli oggetti utilizzati nella memoria allocata.
template<size_t dim>
class MyStack_struct
{
private:
	// creo una struttura dati lista per tenere traccia dei puntatori rilasciati
	struct cella_struct {
		char* indirizzo;
	};
	// size di stack in bytes
	size_t sz;
	// indirizzo dello stack
	char* inizio_stack;
	// cella libera dello stack
	cella_struct* cella;
public:
	// costruttore
	MyStack_struct() {
		sz = dim;
		inizio_stack = new char[dim];
		cella = new cella_struct[dim]; // massimo numero di allocazione uguale al numero di bytes alllocati
		cella->indirizzo = inizio_stack;
	}
	
	// get per ricevere il puntatore alla memoria di tot bytes
	void* get(int dimensione) {
		// non possiamo allocare più spazio di quanto ne abbiamo
		if ((cella->indirizzo + dimensione) > (inizio_stack + sz)) return 0;
		void* retVal = cella->indirizzo;
		++cella; // operatori aritmetici sui puntatori
		cella->indirizzo = (char*)retVal + dimensione; // lo stesso indirizzo iniziale è utilizzabile
		return retVal;
	}

	// libera l'ultima allocazione
	void free() {
		// se sono in testa non ho nulla da liberare
		if (cella->indirizzo == inizio_stack) return;
		--cella; // ritorno al precedente indirizzo rilasciato
	}

	// spazio ancora libero in bytes
	size_t available() const {
		size_t retVal = (size_t)((inizio_stack + sz) - (cella->indirizzo));
		return retVal;
	}

	// dimensione dello stack
	size_t size() const {
		return sz;
	}
};

// Soluzione 2: creo semplicemente un array di puntatori char al posto della struttura

// per comodità e rendere la lettura più facile potrei sostituire new char*[dim] con new Address[dim]
// in entrami i casi new mi rilascia un punttaore a uno spazio di memoria occupato da un puntatore char per dim volte
// quindi il puntatore rilasciato lo deferenzio con le [] che ottengo un puntatore char dove conservo l'indirizzo nella zona di memoria del mio stack
typedef char* Address;

template<size_t dim>
class MyStack
{
private:
	// indice dei puntatori rilasciati (un puntatore alla zona di memoria di puntatori rilasciati
	char** array_ptr;
	// indice nell'array di puntatori
	size_t address_index;
	// size di stack in bytes
	size_t sz;
	// indirizzo dello stack
	char* inizio_stack;
public:
	// costruttore
	MyStack() {
		sz = dim;
		inizio_stack = new char[dim];
		//array_ptr = new char*[dim]; // al massimo dim allocazioni di 1 byte
		array_ptr = new Address[dim]; // semplificazione
		address_index = 0;
		array_ptr[address_index] = inizio_stack;
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
		--address_index;
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
