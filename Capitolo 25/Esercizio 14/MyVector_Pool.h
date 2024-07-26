#pragma once

#include <iostream>
#include <iomanip>

/*
La differenza verso un normale vettore è che lo spazio di memoria allocata non dovrà cambiare.
Possiamo allocare oggetti dello stesso tipo nel Pool e possiamo deallocarli;
tutto questo senza modificare la memoria che in realtà è già tutta preassegnata dal sistema alla creazione del Pool.
Ci serve quindi una struttura che memorizza un dato ma che contiene informazioni sui singoli spazi di memoria, tipo se utilizzato o cancellato e il suo successivo.
Creando una lista che non usa allocazioni dinamiche ma che si muova in un blocco contiguo di indirizzi bisognerà creare la logica che aggiorni i puntatori e consuma troppa CPU
Stessa cosa se ad ogni inserimento dobbiamo cercarne uno libero.
Come compromesso ho consumato in più lo spazio di 3 puntatori che delimitano l'area di ricerca tra il primo e l'ultimo libero;
la logica è solo per scorrere verso il primo libero e in ogni inserimento e cancellazione si mantiene compattata la memoria verso gli indirizzi più bassi.
*/

// vettore che utilizza un pool (spazio di memoria che non varia dinamicamente)
template<class T, size_t N>
class MyVector_Pool {
private:
	// cella di memoria
	struct cella {
		T dato{ T() }; // dato se presente
		//cella* prox_free{ 0 }; // prossimo spazio vuoto
		// stao della cella, se false significa che non abbiamo rilasciato il puntatore su di essa, è una cella libera
		bool pieno{ false };
	};
public:
	MyVector_Pool() {
		pool = new cella[N];

		if (pool) {
			sz = 0; // intero pool non occupato
			space = N; // spazio nel pool per N elementi
			prox_free = pool; // il primo elemento è libero
			//formatta();
			last_free = pool + N; // prox e last delimitano l'intero Pool.
		}
		else {
			// eccezzione di new, allocazione fallita da gestire
			throw;
		}
	}
	~MyVector_Pool() {
		delete[] pool;
	}
	// copy costructor
	//MyVector_Pool(const MyVector_Pool<T, N>& v);
	// copy assignement
	//MyVector_Pool<T, N>& operator=(const MyVector_Pool<T, N>& v);
	// move costructor
	//MyVector_Pool<T, N>(MyVector_Pool<T, N>&& v);
	// move assignement
	//MyVector_Pool<T, N>& operator=(MyVector_Pool<T, N>&& v);
	// ditruttore
	//~MyVector_Pool();
	// operatori di accesso
	//T& operator[](size_t n);
	//const T& operator[](size_t n) const;
	// utility di controllo spazio
	size_t size() const { return sz; }
	size_t capacity() const { return space; }
	
	// gestione spazio
	T* get() {
		// ci sono celle libere?
		if (sz == space) {
			//prox_free = nullptr;
			//last_free = nullptr;
			return nullptr;
		}
		
		//cella* attuale = prox_free;
		
		// controlliamo solo il prossimo libero in avanti, potrebbe scappare qualche posto vacante
		/*
		if (sz > 0 && prox_free == 0) {
			cella* attuale = pool;
			while (attuale < (pool + space)) {
				if (!attuale->pieno) {
					// trovato
					prox_free = attuale;
					break;
				}
				++attuale;
			}
		}
		*/

		/*
		while (prox_free->pieno) {
			if (!prox_free) throw; // qualcosa non va, dove sono finiti i posti vuoti?
			//prox_free = prox_free->prox_free;
			++prox_free;
		}
		*/

		// occupazione della cella
		T* retval = &(prox_free->dato);
		prox_free->pieno = true;
		++sz;

		/*
		// siamo al primo elemento del pool?
		if (prox_free > pool) {
			// il precedente deve aggiornare il suo prox_free
			navetta = prox_free;
			--navetta;
			navetta->prox_free = prox_free->prox_free;
			navetta = nullptr;
		}
		*/

		// prepariamo il prossimo get()
		//navetta = prox_free + 1;
		//prox_free = last_free;

		while (prox_free < last_free) {
			if (prox_free->pieno) ++prox_free; else break;
		}

		//prox_free = prox_free->prox_free;
		
		//if (prox_free > last_free) last_free = prox_free; // spostiamo in avanti anche last_free

		//navetta = nullptr;
		return retval;
	}

