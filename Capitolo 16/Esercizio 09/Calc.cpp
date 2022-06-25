#include "Calc.h"

// preleva un Token dallo stream controllando prima nel suo buffer, se vuoto lo legge dallo standard input (cin)
Token Token_stream::get()
{
	if (full) { full = false; return buffer; }

	char ch[1];

	while (input->read(ch, 1) && isspace(ch[0]) && ch[0] != '\n') {} // Normalmente cin ignora i caratteri bianchi (gli spazi, tab, new line...) mentre read legge ogni cosa.
	
	if (!isascii(ch[0])) return Token(nullo, 0.00);

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
		input->unget(); // rimettiamo il carattere nello stream per leggerlo come un double
		double val;
		*input >> val;
		return Token(number, val); // leggendo da cin uno dei caratteri che formano un numero sarà inizializzato e restituitito un Token di tipo numerico
	}
	case '#':
		return Token(let); // abbiamo sostituito la parola chiave 'let' col carattere '#' che isalpfha('#') restutisce false
		break;
	default: // diversamente i caratteri saranno una parola chiave e saranno aggiunti ad una stringa
		if (!isspace(ch[0]) && (isalpha(ch[0]) || ch[0] == '_')) { // aggiungiamo la possibilità di avere underscore nella stringa
			string s;
			s += ch[0];
			while (input->get(ch[0]) && (isalpha(ch[0]) || isdigit(ch[0]) || ch[0] == '_')) s += ch[0]; // errore logico s=ch, ch deve essere accodato per costruire la stringa
			input->unget();
			if (s == keyquit) return Token(quit); // la parola chiave per uscire è ora memorizzata nella costante keyquit
			if (s == "sqrt") return Token(funzione, radice); // imposta il tipo funzione, il nome sqrt richiamerà la radice quadrata
			if (s == "pow") return Token(funzione, potenza); // imposta il tipo funzione, il nome pow richiamerà la potenza
			if (s == "const") return Token(costante);
			return Token(name, s);
		}
		errore("Bad token");
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

	while (input->read(ch, 1))
	{
		if (ch[0] == c || (isspace(ch[0]) && ch[0] == '\n')) return; // considero anche i carrier return perché sono trattati come il carattere per il print
	}
}

double Token_stream::Square()
{
	Token t = get();
	if (t.kind != '(') errore("dopo sqrt mi aspetto il valore o una espressione tra parentesi");
	double parentesi = expression();
	if (parentesi <= 0) errore("Non possiamo calcolare la radice quadrata di un numero che non sia maggiore di zero");
	t = get();
	if (t.kind != ')') errore("non trovo la parentesi di chiusura per la funzione sqrt");
	return sqrt(parentesi);
}

// calcolo della potenza: un valore elevato ad un numero intero
double Token_stream::Potenza()
{
	Token t = get();
	if (t.kind != '(') errore("Manca la parentesi tonda aperta. La sintassi corretta è pow(x,i) dove x è il valore e i è il numero di volte che si moltiplica");
	double x = expression();
	t = get();
	if (t.kind != ',') errore("Manca la virgola per separare i valori. La sintassi corretta è pow(x,i) dove x è il valore e i è il numero di volte che si moltiplica");
	double i = expression();
	int ii = (int)i;
	double modulo = i / ii;
	if (modulo != 1) errore("i nella funzione pow(x,i) deve essere un intero e maggiore di zero.");
	t = get();
	if (t.kind != ')') errore("mi aspettavo la parentesi chiusa dopo i. La sintassi corretta è pow(x,i)");
	return pow(x, i);
}

// selezione delle funzioni in base alla parola chiave
double Token_stream::funzioni()
{
	Token t = get();

	switch (t.kind)
	{
	case funzione:
		if (t.name == radice) return Square();
		if (t.name == potenza) return Potenza();
		errore("Mi aspettavo un nome di funzione");
		break;
	default:
		errore("Parola chiave non identificata.");
		break;
	}
}

