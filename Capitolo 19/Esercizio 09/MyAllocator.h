#pragma once

#include "MySize.h"
#include <memory>

template<class T>
class MyAllocator {
	void* _punt; // gestione interna dell'indirizzo restituito
	size_t _space; // dimensione della memoria allocata
public:
	MyAllocator() : _punt{ nullptr }, _space{ 0 } {}
	// alloco n oggetti di tipo T e restituisco un puntatore dello stesso tipo
	T* allocate(int n) {
		size_t dim = MySize<T>();
		_space = dim * n;
		_punt = malloc(_space);
		return reinterpret_cast<T*>(_punt);
	}
	// deallocazione di n oggetti di tipo T a partire dall'indirizzo in p
	void deallocate(T* p, int n) {
		// Per n positivo se l'indirizzo p + (bytes di T * n) superano l'indirizzo di _punt + _space allora c'è un eccezzione
		// Per n negativo se l'indirizzo p + (bytes di T * n) è minore dell'indirizzo _punt allora c'è un eccezione
		// in questi casi di ritorna senza far nulla
		void* p1 = reinterpret_cast<void*>(p);
		if (n > 0) {
			if (&p1 + (MySize<T>() * n) > (&_punt + _space)) return;
		}
		else if (n < 0) {
			if (&p1 + (MySize<T>() * n) < &_punt) return;
		}
		else return; // n == 0
		// rialloco la memoria che mi serve (differenza tra spazio che avevo e quello da togliere n
		// caso in cui libero tutto lo spazio
		if (_space - (MySize<T>() * n) == 0) {
			free(_punt);
			_punt = 0;
			return;
		}
		// caso in cui non lascio memoria inizializzata alla fine
		if (((&_punt + _space) - &p1) == (MySize<T>() * n)) {
			void* p2 = malloc((_space - (MySize<T>() * n)));
			memcpy(p2, _punt, (_space - (MySize<T>() * n)));
			free(_punt);
			_punt = p2;
			_space -= (MySize<T>() * n);
			return;
		}
		// altri casi
		size_t first_space = &p1 - &_punt;
		size_t cross_space = MySize<T>() * n;
		size_t last_space = _space - first_space - cross_space;
		// copia la parte iniziale inizilaizzata
		void* p2 = malloc(first_space + last_space);
		memcpy(p2, _punt, first_space);
		memcpy((&p2 + first_space), (&p1 + cross_space), last_space);
		free(_punt);
		_punt = p2;
		_space = first_space + last_space;
	}
	// costruisci p col valore v (inizializza la memoria grezza)
	void construct(T* p, const T& v) {
		*p = v;
	}
	// distruggi l'elemento in p per riavere memoria grezza, non inizializzata (il contrario di costruisci)
	void destroy(T* p) {
		p->~T();
	}
};

