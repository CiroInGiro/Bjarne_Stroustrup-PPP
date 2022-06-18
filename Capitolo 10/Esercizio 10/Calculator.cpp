/*
Grammatica:
Calcolo()
	Modificatore() // controlla i modificatori di comportamento
	iofile() // configura gli input e output dei iostream
	Statement() // controlla le parole chiavi possiamo avere una istruzione di assegnazione: let k=1000;
	expression() // oppure una espressione: k*2;
	q: Quit // esce dal programma
	h: Stampa_Guida() // stampa a video la guida su calculator08
	;: stampa il risultato e rileggi il prossimo carattere per una nuova espressione

Modificatore()
	arabic: imposta il risultato in formato arabico
	roman: imposta il risultato in formato romano
	from: imposta input da file
	to: inposta output secondario su file

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

// Calculator del capitolo 7 
// modificato nel capitolo 8 per accettare un istream
// Capitolo 10 Esercizio 7 aggiunge il calcolo coi numeri romani.
// Capitolo 10 Esercizio 10 aggiunge la possibilità di ricevere l'input da file e salvare tutto l'output su file
// - ho provato ad avere uno istream membro privbato da sostituire ma gli stream li riesco solo ad inizializzare
// - ho provato allora a creare un nuovo calculator passando il nuovo stream ma a parte il bug che devo controllare se lo stream è disponibile perché alla fine del file c'è l'eccezione
//	 ma è anche vero che calculate() crea un loop infinito, quindi o si mette un limitatore che però si innescherebbe alla fine del file o si pensa ad iniettare nello stream corrente quello nuovo.

#include "Calculator.h"
#include "Roman_int.h"

#include <exception>

using namespace Calculation;

// imposta un file come streaming di input
void Token_stream::setFile(std::string filename) {
	if (fileInput.is_open()) {
		//fileInput.close();
		throw Error("Un file è già aperto.");
	}
	else fileInput.open(filename, std::ios::in);
	if (!fileInput) throw Error{ "Problemi nell'aprire il file di input ", filename };
}


std::istream& Token_stream::getStream() {
	if (fileInput.is_open()) {
		fileInput.peek();
		if (fileInput.eof()) {
			fileInput.close();
			return std::cin;
		}
		if (fileInput.fail()) {
			fileInput.close();
			throw Error{ "Errore di lettura dal file" };
		}
		if (fileInput.bad()) { 
			fileInput.close();
			throw Error{ "Errore nell'usare il dispositivo di input" };
		}
		return fileInput;
	}
	return std::cin;
}

// preleva un Token dallo stream controllando prima nel suo buffer, se vuoto lo legge dallo standard input (cin)
Token Token_stream::get()
{
	using std::string;
	if (full) { full = false; return buffer; }
	//char ch;
	//cin >> ch;
	char ch[1]{ ' ' };
	// prepariamo lo streaming di input
	std::istream& mystream{ getStream() };

	//mystream.putback(ch[0]);

	/*
	while (true) {
		if (!mystream.read(ch, 1)) break;
		if (ch[0] == '\n') break;
		if (!isWhiteSpace(ch[0])) break;
	}
	*/

	while (mystream.read(ch, 1) && isWhiteSpace(ch[0]) && ch[0] != '\n') {} // Normalmente cin ignora i caratteri bianchi (gli spazi, tab, new line...) mentre read legge ogni cosa.
	switch (ch[0]) {
	case '\n': // sostituisce il carattere speciale carrier return con il tipo print
		return Token(print);
		//case 'H': // cambiato dall'esercizio 7
	case 'h': // voglio conservare la 'h' minuscola per i nomi variabile, laguida potrà essere chiesta solo con la 'H' maiuscola
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
		mystream.unget(); // rimettiamo il carattere nello stream per leggerlo come un double
		double val;
		mystream >> val;
		return Token(number, val); // leggendo da cin uno dei caratteri che formano un numero sarà inizializzato e restituitito un Token di tipo numerico
	}
	case 'I':
	case 'V':
	case 'X':
	case 'L':
	case 'C':
	case 'D':
	case 'M':
	{
		mystream.unget();
		//double val;
		Roman_int num_roman; // inizializiamo la classe Roman_int
		mystream >> num_roman; // leggiamo i simboli romani dallo stream, la classe li convertirà
		//val = num_roman.as_int(); // preleviamo il valore decimale convertiro dalla classe Roman_int
		//return Token(number, val); // creiamo un nuovo Token col valore convertito.
		return Token(numero_romano, num_roman); // ora gestiamo anche il tipo Roman_int nel Token
	}
	case '#':
		return Token(let); // abbiamo sostituito la parola chiave 'let' col carattere '#' che isalpfha('#') restutisce false
		break;
	default: // diversamente i caratteri saranno una parola chiave e saranno aggiunti ad una stringa
		if (!isWhiteSpace(ch[0]) && (isAlfa(ch[0]) || ch[0] == '_')) { // aggiungiamo la possibilità di avere underscore nella stringa
			string s;
			s += ch[0];
			while (mystream.get(ch[0]) && (isAlfa(ch[0]) || isNumero(ch[0]) || ch[0] == '_' || ch[0] == '.')) s += ch[0]; // errore logico s=ch, ch deve essere accodato per costruire la stringa
			mystream.unget();
			//if (s == "let") return Token(let);	// parola chiave 'let' per assegnare una variabile, il carattere è identifiato dalla costante let
			//if (s == "quit") return Token(quit); // allo stesso modo se la stringa letta è quit assegnamo al token il carattere della costante quit e non name
			if (s == keyquit) return Token(quit); // la parola chiave per uscire è ora memorizzata nella costante keyquit
			if (s == "sqrt") return Token(funzione, radice); // imposta il tipo funzione, il nome sqrt richiamerà la radice quadrata
			if (s == "pow") return Token(funzione, potenza); // imposta il tipo funzione, il nome pow richiamerà la potenza
			if (s == "const") return Token(costante);
			if (s == "mod") return Token(modo);
			//if (s == "from" || s == "to") return Token(modo, s);
			// Token(char, string) non esisteva, errore di compilazione
			return Token(name, s);
		}
		throw Error("Bad token");
	}
}

