/*
Capitolo 19 Esercizio 4
Modifica la classe Link del paragrafo 17.9.3 per essere un modello con il tipo di valore come parametro del template.
Poi rivedi l'esercizio 13 del capitolo 17 con Link<God>.
*/

#include <iostream>
#include "../MyClass/Link.h"

struct God {
	std::string name;
	std::string mythology;
	std::string vehicle;
	std::string weapon;
	bool operator>(const God& right) {
		if (name > right.name) return true;
		else return false;
	}
	bool operator<(const God& right) {
		if (right.name > name) return true;
		else return false;
	}
	bool operator==(God& right) {
		if (name == right.name) return true;
		else return false;
	}
};



class LinkGod : public Link<God> { // eventuale interfaccia per gestire internamente il tipo God come il vecchio Link.
	
};

template<typename T>
void print_all(Link<T>* l) {
	if (!l) return;
	Link<T>* lista = l->begin();
	while (lista) {
		std::cout << "{ " << lista->get()->name << ", " << lista->get()->mythology << ", " << lista->get()->vehicle << ", " << lista->get()->weapon << " }" << std::endl;
		lista = lista->next();
	}
}

int main(int argc, char** argv) {
	// TEST
	/*
	God l{ "Cico", "", "", "" };
	God r{ "Arkea", "", "", "" };
	if (l == r) return 0; else return 1;
	*/
	
	// esercizio Capitolo 17 Numero 13 modificato
	Link<God>* gods;
	Link<God>* mitici;
	Link<God>* film;
	Link<God>* gods_ordered;
	Link<God>* mitici_ordered;
	Link<God>* film_ordered;
	std::cout << "Creo e stampo la lista degli dei: " << std::endl;
	gods = new Link<God>{ new God{"Ade", "Dio degli inferi", "a piedi", "parole" } };
	gods = gods->insert(new Link<God>{ new God{"Urano", "Figlio e sposo di Gea e padre dei Titani", "ape cross", "coltellino" } });
	gods = gods->insert(new Link<God>{ new God{"Gea", "Simbolo della terra", "quad", "pietra" } });
	gods = gods->insert(new Link<God>{ new God{"Tanato", "La morte", "onda cbr","puzzette" } });
	print_all(gods);
	std::cout << std::endl;

	std::cout << "Ora creo e stampo la lista mitici: " << std::endl;
	mitici = new Link<God>{ new God{"Sara", "figlia del fabbro", "calzini", "parole a ripetizione" } };
	mitici = mitici->insert(new Link<God>{ new God{"Ark", "figlio del fabbro", "skate", "grido di pipistrello" } });
	mitici = mitici->insert(new Link<God>{ new God{"Gelsomina", "moglie del fabbro", "a piedi", "mattarello" } });
	mitici = mitici->insert(new Link<God>{ new God{"Il Fabbro", "marito di gelsomina", "internet", "bytes" } });
	print_all(mitici);
	std::cout << std::endl;

	std::cout << "Ora tocca alla lista dei miti nei film: " << std::endl;
	film = new Link<God>{ new God{"Fonzarello", "Fonzi", "moto", "fascino" } };
	film = film->insert(new Link<God>{ new God{"Brus", "duri a morire", "di tutto", "il pugno" } });
	film = film->insert(new Link<God>{ new God{"Hoppinks", "fuga da alcatraz", "motoscafo", "veleno" } });
	print_all(film);
	std::cout << std::endl;

	std::cout << "Inserimento finito. Ora copio le liste in altrettante liste ordinate e ristampo:" << std::endl;
	gods_ordered = new Link<God>{ new God{gods->get()->name, gods->get()->mythology, gods->get()->vehicle, gods->get()->weapon} };
	while (gods = gods->next()) gods_ordered = gods_ordered->add_ordered(new Link<God>{ new God{gods->get()->name, gods->get()->mythology, gods->get()->vehicle, gods->get()->weapon } });
	print_all(gods_ordered);
	std::cout << std::endl;

	mitici_ordered = new Link<God>{ new God{mitici->get()->name, mitici->get()->mythology, mitici->get()->vehicle, mitici->get()->weapon } };
	while (mitici = mitici->next()) { mitici_ordered = mitici_ordered->add_ordered(new Link<God>{ new God{mitici->get()->name, mitici->get()->mythology, mitici->get()->vehicle, mitici->get()->weapon } }); }
	print_all(mitici_ordered);
	std::cout << std::endl;

	film_ordered = new Link<God>{ new God{film->get()->name, film->get()->mythology, film->get()->vehicle, film->get()->weapon} };
	while (film = film->next()) { film_ordered = film_ordered->add_ordered(new Link<God>{ new God{film->get()->name, film->get()->mythology, film->get()->vehicle, film->get()->weapon } }); }
	print_all(film_ordered);
	std::cout << std::endl;
	return 0;
}