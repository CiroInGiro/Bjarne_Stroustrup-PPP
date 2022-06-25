/*
Capitolo 16 Esercizio 8
Provvedi a un convertitore di valute.
Leggi i fattori di conversione da un file all'avvio.
Inserisci l'ammontare in una finestra di input e fornisci una soluzione per selezionare la valuta da e a quale valuta convertire
(ad esempio un paio di menu).
*/

// ToDo dettagliare il log, tipo indicare le valute da e a

#include <string>
#include <sstream>
#include <fstream>
#include "../GUI/Graph.h"
#include "../GUI/Window.h"
#include "../GUI/GUI.h"
#include <vector>

using namespace Graph_lib;

// creiamo una struttura dati con valuta da e a, il rapporto di conversione e un puntatore callback
// ho ricreato il bottone e il menu in modo che bottone includa una funzione che restituisca l'indirizzo del tasto fltk come id dello stesso
// menu invece gestisce il nuovo tipo di bottone ma è indentico, anzi eredita proprio da menu.
// una volta trovato sappiamo anche quale tasto è stato premuto ricercando in tutti i bottoni del menu chi ha l'indirizzo corrispondente

class ButtonId : public Widget {
public:
	ButtonId(Point pos, int width, int height, const std::string& label, Callback cb) : Widget(pos, width, height, label, cb) {}
	Fl_Widget* get_pw() { return pw; }
	std::string get_label() { return label; }
	void attach(Graph_lib::Window& win) {
		pw = new Fl_Button(loc.x, loc.y, width, height, label.c_str());
		pw->callback(reinterpret_cast<Fl_Callback*>(do_it), &win); // pass the window
		own = &win;
	}
};

class MenuId : public Menu {
public:
	MenuId(Point pos, int width, int height, Kind tipo, const std::string& label) : Menu(pos, width, height, tipo, label) {}
	Vector_ref<ButtonId> selection;
	int attach(ButtonId* p) {
		return attach(*p);
	}
	int attach(ButtonId& b) {
		b.width = width;
		b.height = height;

		switch (k) {
		case horizontal:
			b.loc = Point(loc.x + offset, loc.y);
			offset += b.width;
			break;
		case vertical:
			b.loc = Point(loc.x, loc.y + offset);
			offset += b.height;
			break;
		}
		selection.push_back(&b); // b is OWNED: pass by pointer
		return int(selection.size() - 1);
	}
	void show()                 // show all buttons
	{
		for (unsigned int i = 0; i < selection.size(); ++i)
			selection[i].show();
	}
	void hide()                 // hide all buttons
	{
		for (unsigned int i = 0; i < selection.size(); ++i)
			selection[i].hide();
	}
	void move(int dx, int dy)   // move all buttons
	{
		for (unsigned int i = 0; i < selection.size(); ++i)
			selection[i].move(dx, dy);
	}

	void attach(Graph_lib::Window& win)    // attach all buttons
	{
		for (int i = 0; i < selection.size(); ++i) win.attach(selection[i]);
		own = &win;
	}
};

// funzione dichiarata ma che in Gui.cpp non era definita
void Out_box::put(int i) {
	std::ostringstream oss;
	oss << i;
	put(oss.str());
}