void Token_stream::unget(Token t) { buffer = t; full = true; }

// quando leggiamo un token che non possiamo gestire, cioè un errore di sintassi nell'espressione
// allora gestiamo l'errore in modo da saltare alla prossima espressione
// nel nostro caso la funzione ci permette di leggere token fino a cercare il carattere c, a noi serve ';'
void Token_stream::ignore(char c)
{
	//using std::cin;

	if (full && c == buffer.kind) {
		full = false;
		return;
	}
	full = false;

	// modifico questa parte per considerare anche i caratteri bianchi come print

	// in caso di errore di lettura dallo stream non sarà usato ch nullo
	char ch[1]{ ' ' };
	std::istream& mystream{ getStream() };
	bool readfail = true;

	if (mystream.read(ch, 1)) readfail = false;
	else mystream.clear(); // se lo stream é in errore viene resettato

	while (!readfail)
	{
		if (ch[0] == c || (isWhiteSpace(ch[0]) && ch[0] == '\n')) return; // considero anche i carrier return perché sono trattati come il carattere per il print
		if (mystream.read(ch, 1)) readfail = false;
	}
}

bool Symbol_table::is_declared(std::string name)
{
	for (unsigned int indice = 0; indice < names.size(); ++indice)
		if (names[indice].name == name) return true;
	return false;
}


double Symbol_table::get(std::string name)
{
	for (unsigned int indice = 0; indice < names.size(); ++indice)
		if (names[indice].name == name) return names[indice].value;
	throw Error("Non trovo nessuna variabile dichiarate col nome: ", name);
}



