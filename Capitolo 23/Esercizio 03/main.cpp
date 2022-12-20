/* Capitolo 23 Esercizio 3
* Modifica l'esempio sulle email del paragrafo 23.4 aggiungendo le espressioni regolari per cercare nel mittente e nell'oggetto.
*/

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
	Mail_file mfile{ "my-mail-file.txt" };

	// prima raggruppiamo i messaggi da ogni mittente assieme in un multimap
	multimap<string, const Message*> sender;

	// Aggiungiamo anche una multimap per organizzare gli oggetti delle email
	multimap<string, const Message*> objects;

	cout << "\n\nOra inserisci una parola o frase da ricercare tra i mittenti e l'oggetto di una mail:\n";
	string parola;
	getline(cin, parola);

	// Creiamo qui la mappa dei mittenti che hanno <<parola>> compresa
	// Creiamo poi la mappa degli oggetti che hanno <<parola>> compresa
	// nello stesso ciclo organizziamo anche gli oggetti delle email
	
	regex pattern;
	smatch matches;

	try {
		pattern = parola;
	}
	catch (bad_expression) {
		std::cerr << "\n\n\n Errore pattern...\n";
		exit(1);
	}

	for (const auto& m : mfile) {
		string s;
		string o; // oggetto della email

		if (find_from_addr(&m, s)) {
			if (regex_search(s, matches, pattern)) sender.insert(make_pair(s, &m));
		}
		o = find_subject(&m);
		if (regex_search(o, matches, pattern)) objects.insert(make_pair(o, &m));
	}
		
	// visualizziamo i dati
	cout << "\nEcco le mail che hanno " << parola << " compresa nel mittente:\n\n";
	
	for (const auto m : sender) {
		cout << "Messaggio da " << m.first << " e oggetto " << find_subject(m.second) << ";" << endl;
	}

	cout << "Messaggi che hanno " << parola << " nell'oggetto:\n\n";

	for (const auto m : objects) {
		string mittente{ "" };
		find_from_addr(m.second, mittente);
		cout << "Messaggio da " << mittente << " con oggetto " << m.first << ";\n";
	}

	return 0;
}

Mail_file::Mail_file(const string& n) {
	// apri il file n
	// leggi le righe da n e salva in lines
	// trova i messaggi tra le linee e cosrtruiscilo in m
	// per semplicità presumiamo che ogni messaggio finisca con la linea ----
	ifstream in{ n };
	if (!in) {
		cerr << "no " << n << '\n';
		exit(1); // termina il programma
	}

	// riempimento del vettore di linee
	for (string s; getline(in, s);) lines.push_back(s);

	// riempimento vettore di messaggi
	auto first = lines.begin();
	for (auto p = lines.begin(); p != lines.end(); ++p) {
		if (*p == "----") {
			// fine del messaggio
			m.push_back(Message(first, p));
			first = p + 1; // salto dopo la fine di questo messaggio
		}
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