class Conv : public Window {
public:
	Conv(Point pos, int width, int height, const std::string& titolo) : Window(pos, width, height, titolo),
		_ammontare(Point{ pos.x + 100,pos.y + 10 }, 100, 30, "Ammontare"),
		_bt_da(Point{pos.x+210, pos.y+10}, 70, 30, "DA", [](Address, Address pw) { reference_to<Conv>(pw)._da(); }),
		_bt_a(Point{pos.x+290, pos.y+10}, 70, 30, "A", [](Address, Address pw) { reference_to<Conv>(pw)._a(); }),
		_bt_converti(Point{pos.x+390, pos.y+10}, 70, 30, "CONVERTI", [](Address, Address pw) { reference_to<Conv>(pw)._converti(); }),
		_conversione(Point{pos.x+550, pos.y+10}, 100, 30, "Valore"),
		_menu_da(Point{pos.x+210, pos.y+10}, 70, 30, Menu::Kind::vertical, "DA"),
		_menu_a(Point{pos.x+290, pos.y+10}, 70, 30, Menu::Kind::vertical, "A"),
		_log(Point{ pos.x + 100, pos.y + 80 }, "")
	{
		// in inizializzazione
		_inizializzato = false;
		_log.set_label("Sto inizializzando ma non vedrai questa scritta...");
		// leggiamo i tassi di conversione dal file
		_idata.open(_file);
		if (!_idata.is_open()) _errore("Non posso aprire il file", _file);
		while (!(_idata.fail() || _idata.eof())) {
			if (_valuta_attuale << _idata) {
				_valute.push_back(_valuta_attuale);
			}
		}
		if (_idata.fail() && !_idata.eof()) {
			if (_idata.bad()) _errore("Problemi I/O sul file", _file);
			else _errore("Errore in lettura ", _file);
		}
		if (_idata.eof()) {
			_idata.clear();
			_inizializzato = true;
			_log.set_label("Inizializzato, creo la finestra...");
		}
		_idata.close();
		// costruzione menu
		for (int indice = 0; indice < _valute.size(); ++indice) {
			_valuta_attuale = _valute[indice];
			// lavoro sul menu DA
			if (!_is_valuta_presente(indice, _valute[indice].da)) {
				ButtonId* p_bt = new ButtonId(Point{ 0,0 }, 0, 0, _valute[indice].da, cb_da);
				_menu_da.attach(p_bt);
				p_bt = new ButtonId(Point{ 0,0 }, 0, 0, _valute[indice].da, cb_a);
				_menu_a.attach(p_bt);
			}
			// lavoro sul menu A
			if (!_is_valuta_presente(indice, _valute[indice].a)) {
				ButtonId* p_bt = new ButtonId(Point{ 0,0 }, 0, 0, _valute[indice].a, cb_da);
				_menu_da.attach(p_bt);
				p_bt = new ButtonId(Point{ 0,0 }, 0, 0, _valute[indice].a, cb_a);
				_menu_a.attach(p_bt);
			}
			_valute[indice] = _valuta_attuale;
		}
		attach(_ammontare);
		attach(_bt_da);
		attach(_bt_a);
		attach(_bt_converti);
		attach(_conversione);
		_conversione.put(0);
		attach(_menu_da);
		attach(_menu_a);
		attach(_log);
		_log.set_label("Finestra creata...");
		_menu_da.hide();
		_menu_a.hide();
	}
	static void cb_da(Address pb, Address pw) {
		reference_to<Conv>(pw).search_da(pb);
	}
	static void cb_a(Address pb, Address pw) {
		reference_to<Conv>(pw).search_a(pb);
	}
private:
	// strutture dati interne
	struct Tasso {
		std::string da;
		std::string a;
		double rapporto;
		Tasso& operator<<(ifstream& ifs) {
			letto = false;
			if (!ifs.eof()) std::getline(ifs, da, ',');
			if (!ifs.eof()) std::getline(ifs, a, ',');
			if (!ifs.eof()) ifs >> rapporto;
			if (da != "" && a != "" && rapporto > 0.00) letto = true;
			char endchar{ ' ' };
			ifs.get(endchar);
			if (endchar != '\n' && endchar != ' ') ifs.unget();
			return *this;
		}
		operator bool() const { return letto;  }
	private:
		bool letto{ false };
	};
	// variabili e widget
	bool _inizializzato;
	vector<Tasso> _valute;
	Tasso _valuta_attuale;
	const std::string _file{ "valute.txt" };
	std::ifstream _idata;
	In_box _ammontare;
	Button _bt_converti;
	Graph_lib::Out_box _conversione;
	Text _log;
	Button _bt_da;
	Button _bt_a;
	MenuId _menu_da;
	MenuId _menu_a;
	// funzioni
	// Bottone Da: apre il menu delle valute dell'ammontare
	void _da() {
		_bt_da.hide();
		_menu_da.show();
	}
	// Bottone A: apre il menu delle valute per la conversione
	void _a() {
		_bt_a.hide();
		_menu_a.show();
	}
	// Bottone Converti: esegue la conversione
	void _converti() {
		std::ostringstream oss;
		// ricerca tasso e conversione coi valori impostati
		if (_valuta_attuale.da == _valuta_attuale.a || _valuta_attuale.da == "" || _valuta_attuale.a == "") {
			_valuta_attuale.rapporto = 1.00;
			_conversione.put(_ammontare.get_int());
			std::ostringstream oss;
			oss << "Conversione tra " << _valuta_attuale.da << " e " << _valuta_attuale.a << "con rapporto " << _valuta_attuale.rapporto << ".";
			_log.set_label(oss.str());
			return;
		}
		int indice{ 0 };
		if (_is_rapporto_presente(indice, _valuta_attuale.da, _valuta_attuale.a)) {
			_valuta_attuale.rapporto = _valute[indice].rapporto;
			oss << (_ammontare.get_int() * _valuta_attuale.rapporto);
			_conversione.put(oss.str());
			oss << "Conversione tra " << _valuta_attuale.da << " e " << _valuta_attuale.a << "con rapporto " << _valuta_attuale.rapporto << ".";
			_log.set_label(oss.str());
			return;
		}
		// nel caso troviamo nella tabella la conversione inversa utiliziamo quella
		if (_is_rapporto_presente(indice, _valuta_attuale.a, _valuta_attuale.da)) {
			_valuta_attuale.rapporto = _valute[indice].rapporto;
			oss << (_ammontare.get_int() / _valuta_attuale.rapporto);
			_conversione.put(oss.str());
			oss << "Conversione tra " << _valuta_attuale.da << " e " << _valuta_attuale.a << "con rapporto " << _valuta_attuale.rapporto << ".";
			_log.set_label(oss.str());
			return;
		}
		if (_is_rapporto_presente(indice, "", _valuta_attuale.da)) {
			double rapporto = _valute[indice].rapporto;
			std::string _valuta_temp = _valute[indice].da;
			if (_is_rapporto_presente(indice, _valuta_temp, _valuta_attuale.a)) {
				rapporto /= _valute[indice].rapporto;
				oss << (_ammontare.get_int() * rapporto);
				_conversione.put(oss.str());
				oss << "Conversione tra " << _valuta_attuale.da << " e " << _valuta_attuale.a << "con rapporto " << _valuta_attuale.rapporto << ".";
				_log.set_label(oss.str());
				return;
			}
		}
		_errore("Conversione non possibile");
	}
	void _errore(const std::string& errore, const std::string& data = "") {
		_log.set_label(errore + data);
	}
	bool _is_valuta_presente(int indice, const std::string& v) const {
		for (int i = 0; i < indice; ++i) {
			if (_valute[i].da == v || _valute[i].a == v) return true;
		}
		return false;
	}
	bool _is_rapporto_presente(int& indice, const std::string& da, const std::string& a = "") const {
		// aggiorna l'indice in cui si trovano i valori cercati
		if (da == "" && a == "") return false;
		if (da != "" && a == "") {
			for (int i = 0; i < _valute.size(); ++i) {
				if (da == _valute[i].da) {
					indice = i;
					return true;
				}
			}
		}
		if (da == "" && a != "") {
			for (int i = 0; i < _valute.size(); ++i) {
				if (a == _valute[i].a) {
					indice = i;
					return true;
				}
			}
		}
		if (da != "" && a != "") {
			for (int i = 0; i < _valute.size(); ++i) {
				if (da == _valute[i].da && a == _valute[i].a) {
					indice = i;
					return true;
				}
			}
		}
		return false;
	}