void Symbol_table::set(std::string name, double valore)
{
	for (unsigned int indice = 0; indice < names.size(); ++indice)
		if (names[indice].name == name)
		{
			if (names[indice].isCostante) throw Error("La variabile è dichiarata come costante, il suo valore non può più cambiare");
			names[indice].value = valore;
			return;
		}
	throw Error("Variabile non trovata");
}



void Symbol_table::declare(std::string name, double valore, bool costante)
{
	if (is_declared(name)) throw Error("Variabile già dichiarata");
	names.push_back(Variable(name, valore, costante));
}

Error::Error() : _message{ "" } {}
Error::Error(std::string messaggio) : _message{ messaggio } {}
Error::Error(std::string messaggio, std::string oggetto) { _message = messaggio + ": " + oggetto; }
std::string Error::what() { return _message; }

Calculator::Calculator() {}

void Calculator::declare(std::string nome, double valore, bool iscostante) {
	variabili.declare(nome, valore, iscostante);
}

double Calculator::Square(Token_stream& ts)
{
	Token t = ts.get();
	if (t.kind != '(') throw Error("dopo sqrt mi aspetto il valore o una espressione tra parentesi", "Square");
	double parentesi = expression(ts);
	if (parentesi <= 0) throw Error("Non possiamo calcolare la radice quadrata di un numero che non sia maggiore di zero", "Square");
	t = ts.get();
	if (t.kind != ')') throw Error("non trovo la parentesi di chiusura per la funzione sqrt", "Square");
	return sqrt(parentesi);
}


double Calculator::Potenza(Token_stream& ts)
{
	Token t = ts.get();
	if (t.kind != '(') throw Error("Manca la parentesi tonda aperta. La sintassi corretta è pow(x,i) dove x è il valore e i è il numero di volte che si moltiplica", "Potenza");
	double x = expression(ts);
	t = ts.get();
	if (t.kind != ',') throw Error("Manca la virgola per separare i valori. La sintassi corretta è pow(x,i) dove x è il valore e i è il numero di volte che si moltiplica", "Potenza");
	double i = expression(ts);
	int ii = (int)i;
	double modulo = i / ii;
	if (modulo != 1) throw Error("i nella funzione pow(x,i) deve essere un intero e maggiore di zero", "Potenza");
	t = ts.get();
	if (t.kind != ')') throw Error("mi aspettavo la parentesi chiusa dopo i. La sintassi corretta è pow(x,i)", "Potenza");
	return pow(x, i);
}


double Calculator::funzioni(Token_stream& ts)
{
	Token t = ts.get();

	switch (t.kind)
	{
	case funzione:
		if (t.name == radice) return Square(ts);
		if (t.name == potenza) return Potenza(ts);
		Error("Mi aspettavo un nome di funzione", "");
		break;
	default:
		throw Error("Parola chiave non identificata.", "");
		break;
	}
}

void Calculator::stampa_guida()
{
	using std::cout;
	cout << "\n"
		<< "Calculator 8.Roman:\n"
		<< "puoi usare tutti i caratteri dell'alfabeto per identificare le variabili e costanti e i numeri a..z,0..9\n"
		<< "usa + per l'addizione, - per la sottrazione, * per la moltiplicazione e / per la divisione\n"
		<< "per dichiarare una variabile usa la parola chiave #, ad esempio # nome_variabile=10\n"
		<< "per dichiarare una costante usa la parola chiave const, ad esempio const nome_costante=10,\n"
		<< "una volta dichiarata il suo valore non è più modificabile.\n"
		<< "hai a disposizione anche le funzioni sqrt(numero) che calcola la radice quadrata di numero\n"
		<< "e pow(numero, esponente) che calcola la potenza all'esponente di numero.\n"
		<< "l'ordine di importanza degli operatori è * e /, + e -\n"
		<< "usa i numeri romani formati da simboli I, V, X, L, C, D e M\n"
		<< "puoi richiedere il risultato col carattere " << print << " oppure invio\n"
		<< "se vuoi il risultato in numeri roamni usa il modificatore 'mod roman', nel sistema arabico usa 'mod arabic' (di default)\n"
		<< "per caricare l'input da un file usa il modificatore 'mod from nomefile'\n"
		<< "per avere l'output salvato su file usa il modificatore 'mod to nomefile'\n"
		<< "puoi stampare questa guida col carattere " << guida << "\n";
}


