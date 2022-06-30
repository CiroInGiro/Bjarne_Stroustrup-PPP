/*
Capitolo 21 Esercizio 12
Fornire un'interfaccia GUI per interrogare un file di Ordini;
ad esempio, "Trova tutti gli ordini da Joe",
"Trova il valore totale degli ordini nel file Hardware"
e "Elenca tutti gli ordini nel file Abbigliamento".
Suggerimento: progettare prima un'interfaccia non GUI;
quindi, crea la GUI su di essa.
*/

/*
Testualmente si crea il classimo menù in shell con l'elenco numerato e si sceglie l'operazione da fare dando in input il numero corrispondente.
Graficamente i numeri saranno sostituiti da bottoni e le azioni associati dovranno visualizzare e nascondere campi a secondo degli input aggiuntivi che serviranno.
*/

/*
Una versione evoluta potrebbe essere l'aggiunta della lettura e sintassi in un unico campo di input:
lettura riga fino al carrier return
elaborazione delle parole chiavi all'interno della riga
azioni in base alla parola chiave
*/

// Grammatica:
// comando - opzione parametro e ';' per terminare
// # comandi :
// trova : per la ricerca
// tutti, primo, ultimo, primi n, ultimi n per specificare la ricerca
// ordini : oggetto della ricerca
// file : nel file corrente oppure file string : nel file specificato
// da string : specifica del filtro, dalla intestazione specificata nella stringa
// es.trova tutti gli ordini da Joe->trova tutti ordini da Joe

/*
Usiamo token e token string per costruire i comandi.
Potremmo anche creare una classe comandi per memorizzare il comando con le sue opzioni man mano che si incontrano nello stream così da avere una sintassi meno strutturale.
*/

#include <iostream>
#include <iomanip>
#include <vector>
#include <iterator>
#include <algorithm> // copy_if
#include <numeric> // accumulate
#include <string>
//#include "Ordini.h"
#include "OrdiniGUI.h"
#include "menu_action2.h"

char menu_main() {
	using std::cin;
	using std::cout;
	using std::endl;
	char c = ' ';
	cout << endl << endl;
	cout << "1. Trova tutti gli ordini da Joe;\n";
	cout << "2. Trova il valore totale degli ordini nel file Hardware;\n";
	cout << "3. Elenca tutti gli ordini nel file Abbigliamento;\n";
	cout << "q. Uscita.\n\n";
	cout << "Scelta: ";
	cin >> c;
	if (c == 'Q') c = 'q';
	return c;
}

void menu_action1() {
	// Tutti gli ordini di Joe
	std::ifstream if_order("Ordini.txt");
	std::istream_iterator<Order> i_order{ if_order };
	std::istream_iterator<Order> eof_order;
	//std::vector<Order> v_order{ i_order, eof_order};
	std::vector<Order> v_order;
	//std::copy(i_order, eof_order, v_order.begin()); // errore di dereferenzazione perchè il vettore è vuoto
	std::copy_if(i_order, eof_order, std::back_inserter(v_order), [](const Order o) { return o.cliente == "Joe"; });
	std::cout << "Stampa Ordini dal vettore:\n";
	for (Order o : v_order) {
		//std::cout << o << std::endl << std::endl;
		// aggiungiamo la modalità GUI
		InserimentoOrdini* ogui = new InserimentoOrdini(Point{ 10, 10 }, 800, 600, "Ordini di Joe", o);
		Fl::run();
//		ogui->go();
//		ogui->stop();
		delete ogui;
	}
	//std::cout << "--------------- FINE --------------\n";
	if_order.close();
	v_order.clear();
}

void menu_action2() {
	// Valore totale degli ordini in Hardware.txt
	std::ifstream hw{ "Hardware.txt" };
	if (!hw) {
		Logger("File Hardware.txt non trovato."); return;
	}
	std::istream_iterator<Order> i_hw{hw};
	std::istream_iterator<Order> eof;
	double sum{ 0.0 };
	sum = std::accumulate(i_hw, eof, sum, [](double d, const Order& o) {for (Purchase p : o.acquisti) { d += (p.unit_price * p.count); } return d; });
	hw.close();
	//std::cout << "Totale degli ordini per hardaware: € " << sum << "\n\n";
	std::ostringstream oss{ "" };
	oss << "Totale degli ordini per hardware: € " << sum;
	message msg(Point{ 100, 100 }, 300, 100, "Menu 2", oss.str());
	Fl::run();
}

void menu_action3() {
	// Elenca tutti gli ordini nel file Abbigliamento.txt
	using std::cout; 
	using std::endl;
	std::ifstream ifs("Abbigliamento.txt");
	if (!ifs) {
		Logger("Errore file Abbigliamento.txt"); return;
	}
	std::istream_iterator<Order> i_order(ifs);
	std::istream_iterator<Order> eof;
	InserimentoOrdini* win_ordine = NULL;

	while (i_order != eof) {
		Order temp = *i_order;
		/*
		cout << "Cliente: " << temp.cliente << ";" << endl;
		cout << "Indirizzo: " << temp.address << ";" << endl;
		cout << "Data Ordine: " << temp.data_ordine << ";" << endl;
		cout << "Acquisti:\n";
		std::printf("%-20s | %-5s | %-15s | %-15s |\n", "Prodotto", "Qty", "Prezzo unitario", "Prezzo riga");
		for (Purchase p : temp.acquisti) {
			cout << std::left << std::setw(20) << p.prodotto << " | ";
			cout << std::right << std::setw(5) << p.count << " | ";
			cout << std::setprecision(2) << std::fixed << std::setw(15) << p.unit_price << " | ";
			cout << std::setw(15) << (p.count * p.unit_price) << " |" << endl;
		}
		++i_order;
		//cout << "---------------------------------------------------------" << endl;
		cout << std::setfill('-') << std::setw(66) << " |" << endl;
		*/
		win_ordine = new InserimentoOrdini(Point{ 10, 10 }, 800, 600, "Ordini in Abbigliamento.txt", temp);
		win_ordine->go();
		++i_order;
	}
	ifs.close();
}

int main(int argc, char** argv) {
	
	try {
		const char quit = 'q';
		char choice = ' ';
		while (choice != quit) {
			choice = menu_main();
			switch (choice)
			{
				case '1':
					menu_action1();
				break;
				case '2':
					menu_action2();
					break;
				case '3':
					menu_action3();
					break;
			default:
				break;
			}
		}
	}
	catch (std::runtime_error e) {
		std::cout << "\n\nErrore di runtime: " << e.what() << "\n\n";
	}
	catch (...) {
		std::cout << "\n\nErrore non gestito.\n\n";
	}
	return 0;
}