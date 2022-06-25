/*
Capitolo 17 Esercizio 14
La lista usata nel paragrafo 17.10.1 potrebbe essere usato con una lista collegata singolarmente?
Cioè avremmo potuto fare a meno del link prec?
Perché avremmo dovuto farlo?
Per quale tipo di esempio potrebbe servire una lista collegata singolarmente?
Reimplementa questo esempio utilizzando una lista a singolo link.
*/

#include <iostream>
#include "SLink.h"

void print_all(SLink* l) {
	if (!l) return;
	while (l) {
		std::cout << "{ " << l->name() << ", " << l->mythology() << ", " << l->vehicle() << ", " << l->weapon() << " }" << std::endl;
		l = l->next();
	}
}

int main(int argc, char** argv) {
	SLink* gods;
	SLink* tizi;
	SLink* film;
	SLink* gods_ordered;
	SLink* tizi_ordered;
	SLink* film_ordered;
	std::cout << "Creo e stampo la lista degli dei: " << std::endl;
	gods = new SLink{ "Ade", "Dio degli inferi", "a piedi", "parole" };
	gods = gods->insert(new SLink{ "Urano", "Figlio e sposo di Gea e padre dei Titani", "ape cross", "coltellino" });
	gods = gods->insert(new SLink{ "Gea", "Simbolo della terra", "quad", "pietra" });
	gods = gods->insert(new SLink{ "Tanato", "La morte", "onda cbr","puzzette" });
	print_all(gods);
	std::cout << std::endl;

	std::cout << "Ora creo e stampo la lista dei tizi: " << std::endl;
	tizi = new SLink{ "Sara", "figlia del fabbro", "bici", "parole a ripetizione" };
	tizi = tizi->insert(new SLink{ "Arthur", "figlio del fabbro", "skate", "grido di pipistrello" });
	tizi = tizi->insert(new SLink{ "Gaia", "moglie del fabbro", "a piedi", "mattarello" });
	tizi = tizi->insert(new SLink{ "Il fabbro", "marito di gina", "internet", "bytes" });
	print_all(tizi);
	std::cout << std::endl;

	std::cout << "Ora tocca alla lista dei miti nei film: " << std::endl;
	film = new SLink{ "Fonzarello", "Fonzi", "moto", "fascino" };
	film = film->insert(new SLink{ "Brus", "duri a morire", "di tutto", "il pugno" });
	film = film->insert(new SLink{ "Hoppinks", "fuga da alcatraz", "motoscafo", "veleno" });
	print_all(film);
	std::cout << std::endl;

	std::cout << "Inserimento finito. Ora copio le liste in altrettante liste ordinate e ristampo:" << std::endl;
	gods_ordered = new SLink{ gods->name(), gods->mythology(), gods->vehicle(), gods->weapon() };
	while (gods = gods->next()) gods_ordered = gods_ordered->add_ordered(new SLink{ gods->name(), gods->mythology(), gods->vehicle(), gods->weapon() });
	print_all(gods_ordered);
	std::cout << std::endl;

	tizi_ordered = new SLink{ tizi->name(), tizi->mythology(), tizi->vehicle(), tizi->weapon() };
	while (tizi = tizi->next()) { tizi_ordered = tizi_ordered->add_ordered(new SLink{ tizi->name(), tizi->mythology(), tizi->vehicle(), tizi->weapon() }); }
	print_all(tizi_ordered);
	std::cout << std::endl;

	film_ordered = new SLink{ film->name(), film->mythology(), film->vehicle(), film->weapon() };
	while (film = film->next()) { film_ordered = film_ordered->add_ordered(new SLink{ film->name(), film->mythology(), film->vehicle(), film->weapon() }); }
	print_all(film_ordered);
	std::cout << std::endl;
	return 0;
}