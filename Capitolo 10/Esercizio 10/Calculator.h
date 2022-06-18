#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include "Roman_int.h"
//#include "..\std_lib_facilities.h"

namespace Calculation {

	// definiamo delle costanti per ricordarci e usare i tipi possibili da memorizzare in Token
	const char let = 'l'; // questo tipo ci avvisa che stiamo scrivendo in input un assegnazione di una variabile
	const char quit = 'q';
	const std::string keyquit = "exit";
	const char print = ';'; // per avere il risultato dell'espressione
	const char number = '8'; // tipo numerico
	const char name = 'a'; // tipo carattere
	const char funzione = 'F'; // tipo funzione
	const std::string radice = "sqrt";
	const std::string potenza = "pow";
	const char costante = 'c';
	const char guida = 'h';
	const char numero_romano = 'r';
	const char modo = 'm';
	const char file = 'f';

	// Gli imput sono memorizzati in una struttura dati che distinghe il tipo di input per  farne l'uso appropriato
	struct Token {
		char kind; // memorizziamo il tipo di carattere in input
		double value; // memorizziamo il valore numerico in caso di numero
		std::string name; // memorizziamo il nome della variabile nel caso l'input è di tipo variabile + lo usiamo per identificare la funziona da usare
		Roman_int roman;
		Token(char ch) :kind(ch), value(0) { } // costruttore con solo il tipo, perché ci serve solo questo carattere, ad es. '+', '-' ...
		Token(char ch, double val) :kind(ch), value(val) { } // costruttore di un tipo numerico, memorizziamo anche il suo valore
		// Aggiungo Token(char, string) 
		Token(char ch, std::string nome) :kind(ch), value(0), name(nome) { } // costruttore di una variabile, il suo valore sarà contenuto in un'altra struttura Variable
		Token(char ch, Roman_int r) : kind(ch), roman(r.as_int()) { }
	};
	// La classe che gestisce i caratteri in input come cin ma aggiunge un carattere di buffer in modo che
	// se nella lettura non abbiamo il carattere del tipo aspettato possiamo rimettere il carattere nello stream per farlo leggere ad un'altra funzione
	class Token_stream {
		bool full;
		Token buffer;
		//std::istream& mystream;
		std::ifstream fileInput;
		std::istream& getStream(); // restituisce lo stream aperto in ordine file, std in

	public:
		Token_stream() :full(0), buffer(0), fileInput{ "" } { }
		void setFile(std::string filename);
		Token get();
		void unget(Token t);
		void ignore(char);
	};

	// questa struttura contiene i valori di variabili che nell'espressione vengono definite con la stringa 'let'
	struct Variable {
		std::string name;
		double value;
		bool isCostante; // indica se il valore è modificabile oppure è una costante 
		Variable(std::string n, double v) :name(n), value(v), isCostante(false) { }
		Variable(std::string n, double v, bool c) :name(n), value(v), isCostante(c) { }
	};

	// definiamo qui una classe che racchiude il vettore delle variabili e le funzioni che ci lavorano sopra.
	class Symbol_table
	{
	private:
		std::vector<Variable> names;
		bool is_declared(std::string name);

	public:
		double get(std::string name);
		void set(std::string name, double valore); // assegna un valora ad una variabile nota
		void declare(std::string name, double valore, bool costante = false);
	};

	class Error {
	public:
		// Errore senza specificare niente
		Error();
		// crea l'oggetto Error salvando il messaggio in _message
		Error(std::string); 
		// crea l'errore con messagge risultante dalle due stringhe messaggio e le info aggiuntive
		Error(std::string, std::string);
		std::string what();
	private:
		std::string _message;
	};

	class Calculator {
	public:
		Calculator();
		// guida stampata a video
		void stampa_guida();
		// iniziamo la lettura delle espressioni per il loro calcolo
		void calculate(); // usa come input stream lo standard input cin
		void declare(std::string nome, double valore, bool iscostante);
	private:
		const std::string prompt = "> ";
		const std::string result = "= ";
		// ogni variabile definita con 'let' sarà contenuta nella struttura Variable e un vettore di questo tipo ci permette di memorizzare più di una variabile
		// vector<Variable> names; incluso nella classe Symbol_table
		// utilizziamo la classe Symbol_table
		Symbol_table variabili;
		char modo_numerico{ 'a' }; // modalità a=arabic, r=roman
		// output su file se impostato
		std::ofstream output;
		// risolviamo la radice quadrata utilizzando la funzione sqrt di std_lib_facilities
		double Square(Token_stream& ts);

		// calcolo della potenza: un valore elevato ad un numero intero
		double Potenza(Token_stream& ts);

		// selezione delle funzioni in base alla parola chiave
		double funzioni(Token_stream& ts);
		// questa funzione restituisce il risultato di una operazione primaria, toglie le parentesi e nel caso ci sia una operazione di sottrazione
		// il segno '-' viene passato al valore in modo da poter aggiungere un valore negativo invece di sottrarre un negativo che significherebbe aggiungere.
		double primary(Token_stream& ts);

		// controlla che non si tratti di moltiplicazione o divisione e che la divisione avvenga per un numero diverso da zero
		double term(Token_stream& ts);

		// expression() cerca due valori, il sinistro e destro del segno più o meno con la funzione term()
		// richima prima term() per dare priorità a moltiplicazione e divisione
		double expression(Token_stream& ts);

		// controlla i modificatori
		void modificatore(Token_stream& ts);

		// quando viene dichiarata una variabile con 'let' si chiama questa funzione
		// la funzione controlla che il Token sia di tipo stringa
		// controlla che non esista già
		// controlla la sintassi, dopo il nome variabile ci deve essere '=' per l'assegnazione del valore
		// memorizza il nome variabile e il valore restituito da expression() in Variable che accoda al vettore delle variabili
		double declaration(Token_stream& ts, bool costante = false);

		// controllo delle parole chiavi altrimenti passiamo a expression() per calcolare un risultato
		double statement(Token_stream& ts);

		// funzione chiamata in caso di errore, chiama ts.ignore(';') per saltare alla prossima espressione
		// in questo caso print è una costante che equivale al carattere ';'
		void clean_up_mess(Token_stream& ts);

		// Stampa i risultati
		void printout(double result);

		// viene chiamato dai precedenti due (calculate() e calculate(istream&) con Token_stream opportunatamente creato
		void calculate(Token_stream& ts);
	};
} // namespace Calculation

 // restituisce vero se il carattere passato è nell'alfabeto
bool isAlfa(char);

 // restituisce vero se il catattere passato è uno spazio o comando sugli spazi
bool isWhiteSpace(char);

// restituisce vero se il carattere passato rappresenta una cifra numerica
bool isNumero(char);
