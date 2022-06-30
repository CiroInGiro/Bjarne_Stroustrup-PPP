/*
Capitolo 21 Esercizio 9
Definisci una classe Order con (clienti) name, address, data e un vector<Purchase>.
Purchase è una classe con un (prodotto) name, unit_price e count.
Definisci un meccanismo per leggere e scrivere Order in un file.
Definisci un meccanismo per stampare Order.
Crea un file con almeno dieci Order, leggili in un vector<Order>,
ordinali per nome (di cliente) e scrivili in un file.
Crea un altro file con almeno 10 Order di cui almeno 1/3 sono uguali al primo file,
leggilo in un list<Order>, ordinalo in base a address (del cliente) e scrivilo in un file.
Utilizza std::merge() per unire i 2 file in un terzo file.
*/

/*
Capitolo 21 esercizio 10
Calcola il valore totale degli ordini nei 2 files del precedente esercizio.
Il valore di un individuale acquisto è il unit_price*count.
*/

#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <list>
#include <algorithm> // per merge e sort
#include <iterator>

void svuota_sbuff(std::istream& is, const char& c) {
	//char buff{ ' ' };
	//while (buff != c) { is.get(buff); }
	std::string line{ "" };
	std::getline(is, line, c);
}

struct Logger {
	std::ofstream ofile;
	std::string last_message;
public:
	Logger() : last_message{ "Errore geenrico" } {
		logga(last_message);
	}
	Logger(const std::string& s) {
		logga(s);
	}
	Logger(const Logger& old) {
		last_message = old.last_message;
	}
	void logga(const std::string testo) {
		ofile.open("log.txt", std::ios_base::app);
		if (!ofile) ofile.open("log.txt");
		ofile << testo << std::endl;
		ofile.close();
	}
	std::string what() { return last_message; }
	//~Error() { ofile.close(); }
};

struct Data {
	int day;
	int month;
	int year;
	Data() : day{ 0 }, month{ 0 }, year{ 0 } {}
	friend std::ofstream& operator<<(std::ofstream& ofs, Data& d);
	friend std::ifstream& operator>>(std::ifstream& ifs, Data& d);
	friend std::ostream& operator<<(std::ostream& os, Data& d);
	friend std::istream& operator>>(std::istream& is, Data& d);
	void operator=(const Data& d) {
		day = d.day;
		month = d.month;
		year = d.year;
	}
	operator bool() { return !(day == 0 || month == 0 || year == 0); }
};

struct Purchase {
	std::string prodotto;
	double unit_price;
	int count;
public:
	Purchase() : prodotto{ "" }, unit_price{ 0 }, count{ 0 } {}
	friend std::ofstream& operator<<(std::ofstream& ofs, Purchase& p);
	friend std::ifstream& operator>>(std::ifstream& ifs, Purchase& p);
	friend std::ostream& operator<<(std::ostream& os, Purchase& p);
	friend std::istream& operator>>(std::istream& is, Purchase& p);
	void operator=(Purchase& b) {
		prodotto = b.prodotto;
		unit_price = b.unit_price;
		count = b.count;
	}
	operator bool() { return (prodotto != "" && unit_price > 0); }
};

struct Order {
	std::string cliente;
	std::string address;
	Data data_ordine;
	std::vector<Purchase> acquisti;
public:
	Order() : cliente{ "" }, address{ "" }, data_ordine{} {}
	friend std::ofstream& operator<<(std::ofstream& ofs, Order& o);
	friend std::ifstream& operator>>(std::ifstream& ifs, Order& o);
	friend std::ostream& operator<<(std::ostream& os, Order& o);
	friend std::istream& operator>>(std::istream& is, Order& o);
	operator bool() { return (cliente != "" && address != "" && data_ordine && acquisti.size() > 0); }
	void operator=(const Order& o) {
		cliente = o.cliente;
		address = o.address;
		data_ordine = o.data_ordine;
		acquisti = o.acquisti; // copia del vettore
	}
};

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

// Legge gli ordini per memorizzarli in un file
void leggi_ordini(std::ofstream& file) {
	using std::cin;
	using std::cout;
	using std::endl;
	std::cout << "Inserimento ordini ('--' per fermarti):\n";
	std::string stop{ "" };
	while (stop != "--") {
		Order buff;
		std::cout << "Nuovo ordine:\n";
		if (std::cin >> buff) {
			file << buff;
		}
		std::cout << "\nSe hai finito con gli ordini digita '--' altrimenti altro.\n";
		//std::cin >> stop;
		std::getline(std::cin, stop, '\n');
	}
	file.flush();
}

// stampa gli ordini contenuti in un file
void stampa_ordini(std::ifstream& ifs) {
	if (!ifs) throw Logger("Errore file ordini da stampare.");
	Order buff;
	while (ifs >> buff) {
		if (ifs.eof()) return;
		std::cout << buff << std::endl << std::endl;
	}
}