// guida stampata a video
void Token_stream::stampa_guida()
{
	*output << "\n"
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
double Token_stream::primary()
{
	Token t = get();
	Token t2(number, 0.0);

	switch (t.kind) {
	case '(':
	{	
		double d = expression();
		t = get();
		if (t.kind != ')') errore("'(' expected");
		return d;
	}
	case '-':
		return -primary(); // inverte il segno in modo che in sottrazione si consideri una sola volta il cambio segno dovuto al doppio '-'
	case number:
	{
		//int retVal = narrow_cast<int>(t.value);
		double retVal = t.value;
		return retVal;
	}
	case name:
		t2 = get();
		if (t2.kind == '=') // se si stratta di una stringa e il prossimo Token è '=' allora devo fare una assegnazione
		{
			double risultato = expression(); // l'espressione dopo il segno uguale sarà assegnata alla variabile che c'era prima di '='
			variabili.set(t.name, risultato);
		}
		else
		{
			unget(t2); // se manca uguale vogliamo usare la variabile precedentemente assegnata
		}
		return variabili.get(t.name);
	case funzione: // gestiamo le funzioni, funzioni() identifica la funzione e richiama la funzione opportuna
		unget(t);
		return funzioni();
	default:
		errore("primary expected");
	}
}

// controlla che non si tratti di moltiplicazione o divisione e che la divisione avvenga per un numero diverso da zero
double Token_stream::term()
{
	double left = primary();
	while (true) {
		Token t = get();
		switch (t.kind) {
		case '*':
			left *= primary();
			break;
		case '/':
		{
			double d = primary();
			if (d == 0) {
				errore("Divisione per uno 0. Annullata.");
				left = 0;
			}
			else {
				left /= d;
			}
			//int left_int = (int)left / (int)d;
			//if (left_int < left) errore("Divisione con decimali");
			break;
		}
		case '%':
		{
			double d = primary();
			left *= (d / 100);
			int left_int = (int)left * ((int)d / 100);
			if (left_int < left) errore("La percentuale ha un risultato con la virgola");
			break;
		}
		default:
			unget(t);
			return left;
		}
	}
}

// expression() cerca due valori, il sinistro e destro del segno più o meno con la funzione term()
// richima prima term() per dare priorità a moltiplicazione e divisione
double Token_stream::expression()
{
	double left = term();
	while (true) {
		Token t = get();
		switch (t.kind) {
		case '+':
			left += term();
			break;
		case '-':
			left -= term();
			break;
		default:
			unget(t);
			return left;
		}
	}
}

// quando viene dichiarata una variabile con 'let' si chiama questa funzione
// la funzione controlla che il Token sia di tipo stringa
// controlla che non esista già
// controlla la sintassi, dopo il nome variabile ci deve essere '=' per l'assegnazione del valore
// memorizza il nome variabile e il valore restituito da expression() in Variable che accoda al vettore delle variabili
double Token_stream::declaration(bool costante)
{
	Token t = get();
	if (t.kind != 'a') errore("name expected in declaration");
	string name = t.name;
	Token t2 = get();
	if (t2.kind != '=') errore("= missing in declaration of ", name);
	//double d = narrow_cast<int>(expression());
	double d = expression();
	variabili.declare(name, d, costante);
	return d;
}

// controllo delle parole chiavi altrimenti passiamo a expression() per calcolare un risultato
double Token_stream::statement()
{
	Token t = get();
	switch (t.kind) {
	case let:
		return declaration();
	case costante:
		return declaration(true);
	default:
		unget(t);
		//return narrow_cast<int>(expression());
		return expression();
	}
}

// funzione chiamata in caso di errore, chiama ts.ignore(';') per saltare alla prossima espressione
// in questo caso print è una costante che equivale al carattere ';'
void Token_stream::clean_up_mess()
{
	ignore(print);
}

void Token_stream::errore(const std::string& e, const std::string& cosa) {
	*error << e;
	if (cosa != "") { *error << ": " << cosa; }
	*error << ". ";
	clean_up_mess();
	throw runtime_error("");
}

// iniziamo la lettura delle espressioni per il loro calcolo
double Token_stream::calculate()
{
	double risultato{ 0.00 };
	
	*output << prompt; // visualizziamo il carattere che sullo schermo ci fa capire di inserire qualcosa
	bool multiprompt = true;

	while (!(input->eof() || input->fail())) try {
		Token t = get();

		while (t.kind == print)
		{
			if (!multiprompt)
			{
				multiprompt = true;
				*output << " ..." << prompt; // voglio il prompt anche se ho solo invio 
			}

			t = get();
		} // server a ignorare i caratteri print anche consecutivi, passando al prossimo carattere

		if (t.kind == quit) return risultato; // se viene letto il carattere per uscire termina tutto
		if (t.kind == guida)
		{
			stampa_guida();
		}
		else if (!(input->eof() || input->fail()))
		{
			unget(t); // se il carattere non è nulla di questo allora viene stampato la valutazione dell'espressione, partendo dalla chiamata a statement()
			risultato = statement(); // facciamo in modo da poter usare anche il formato numero per calcoli esterni a questa classe.
			*output << result << risultato;// << endl;
			multiprompt = false;
		}
	}
	catch (runtime_error e) {
		// solo per uscire dal ciclo while dopo un errore.
	}
	return risultato;
}

Calc::Calc(std::istringstream& iss, std::ostringstream& oss, std::ostringstream& err) {
	_iss = &iss;
	_oss = &oss;
	_err = &err;
}