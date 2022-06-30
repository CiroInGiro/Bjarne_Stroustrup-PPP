#pragma once
#include "..\GUI\Simple_window.h"
#include <map>
#include "winlist.h"

class Cap21Es15GUI : public Simple_window
{
public:
	Cap21Es15GUI(Point xy, int width, int height, const std::string& titolo, const std::map<std::string, int>& mappa);
	static void cb_precedente(Graph_lib::Address, Graph_lib::Address);
	static void cb_successivo(Graph_lib::Address, Graph_lib::Address);
	void successivo();
	void precedente();
private:
	const std::map<std::string, int>* _mappa;
	Graph_lib::Button bt_prec, bt_succ;
	// widget che da un vettore di stringhe costruisce una lista di Text inpagginate
	winlist* _win{nullptr};
	// le varie pagine sono funzioni grafiche chiamate in successione.
	void quante_parole(const std::string& parola);
	void quale_piu_spesso();
	void quale_piu_lunga();
	void quale_meno_lunga();
	void parole_che_iniziano_per(const char& c);
	void parole_di_lettere_n(const unsigned int& n);
};