	// cerca l'indirizzo del dato e libera la sua cella.
	void del(T* p) {
		navetta = pool;
		// cerchiamo l'indirizzo in tutto il range perché potrebbe essere frammentato il Pool
		while (navetta < (pool + space)) {
			if (p == &(navetta->dato)) {
				// trovato
				navetta->dato = T(); // mantiene formattato il Pool
				navetta->pieno = false;
				--sz;
				//if (prox_free > navetta->prox_free) navetta->prox_free = prox_free;
				
				// caso in cui liberiamo una cella a sinistra della zona libera
				if (navetta < prox_free) {
					//navetta->prox_free = prox_free;
					prox_free = navetta; // mantiene compatta la zona di memoria (deframmentazione)
				}
				/*
				// caso in cui liberiamo una cella all'interno della zona libera
				else if ((navetta > prox_free) && (navetta < last_free)) {
					// dobbiamo cercare se le celle tra prox_free e questa contengono un puntatore oltre la nostra posizione perché l'ultima di esse dovrà puntare a me e io alla sua
					// ci serve ancora un puntatore che sono altri 8 byte per scorrere
					search = prox_free;
					while (search->prox_free < navetta) search = search->prox_free;
					navetta->prox_free = search->prox_free;
					search->prox_free = navetta;
					search = nullptr;
					//(navetta - 1)->prox_free = navetta; // il precedente punta alla cella liberata (riformattazione catena)
				}
				*/
				// caso in cui liberiamo una cella successiva alla zona libera
				else if (navetta > last_free) {
					//navetta->prox_free = last_free->prox_free; // dovrebbe essere nullptr
					//navetta->prox_free = nullptr; // sono io l'ultimo libero
					//last_free->prox_free = navetta;
					last_free = navetta;
				}

				// non ci possono essere casi in cui si libera una cella già libera, dove navetta == prox_free o navetta == last_free

				// Se il Pool era pieno avremo che prox_free == last_free e dovrà esserlo acnhe dopo l'aggiornamento di prox_free quando size == (space - 1)
				if (sz == (space - 1)) last_free = prox_free;

				p = nullptr; // questa cella non deve essere utilizzata impropriamente. <- la variabile esterna conterrà sempre l'indirizzo.
				navetta = nullptr;
				return;
			}
			++navetta;
		}
		navetta = nullptr;
	} // cencellato il dato puntato dall'indirizzo, l'indirizzo è disponibile per un get() futuro
	
	  //bool push_back(T dato);

	// stampa mappa della memoria
	void stampa() {
		std::cout << "Mappa del Pool:\n";
		if (space == 0) std::cout << "Nulla da stampare" << std::endl; else std::cout << "Spazio nel Pool: " << std::dec << std::noshowbase << space << "; dimensione: " << sz << std::endl;
		if (prox_free) std::cout << "Prossimo indirizzo libero: " << std::hex << std::showbase << prox_free << std::endl; else std::cout << "prox_free nullo\n";
		if (last_free) std::cout << "Ultimo indirizzo libero: " << std::hex << std::showbase << last_free << std::endl; else std::cout << "last_free nullo\n";
		navetta = pool;
		while (navetta < (pool + space)) {
			std::cout << "Indirizzo: " << std::showbase << std::hex << navetta;
			if (navetta->pieno) std::cout << " contiene " << std::noshowbase << std::dec << navetta->dato << "; "; else std::cout << " è vuoto; ";
			std::cout << std::endl << std::endl;
			//std::cout << "il suo prossimo indirizzo libero: " << std::hex << std::showbase << navetta->prox_free << std::endl << std::endl;
			navetta++;
		}
		std::cout << std::noshowbase << std::dec << std::endl;
		navetta = nullptr;
	}
private:
	size_t sz; // dimensione consumata
	size_t space; // dimensione del pool
	// Puntatori preallocati per non variare la memoria dopo la costruzione del Pool.
	cella* pool{ nullptr }; // dove inizia il pool
	cella* prox_free{ nullptr }; // prossima cella libera
	cella* navetta{ nullptr }; // per scorrere il Pool
	cella* last_free{ nullptr }; // cella libera con indirizzo più grande (non sono riuscito a gestire la compattazione con un solo puntatore)
	//cella* search{ nullptr }; // per ricerche temporanee
	
	void formatta() {
		navetta = pool;
		prox_free = pool;
		while (navetta < (pool + space)) {
			navetta->dato = T();
			navetta->pieno = false;
			//navetta->prox_free = (navetta + 1);
			++navetta;
		}
		// l'ultimo elemento non ha un successore libero
		--navetta;
		//navetta->prox_free = nullptr; // *** annullato, abbiamo last_free ora *** si richiude come su una catena di bicicletta
		last_free = navetta;
		navetta = nullptr; // non serve più
	}
};