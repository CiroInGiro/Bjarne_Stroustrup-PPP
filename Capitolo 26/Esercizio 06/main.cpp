/*
* Capitolo 26 Esercizio 6
* Modificare Calculator del Capitolo 7 in modo minimo per consentirle di prendere input da un file
* e produrre output in un file (o utilizzare le funzionalità del sistema operativo per reindirizzare I/O). 
* Quindi ideare un test ragionevolmente completo per essa. 
*/

#include "Calculator.h"
#include <sstream>
#include <fstream>
#include <vector>
#include <random>
#include <string>
#include <map>

/*
* Ho messo Calculator in un file header, voglio creare una stringstream letta dal file dei test e inizializzare il Token_stream di Calculator.
* Lo potremmo fare aggiungendo a Calculator un operatore di input.
* Possiamo poi aggiungere anche un operatore di output per scrivere in uno stream come il file.
*/

// 1. Pulisco il codice commentato e parto dall'ultima versione del capitolo 7
// 2. Racchiudo, nel header Calculator.h, tutto il codice delle strutture dati e funzioni sotto il namespace Calculator
// 3. creo una classe Calculator e le funzioni diventano membro della classe
// 4. aggiungo qualche funzione membro di inizializzazione stream e gli operatori di input e output sugli stream.
// 5. aggiungo la funzione membro calcola() che deve prendere una stringa con le operazioni e restituisce il risultato.
// Dal main() ora posso crearmi la classe Calculator::Calculator()

// il record sarà l'espressione che utilizziamo e il risultato atteso sempre chiusi tra parentesi '{' e '}'
// esempio: { { 100/((4+4)*2+4) } 5 }\n

/*
* Token_std eredita da Token e aggiunge il costruttore di default per soddisfare il prerequisito di tipo accettato di std::vector<>.
* prepara_test() sceglie da diversi vettori di Token_std (divisi per tipo di Token) i token da aggiungere alla stringa di comandi da testare, in questo modo:
* 1. il Token di tipo print sarà aggiunto alla fine della stringa, quindi non viene scelto;
* 2. la stringa può iniziare con un Token numerico o un cancelletto per iniziare a creare una variabile, scelto da un vettore che contiene i Token con cui poter iniziare: cifre numeriche, '(', '#';
* 3. se il token inserito è un cancelletto bisogna segliere un nome variabile a caso da un vettore di stringhe;
* 4. in un vettore di token principale saranno messi tutti quelli da utilizzare per costruire la stringa di comandi;
* 5. le parentesi saranno contate quelle di apertura e chiusura e se si tenta di chiuderne più di quelle aperte si ignora il token ')', se rimangono parentesi aperte saranno aggiunti i token ')' mancanti alla fine della stringa;
* 6. un altro vettore contiene i token speciali quali quit, help, funzioni;
* 7. dal vettore dei token speciali sarà chiamata una funzione per gestire la logica per quel token;
* 8. per il valore const anche sarà chiamata una funzione per scegliere un nome e valore per poter creare una costante.
* Per fare questo potremmo creare una classe di randomizzazione Token utilizzata dalla funzione prepara_tests e che può essere passato ad altre funzioni.
* Tra le variabili e costanti create in Calculator si considera che abbiano ancora vita nei successivi record perché il file viene letto durante l'esecuzione quando Calculator ha ancora variabili e costanti in memoria, non prevede di cancellare una variabile.
* Bisogna sostituire poi il risultato 0 con quello, o quelli, calcolati in maniera affidabile, credo che nelle STL non ci sia una libreria che funziona da calcolatrice ma funzioni da legare col nostro codice e non avrebbe senso, rimarrebbe ancora codice da testare!
* Problema da risolvere: i risultati saranno chiudi tra parentesi graffe come al solito e letti come string in modo da confrontarli come stringhe esattamente uguali al risultato di Calculator::operator<<()
* QUESTA E' UNA BOZZA, TUTTA DA RIVEDERE MA AUTOMATIZZA ABBASTANZA.
*/

// Struttura con costruttore di default per essere memorizzato in un std::vector
struct Token_std : public Calculator::Token {
	Token_std() : Token('\0') { }
	Token_std(const char t) : Token(t) { }
	Token_std(double val) : Token(Calculator::number, val) { }
	Token_std(const char t, const char* name) : Token(t, std::string(name)) { }
	Token_std(const char t, const std::string name) : Token(t, name) { }
};

