/*
Capitolo 18 Esercizio 11
Cerca sul web Skip List e implememnta questo tipo di lista.
*/

// ho fatto una bozza senza un vero calcolo della promotion basata sulla probabilità 50% di scelte sul rapporto tra livelli e elementi

#include <exception>
#include <iostream>

// Gli Head di lista
class SkipNode {
public:
	SkipNode() {
		//_nodo = { nullptr };
		_key = { nullptr };
		_up = { nullptr };
		_down = { nullptr };
		_next = { nullptr };
		_prev = { nullptr };
		_level = 0;
	}
	~SkipNode() {
		// i distruttori vengono chiamati dal livello più basso al livello più alto, da sinistra verso destra.
		if (_down) delete _down;
		_prev = nullptr;
		if (_next) delete _next;
		_up = nullptr;;
		// i nodi sono al livello 0, negli altri livelli sono copie.
		//if (_level == 0 && _nodo != nullptr) delete _nodo;
		if (_key) delete _key;
	}
	int level() { return _level; }
	void level(int l) { _level = l; }
	int* get() { return _key; }
	void set(int d) {
		if (_key) *_key = d;
		else { _key = new int{ d }; }
	}
	void set(int* p) {
		_key = p;
	}
	SkipNode* up() { return _up; }
	void up(SkipNode* h) { _up = h; }
	SkipNode* down() { return _down; }
	void down(SkipNode* h) { _down = h; }
	SkipNode* next() { return _next; }
	void next(SkipNode* h) { _next = h; }
	SkipNode* prev() { return _prev; }
	void prev(SkipNode* h) { _prev = h; }

	// ricerca esatta o il più vicino
	SkipNode* search(int r, bool forInsert = false) {
		SkipNode* navetta = this;
		while (!navetta->next() && navetta->down()) {
			navetta = navetta->down();
			while (navetta->next()) { // && navetta->next()->get() && *navetta->next()->get() < r) {
				if (navetta->next()->get()) {
					if (*navetta->next()->get() == r) return navetta->next();
					if (*navetta->next()->get() < r) navetta = navetta->next();
					else break;
				}
			}
		}
		// se è solo per l'inserimento lo inseriamo qui, questo nodo è il più prossimo
		if (forInsert) return navetta; else return nullptr;
		// ritorniamo navetta se cerchiamo il più vicino altrimenti un null
	}
	SkipNode* insert(int r) {
		SkipNode* nuovo = new SkipNode();
		nuovo->set(r);
		// search restituisce il primo nodo che abbia il dato più vicino
		SkipNode* pos = search(r, true);
		if (!pos) pos = this;
		// ora dobbiamo però scendere al livello 0 per l'inserimento
		while (pos->down()) pos = pos->down();
		// pos inserisce il nuovo nodo sul livello 0
		if (pos->level() > 0) return nullptr; // non dovrebbe accadere
		nuovo->next(pos->next());
		nuovo->prev(pos);
		if (nuovo->next()) nuovo->next()->prev(nuovo);
		pos->next(nuovo);
		return nuovo;
	}
	void remove() {
		if (_next) _next->prev(_prev);
		if (_prev) _prev->next(_next);
		_prev = nullptr;
		_next = nullptr;
		if (_up) {
			//_up->remove(); // non dovrebbe succedere
			_up = nullptr;
		}
		if (_down) {
			_down->remove();
			delete _down;
			_down = nullptr;
		}
		if (_key) {
			delete _key;
			_key = nullptr;
		}
	}
	SkipNode* newNode() {
		SkipNode* nuovo = new SkipNode;
		nuovo->level(_level + 1);
		nuovo->set(_key);
		_up = nuovo;
		nuovo->down(this);
		return nuovo;
	}

