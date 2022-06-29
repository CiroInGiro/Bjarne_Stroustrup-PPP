/*
Capitolo 20 Esercizio 19
Definisci un safe check iterator per un list (iteratore biderazionale).
*/

#include <exception>
#include <iostream>

template<typename T>
class list {
	// celle di memorizzazione
	struct Elem {
		Elem* next;
		Elem* prev;
		T dato;
		Elem(const T& d = T(), Elem* n = 0, Elem* p = 0) : dato{ d }, next{ n }, prev{ p } {}
	};
public:
	// iteratore
	class safe_iterator {
	public:
		safe_iterator(Elem* p) : cur{ p } {}
		T operator*() { return cur->dato; }
		safe_iterator operator++() { if (cur->next) cur = cur->next; else throw std::exception("Non posso più avanzare."); return *this; }
		safe_iterator operator--() { if (cur->prev) cur = cur->prev; else throw std::exception("Non c'è nulla prima di me."); return *this; }
		friend bool operator==(const safe_iterator& l, const safe_iterator& r) {
			return l.cur == r.cur;
		}
		friend bool operator!=(const safe_iterator& l, const safe_iterator& r) {
			return !(l == r);
		}
	private:
		Elem* cur;
	};
	// core della lista
	list() : primo{ new Elem() }, ultimo{ primo } {}
	safe_iterator begin() {
		return safe_iterator(primo);
	}
	safe_iterator end() { 
		return safe_iterator(ultimo); // end() rappresenta il puntatore 1 dopo l'ultimo
	}
	void push_back(const T& val) {
			ultimo->next = new Elem(T(), 0, ultimo);
			ultimo->dato = val;
			ultimo = ultimo->next;
	}
private:
	Elem* primo;
	Elem* ultimo;
};

int main(int argc, char** argv) {
	list<int> l;
	l.push_back(12);
	l.push_back(24);
	list<int>::safe_iterator si = l.begin();

	try {
	
		std::cout << "Ho inserito in una lista 12 e 24, ora con un safe iterator stampo i 2 elementi:" << std::endl;
		std::cout << "Primo elemento: " << *si << std::endl;
		std::cout << "Secondo elemento: " << *(++si) << std::endl;
		std::cout << "Ora vado avanti e sono 1 oltre l'ultimo." << std::endl;
		++si;
		std::cout << "Ora vado ancora avanti per sollevare l'eccezione..." << std::endl;
		++si;
	}
	catch (std::exception e) {
		std::cerr << "Eccezione: " << e.what() << std::endl;
		//return 1;
	}
	try {
		std::cout << "Ora provo ad accedere ad un elemento prima del primo (cioè di begin())..." << std::endl;
		si = l.begin();
		--si;
	}
	catch (std::exception e) {
		std::cerr << "Eccezione: " << e.what() << std::endl;
	}
	try {
		std::cout << "Ora provo di nuovo, partendo da end() ad avanzare di 1..." << std::endl;
		si = l.end();
		++si;
	}
	catch (std::exception e) {
		std::cerr << "Eccezione: " << e.what() << std::endl;
	}

	return 0;
}