// Per rendere più casuale l'estrazione dei tokens gli engine random saranno inizializzati ad ogni utilizzo nelle funzioni membro, a scapito delle prestazioni.

// classe che resstituisce un tipo richiesto di token in maniera random.
class Random_tokens {
public:
	Random_tokens() {
		// Saranno aggiunti comunque tutti i tokens possibili
		tokens.push_back(Token_std(Calculator::print));	//	.	.	.	.	.	.	0
		tokens.push_back(Token_std(Calculator::guida));							//	1
		tokens.push_back(Token_std(Calculator::quit));							//	2
		tokens.push_back(Token_std('('));	//	.	.	.	.	.	.	.	.	.	3
		tokens.push_back(Token_std(')'));										//	4
		tokens.push_back(Token_std('+'));										//	5
		tokens.push_back(Token_std('-'));										//	6
		tokens.push_back(Token_std('*'));										//	7
		tokens.push_back(Token_std('/'));										//	8
		tokens.push_back(Token_std('%'));										//	9
		tokens.push_back(Token_std('='));										//	10
		tokens.push_back(Token_std(','));										//	11
		tokens.push_back(Token_std('.'));	//	.	.	.	.	.	.	.	.	.	12
		tokens.push_back(Token_std(0.0));										//	13
		tokens.push_back(Token_std(1.0));										//	14
		tokens.push_back(Token_std(2.0));										//	15
		tokens.push_back(Token_std(3.0));										//	16
		tokens.push_back(Token_std(4.0));										//	17
		tokens.push_back(Token_std(5.0));										//	18
		tokens.push_back(Token_std(6.0));										//	19
		tokens.push_back(Token_std(7.0));										//	20
		tokens.push_back(Token_std(8.0));										//	21
		tokens.push_back(Token_std(9.0));										//	22
		tokens.push_back(Token_std(Calculator::let));	//	.	.	.	.	.	.	23
		tokens.push_back(Token_std(Calculator::funzione, Calculator::radice));	//	24
		tokens.push_back(Token_std(Calculator::funzione, Calculator::potenza));	//	25
		tokens.push_back(Token_std(Calculator::costante));						//	26
		// alcune variabili
		tokens.push_back(Token_std(Calculator::name, "x"));	//	.	.	.	.	.	27
		tokens.push_back(Token_std(Calculator::name, "y"));						//	28
		tokens.push_back(Token_std(Calculator::name, "z"));						//	29
		// alcuni nomi per le costanti
		tokens.push_back(Token_std(Calculator::name, "conversione1"));	//	.	.	30
		tokens.push_back(Token_std(Calculator::name, "conversione2"));			//	31
		tokens.push_back(Token_std(Calculator::name, "conversione3"));			//	32

		// token con cui iniziare
		tokens_apertura.push_back(&tokens[1]);
		tokens_apertura.push_back(&tokens[3]);
		tokens_apertura.push_back(&tokens[12]);
		tokens_apertura.push_back(&tokens[13]);
		tokens_apertura.push_back(&tokens[14]);
		tokens_apertura.push_back(&tokens[15]);
		tokens_apertura.push_back(&tokens[16]);
		tokens_apertura.push_back(&tokens[17]);
		tokens_apertura.push_back(&tokens[18]);
		tokens_apertura.push_back(&tokens[19]);
		tokens_apertura.push_back(&tokens[20]);
		tokens_apertura.push_back(&tokens[21]);
		tokens_apertura.push_back(&tokens[22]);
		tokens_apertura.push_back(&tokens[23]);
		tokens_apertura.push_back(&tokens[24]);
		tokens_apertura.push_back(&tokens[25]);
		tokens_apertura.push_back(&tokens[26]);

		// token numerici
		tokens_numeri.push_back(&tokens[12]);
		tokens_numeri.push_back(&tokens[13]);
		tokens_numeri.push_back(&tokens[14]);
		tokens_numeri.push_back(&tokens[15]);
		tokens_numeri.push_back(&tokens[16]);
		tokens_numeri.push_back(&tokens[17]);
		tokens_numeri.push_back(&tokens[18]);
		tokens_numeri.push_back(&tokens[19]);
		tokens_numeri.push_back(&tokens[21]);
		tokens_numeri.push_back(&tokens[22]);

		// token operatori
		tokens_operatori.push_back(&tokens[4]);
		tokens_operatori.push_back(&tokens[5]);
		tokens_operatori.push_back(&tokens[6]);
		tokens_operatori.push_back(&tokens[7]);
		tokens_operatori.push_back(&tokens[8]);
		tokens_operatori.push_back(&tokens[9]);
		
		// token funzioni
		tokens_funzioni.push_back(&tokens[23]);
		tokens_funzioni.push_back(&tokens[24]);
		tokens_funzioni.push_back(&tokens[25]);
		tokens_funzioni.push_back(&tokens[26]);

		// token variabili
		tokens_variabili.push_back(&tokens[27]);
		tokens_variabili.push_back(&tokens[28]);
		tokens_variabili.push_back(&tokens[29]);

		// token costanti
		tokens_costanti.push_back(&tokens[30]);
		tokens_costanti.push_back(&tokens[31]);
		tokens_costanti.push_back(&tokens[32]);
	}

