#pragma once

/*
Grammatica:
Calcolo()
	Statement() // possiamo avere una istruzione di assegnazione: let k=1000;
	expression() // oppure una espressione: k*2;
	q: Quit // esce dal programma
	h: Stampa_Guida() // stampa a video la guida su calculator08
	;: stampa il risultato e rileggi il prossimo carattere per una nuova espressione

 Statement()
	#: aggiungi una variabile
	const: aggiungi una costante

expression()
	left = term()
	+ term()
	- term()

term()
	left = primary()
	* primary()
	/ primary()
	(primary() / 100) * left // percentuale

primary()
	numero // restituisce il valore per un tipo di token numerico
	variabile // restituisce il valore dal vettore delle variabili se il nome variabile viene trovato
	costante // o di una costante
	- numero // complementare
	funzioni() // se non è un numero e non è memorizzato in una variabile sarà restituito da una funzione

Funzioni()
	sqrt() // restituisce la radice quadrata
	pow(x,i) // restituisce la potenza di i per il numero x

*/

/*
* Codici di errori bloccanti:
* 1: Errore stream std::cin (molto improbabile)
* 2: Errore stream impostato
*/

#include "std_lib_facilities.h"

namespace Calculator {
	// definiamo delle costanti per ricordarci e usare i tipi possibili da memorizzare in Token
	const char let = 'L'; // questo tipo ci avvisa che stiamo scrivendo in input un assegnazione di una variabile
	const char quit = 'q';
	const string keyquit = "exit";
	const char print = ';'; // per avere il risultato dell'espressione
	const char number = '8'; // tipo numerico
	const char name = 'a'; // tipo carattere
	const char funzione = 'F'; // tipo funzione
	const string radice = "sqrt";
	const string potenza = "pow";
	const char costante = 'C';
	const char guida = 'h';
	const string prompt = "\n> ";
	const string result = "\n= ";

	// Gli imput sono memorizzati in una struttura dati che distinghe il tipo di input per farne l'uso appropriato
	struct Token {
		char kind; // memorizziamo il tipo di carattere in input
		double value; // memorizziamo il valore numerico in caso di numero
		string name; // memorizziamo il nome della variabile nel caso l'input è di tipo variabile + lo usiamo per identificare la funziona da usare
		Token(char ch) :kind(ch), value(0) { } // costruttore con solo il tipo, perché ci serve solo questo carattere, ad es. '+', '-' ...
		Token(char ch, double val) :kind(ch), value(val) { } // costruttore di un tipo numerico, memorizziamo anche il suo valore
		Token(char ch, string nome) :kind(ch), value(0), name(nome) { } // costruttore di una variabile, il suo valore sarà contenuto in un'altra struttura Variable
	};

	// La classe che gestisce i caratteri in input come cin ma aggiunge un carattere di buffer in modo che
	// se nella lettura non abbiamo il carattere del tipo aspettato possiamo rimettere il carattere nello stream per farlo leggere ad un'altra funzione
	class Token_stream {
		bool full;
		Token buffer;
		std::istream& stream; // Capitolo 26 Esercizio 6: aggiunto una variabile che contiene lo stream da utilizzare e modificate le funzioni get() e ignore()
	public:
		Token_stream() :full(0), buffer(0), stream ( std::cin ) { 
			// Controllo lo stream
			if (!stream.good()) error("Errore input stream Codice 1", "std::cin.");
		}
		// Capitolo 26 Esercizio 6: stream da implementare
		Token_stream(istream& in_stream) :full(0), buffer(0), stream( in_stream ) {
			if (!stream.good()) error("Errore input stream Codice 2");
		}
		// preleva un Token dallo stream controllando prima nel suo buffer, se vuoto lo legge dallo standard input (cin)
		Token get();
		void unget(Token t) { buffer = t; full = true; }
		/* quando leggiamo un token che non possiamo gestire, cioè un errore di sintassi nell'espressione
		* allora gestiamo l'errore in modo da saltare alla prossima espressione
		* nel nostro caso la funzione ci permette di leggere token fino a cercare il carattere c, a noi serve ';'
		*/
		void ignore(char);
	};

	// questa struttura contiene i valori di variabili che nell'espressione vengono definite con la stringa 'let'
	struct Variable {
		string name;
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

	class Calculator {
	private:
		// un puntatore ci permette di scambiare lo stream di inpunt
		Token_stream* _ts;
		// facciamo lo stesso per poter scegliere lo stream di output
		std::ostream* _out;

		// risolviamo la radice quadrata utilizzando la funzione sqrt di std_lib_facilities
		double Square(Token_stream& ts);

		// calcolo della potenza: un valore elevato ad un numero intero
		double Potenza(Token_stream& ts);

		// selezione delle funzioni in base alla parola chiave
		double funzioni(Token_stream& ts);

		// guida stampata a video
		void stampa_guida();

		// questa funzione restituisce il risultato di una operazione primaria, toglie le parentesi e nel caso ci sia una operazione di sottrazione
		// il segno '-' viene passato al valore in modo da poter aggiungere un valore negativo invece di sottrarre un negativo che significherebbe aggiungere.
		double primary(Token_stream& ts);

		// controlla che non si tratti di moltiplicazione o divisione o che la divisione avvenga per un numero diverso da zero
		double term(Token_stream& ts);

		// expression() cerca due valori, il sinistro e destro del segno più o meno con la funzione term()
		// richima prima term() per dare priorità a moltiplicazione e divisione
		double expression(Token_stream& ts);

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

		// Capitolo 26 Esercizio 6 Ora accetta un bool che quando true calculate() oltre a stampare il risultato esce dalla funzione e ritorna il risultato, quindi in questa modalità non è possibile avere più risultati consecutivi.
		// iniziamo la lettura delle espressioni per il loro calcolo
		double calculate(Token_stream& ts, std::ostream& out, const bool& esci = 0);

	public:
		// Costruttore di default: imposta l'interprete sullo standard input stream std::cin
		Calculator();

		// Imposta lo stream di input
		void set_input(std::istream& in = std::cin);

		// imposta lo stream di output
		void set_output(std::ostream& out = std::cout);

		// Funzione di avvio dell'interprete
		void go();

		// come go ma termina con la restituzione del risultato
		double calcola(const bool& esci = true);

		// funzione che restituisce il risultato dei comandi presi da una stringa
		double calcola(const char* comandi, const bool& esci = true, std::ostream& out = std::cout);
		double calcola(const std::string& comandi, const bool& esci = true, std::ostream& out = std::cout);

		// funzione che restituisce il risultato dei comandi presi da uno stream
		double calcola(std::istream& in, const bool& esci = true, std::ostream& out = std::cout);

		friend std::istream& operator>>(std::istream& is, Calculator& calc);

		// manda in output il risultato preso dall'input stream
		friend std::ostream& operator<<(std::ostream& os, Calculator& calc);

		~Calculator() {
			if (_ts) delete _ts;
			_out = nullptr; // L'output stream non è un oggetto gestito da noi come Token_stream
		}
	};
} // namespace Calculator