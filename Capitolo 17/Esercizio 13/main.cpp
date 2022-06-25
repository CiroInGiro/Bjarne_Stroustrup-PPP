/*
Capitolo 17 Esercizio 13
Modifica la classe Link per memorizzare una struttura God.
God dovrebbe avere i membri di tipo stringa: name, mythology, vehicle, weapon.
Per esempio God{"Zeus", "Greek", "", "lightning"} e God{"Odin", "Norse", "Eight-leggend flying horse called Sleipner", "Spear called Gungnir"}.
Scrivi una funzione print_all() che elenca i god coi loro attributi uno per linea.
Aggiungi una funzione membro add_ordered() che inserisce un nuovo elemento nella posizione lessicografica corretta.
Utilizzando Links con i valori di tipo God, crea 3 liste di dei delle mitologie.
Poi muovi gli elementi (God) da queste liste in 3 liste ordinate - una per ogni mitologia.
*/

#include "Link.h"
#include <iostream>

void print_all(Link* l) {
	if (!l) return;
	Link* lista = l->begin();
	while (lista) {
		std::cout << "{ " << lista->name() << ", " << lista->mythology() << ", " << lista->vehicle() << ", " << lista->weapon() << " }" << std::endl;
		lista = lista->next();
	}
}

int main(int argc, char** argv) {
	Link* gods;
	Link* tizi;
	Link* film;
	Link* gods_ordered;
	Link* tizi_ordered;
	Link* film_ordered;
	std::cout << "Creo e stampo la lista degli dei: " << std::endl;
	gods = new Link{ "Ade", "Dio degli inferi", "a piedi", "parole" };
	gods = gods->insert(new Link{ "Urano", "Figlio e sposo di Gea e padre dei Titani", "ape cross", "coltellino" });
	gods = gods->insert(new Link{ "Gea", "Simbolo della terra", "quad", "pietra" });
	gods = gods->insert(new Link{ "Tanato", "La morte", "onda cbr","puzzette" });
	print_all(gods);
	std::cout << std::endl;

	std::cout << "Ora creo e stampo la lista dei tizi: " << std::endl;
	tizi = new Link{ "Sara", "figlia del fabbro", "bici", "parole a ripetizione" };
	tizi = tizi->insert(new Link{ "Arthur", "figlio del fabbro", "skate", "grido di pipistrello" });
	tizi = tizi->insert(new Link{ "Gaia", "moglie del fabbro", "a piedi", "mattarello" });
	tizi = tizi->insert(new Link{ "Jo", "il fabbro", "internet", "bytes" });
	print_all(tizi);
	std::cout << std::endl;

	std::cout << "Ora tocca alla lista dei miti nei film: " << std::endl;
	film = new Link{ "Fonzarello", "Fonzi", "moto", "fascino" };
	film = film->insert(new Link{ "Brus", "duri a morire", "di tutto", "il pugno" });
	film = film->insert(new Link{ "Hoppinks", "fuga da alcatraz", "motoscafo", "veleno" });
	print_all(film);
	std::cout << std::endl;

	std::cout << "Inserimento finito. Ora copio le liste in altrettante liste ordinate e ristampo:" << std::endl;
	gods_ordered = new Link{ gods->name(), gods->mythology(), gods->vehicle(), gods->weapon() };
	while (gods = gods->next()) gods_ordered = gods_ordered->add_ordered(new Link{ gods->name(), gods->mythology(), gods->vehicle(), gods->weapon() });
	print_all(gods_ordered);
	std::cout << std::endl;

	tizi_ordered = new Link{ tizi->name(), tizi->mythology(), tizi->vehicle(), tizi->weapon() };
	while (tizi = tizi->next()) { tizi_ordered = tizi_ordered->add_ordered(new Link{ tizi->name(), tizi->mythology(), tizi->vehicle(), tizi->weapon() }); }
	print_all(tizi_ordered);
	std::cout << std::endl;

	film_ordered = new Link{ film->name(), film->mythology(), film->vehicle(), film->weapon() };
	while (film = film->next()) { film_ordered = film_ordered->add_ordered(new Link{ film->name(), film->mythology(), film->vehicle(), film->weapon() }); }
	print_all(film_ordered);
	std::cout << std::endl;

	return 0;
}