	// restituisce un token da utilizzare all'inizio della stringa di comandi
	Token_std apri() {
		std::random_device rnd_device;
		std::mt19937_64 rnd_generatore(rnd_device());
		std::uniform_int_distribution<> rnd_distribuzione(0, (tokens_apertura.size() - 1));
		size_t idx_estratto = rnd_distribuzione(rnd_generatore);
		token = *(tokens_apertura[idx_estratto]);
		
		return token;
	}

	// restituisce un token di 3 cifre compreso eventuale '.'
	Token_std operandi() {
		std::random_device rnd_device;
		std::mt19937_64 rnd_generatore(rnd_device());
		std::uniform_int_distribution<> rnd_distribuzione(0, (tokens_numeri.size() - 1));
		std::string cifre;
		bool punto = false;

		for (int i = 0; i < 3; ++i) {
			size_t idx_estratto = rnd_distribuzione(rnd_generatore);
			token = *(tokens_numeri[idx_estratto]);
			if (token.kind == '.' && !punto) {
				punto = true;
				cifre += token.kind;
			} else cifre += std::to_string((int)token.value);
		}

		if (cifre.size() == 0) token = Token_std(Calculator::number, 0);
		else {
			std::istringstream iss{ cifre };
			token.kind = Calculator::number;
			iss >> token.value;
		}

		return token;
	}

	// restituisce un token operatore
	Token_std operatori() {
		std::random_device rnd_device;
		std::mt19937_64 rnd_generatore(rnd_device());
		std::uniform_int_distribution<> rnd_distribuzione(0, (tokens_operatori.size() - 1));
		size_t idx_estratto = rnd_distribuzione(rnd_generatore);
		token = *(tokens_operatori[idx_estratto]);

		return token;
	}

	// restituisce un token con una delle funzioni
	Token_std funzioni() {
		std::random_device rnd_device;
		std::mt19937_64 rnd_generatore(rnd_device());
		std::uniform_int_distribution<> rnd_distribuzione(0, (tokens_funzioni.size() - 1));
		size_t idx_estratto = rnd_distribuzione(rnd_generatore);
		token = *(tokens_funzioni[idx_estratto]);

		return token;
	}
	
	// restituisce un token da utilizzare come nome di variabile e aggiorna lo stato sulla sua esistenza
	Token_std variabili(bool& esiste) {
		std::random_device rnd_device;
		std::mt19937_64 rnd_generatore(rnd_device());
		std::uniform_int_distribution<> rnd_distribuzione(0, (tokens_variabili.size() - 1));
		size_t idx_estratto = rnd_distribuzione(rnd_generatore);
		token = *(tokens_variabili[idx_estratto]);

		if (variabili_costanti[token.name]++) esiste = true;
		else esiste = false;

		return token;
	}

	// restituisce un token da utilizzare come nome di costante
	Token_std costanti(bool& esiste) {
		std::random_device rnd_device;
		std::mt19937_64 rnd_generatore(rnd_device());
		std::uniform_int_distribution<> rnd_distribuzione(0, (tokens_costanti.size() - 1));
		size_t idx_estratto = rnd_distribuzione(rnd_generatore);
		token = *(tokens_costanti[idx_estratto]);

		if (variabili_costanti[token.name]++) esiste = true;
		else esiste = false;

		return token;
	}

