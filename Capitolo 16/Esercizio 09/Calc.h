#pragma once
#include <sstream>
#include "../GUI/std_lib_facilities.h"

using std::string;

// questa struttura contiene i valori di variabili che nell'espressione vengono definite con la stringa 'let'
struct Variable {
	std::string name;
	double value;
	bool isCostante; // indica se il valore è modificabile oppure è una costante 
	Variable(string n, double v) :name(n), value(v), isCostante(false) { }
	Variable(string n, double v, bool c) :name(n), value(v), isCostante(c) { }
};

// definiamo qui una classe che racchiude il vettore delle variabili e le funzioni che ci lavorano sopra.
class Symbol_table
{
private:
	vector<Variable> names;

	bool is_declared(string name)
	{
		for (unsigned int indice = 0; indice < names.size(); ++indice)
			if (names[indice].name == name) return true;
		return false;
	}

public:
	double get(string name)
	{
		for (unsigned int indice = 0; indice < names.size(); ++indice)
			if (names[indice].name == name) return names[indice].value;
		error("Non trovo nessuna variabile dichiarate col nome: ", name);
	}

	void set(string name, double valore)
	{
		for (unsigned int indice = 0; indice < names.size(); ++indice)
			if (names[indice].name == name)
			{
				if (names[indice].isCostante) error("La variabile è dichiarata come costante, il suo valore non può più cambiare");
				names[indice].value = valore;
				return;
			}
		error("Variabile non trovata");
	}

	void declare(string name, double valore, bool costante = false)
	{
		if (is_declared(name)) error("Variabile già dichiarata");
		names.push_back(Variable(name, valore, costante));
	}
};


// Gli imput sono memorizzati in una struttura dati che distinghe il tipo di input per farne l'uso appropriato
struct Token {
	char kind; // memorizziamo il tipo di carattere in input
	double value; // memorizziamo il valore numerico in caso di numero
	string name; // memorizziamo il nome della variabile nel caso l'input è di tipo variabile + lo usiamo per identificare la funziona da usare
	Token(char ch) :kind(ch), value(0) { } // costruttore con solo il tipo, perché ci serve solo questo carattere, ad es. '+', '-' ...
	Token(char ch, double val) :kind(ch), value(val) { } // costruttore di un tipo numerico, memorizziamo anche il suo valore
	// Aggiungo Token(char, string) 
	Token(char ch, string nome) :kind(ch), value(0), name(nome) { } // costruttore di una variabile, il suo valore sarà contenuto in un'altra struttura Variable
};

// La classe che gestisce i caratteri in input come cin ma aggiunge un carattere di buffer in modo che
// se nella lettura non abbiamo il carattere del tipo aspettato possiamo rimettere il carattere nello stream per farlo leggere ad un'altra funzione
class Token_stream {
	bool full;
	Token buffer;
	istream* input;
	ostream* output;
	ostream* error;
	// definiamo delle costanti per ricordarci e usare i tipi possibili da memorizzare in Token
	static const char let = 'L'; // questo tipo ci avvisa che stiamo scrivendo in input un assegnazione di una variabile
	static const char quit = 'q';
	const string keyquit{ "exit" };
	static const char print = ';'; // per avere il risultato dell'espressione
	static const char number = '8'; // tipo numerico
	static const char name = 'a'; // tipo carattere
	static const char funzione = 'F'; // tipo funzione
	const string radice = "sqrt";
	const string potenza = "pow";
	static const char costante = 'C';
	static const char guida = 'h';
	const string prompt = "> ";
	const string result = "= ";
	static const char nullo = 'n';
	// ogni variabile definita con 'let' sarà contenuta nella struttura Variable e un vettore di questo tipo ci permette di memorizzare più di una variabile
	// vector<Variable> names; incluso nella classe Symbol_table
	// utilizziamo la classe Symbol_table
	Symbol_table variabili;
	double expression();
	double Square();
	double Potenza();
	double funzioni();
	void stampa_guida();
	double primary();
	double term();
	double declaration(bool costante = false);
	double statement();
	void clean_up_mess();
	Token get();
	void unget(Token t) { buffer = t; full = true; }
	void ignore(char);
	void errore(const std::string& e, const std::string& cosa = "");
public:
	Token_stream() :full(0), buffer(0) { input = &cin; output = &cout; error = &cerr; }
	Token_stream(istream& in_stream, ostream& out_stream, ostream& err_stream) :full(0), buffer(0) { input = &in_stream; output = &out_stream; error = &err_stream; }
	double calculate();
};


class Calc
{
public:
	Calc(std::istringstream& iss, std::ostringstream& oss, std::ostringstream& err);
	Calc() {}
	void set_io(std::istringstream& input, std::ostringstream& output, std::ostringstream& errore) { _iss = &input; _oss = &output; _err = &errore; }
	std::ostream& get_output() { return *_oss; }
	double get_result() { return _result; }
	std::ostream& get_error() { return *_err; }
	void calcola() {
		Token_stream ts(*_iss, *_oss, *_err);
		_result = ts.calculate();
	}
private:
	std::istringstream* _iss{ nullptr };
	std::ostringstream* _oss{ nullptr };
	std::ostringstream* _err{ nullptr };
	double _result{ 0 };
};