double Calculator::primary(Token_stream& ts)
{
	Token t = ts.get();
	Token t2(number, 0.0);

	switch (t.kind) {
	case '(':
	{
		double d = expression(ts);
		t = ts.get();
		if (t.kind != ')') Error("'(' expected");
		// errore logico, manca il ritorno dell'espressione tra parentesi, inizialmente non ci avevo fatto caso (Drill 5)
		return d;
	}
	case '-':
		return -primary(ts); // inverte il segno in modo che in sottrazione si consideri una sola volta il cambio segno dovuto al doppio '-'
	case number:
	{
		//int retVal = narrow_cast<int>(t.value);
		//modo = 'a'; // se usiamo numeri arabici calculator passa in questa modalità
		return t.value;
		//return retVal;
	}
	case numero_romano:
		return (double)t.roman.as_int();
	case let:
	case costante:
		ts.unget(t);
		return statement(ts);
	case name:
		t2 = ts.get();
		if (t2.kind == '=') // se si stratta di una stringa e il prossimo Token è '=' allora devo fare una assegnazione
		{
			double risultato = expression(ts); // l'espressione dopo il segno uguale sarà assegnata alla variabile che c'era prima di '='
			//set_value(t.name, risultato);
			variabili.set(t.name, risultato);
			return risultato;
		}
		else
		{
		ts.unget(t2); // se manca uguale vogliamo usare la variabile precedentemente assegnata
		}
		//return get_value(t.name); // restituiamo la variabile
		return variabili.get(t.name);
	case funzione: // gestiamo le funzioni, funzioni() identifica la funzione e richiama la funzione opportuna
		ts.unget(t);
		return funzioni(ts);
	case modo:
		//ts.unget(t);
		modificatore(ts); // continuo dal file e restituisco il token letto da primary nel file
		//return primary(ts);
		return statement(ts);
	case print:
		return statement(ts);
	default:
		throw Error("primary expected", "Primary");
	}
}

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
			if (d == 0) throw Error("divide by zero", "term");
			left /= d;
			//int left_int = (int)left / (int)d;
			//if (left_int < left) throw Error("Divisione con decimali");
			break;
		}
		case '%':
		{
			double d = primary(ts);
			left *= (d / 100);
			//int left_int = (int)left * ((int)d / 100);
			//if (left_int < left) Error("La percentuale ha un risultato con la virgola");
			break;
		}
		default:
			ts.unget(t);
			return left;
		}
	}
}


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


double Calculator::declaration(Token_stream& ts, bool costante)
{
	using std::string;
	Token t = ts.get();
	if (t.kind != 'a') throw Error("name expected in declaration", "declaration");
	string name = t.name;
	//if (is_declared(name)) error(name, " declared twice"); // faccio il controllo nella classe al momento dell'assegnazione
	Token t2 = ts.get();
	if (t2.kind != '=') throw Error("= missing in declaration of ", name);
	//double d = narrow_cast<int>(expression(ts));
	double d = expression(ts);
	//names.push_back(Variable(name,d,costante));
	variabili.declare(name, d, costante);
	return d;
}

void Calculator::modificatore(Token_stream& ts) {
	Token t = ts.get();
	if (t.name == "arabic") {
		modo_numerico = 'a';
		return;
	}
	if (t.name == "roman") {
		modo_numerico = 'r';
		return;
	}
	if (t.name == "from") {
		Token t2 = ts.get();
		if (t2.kind != name) throw Error{ "manca il nome del file", "from" };
		ts.setFile(t2.name);
		return;
	}
	if (t.name == "to") {
		Token t2 = ts.get();
		if (t2.kind != name) throw Error{ "manca il nome del file", "to" };
		if (output.is_open()) output.close();
		output.open(t2.name, output.out);
		if (!output) throw Error{ "non sono riuscito a creare il file di output", t2.name };
		return;
	}
	throw Error("Modificatore sconosciuto", t.name);
}

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
		//return narrow_cast<int>(expression(ts));
		return expression(ts);
	}
}