	// restituisce un token per la chiusura stringa di comandi
	Token_std chiudi() { return Token_std(Calculator::print); }

	// rilascia l'ultimo token
	Token_std last() { return token; }

private:
	Token_std token; // contiene l'ultimo token cercato
	Vector<Token_std> tokens; // contiene tutti i token
	Vector<Token_std*> tokens_apertura; // contiene i token adatti per iniziare una sequenza di comandi.
	Vector<Token_std*> tokens_numeri; // contiene i token adatti a comporre un numero
	Vector<Token_std*> tokens_operatori; // contiene gli operatori da utilizzare nell'espressione
	Vector<Token_std*> tokens_funzioni; // token che richiedono altri token
	Vector<Token_std*> tokens_variabili; // token che contengono nomi di variabili
	Vector<Token_std*> tokens_costanti; // token che contengono nomi da usare per le costanti
	std::map<std::string, bool> variabili_costanti; // mappa delle variabili e costanti definite
};


// La funzione che ci prepara il file dei tests
void prepara_tests(std::fstream& ofs);

// La funzione che legge il file dei tests e controlla i risultati
void report_tests(std::fstream& ifs);

// nel main() chiamiamo calculate() per iniziare il calcolo e gestiamo gli errori
int main(int argc, char** argv) {
	Calculator::Calculator calc;
	
	/*
	calc.go();
	
	// proviamo le nuove funzioni membro sullo stream
	std::istringstream iss{ "5+2" }; // OK anche senza terminare lo stream con ';' o '\n'
	std::cout << "Provo ad avere un risultato da una inputstringstream:\n\n";
	std::cout << "5+2=" << calc.calcola(iss) << std::endl;

	std::cout << "\n***\n\nProvo ora ad avere un risultato da una stringa:\n\n";
	std::cout << "10*10=" << calc.calcola("10*10") << std::endl; // OK

	std::cout << "\n***\n\nProvo di nuovo ad avere un risultato da una stringa vuota:\n\n";
	std::cout << "10*10=" << calc.calcola("") << std::endl; // OK

	std::cout << "\n***\n\nProvo ora ad avere un risultato con l'operatore di inpunt:\n\n";
	std::cin >> calc; // OK

	//iss >> calc; // eccezzione perché lo stream era già usato e alla fine.

	iss.clear();
	iss.str("8/2");
	std::cout << "\nMando in input 8/2: ";
	iss >> calc;

	std::cout << "\n***\n\nProvo ora a mandare un risultato in output sullo stream dallo stream impostato:\n\n";
	calc.set_input(std::cin);
	std::cout << "10*10=" << calc << std::endl; // OK
	*/

	// Prepara file di test
	std::fstream file_tests("Test Calculator.txt", std::fstream::in | std::fstream::out); // | std::fstream::trunc);

	if (!file_tests.is_open()) return 1;

	// prepara_tests(file_tests); // Fatto

	// Eseguo Calculator per eseguire manualmente il test e confrontarlo con un risultato certo.
	//calc.go();

	// Eseguo un test con una string per avere una idea sull'uso dekka nuova interfaccia.
	/*
	std::string is{ "31; #z=813; 0-690%354*545* pow(0, 561) -352-921%235-245%50+ pow(585, 635) *609; #x=0; 5/850; const conversione1=284; 4/41% pow(402, 865) /820*956/163-421-388% sqrt(459) +116* pow(601, 418) - x - conversione1 / sqrt(588) -259%516; const conversione2=661;  conversione1 + pow(609, 411) /800*361+ conversione1 + sqrt(266) -918- pow(883, 219) -304% conversione1 % conversione2 /920; const conversione3=543; 0-0+988*586-369/ pow(589, 866) *408% conversione2 *62-382; #y=125; 6% conversione3 *152+413% pow(6, 4) % pow(138, 904) *434/913-550* conversione2 / sqrt(92) + conversione1 * pow(205, 4) / pow(893, 13) %108+ conversione3 / conversione2 + pow(454, 135) * sqrt(1) /300/ conversione2 * sqrt(815) + conversione2 *322+9% sqrt(646) %1*906- z -868% x * pow(902, 120) *659- pow(324, 169) *955/ conversione1 / conversione2 +42+ y *15*94/0/ conversione1 %8+ pow(0, 82) %222+ x / conversione2 /9* sqrt(4) - sqrt(915) + sqrt(0) /925% y * pow(269, 640) -384+ sqrt(162) ; " };
	std::istringstream iss{ is };
	std::ostringstream oss;
	oss << calc.calcola(iss) << std::endl;
	oss << calc.calcola(iss) << std::endl;
	std::cout << "\n\n\nTest record comandi:\n*** Risultati ***\n ";
	std::cout << oss.str() << "\n*** FINE ***\n\n\n";
	*/
	/*
	std::string is{ "7*5;" };
	std::istringstream iss{ is };
	std::ostringstream oss;
	oss << calc.calcola(iss) << std::endl;
	oss << calc.calcola(iss) << std::endl;
	oss << calc.calcola(iss) << std::endl;
	std::cout << "\n\n\nTest record comandi:\n*** Risultati ***\n ";
	std::cout << oss.str() << "\n*** FINE ***\n\n\n";
	*/

	// Impostare il puntatore lettura nel file all'inizio
	file_tests.seekg(0);

	// Eseguire i test dal file.
	report_tests(file_tests);

	file_tests.close();

	return 0;
}

