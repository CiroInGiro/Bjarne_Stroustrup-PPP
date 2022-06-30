#pragma once
/*
Maschera di inserimento ordini.
In alto i campi per l'intestazione ordine, in basso alcune righe per l'inserimento degli acquisti;
Un tasto per salvare le righe non vuote in un vettore e svuotare le righe per nuovi inserimenti.
Un tasto per salvare l'ordine e preparare la maschera ad un nuovo inserimento.
Ogni salvataggio sarà prima controllato per eventuali mancanze.
*/

#include "../GUI/Window.h"
#include "../GUI/GUI.h"
#include "../GUI/Graph.h"
#include <vector>
#include "Ordini.h"

// --------------------------------------------------------------------------------------
// Ogni riga è formata da 3 campi che sono il prodotto, il prezzo e la quantità
// Siccome In_Box è un campo in cui è solo possibile leggere i valori immessi e Out_box serve solo a scriverci dentro
// creiamo un nuovo widget da usare nelle righe al posto di In_box il quale utilizzerà Fl::Fl_Input.value() per leggere e scrivere nel campo.

// campi per righe di input e output
namespace Graph_lib {
	struct In_Out_Box : Widget {
		In_Out_Box(Point xy, int w, int h, const std::string& s) : Widget(xy, w, h, s, 0) {}
		int get_int();
		std::string get_string();
		void put(const std::string& s);
		void put(int i);
		void attach(Window& win);
	};
}

// righe
class righe_ordine : public Graph_lib::Widget {
public:
	righe_ordine(Point pos, int width, int height, int percentuale1 = 30, int percentuale2 = 30, int percentuale3 = 30);
	void move(int dx, int dy) override;
	void attach(Graph_lib::Window& w) override;
	void hide() override;
	void show() override;
	Purchase get_riga();
	void set_riga(const Purchase& p);
	~righe_ordine() override {}
private:
	//Graph_lib::In_box* _prodotto; // campo prodotto
	//Graph_lib::In_box* _prezzo; // campo unit_price
	//Graph_lib::In_box* _quantità; // campo count
	Graph_lib::In_Out_Box* _prodotto; // campo prodotto
	Graph_lib::In_Out_Box* _prezzo; // campo unit_price
	Graph_lib::In_Out_Box* _quantità; // campo count
};
// --------------------------------------------------------------------------------------

// --------------------------------------------------------------------------------------
// La finestra ordini ha i campi di intestazione
// e un vettore con le righe_ordine (numero limitato)
class InserimentoOrdini : Graph_lib::Window {
public:
	InserimentoOrdini(Point pos, int width, int height, const std::string titolo, Order& ordine);
	static void cb_prev(Graph_lib::Address own, Graph_lib::Address pw);
	static void cb_next(Graph_lib::Address own, Graph_lib::Address pw);
	static void cb_salva(Graph_lib::Address own, Graph_lib::Address pw);
	void prev();
	void next();
	void salva();
	// funzione per il loop, potremmo restituire qui un Order
	void go();
private:
	Order* _ordine;
	// Testata dell'ordine
	//Graph_lib::In_box _cliente;
	//Graph_lib::In_box _indirizzo;
	//Graph_lib::In_box _data;
	// Utilizziamo i campi sia di input che di output per l'esercizio 12 capitolo 21
	Graph_lib::In_Out_Box _cliente;
	Graph_lib::In_Out_Box _indirizzo;
	Graph_lib::In_Out_Box _data;
	// gestione righe dell'ordine
	std::vector<righe_ordine*> _righe;
	int r_start; // prima riga del vettore visualizzata
	int r_max; // massimo righe visualizzabili
	Point r_pos; // posizione del widget righe
	// pulsanti
	Graph_lib::Button _prev; // righe precedenti nell'ordine
	Graph_lib::Button _next; // righe successive nell'ordine
	Graph_lib::Button _salva; // salvataggio dell'ordine
	// dimensioni finestra minime e misure
	// Testata con i campi cliente, indirizzo e data
	// riga di intestazione colonne
	// colonne in base allo spazio rimasto
	// riga dei bottoni
	int _margine;
	int _field_height;
	int x_min;
	int y_min;
	// Controllo uscita
	bool gira;
};
// --------------------------------------------------------------------------------------
