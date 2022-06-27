/*
Capitolo 19 Esercizio 13
Scrivi la classe Tracer che prende una stringa nel suo costruttore e la stampa il suo costruttore e il suo distruttore.
Usala per vedere come RAII (Risorse Acquisite Sono Inizializzate) fa il suo lavoro, ad esempio sperimenta su:
oggetti locali,
oggetti membro,
oggetti globali,
oggetti allocati da new(),
ecc...
Poi aggiungi un costruttore di copia e uno di assegnazione, per vedere quando la copia si è completata.
*/

#include <iostream>

class Tester {
	std::string _id;
public:
	Tester(const std::string& id) : _id{ id } {
		std::cout << "Tester id " << _id << " costruito.\n";
	}
	~Tester() {
		std::cout << "Tester id " << _id << " distrutto.\n";
	}
	std::string get_id() const { return _id; }
	void set(const std::string& id) { _id = id; }
	Tester(const Tester& right) : _id{ right.get_id() } {
		std::cout << "Copy constructor per id " << _id << "\n";
	} // copy constructor
	Tester& operator=(const Tester& right) {
		_id = right.get_id();
		std::cout << "Copy Assignment per id " << _id << "\n";
		return *this;
	}
};

class Tester2 {
	Tester t1;
	Tester* t2;
public:
	Tester2(const Tester& t) : t1{ t }, t2{ new Tester{t} } {}
	~Tester2() {
		delete t2;
	}
};

Tester tg("Global");

Tester* f(const Tester& t) {
	std::cout << "Funzione f. Dichiaro e inizializzo Tester2\n";
	Tester2 t2(t);
	std::cout << "Creo un new() Tester con id T3 in f: e lo restituisco\n";
	Tester* t3 = new Tester("T3");
	return t3;
}

Tester f2() {
	Tester retVal("f2::Tester");
	return retVal;
}

int main(int argc, char** argv) {
	Tester t1("T1");
	std::cout << "Chiamo f passando T1 e mi faccio restituire il suo in tf\n";
	Tester* tf = f(t1);
	std::cout << "T1 ora c'è ancora? " << t1.get_id() << std::endl;
	std::cin.get();
	std::cout << "Distruggo tf\n";
	delete tf;
	std::cout << "Chiamo f2 che restituisce un Tester\n";
	Tester t4 = f2();
	t4 = t1;
	return 0;
}