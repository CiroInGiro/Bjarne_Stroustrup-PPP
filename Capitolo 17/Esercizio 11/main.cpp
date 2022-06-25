/*
Capitolo 17 Esercizio 11
Completa l'esempio della lista "List of Gods" del paragrafo 17.10.1 e lancialo.
*/

#include <iostream>

struct Link {
	std::string nome;
	Link* succ{ nullptr };
	Link* prec{ nullptr };
	Link(const std::string& n) :nome{ n } {}
	Link* insert(Link* l);
	Link* find(const std::string& s);
	Link* next() const;
	Link* erase();
	~Link();
	Link* begin();
};

Link* Link::insert(Link* l) {
	if (l == nullptr) return nullptr;
	if (prec) {
		prec->succ = l;
	}
	l->prec = prec;
	prec = l;
	l->succ = this;
	return l;
}

Link* Link::find(const std::string& s) {
	if (nome == s) return this;
	Link* p = succ;
	while (p) {
		if (p->nome == s) return p;
		p = p->succ;
	}
	p = prec;
	while (p) {
		if (p->nome == s) return p;
		p = p->prec;
	}
	return nullptr;
}

Link* Link::next() const { return succ; }

Link* Link::erase() {
	Link* retVal{ nullptr };
	if (succ) {
		succ->prec = prec;
		retVal = succ;
	}
	if (prec) {
		prec->succ = succ;
		if (!retVal) retVal = prec;
	}
	succ = nullptr;
	prec = nullptr;
	return retVal;
}

Link::~Link() {
	if (prec) delete begin();
	else if (succ) {
		succ->prec = nullptr;
		delete succ;
		succ = nullptr;
	}
	std::cout << std::endl << "delete " << nome << std::endl;
}

Link* Link::begin() {
	Link* retVal = this;
	while (retVal->prec) retVal = retVal->prec;
	return retVal;
}

void print_all(Link* p) {
	using std::cout;
	cout << "{";
	while (p) {
		cout << p->nome;
		if (p = p->next()) cout << ", ";
		//p = p->next(); // spostato nell'if
	}
	cout << "}";
}

int main(int argc, char** argv) {
	Link* norse_gods = new Link{ "Thor" };
	norse_gods = norse_gods->insert(new Link{ "Odin" });
	norse_gods = norse_gods->insert(new Link{ "Zeus" });
	norse_gods = norse_gods->insert(new Link{ "Freia" });

	Link* greek_gods = new Link{ "Hera" };
	greek_gods = greek_gods->insert(new Link{ "Athena" });
	greek_gods = greek_gods->insert(new Link{ "Mars" });
	greek_gods = greek_gods->insert(new Link{ "Poseidon" });

	Link* p = greek_gods->find("Mars");
	if (p) p->nome = "Ares";

	Link* p2 = norse_gods->find("Zeus");
	if (p2) {
		if (p2 == norse_gods) norse_gods = p2->next();
		p2->erase();
		greek_gods = greek_gods->insert(p2);
	}

	print_all(norse_gods);
	delete norse_gods;
	std::cout << std::endl;

	print_all(greek_gods);
	delete greek_gods;
	std::cout << std::endl;
	
	std::cin.get();
	// 933 Kb senza deallocare i puntatori quando non più necessari.
	// stessa dimensione con il delete degli oggetti. Lo spazio occupato da questi dati è troppo poco.
	return 0;
}

/*
Capitolo 17 Esercizio 12
Perchè abbiamo definito due versioni di find()?
Servono per cercare verso avanti o verso dietro nella lista seguendo rispettivamente i puntatori succ o prec.
Ho utilizzato una sola versione di find() ponendomi il problema da subito, ho quindi memorizzato la posizione nella lista e cercato in una direzione, in caso di esito negativo riprendo da quella posizione nel verso opposto.
*/