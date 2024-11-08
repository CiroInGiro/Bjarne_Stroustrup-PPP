#include "Calculator.h"

namespace Calculator {
	// ogni variabile definita con 'let' sarà contenuta nella struttura Variable e la classe Symbol_table le gestisce.
	// utilizziamo la classe Symbol_table
	Symbol_table variabili;

	// preleva un Token dallo stream controllando prima nel suo buffer, se vuoto lo legge dallo standard input (cin)
	Token Token_stream::get()
	{
		if (full) { full = false; return buffer; }
		char ch[1]{ quit }; // Capitolo 26 Esercizio 6 Bug carattere non inizializzati e per stream non terminati diversi da std::cin si mandava in errore std::isspace()

		while (stream.read(ch, 1) && isspace(ch[0]) && ch[0] != '\n') { } // Normalmente cin ignora i caratteri bianchi (gli spazi, tab, new line...) mentre read legge ogni cosa.

		switch (ch[0]) {
		case '\n': // sostituisce il carattere speciale carrier return con il tipo print
			return Token(print);
		case 'h': // voglio conservare la 'h' minuscola per i nomi variabile, la guida potrà essere chiesta solo con la 'H' maiuscola
			return Token(guida); // se chiediamo di stampare la guida
		case 'q':
			return Token(quit);
		case '(':
		case ')':
		case '+':
		case '-':
		case '*':
		case '/':
		case '%':
		case ';':
		case '=':
		case ',': // aggiunta per dividere i parametri in una funzione, esempio pow(x,i)
			return Token(ch[0]); // leggendo da cin uno di questi caratteri sarà inizializzato e restituito un Token di tipo char
		case '.':
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
		{
			stream.unget(); // rimettiamo il carattere nello stream per leggerlo come un double
			double val;
			stream >> val;
			return Token(number, val); // leggendo da cin uno dei caratteri che formano un numero sarà inizializzato e restituitito un Token di tipo numerico
		}
		case '#':
			return Token(let); // abbiamo sostituito la parola chiave 'let' col carattere '#' che isalpfha('#') restutisce false
			break;
		default: // diversamente i caratteri saranno una parola chiave e saranno aggiunti ad una stringa
			if (!isspace(ch[0]) && (isalpha(ch[0]) || ch[0] == '_')) { // aggiungiamo la possibilità di avere underscore nella stringa
				string s;
				s += ch[0];
				while (stream.get(ch[0]) && (isalpha(ch[0]) || isdigit(ch[0]) || ch[0] == '_')) s += ch[0];
				stream.unget();
				if (s == keyquit) return Token(quit); // la parola chiave per uscire è ora memorizzata nella costante keyquit
				if (s == "sqrt") return Token(funzione, radice); // imposta il tipo funzione, il nome sqrt richiamerà la radice quadrata
				if (s == "pow") return Token(funzione, potenza); // imposta il tipo funzione, il nome pow richiamerà la potenza
				if (s == "const") return Token(costante);
				return Token(name, s);
			}

			error("Bad token");
		}
	}

	// quando leggiamo un token che non possiamo gestire, cioè un errore di sintassi nell'espressione
	// allora gestiamo l'errore in modo da saltare alla prossima espressione
	// nel nostro caso la funzione ci permette di leggere token fino a cercare il carattere c, a noi serve ';'
	void Token_stream::ignore(char c)
	{
		if (full && c == buffer.kind) {
			full = false;
			return;
		}

		full = false;
		char ch[1];

		while (stream.read(ch, 1))
		{
			if (ch[0] == c || (isspace(ch[0]) && ch[0] == '\n')) return; // considero anche i carrier return perché sono trattati come il carattere per il print
		}
	}

	// risolviamo la radice quadrata utilizzando la funzione sqrt di std_lib_facilities
	double Calculator::Square(Token_stream& ts)
	{
		Token t = ts.get();
		if (t.kind != '(') error("dopo sqrt mi aspetto il valore o una espressione tra parentesi");
		double parentesi = expression(ts);
		if (parentesi <= 0) error("Non possiamo calcolare la radice quadrata di un numero che non sia maggiore di zero");
		t = ts.get();
		if (t.kind != ')') error("non trovo la parentesi di chiusura per la funzione sqrt");
		return sqrt(parentesi);
	}

	// calcolo della potenza: un valore elevato ad un numero intero
	double Calculator::Potenza(Token_stream& ts)
	{
		Token t = ts.get();
		if (t.kind != '(') error("Manca la parentesi tonda aperta. La sintassi corretta è pow(x,i) dove x è il valore e i è il numero di volte che si moltiplica");
		double x = expression(ts);
		t = ts.get();
		if (t.kind != ',') error("Manca la virgola per separare i valori. La sintassi corretta è pow(x,i) dove x è il valore e i è il numero di volte che si moltiplica");
		double i = expression(ts);
		int ii = (int)i;
		double modulo = i / ii;
		if (modulo != 1) error("i nella funzione pow(x,i) deve essere un intero e maggiore di zero.");
		t = ts.get();
		if (t.kind != ')') error("mi aspettavo la parentesi chiusa dopo i. La sintassi corretta è pow(x,i)");
		return pow(x, i);
	}