void Calculator::clean_up_mess(Token_stream& ts)
{
	ts.ignore(print);
}

void Calculator::calculate() {
	Token_stream ts;
	calculate(ts);
}

void Calculator::printout(double result) {
	using std::cout;
	using std::endl;

	if (modo_numerico == 'a') {
		cout << endl << "= " << result << endl; // normalmente abbiamo il risultato nel sistema decimale
		if (output.is_open()) {
			output << endl << "= " << result << endl;
		}
	}
	
	// nel caso abbiamo modificato il comportamento di calculator in numeri romani convertiamo il risultato per scriverlo in numeri romani.
	if (modo_numerico == 'r') {
		Roman_int romano{ (int)result };
		cout << romano << endl;
		if (output.is_open()) {
			output << romano << endl;
		}
	}
}

void Calculator::calculate(Token_stream& ts)
{
	using std::cout;
	using std::endl;
	using std::cerr;
	cout << prompt; // visualizziamo il carattere che sullo schermo ci fa capire di inserire qualcosa
	bool multiprompt = false;

	while (true) try {
		Token t = ts.get();

		while (t.kind == print)
		{
			if (!multiprompt)
			{
				multiprompt = true;
				cout << "\n" << prompt; // voglio il prompt anche se ho solo invio 
			}

			t = ts.get();
		} // server a ignorare i caratteri print anche consecutivi, passando al prossimo carattere

		if (t.kind == quit) return; // se viene letto il carattere per uscire termina tutto
		if (t.kind == guida)
		{
			stampa_guida();
		}
		else if (t.kind == modo) {
			modificatore(ts);
			multiprompt = false;
		}
		else
		{
			ts.unget(t); // se il carattere non è nulla di questo allora viene stampato la valutazione dell'espressione, partendo dalla chiamata a statement()
			double result = statement(ts);
			printout(result);
			multiprompt = false;
		}
	}
	//catch (runtime_error & e) {
	catch (Error & e) {
		cerr << e.what() << endl;
		if (output) { output << e.what() << endl; }
		clean_up_mess(ts);
	}
}

bool isAlfa(char c) {
	switch (c) {
		// alfabeto in minuscolo
	case 'a':
	case 'b':
	case 'c':
	case 'd':
	case 'e':
	case 'f':
	case 'g':
	case 'h':
	case 'i':
	case 'j':
	case 'k':
	case 'l':
	case 'm':
	case 'n':
	case 'o':
	case 'p':
	case 'q':
	case 'r':
	case 's':
	case 't':
	case 'u':
	case 'v':
	case 'w':
	case 'x':
	case 'y':
	case 'z':
		// alfabeto in maiuscolo
	case 'A':
	case 'B':
	case 'C':
	case 'D':
	case 'E':
	case 'F':
	case 'G':
	case 'H':
	case 'I':
	case 'J':
	case 'K':
	case 'L':
	case 'M':
	case 'N':
	case 'O':
	case 'P':
	case 'Q':
	case 'R':
	case 'S':
	case 'T':
	case 'U':
	case 'V':
	case 'W':
	case 'X':
	case 'Y':
	case 'Z':
		return true;
	default:
		return false;
		break;
	}
}

bool isWhiteSpace(char c) {
	switch (c) {
	case ' ':
	case '\t':
	case '\v':
	case '\f':
	case '\c':
	case '\r':
	case '\n':
		return true;
	default:
		return false;
	}
}

bool isNumero(char c) {
	switch (c) {
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
		return true;
	default:
		return false;
	}
}