/*
Capitolo 21 Esercizio 6
Nell'esempio di Fruit (21.6.5), abbiamo copiato i Fruit in set.
Se non volessimo copiare Fruit?
Potremmo avere un set<Fruit*> invece.
Comunque, per fare questo, dovremmo definire un comparatore come operatore di questo set.
Implementa l'esempio di Fruit utilizzando set<Fruit*, Fruit_comparison>.
Discuti le differenze tra le 2 implementazioni.
*/

#include <set>
#include <string>
#include <iostream>

struct Date {
	int day;
	int mounth;
	int year;
};

struct Fruit {
	std::string name;
	int count;
	double unit_price;
	Date last_sale_date;
	// ... //
};

struct Fruit_order {
	bool operator()(const Fruit& a, const Fruit& b) const {
		return a.name < b.name;
	}
};

struct Fruit_comparison {
	bool operator()(const Fruit* a, const Fruit* b) const {
		return a->name < b->name;
	}
};

int main(int argc, char** argv) {
	std::set<Fruit, Fruit_order> inventory;
	inventory.insert(Fruit{ "quince", 5 });
	inventory.insert(Fruit{ "apple", 200, 0.37 });

	std::cout << "Inventory:\n\n";
	for (auto f : inventory) {
		std::cout << "Frutta " << f.name << ", giacenza " << f.count << " al prezzo di " << (f.count * f.unit_price) << ";\n";
	}

	std::cout << "\n\nModifiche per l'uso di set<Fruit*, Fruit_comparison>\n\n";

	std::set<Fruit*, Fruit_comparison> magazzino2;
	magazzino2.insert(new Fruit{ "quince", 12, 2.5 });
	magazzino2.insert(new Fruit{ "orange", 30, 1.12 });
	magazzino2.insert(new Fruit{ "apple", 2, .4 });

	std::cout << "\n\nInventario al magazzino 2:\n\n";
	for (auto f : magazzino2) {
		std::cout << "Frutta " << f->name << ", giacenza " << f->count << " al prezzo di " << (f->count * f->unit_price) << ";\n";
	}

	return 0;
}

/*
La differenza dal punto di vista di implementazione è la gestione del puntatore in più e il controllo della sua validità.
Un inconveniente è che in set non bisognerà mai far capitare un puntatore null altrimenti la funzione di comparazione non potrà funzionare
Forse siccome set al suo interno è come una lista conviene memorizzare direttamente il dato, lasciare gestire il puntatore a set, non credo che si risparmi spazio in memoria con l'uso di questa versione a puntatori.
*/