	// selezione delle funzioni in base alla parola chiave
	double Calculator::funzioni(Token_stream& ts)
	{
		Token t = ts.get();

		switch (t.kind)
		{
		case funzione:
			if (t.name == radice) return Square(ts);
			if (t.name == potenza) return Potenza(ts);
			error("Mi aspettavo un nome di funzione");
			break;
		default:
			error("Parola chiave non identificata.");
			break;
		}
	}

	// guida stampata a video
	void Calculator::stampa_guida()
	{
		cout << "\n"
			<< "Calculator 8:\n"
			<< "puoi usare tutti i caratteri dell'alfabeto per identificare le variabili e costanti e i numeri a..z,0..9\n"
			<< "usa + per l'addizione, - per la sottrazione, * per la moltiplicazione e / per la divisione\n"
			<< "per dichiarare una variabile usa la parola chiave #, ad esempio # nome_variabile=10\n"
			<< "per dichiarare una costante usa la parola chiave const, ad esempio const nome_costante=10, una volta dichiarata il suo valore non è più modificabile"
			<< "hai a disposizione anche le funzioni sqrt(numero) che calcola la radice quadrata di numero\n"
			<< "e pow(numero, esponente) che calcola la potenza all'esponente del numero numero.\n"
			<< "l'ordine di importanza degli operatori è * e /, + e -\n"
			<< "puoi richiedere il risultato col carattere " << print << " oppure invio\n"
			<< "puoi stampare questa guida col carattere " << guida << "\n";
	}

	// questa funzione restituisce il risultato di una operazione primaria, toglie le parentesi e nel caso ci sia una operazione di sottrazione
	// il segno '-' viene passato al valore in modo da poter aggiungere un valore negativo invece di sottrarre un negativo che significherebbe aggiungere.
	double Calculator::primary(Token_stream& ts)
	{
		Token t = ts.get();
		Token t2(number, 0.0);

		switch (t.kind) {
		case '(':
		{
			double d = expression(ts);
			t = ts.get();
			//if (t.kind != ')') error("'(' expected"); // Capitolo 26 Esercizio 6 - bug: la parentesi mancante è quella di apertura.
			if (t.kind != ')') error("')' expected");
			return d;
		}
		case '-':
			return -primary(ts); // inverte il segno in modo che in sottrazione si consideri una sola volta il cambio segno dovuto al doppio '-'
		case number:
		{
			int retVal = narrow_cast<int>(t.value);
			return retVal;
		}
		case name:
			t2 = ts.get();
			if (t2.kind == '=') // se si stratta di una stringa e il prossimo Token è '=' allora devo fare una assegnazione
			{
				double risultato = expression(ts); // l'espressione dopo il segno uguale sarà assegnata alla variabile che c'era prima di '='
				variabili.set(t.name, risultato);
			}
			else
			{
				ts.unget(t2); // se manca uguale vogliamo usare la variabile precedentemente assegnata
			}
			return variabili.get(t.name); // restituiamo la variabile
		case funzione: // gestiamo le funzioni, funzioni() identifica la funzione e richiama la funzione opportuna
			ts.unget(t);
			return funzioni(ts);
		default:
			error("primary expected");
		}
	}

	// controlla che non si tratti di moltiplicazione o divisione o che la divisione avvenga per un numero diverso da zero
	double Calculator::term(Token_stream& ts)
	{
		double left = primary(ts);
		while (true) {
			Token t = ts.get();
			switch (t.kind) {
			case '*':
				left *= primary(ts);
				break;
			case '/':
			{
				double d = primary(ts);
				if (d == 0) error("divide by zero");
				int left_int = (int)left / (int)d;
				left /= d;
				//int left_int = (int)left / (int)d; // Capitolo 26 Esercizio 6 - bug: left è già agiornato in questo punto.
				if (left_int < left) error("Divisione con decimali");
				break;
			}
			case '%':
			{
				double d = primary(ts);
				int left_int = (int)(left * (d / 100)); // Capitolo 26
				left *= (d / 100);
				//int left_int = (int)left * ((int)d / 100); // bug: left è stato già modificato, quindi left_int sarà sempre diverso da left.
				if (left_int < left) error("La percentuale ha un risultato con la virgola");
				break;
			}
			default:
				ts.unget(t);
				return left;
			}
		}
	}

	// expression() cerca due valori, il sinistro e destro del segno più o meno con la funzione term()
	// richima prima term() per dare priorità a moltiplicazione e divisione
	double Calculator::expression(Token_stream& ts)
	{
		double left = term(ts);
		while (true) {
			Token t = ts.get();
			switch (t.kind) {
			case '+':
				left += term(ts);
				break;
			case '-':
				left -= term(ts);
				break;
			default:
				ts.unget(t);
				return left;
			}
		}
	}

