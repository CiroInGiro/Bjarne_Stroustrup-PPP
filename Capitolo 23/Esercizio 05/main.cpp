/* Capitolo 23 esercizio 5
* Trova un file di posta grande, migliaia di email e cronometra quando ci mette a scrivere in un multimap
* e poi sostituisci la multimap con una unordered_multipap perché non traiamo benefici dall'ordinamento in questo programma.
*/

// Testato col mio file INBOX di Thunderbird 102 di 65MB
// 146 millisecondi per riempire la mappa ordinata
// 141 millisecondi per riempire la mappa non ordinata
// CPU i5 2 core Gen.3

#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <iostream>
#include <regex>
#include <chrono>
#include <unordered_map>

struct bad_expression {};

using namespace std;

typedef vector<string>::const_iterator Line_iter;

// Definizione di Messaggio come una coppia di iteratori in un vector<string> (il nostro vettore di linee)
class Message {
	// Un puntatore Message alla prima e ultima riga del messaggio
	Line_iter first;
	Line_iter last;
public:
	Message(Line_iter p1, Line_iter p2) : first{ p1 }, last{ p2 } {}
	Line_iter begin() const { return first; }
	Line_iter end() const { return last; }
	// ...
};

using Mess_iter = vector<Message>::const_iterator;
// Definiamo un Mail_file come uan struttura che memorizza linee di testo e messaggi.
struct Mail_file {
	// memorizza le linee da un file e semplifica l'accesso ai messaggi
	string name; // nome file
	vector<string> lines; // le linee ordinate
	vector<Message> m; // messaggi ordinati

	Mail_file(const string& n); // legge il file n in lines

	Mess_iter begin() const { return m.begin(); }
	Mess_iter end() const { return m.end(); }
};

// controlla una sottostringa
int is_prefix(const string&, const string&);

// ricerca il nome del mittende in una mail
// ritorna true se trovato e mette il nome del mittente in s
bool find_from_addr(const Message* m, string& s);

// ritorna l'oggetto della mail se c'è altrimenti ""
string find_subject(const Message* m);

int main(int argc, char* argv[]) {
	// inizializza mfile da un file
	Mail_file mfile{ "INBOX" };

	// prima raggruppiamo i messaggi da ogni mittente assieme in un multimap
	multimap<string, const Message*> sender;

	// aggiungiamo una mappa dei mittenti non ordinata
	unordered_multimap<string, const Message*> unordered_sender;

	// Aggiungiamo anche una multimap per organizzare gli oggetti delle email
	multimap<string, const Message*> objects;

	std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
	std::chrono::steady_clock::time_point end;
	std::chrono::steady_clock::duration time_ordered, time_unordered;

	// Creiamo la mappa dei mittenti su cui fare le ricerche
	for (const auto& m : mfile) {
		string s;

		if (find_from_addr(&m, s))
			sender.insert(make_pair(s, &m));
	}
	end = std::chrono::steady_clock::now();
	time_ordered = end - start;
	cout << "\nTempo trascorso per riempire la mappa ordinata dei mittenti: " << std::chrono::duration_cast<std::chrono::milliseconds>(time_ordered).count() << " millisecondi.\n";

	start = std::chrono::steady_clock::now();
	// Creiamo la mappa non ordinata dei mittenti su cui fare le ricerche
	for (const auto& m : mfile) {
		string s;

		if (find_from_addr(&m, s))
			unordered_sender.insert(make_pair(s, &m));
	}
	end = std::chrono::steady_clock::now();
	time_unordered = end - start;
	cout << "\nTempo trascorso per riempire la mappa non ordinata dei mittenti: " << std::chrono::duration_cast<std::chrono::milliseconds>(time_unordered).count() << " millisecondi.\n";

	return 0;
}

Mail_file::Mail_file(const string& n) {
	// apri il file n
	// leggi le righe da n e salva in lines
	// trova i messaggi tra le linee e cosrtruiscilo in m
	// faccio finire il messaggio sula linea precedente al prossimo inizio in modo che come ultima riga ci possa essere qualsiasi cosa.

	ifstream in{ n };
	if (!in) {
		cerr << "no " << n << '\n';
		exit(1); // termina il programma
	}

	// riempimento del vettore di linee
	for (string s; getline(in, s);) lines.push_back(s);

	in.close();

	// riempimento vettore di messaggi
	// in mozilla abbiamo solo l'inizio del messaggio tipo questo:
	// From - Sun Jul  3 21:55:40 2022
	// quindi "^From - \w{3} \w{3} \d{1,2}| {0,1} \d{1,2}:\d{1,2}:\d{1,2} \d{4}

	auto first = lines.begin(); // condizione iniziale
	auto last = first; // condizione iniziale
	regex head_msg;
	//head_msg = R"(^From - \w{3} \w{3} ( \d)|(\d{2}) {1,2}\d{1,2}:\d{1,2}:\d{1,2} \d{4})"; // con così tante regole il programma rallenta in maniera esponenziale alle regole e impiega troppi minuti
	head_msg = R"(^(From - ))"; // per velocizzare con le operazioni regex strettamente necessarie.
	smatch head_match;

	for (auto p = lines.begin(); p != lines.end(); ++p) {
		// controllo se abbiamo trovato una riga che inizia il messaggio
		if (regex_search(*p, head_match, head_msg)) {
			// inizialmente sia first che last sono all'inizio del vettore, quindi abbiamo trovato solo first per ora
			if (first != last) {
				// memorizza questo messaggio (first e last attuali)
				m.push_back(Message(first, last));
			}
			// assegnamo a first la testa del nuovo messagio
			first = p;
		}
		// last memorizza la riga già controllata, p risulterà nei controlli come last+1
		last = p;
	}
}

int is_prefix(const string& s, const string& p) {
	// p è la parte iniziale della stringa s?
	int n = p.size();
	if (string(s, 0, n) == p) return n;
	return 0;
}

bool find_from_addr(const Message* m, string& s) {
	for (const auto& x : *m)
		if (int n = is_prefix(x, "From: ")) {
			s = string(x, n);
			return true;
		}
	return false;
}

string find_subject(const Message* m) {
	for (const auto& x : *m)
		if (int n = is_prefix(x, "Subject: ")) return string(x, n);
	return "";
}