bool scelta_tipo() {
	std::random_device rnd_device;
	std::mt19937_64 rnd_engine(rnd_device());
	std::uniform_int_distribution<> rnd_distribuzione(0, 1);
	return rnd_distribuzione(rnd_engine);
}

void prepara_tests(std::fstream& ofs) {
	
	if (!ofs.good() || ofs.eof()) return;

	// utilizziamo una lunghezza di comandi random, scegliamo degli operatori random (dobbiamo controllare che siano compatibili in sequenza tra loro) e dei numeri random per le operazioni.
	// I numeri dovranno essere interi visto che non si è toccata la logica di Calculator e che come esercizio è stato uitizzato il template narrow_cast a int
	std::random_device rnd_device;
	std::mt19937_64 rnd_engine(rnd_device());
	std::uniform_int_distribution<> rnd_distribuzione(3, 100);
	Token_std token;
	Random_tokens rnd_tokens;

	for (int record = 0; record < 10; ++record) {
		std::string record_comandi;
		int num_comandi = rnd_distribuzione(rnd_engine);
		int count_parentesi{ 0 };

		// inizio record
		ofs << "{ ";

		token = rnd_tokens.apri();

		do {
			switch (token.kind) {

			case Calculator::guida:
				record_comandi += token.kind;
				record_comandi += "; ";
				--num_comandi;
				token = rnd_tokens.apri();
				break;

			case ')':

				if (count_parentesi <= 0) { count_parentesi = 0; }
				else {
					--count_parentesi;
					record_comandi += token.kind;
					--num_comandi;
				}

				token = rnd_tokens.operatori();
				break;

			case '(':
			{
				++count_parentesi;
				record_comandi += token.kind;
				--num_comandi;
				bool scelta = scelta_tipo();

				if (scelta) token = rnd_tokens.funzioni();
				else token = rnd_tokens.operandi();

			}
			break;

			case '+':
			case '-':
			case '*':
			case '/':
			case '%':
			{
				record_comandi += token.kind;
				//--num_comandi; // non posso finire con un operatore

				bool scelta = scelta_tipo();

				if (scelta) token = rnd_tokens.funzioni();
				else token = rnd_tokens.operandi();

			}
			break;

			case '.':
			case Calculator::number:
			{
				int operando = (int)token.value;
				record_comandi += std::to_string(operando);
				--num_comandi;
				token = rnd_tokens.operatori();
			}
			break;

			case Calculator::let:
			{
				bool esistenza;
				Token_std variabile = rnd_tokens.variabili(esistenza);
				//record_comandi += Calculator::let; // cambiato in '#' come esercizio precedente
				
				if (esistenza) {
					record_comandi = record_comandi + " " + variabile.name + " ";
					token = rnd_tokens.operatori();
				}
				else {
					int operando = (int)rnd_tokens.operandi().value;
					record_comandi += std::to_string(operando);

					// completiamo le parentesi
					while (count_parentesi > 0) {
						record_comandi += ')';
						--count_parentesi;
					}
					record_comandi = record_comandi + rnd_tokens.chiudi().kind + " ";

					// assegna valore alla variabile
					operando = (int)rnd_tokens.operandi().value;
					record_comandi = record_comandi + "#" + variabile.name + "=" + std::to_string(operando) + rnd_tokens.chiudi().kind + " ";

					// ricomincia
					token = rnd_tokens.apri();
				}
			}
			break;

			case Calculator::costante:
			{
				bool esistenza;
				Token_std costante = rnd_tokens.costanti(esistenza);
				if (esistenza) {
					record_comandi = record_comandi + " " + costante.name + " ";
					token = rnd_tokens.operatori();
				}
				else {
					// chiudi espressione
					int operando = (int)rnd_tokens.operandi().value;
					record_comandi += std::to_string(operando);

					// completiamo le parentesi
					while (count_parentesi > 0) {
						record_comandi += ')';
						--count_parentesi;
					}
					record_comandi = record_comandi + rnd_tokens.chiudi().kind + " ";

					// assegna un valore alla costante
					operando = (int)rnd_tokens.operandi().value;
					record_comandi = record_comandi + "const " + costante.name + "=" + std::to_string(operando) + rnd_tokens.chiudi().kind + " ";

					// ricomincia
					token = rnd_tokens.apri();
				}
			}
			break;

			case Calculator::funzione:
				int valore;

				// radice
				if (token.name == Calculator::radice) {
					valore = (int)rnd_tokens.operandi().value;
					record_comandi = record_comandi + " " + token.name + "(";
					record_comandi += std::to_string(valore);
					record_comandi += ") ";
					token = rnd_tokens.operatori();
				}

				// potenza
				if (token.name == Calculator::potenza) {
					valore = (int)rnd_tokens.operandi().value;
					record_comandi += " pow(";
					record_comandi += std::to_string(valore);
					record_comandi += ", ";
					valore = (int)rnd_tokens.operandi().value;
					record_comandi += std::to_string(valore);
					record_comandi += ") ";
					token = rnd_tokens.operatori();
				}

				--num_comandi;
				break;

			default:
				// non dovremmo trovarci qui
				record_comandi += token.kind;
				--num_comandi;
			}

		} while (num_comandi > 0);

		// completiamo le parentesi
		while (count_parentesi > 0) {
			record_comandi += ')';
			--count_parentesi;
		}

		// chiudiamo la sequenza di comandi
		record_comandi += rnd_tokens.chiudi().kind;
		ofs << record_comandi << " } ";

		// aggiungiamo il valore che ci aspettiamo e chiudiamo
		ofs << 0.0 << " }" << std::endl;
	}
}