	// quando viene dichiarata una variabile con 'let' si chiama questa funzione
	// la funzione controlla che il Token sia di tipo stringa
	// controlla che non esista già
	// controlla la sintassi, dopo il nome variabile ci deve essere '=' per l'assegnazione del valore
	// memorizza il nome variabile e il valore restituito da expression() in Variable che accoda al vettore delle variabili
	double Calculator::declaration(Token_stream& ts, bool costante)
	{
		Token t = ts.get();
		if (t.kind != 'a') error("name expected in declaration");
		string name = t.name;
		Token t2 = ts.get();
		if (t2.kind != '=') error("= missing in declaration of ", name);
		double d = narrow_cast<int>(expression(ts));
		variabili.declare(name, d, costante);
		return d;
	}

	// controllo delle parole chiavi altrimenti passiamo a expression() per calcolare un risultato
	double Calculator::statement(Token_stream& ts)
	{
		Token t = ts.get();
		switch (t.kind) {
		case let:
			return declaration(ts);
		case costante:
			return declaration(ts, true);
		default:
			ts.unget(t);
			return narrow_cast<int>(expression(ts));
		}
	}

	// funzione chiamata in caso di errore, chiama ts.ignore(';') per saltare alla prossima espressione
	// in questo caso print è una costante che equivale al carattere ';'
	void Calculator::clean_up_mess(Token_stream& ts)
	{
		ts.ignore(print);
	}

	// iniziamo la lettura delle espressioni per il loro calcolo
	double Calculator::calculate(Token_stream& ts, std::ostream& out, const bool& esci)
	{
		// Se esci è true vogliamo solo il risultato e uscire.

		double retVal{ 0 };

		if (!esci) out << prompt; // visualizziamo il carattere che sullo schermo ci fa capire di inserire qualcosa

		while (true) try {
			Token t = ts.get();
			bool multiprompt = false;

			while (t.kind == print)
			{
				if (!multiprompt)
				{
					multiprompt = true;
					if (!esci) out << "\n" << prompt; // voglio il prompt anche se ho solo invio 
				}

				t = ts.get();
			} // serve a ignorare i caratteri print anche consecutivi, passando al prossimo carattere

			if (t.kind == quit) {
				//if (esci) out << retVal;
				return retVal; // se viene letto il carattere per uscire termina tutto
			}

			if (t.kind == guida)
			{
				stampa_guida();
			}
			else
			{
				ts.unget(t); // se il carattere non è nulla di questo allora viene stampato la valutazione dell'espressione, partendo dalla chiamata a statement()
				retVal = statement(ts);
				if (!esci) out << result << retVal << endl;
				else {
					//out << retVal;
					return retVal;
				}
			}
		}
		catch (runtime_error& e) {
			cerr << e.what() << endl;
			clean_up_mess(ts);
		}
	}

	// Costruttore di default, per impostare lo standard input di default std::cin lo deve gestire Token_stream.
	Calculator::Calculator() { 
		set_input(std::cin);
		set_output(std::cout);
	}

	// imposta lo stream di input
	void Calculator::set_input(std::istream& in) {
		if (_ts) delete _ts;
		_ts = new Token_stream(in);
	}

	void Calculator::set_output(std::ostream& out) {
		if (_out) delete _out;
		_out = &out;
	}

	void Calculator::go() {
		calcola(false);
	}

	double Calculator::calcola(const bool& esci) {
		
		if (!_ts) {
			set_input(std::cin);
		}

		if (!_out) {
			set_output(std::cout);
		}

		return calculate(*_ts, *_out, esci);
	}

	double Calculator::calcola(const char* stringa, const bool& esci, std::ostream& out) {
		std::string nuova_stringa{ stringa };

		return calcola(nuova_stringa, esci, out);
	}

	double Calculator::calcola(const std::string& stringa, const bool& esci, std::ostream& out) {
		std::istringstream iss;

		// accertiamoci che lo stream abbia il carattere di terminazione.
		if (stringa.size() > 0 && *(stringa.end() - 1) != ';' && *(stringa.end() - 1) != '\n') {
			std::string nuova_stringa = stringa + ';';
			iss.str(nuova_stringa);
		}
		else iss.str(stringa);

		return calcola(iss, esci, out);
	}

	double Calculator::calcola(std::istream& stream, const bool& esci, std::ostream& out) {
		// Sto per creare un nuovo stream ma se lo scope è in questa funzione mi ritroverò con un puntatore indefinito: probabile bug.
		double retVal{ 0 };

		if (!stream.good()) return retVal;

		// impostare gli stream
		Token_stream* ts_old = _ts;
		_ts = new Token_stream(stream);
		std::ostream* _out_old = _out;
		_out = &out;

		// eseguire il calcolo
		retVal = calculate(*_ts, out, esci);

		// reimpostare gli stream precedente
		delete _ts;
		_ts = ts_old;
		ts_old = nullptr;
		_out = _out_old;
		_out_old = 0;

		return retVal;
	}

	std::istream& operator>>(std::istream& is, Calculator& calc) {
		calc.calcola(is, false);
		return is;
	}

	std::ostream& operator<<(std::ostream& os, Calculator& calc) {
		double retVal = calc.calcola(std::cin, true, os);
		os << retVal;

		return os;
	}

} // namespace Calculator