// legge Order da file e li salva in vector<Order>
void order_to_vector(std::ifstream& ifs, std::vector<Order>& v) {
	if (!ifs) throw Logger("Errore nel file ordini da memorizzare nel vettore.");
	Order buff;
	while (ifs >> buff) v.push_back(buff);
}

bool sort_by_cliente(const Order& a, const Order& b) {
	return a.cliente < b.cliente;
}

bool sort_by_address(const Order& a, const Order& b) {
	return a.address < b.address;
}

void stampa_vettore_ordini(std::vector<Order>& v) {
	for (Order o : v) std::cout << o << std::endl << std::endl;
}

void salva_vettore_ordini(std::ofstream& file, std::vector<Order>& v) {
	for (Order o : v) file << o;
}

double totale_ordini(const std::string& file) {
	double retVal{ 0 };
	std::ifstream ifs(file);
	if (!ifs) throw Logger("Manca il file...");
	Order ordini;
	while (ifs >> ordini) {
		for (Purchase p : ordini.acquisti) {
			retVal += (p.count * p.unit_price);
		}
	}
	ifs.close();
	return retVal;
}

int main(int argc, char** argv) {
	try {
		std::string risposta{ "" };
		while (risposta != "s" && risposta != "n") {
			std::cout << "\nInserire gli ordini (S/N)? ";
			std::cin >> risposta;
			std::tolower(risposta[0]);
		}
		if(risposta == "s") {
			// definiamo un file per memorizzare gli ordini
			std::ofstream file_ordini("Ordini.txt", std::ios_base::app);
			if (!file_ordini) file_ordini.open("Ordini.txt");
			if (!file_ordini) return 1;
			// svuoto lo stream buffer
			svuota_sbuff(std::cin, '\n');
			// leggiamo i dati da memorizzare nel file ordini.
			leggi_ordini(file_ordini);
			file_ordini.close();

			// Secondo file
			std::cout << "\n\nSecondo file ordini:\n";
			file_ordini.open("Ordini2.txt", std::ios_base::app);
			if (!file_ordini) file_ordini.open("Ordini2.txt");
			if (!file_ordini) return 1;
			// svuoto lo stream buffer
			svuota_sbuff(std::cin, '\n');
			// leggiamo i dati da memorizzare nel file ordini.
			leggi_ordini(file_ordini);
			file_ordini.close();
		}

		// stampa degli ordini contenuti nel file Ordini.txt
		std::ifstream ifile_ordini("Ordini.txt");
		stampa_ordini(ifile_ordini);
		
		// riempimento vettore
		std::vector<Order> vo;
		ifile_ordini.clear();
		ifile_ordini.seekg(0);
		order_to_vector(ifile_ordini, vo);
		// ordinamento vettore per cliente
		std::sort(vo.begin(), vo.end(), sort_by_cliente);
		// stampa del vettore
		stampa_vettore_ordini(vo);
		ifile_ordini.close();

		// carico il secondo file
		ifile_ordini.open("Ordini2.txt");
		if (!ifile_ordini) return 2;
		//std::istream_iterator<Order> in{ ifile_ordini.beg() }; // trovo solo iteratori istream e non da file
		//std::istream_iterator<Order> e{ ifile_ordini.end() };
		std::vector<Order> va;
		
		order_to_vector(ifile_ordini, va);
		std::sort(va.begin(), va.end(), sort_by_address);
		std::cout << "\n\nOrdini per indirizzo:\n\n";
		stampa_vettore_ordini(va);

		// unione dei file in Ordini_uniti.txt
		std::ofstream ofile_ordini{ "Ordini_uniti.txt" };
		if (!ofile_ordini) return 3;
		// siccome ho personalizzato gli istream e ostream operator in modo interattivo
		// faccio funzionare merge con destinazione vettore e poi riverso nel file
		std::vector<Order> vdest((vo.size() + va.size()));
		std::sort(vo.begin(), vo.end(), sort_by_cliente);
		std::sort(va.begin(), va.end(), sort_by_cliente);
		std::merge<std::vector<Order>::iterator, std::vector<Order>::iterator>(vo.begin(), vo.end(), va.begin(), va.end(), vdest.begin(), sort_by_cliente);
		salva_vettore_ordini(ofile_ordini, vdest);
		ofile_ordini.close();

		// calcolo del totale ordini per file.
		std::cout << "\n\nCalcolo il totale a valore degli ordini fatti per file:\n\n";
		std::cout << "\nTotale valore degli ordini nel file Ordini.txt: $ " << totale_ordini("Ordini.txt");
		std::cout << "\n\nTotale valore degli ordini nel file Ordini2.txt: $ " << totale_ordini("Ordini2.txt");
	}
	catch (Logger e)
	{
		std::cerr << "Ultimo errore: " << e.what() << std::endl;
	}
	catch (...) {
		std::cerr << "Errore, controlla il file log.txt\n";
	}

	return 0;
}