void report_tests(std::fstream& ifs) {
	Calculator::Calculator calc;
	char ch;
	std::string comando;
	Vector<std::string> comandi;
	Vector<double> risultati;

	if (!ifs.good()) return;

	// Leggo il file
	while (!ifs.eof()) {

		// Leggere dal record la stringa con la serie di calcoli da eseguire
		while (ifs >> ch && ch != '{');

		while (!ifs.eof() && ifs.get(ch) && ch != '}') {
			if (ch == ';') {
				comandi.push_back(comando);
				comando = "";
			}
			else comando += ch;
		}

		// Leggere dal record la serie di risultati corrispondenti racchiusi tra parrentesi { }
		while (ifs >> ch && ch != '{');

		while (ifs >> ch && ch != '}') {
			std::string risultato;
			while (ch != '{') ifs >> ch;
			while (ifs >> ch && ch != '}') { risultato += ch; } // fine campo risultato
			double add_ris = std::atof(risultato.c_str());
			risultati.push_back(add_ris);
			ch = ' ';
		} // fine record
	// Passare al record successivo
	} // fine del file

	// Per ogni calcolo nella stringa eseguire il calcolo e confrontarlo col risultato
	if (comandi.size() != risultati.size()) return; // record errato nel file

	auto ris = risultati.begin();

	for (std::string str : comandi) {
		std::cout << "\n\nComando: " << str << std::endl;
		std::cout << "Risultato atteso: " << *ris << std::endl;
		double test = calc.calcola(str);
		std::cout << "Risultato da Calculator: " << test << std::endl;

		// Stampare l'esito del confronto.
		if (test == *ris) std::cout << "TEST OK\n**********\n\n";
		else std::cout << "TEST KOOOO\n**********\n\n";

		++ris;
	} // fine test
}
