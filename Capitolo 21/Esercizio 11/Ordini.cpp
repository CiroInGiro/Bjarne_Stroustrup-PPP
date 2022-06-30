#include "Ordini.h"

void svuota_sbuff(std::istream& is, const char& c) {
	std::string line{ "" };
	std::getline(is, line, c);
}

// definiamo gli operatori di input e output per Data
std::ofstream& operator<<(std::ofstream& ofs, Data& d) {
	ofs << "{" << d.day << "/" << d.month << "/" << d.year << "}";
	ofs.flush();
	return ofs;
}

std::ifstream& operator>>(std::ifstream& ifs, Data& d) {
	char p1{ ' ' }, p2{ ' ' }, s1{ ' ' }, s2{ ' ' };
	Data buff;
	ifs >> p1 >> buff.day >> s1 >> buff.month >> s2 >> buff.year >> p2;
	if (!(p1 == '{' && p2 == '}' && s1 == '/' && s2 == s1)) Logger("Errore lettura Data.");
	d = buff;
	return ifs;
}

std::ostream& operator<<(std::ostream& os, Data& d) {
	os << d.day << '/' << d.month << '/' << d.year;
	return os;
}

std::istream& operator>>(std::istream& is, Data& d) {
	char s1{ ' ' }, s2{ ' ' };
	Data buff;
	is >> buff.day >> s1 >> buff.month >> s2 >> buff.year;
	if (!(s1 == '/' && s2 == s1)) { Logger("Errore leggendo data"); is.clear(); svuota_sbuff(is, '\n'); }
	d = buff;
	svuota_sbuff(is, '\n'); // l'invio dopo year
	return is;
}

// definiamo gli operatori di input e output per Purchase
std::ofstream& operator<<(std::ofstream& ofs, Purchase& p) {
	ofs << "{" << p.prodotto << "}";
	ofs << "{" << p.unit_price << "}";
	ofs << "{" << p.count << "}";
	ofs.flush();
	return ofs;
}

std::ifstream& operator>>(std::ifstream& ifs, Purchase& p) {
	char p1{ ' ' };
	char p2{ ' ' };
	Purchase buff;
	ifs >> p1;
	std::getline(ifs, buff.prodotto, '}');
	if (p1 != '{') Logger("Errore lettura Purchase::prodotto.");
	p1 = ' ';
	ifs >> p1 >> buff.unit_price >> p2;
	if (!(p1 == '{' && p2 == '}')) Logger("Errore lettura Purchase::unit_price.");
	p1 = p2 = ' ';
	ifs >> p1 >> buff.count >> p2;
	if (!(p1 == '{' && p2 == '}')) Logger("Errore lettura Purchase::count");
	p = buff;
	return ifs;
}

std::ostream& operator<<(std::ostream& os, Purchase& p) {
	os << "Prodotto: " << p.prodotto << " - Prezzo: " << p.unit_price << " - Qty: " << p.count;
	return os;
}

std::istream& operator>>(std::istream& is, Purchase& p) {
	Purchase buff;
	std::cout << "Prodotto: ";
	std::getline(is, buff.prodotto, '\n');
	std::cout << "\nPrezzo: ";
	while (!(is >> buff.unit_price)) { is.clear(); svuota_sbuff(is, '\n'); }
	std::cout << "\nQuantita': ";
	while (!(is >> buff.count)) {
		is.clear(); svuota_sbuff(is, '\n');
	}
	p = buff;
	svuota_sbuff(is, '\n');
	return is;
}

// definiamo gli operatori di input e output per Order
std::ofstream& operator<<(std::ofstream& ofs, Order& o) {
	ofs << "{" << o.cliente << "}";
	ofs << "{" << o.address << "}";
	ofs << "{"; // restituisce un ostream e non un ofstream, io voglio distinguere
	ofs << o.data_ordine << "}";
	// memorizzo un acquisto per riga
	ofs << "{";
	for (Purchase p : o.acquisti) {
		ofs << std::endl;
		ofs << p;
	}
	ofs << "}";
	ofs.flush();
	return ofs;
}

std::ifstream& operator>>(std::ifstream& ifs, Order& o) {
	Order buff;
	char p1{ ' ' }, p2{ ' ' };
	ifs >> p1;
	std::getline(ifs, buff.cliente, '}');
	if (p1 != '{') Logger("Errore lettura Order::cliente.");
	p1 = ' ';
	ifs >> p1;
	std::getline(ifs, buff.address, '}');
	if (p1 != '{') Logger("Errore lettura Order::address");
	p1 = ' ';
	ifs >> p1;
	ifs >> buff.data_ordine >> p2;
	if (!(p1 == '{' && p2 == '}')) Logger("Errore lettura Order::data_ordine.");
	p1 = p2 = ' ';
	ifs >> p1;
	if (p1 != '{') Logger("Errore lettura Order::acquisti.");
	ifs.get(p2);
	while (p2 != '}') {
		ifs.unget();
		p2 = ' ';
		Purchase pbuff;
		if (ifs >> pbuff) buff.acquisti.push_back(pbuff); else break;
		ifs.get(p2);
	}
	if (p2 != '}') Logger("Errore acquisti in ordine senza fine.");
	o = buff;
	return ifs;
}

std::ostream& operator<<(std::ostream& os, Order& o) {
	os << "Cliente: " << o.cliente << std::endl;
	os << "Indirizzo: " << o.address << std::endl;
	os << "Data ordine: " << o.data_ordine << std::endl;
	os << "Nell'ordine ci sono " << o.acquisti.size() << " righe:";
	for (Purchase p : o.acquisti) os << std::endl << p;
	return os;
}

std::istream& operator>>(std::istream& is, Order& o) {
	Order buff;
	std::cout << "Chi è il cliente? ";
	// controllo il buffer
	std::getline(is, buff.cliente, '\n');
	std::cout << "\nIndirizzo? ";
	std::getline(is, buff.address, '\n');
	std::cout << "\nData? ";
	while (!(buff.data_ordine)) { is >> buff.data_ordine; };
	std::cout << "\nInseriamo gli acquisti (per fermarti digita '--'):\n";
	std::string stop{ "" };
	while (stop != "--") {
		Purchase pbuff;
		while (!pbuff) { is >> pbuff; }
		buff.acquisti.push_back(pbuff);
		std::cout << "Se hai finito con le righe digita '--' altrimenti altro.\n";
		std::getline(is, stop, '\n');
	}
	o = buff;
	return is;
}