	// restituisce un nodo sinistro o destro dello stesso livello
	SkipNode* searcLevel(int d) {
		int mosse[3];
		mosse[0] = _directions::bottom;
		mosse[1] = d; // sinistra o destra
		mosse[2] = _directions::top;
		bool trovato{ false };
		SkipNode* navetta = this;
		int imossa = 0;
		int fallimenti = 0;
		while (!trovato) {
			if (mosse[imossa] == _directions::bottom) {
				if (navetta->down()) {
					navetta = navetta->down();
					fallimenti = 0;
				}
				else fallimenti += 1;
				if (imossa < 2) ++imossa; else imossa = 0;
			}
			if (mosse[imossa] == _directions::left) {
				if (navetta->prev()) {
					navetta = navetta->prev();
					fallimenti = 0;
				}
				else fallimenti += 2;
				if (imossa < 2) ++imossa; else imossa = 0;
			}
			if (mosse[imossa] == _directions::right) {
				if (navetta->next()) {
					navetta = navetta->next();
					fallimenti = 0;
				}
				else fallimenti += 2;
				if (imossa < 2) ++imossa; else imossa = 0;
			}
			if (mosse[imossa] == _directions::top) {
				if (navetta->up()) {
					navetta = navetta->up();
					fallimenti = 0;
				}
				else fallimenti += 3;
				if (imossa < 2) ++imossa; else imossa = 0;
			}
			if (navetta->level() == _level) trovato = true;
			if (fallimenti >= 6) break;
		}
		if (trovato) return navetta;
		return nullptr;
	}
	SkipNode* searcLevel_ver1(int d) {
		enum directions { down = 0, left, up, right };
		int mosse[3];
		mosse[0] = directions::down;
		switch (d) {
		case _directions::left:
			mosse[1] = directions::left;
			break;
		case _directions::right:
			mosse[1] = directions::right;
			break;
		}
		mosse[2] = directions::up;
		bool trovato{ false };
		SkipNode* navetta = this;
		int imossa = 0;
		int fallimento = 0;
		while (!trovato) {
			switch (mosse[imossa]) {
			case directions::down:
				if (navetta->down()) {
					navetta = navetta->down();
					fallimento = 0;
				}
				else fallimento += 1;
				break;
			case directions::left:
				if (navetta->prev()) {
					navetta = navetta->prev();
					fallimento = 0;
				}
				else fallimento += 2;
				break;
			case directions::right:
				if (navetta->next()) {
					navetta = navetta->next();
					fallimento = 0;
				}
				else fallimento += 2;
				break;
			case directions::up:
				if (navetta->up()) {
					navetta = navetta->up();
					fallimento = 0;
				}
				else fallimento += 3;
				break;
			}
			if (imossa < 2) ++imossa; else imossa = 0;
			if (navetta->level() == _level) trovato = true;
			if (fallimento >= 6) break;
		}
		if (trovato) return navetta;
		return nullptr;
	}

	SkipNode* promote() {
		SkipNode* navetta = this;
		// saliamo in cima
		while (navetta->up()) navetta = navetta->up();
		// creiamo il nodo qui
		SkipNode* retVal = navetta->newNode();
		navetta->up(retVal);
		retVal->down(navetta);
		//navetta = nullptr;
		// cerchiamo un nodo sinistro sullo stesso livello del nuovo nodo retVal
		SkipNode* sinistro = retVal->searcLevel(_directions::left);
		if (sinistro) {
			retVal->next(sinistro->next());
			sinistro->next(retVal);
		}
		//sinistro = nullptr;
		// cerchiamo un nodo destro sullo stesso livello del nuovo nodo retVal
		SkipNode* destro = retVal->searcLevel(_directions::right);
		if (destro) {
			retVal->prev(destro->prev());
			destro->prev(retVal);
		}
		else retVal->prev(sinistro);
		// restituiamo il nouvo nodo
		return retVal;
	}
private:
	SkipNode* _up;
	SkipNode* _down;
	SkipNode* _next;
	SkipNode* _prev;
	int _level;
	int* _key;
	enum _directions {top = 0, bottom, left, right};
};

// Lista di tipo Skip List
class SkipList {
public:
	explicit SkipList() {
		_headList = new SkipNode;
		_maxLevel = 1;
		_headList = _headList->newNode();
		_elements = 0;
		_attuale = nullptr;

	}
	~SkipList() {
		delete _headList;
		_attuale = nullptr;
	}
	void add(int elem) {
		_attuale = _headList->insert(elem);
		++_elements;
		// decido se promuovere il nodo
		if (elem == 6) {
			_attuale = _attuale->promote();
			// se raggiungiamo la cima creiamo una nuova testa
			if (_attuale->level() == _maxLevel) {
				_headList = _headList->newNode();
				++_maxLevel;
			}
		}
	}
	void remove(int elem) {
		SkipNode* nodo = _headList->search(elem);
		if (nodo) {
			nodo->remove();
			delete nodo;
			--_elements;
		}
	}
	int last() const { return *_attuale->get(); }
private:
	SkipNode* _headList;
	int _maxLevel;
	int _elements;
	SkipNode* _attuale;
};

int main(int argc, char** argv) {
	try {
		// creo la lista
		SkipList parole;
		// aggiungiamo elementi
		int elemento;
		elemento = 5;
		parole.add(elemento);
		std::cout << "Ho inserito " << elemento << " nella lista e ora nella mia lista punto a " << parole.last() << std::endl;
		elemento = 8;
		parole.add(elemento);
		std::cout << "Ho inserito " << elemento << " nella lista e ora nella mia lista punto a " << parole.last() << std::endl;
		elemento = 6;
		parole.add(elemento);
		std::cout << "Ho inserito " << elemento << " nella lista e ora nella mia lista punto a " << parole.last() << std::endl;
		elemento = 1;
		parole.add(elemento);
		std::cout << "Ho inserito " << elemento << " nella lista e ora nella mia lista punto a " << parole.last() << std::endl;
		// togliamo elementi
		elemento = 6;
		parole.remove(elemento);
		elemento = 1;
		parole.remove(elemento);
	}
	catch (std::exception e) {
		using std::cerr;
		using std::endl;
		cerr << "\n\n\nEccezione: " << e.what() << endl;
	}
	return 0;
}