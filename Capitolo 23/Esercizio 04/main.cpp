/* Capitolo 23 Esercizio 4
** Trova un vero file di email (contenente vere email) e modifica l'esempio sulle email
* per estrarre soggetti dove corrisponde il mittende messo in input dall'utente.
*/

// Nella cartella del progetto va il file di posta, io ho usato INBOX di Thunderbird ver.101
// ma ho messo nell'esercizio il file per le prove precedente modificato

#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <iostream>
#include <regex>

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

	// Aggiungiamo anche una multimap per organizzare gli oggetti delle email
	multimap<string, const Message*> objects;

	string parola;
	cout << "\n\nQual'è il mittente da cercare? ";
	getline(cin, parola);

	regex pattern;
	smatch matches;

	try {
		pattern = parola;
	}
	catch (bad_expression) {
		std::cerr << "\n\n\n Errore pattern...\n";
		exit(1);
	}

	// Creiamo la mappa dei mittenti su cui fare le ricerche
	for (const auto& m : mfile) {
		string s;

		if (find_from_addr(&m, s))
			sender.insert(make_pair(s, &m));
	}

	// visualizziamo i dati
	std::cout << "\nEcco le mail di " << parola << ":\n\n";

	for (const auto m : sender) {
		if (regex_search(m.first, matches, pattern)) {
			cout << "Messaggio da " << m.first << " e oggetto " << find_subject(m.second) << ";" << endl;
		}
	}

	return 0;
}

Mail_file::Mail_file(const string& n) {
	// apri il file n
	// leggi le righe da n e salva in lines
	// trova i messaggi tra le linee e cosrtruiscilo in m
	// faccio finire il messaggio sulla linea precedente al prossimo inizio in modo che come ultima riga ci possa essere qualsiasi cosa.

	ifstream in{ n };
	if (!in) {
		cerr << "no " << n << '\n';
		exit(1); // termina il programma
	}

	name = n;

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
	head_msg = R"(^From - \w{3} \w{3} ( \d)|(\d{2}) {1,2}\d{1,2}:\d{1,2}:\d{1,2} \d{4})";
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
