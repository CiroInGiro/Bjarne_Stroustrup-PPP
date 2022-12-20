/* Capitolo 23  Esercizio 2 
* Aggiungi una multimappa e falla contenere gli oggetti. 
* Lascia che il programma prenda una stringa di input dalla tastiera 
* e stampi ogni messaggio con quella stringa come oggetto. 
*/

#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <iostream>

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

	// nello stesso ciclo organizziamo anche gli oggetti delle email
	for (const auto& m : mfile) {
		string s;
		string o; // oggetto della email
		if (find_from_addr(&m, s)) sender.insert(make_pair(s, &m));
		o = find_subject(&m);
		objects.insert(make_pair(o, &m));
	}

	// ora iteriamo con la multimap
	// ed estraiamo gli oggetti delle mail di John Doe
	auto pp = sender.equal_range("John Doe <jdoe@machine.example>");
	for (auto p = pp.first; p != pp.second; ++p) cout << find_subject(p->second) << '\n';

	cout << "\n\nOra inserisci l'oggetto di una mail che vuoi ricercare:\n";
	string oggetto;
	getline(cin, oggetto);

	int mNo{ 0 };
	for (auto o : objects) {
		++mNo;
		if (o.first == oggetto) {
			cout << "\nBene, l'oggetto <<" << oggetto << ">>è sttao trovato nel messaggio numero " << mNo << ".";
		}
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