	int _search_idx_da(Address pb) {
		for (int i = 0; i < _menu_da.selection.size() - 1; ++i) {
			if (pb == _menu_da.selection[i].get_pw()) return i;
		}
		return -1;
	}
	void search_da(Address pb) {
		int indice = _search_idx_da(pb);
		if (indice >= 0) _valuta_attuale.da = _menu_da.selection[indice].get_label();
		// uscita dal menu
		_menu_da.hide();
		_bt_da.show();
		_log.set_label("Conversione tra " + _valuta_attuale.da + " e " + _valuta_attuale.a + ".");
	}
	int _search_idx_a(Address pb) {
		for (int i = 0; i < _menu_a.selection.size() - 1; ++i) {
			if (pb == _menu_a.selection[i].get_pw()) return i;
		}
		return -1;
	}
	void search_a(Address pb) {
		int indice = _search_idx_a(pb);
		if (indice >= 0) _valuta_attuale.a = _menu_a.selection[indice].get_label();
		// uscita dal menu
		_menu_a.hide();
		_bt_a.show();
		_log.set_label("Conversione tra " + _valuta_attuale.da + " e " + _valuta_attuale.a + ".");
	}
	void set_conversione(double d) {
		_valuta_attuale.rapporto = d;
	}
};

int main() {
	Conv convertitore(Point{ 0,0 }, 800, 300, "Capitolo 16 Esercizio 8");
	convertitore.color(Color::white);
	Graph_lib::gui_main();
}