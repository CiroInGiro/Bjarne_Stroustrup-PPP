#include "MyVector_Pool.h"

/*
template<class T, size_t N>
MyVector_Pool<T, N>::MyVector_Pool() {
	pool = new cella[N];

	///*
	if (pool) {
		prox_free = pool;
		sz = 0;
		space = N;
		*pool->pieno = 0;
		*pool->prox_free = 0;
	}
	//*/
/*
	if (pool) {
		formatta();
	}
	else {
		// eccezzione di new, allocazione fallita da gestire
		throw;
	}
	sz = 0;
	space = N;
}


template<class T, size_t N>
T* MyVector_Pool<T, N>::get() {
	// ci sono celle libere?
	if (sz == space) return nullptr;

	T* retval = &prox_free->dato;
	prox_free->pieno = 1;

	// siamo al primo elemento del pool?
	if (prox_free > pool) {
		// il precedente deve aggiornare il suo prox_free
		--prox_free;
		prox_free->prox_free = retval->prox_free;
	}
	
	// prepariamo il prossimo get()
	prox_free = retval->prox_free;

	return retval;
}

template<class T, size_t N>
void MyVector_Pool<T, N>::del(T* p) {
	cella* navetta = pool;
	
	while (navetta < (pool + sz)) {
		if (p == &navetta->dato) {
			// trovato
			navetta->dato = T();
			navetta->pieno = 0;
			if (navetta->prox_free < prox_free) prox_free = navetta->prox_free; // mantiene compatta la zona di memoria (deframmentazione)
			cella* cella_precedente = navetta - 1;
			cella_precedente->prox_free = navetta;
			p = nullptr; // questa cella non deve essere utilizzata impropriamente.
			return;
		}
		++navetta;
	}
}

template<class T, size_t N>
// inizializza le celle nello spazio di memoria
void MyVector_Pool<T, N>::formatta() {
	cella* navetta = pool;
	while (navetta < (pool + sz)) {
		navetta->dato = T();
		navetta->pieno = 0;
		navetta->prox_free = ++navetta;
	}
	// l'ultimo elemento non ha un successore libero
	--navetta;
	navetta->prox_free = 0;
}


template<class T, size_t N>
bool MyVector_Pool<T, N>::push_back(T dato) {
	if (sz == space) return false;
	
	// alloca al prossimo libero
	if (prox_free) {
		prox_free->dato = dato;
		prox_free->pieno = 0;
		// il precedente non ha più un successore libero
		if (prox_free > pool) {
			--prox_free;
			prox_free->prox_free = 0;
			++prox_free;
		}
		// aggiorna prox_free col successivo libero nella cella
		prox_free = prox_free->prox_free;
	}
	else throw; // bug avrebbe dovuto esserci il puntatore se sz < space

	// incrementa sz
	++sz;
	return true;
}

*/