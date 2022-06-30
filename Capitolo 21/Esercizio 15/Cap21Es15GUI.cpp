#include "Cap21Es15GUI.h"

Cap21Es15GUI::Cap21Es15GUI(Point xy, int width, int height, const std::string& titolo, const std::map<std::string, int>& mappa) 
	: Simple_window(xy, width, height, titolo),
	bt_prec(Point{ 10, (y_max() - 50) }, 100, 30, "Precedente", cb_precedente),
	bt_succ(Point{ (x_max() - 110), (y_max() - 50) }, 100, 30, "Successivo", cb_successivo)
{
	_mappa = &mappa;
	Graph_lib::Text msg{ Point{100 , (y_max() / 2)}, "Premi NEXT per continuare..." };
	msg.set_color(Graph_lib::Color::blue);
	msg.set_font_size(18);
	attach(msg);
	// apettiamo che si prema il tasto next
	wait_for_button();
	detach(msg);

	quante_parole("host");
	//wait_for_button();
	
	quale_piu_spesso();
	//wait_for_button();
	
	quale_piu_lunga();
	//wait_for_button();
	
	quale_meno_lunga();
	//wait_for_button();
	
	parole_che_iniziano_per('s');
	//wait_for_button();
	
	parole_di_lettere_n(4);
	//wait_for_button();
}

void Cap21Es15GUI::cb_precedente(Graph_lib::Address own, Graph_lib::Address pw) {
	reinterpret_cast<Cap21Es15GUI*>(pw)->precedente();
}

void Cap21Es15GUI::cb_successivo(Graph_lib::Address own, Graph_lib::Address pw) {
	reinterpret_cast<Cap21Es15GUI*>(pw)->successivo();
}

void Cap21Es15GUI::precedente() {
	if (_win) {
		_win->precedente();
		Fl::redraw();
	}
}

void Cap21Es15GUI::successivo() {
	if (_win) {
		_win->successivo();
		Fl::redraw();
	}
}

void Cap21Es15GUI::quante_parole(const std::string& s) {
	// 1. controlliamo quante volte è presente la parola 'host'
	std::ostringstream osmsg{ "" };
	auto p = _mappa->find(s);
	if (p != _mappa->end())	osmsg << "La parola host si ripete: " << p->second << " volte." << endl;
	else osmsg << "parola host non trovata.\n";
	Graph_lib::Text msg(Point{ 10, (y_max() / 2) }, osmsg.str());
	msg.set_color(Graph_lib::Color::blue);
	msg.set_font_size(18);
	attach(msg);
	wait_for_button();
	detach(msg);
}

void Cap21Es15GUI::quale_piu_spesso() {
	// 2. cerchiamo la parola che si ripete più spesso
	// ci serve sapere prima il numero di occorrenze più alto
	// poi elenchiamo tutte le parole con quel numero
	size_t max{ 0 };
	for (auto p : (*_mappa)) {
		if (p.second > max) max = p.second;
	}
	std::vector<std::string> words;
	std::map<std::string, int>::const_iterator navetta = _mappa->begin();
	while (navetta != _mappa->end()) {
		if ((*navetta).second == max) words.push_back((*navetta).first);
		++navetta;
	}
	std::ostringstream osmsg{ "" };
	osmsg << "\nElenco di tutte le parole più ripetute (" << max << " volte):";
	_win = new winlist(Point{ 10, 50 }, (x_max() - 20), (y_max() - 100), osmsg.str());
	_win->set_dati(words);
	attach(*_win);
	attach(bt_prec);
	attach(bt_succ);
	wait_for_button();
	detach(*_win);
	detach(bt_prec);
	detach(bt_succ);
	delete(_win);
}

void Cap21Es15GUI::quale_piu_lunga() {
	// 3. Cerchiamo la parola più lunga
	// ci serve sapere prima il numero di caratteri più alto
	// poi elenchiamo tutte le parole con quella lunghezza
	size_t max{ 0 };
	for (auto p : (*_mappa)) {
		if (p.first.size() > max) max = p.first.size();
	}
	std::vector<std::string> words;
	std::map<std::string, int>::const_iterator navetta = _mappa->begin();
	while (navetta != _mappa->end()) {
		if ((*navetta).first.size() == max) words.push_back((*navetta).first);
		++navetta;
	}
	std::ostringstream osmsg{ "" };
	osmsg << "\nElenco di tutte le parole più lunghe (" << max << " caratteri):";
	_win = new winlist(Point{ 10, 50 }, (x_max() - 20), (y_max() - 100), osmsg.str());
	_win->set_dati(words);
	attach(*_win);
	attach(bt_prec);
	attach(bt_succ);
	wait_for_button();
	detach(*_win);
	detach(bt_prec);
	detach(bt_succ);
	delete(_win);
}

void Cap21Es15GUI::quale_meno_lunga() {
	// 4. Cerchiamo la parola più corta
	// ci serve sapere prima il numero di caratteri minimo
	// poi elenchiamo tutte le parole con quella lunghezza
	std::map<std::string, int>::const_iterator it_mappa = (*_mappa).begin();
	size_t min{ (*it_mappa).first.size() };
	++it_mappa;
	while (it_mappa != _mappa->end()) {
		if (it_mappa->first.size() < min) min = it_mappa->first.size();
		++it_mappa;
	}
	std::vector<std::string> words;
	std::map<std::string, int>::const_iterator navetta = _mappa->begin();
	while (navetta != _mappa->end()) {
		if ((*navetta).first.size() == min) words.push_back((*navetta).first);
		++navetta;
	}
	std::ostringstream osmsg{ "" };
	osmsg << "Elenco di tutte le parole più corte (" << min << " caratteri):";
	_win = new winlist(Point{ 10, 50 }, (x_max() - 20), (y_max() - 100), osmsg.str());
	_win->set_dati(words);
	attach(*_win);
	attach(bt_prec);
	attach(bt_succ);
	wait_for_button();
	detach(*_win);
	detach(bt_prec);
	detach(bt_succ);
	delete(_win);
}

void Cap21Es15GUI::parole_che_iniziano_per(const char& c) {
	// 5. Lista delle parole che iniziano con 's'
	std::vector<std::string> words;
	std::map<std::string, int>::const_iterator navetta = _mappa->begin();
	while (navetta != _mappa->end()) {
		navetta = find_if(navetta, _mappa->end(), [c](std::pair<std::string, int> v) { return v.first[0] == c; });
		if (navetta != _mappa->end()) {
			words.push_back((*navetta).first);
			++navetta;
		}
	}
	std::ostringstream osmsg{ "" };
	osmsg << "Elenco parole che iniziano con '" << c << "':";
	_win = new winlist(Point{ 10, 50 }, (x_max() - 20), (y_max() - 100), osmsg.str());
	_win->set_dati(words);
	attach(*_win);
	attach(bt_prec);
	attach(bt_succ);
	wait_for_button();
	detach(*_win);
	detach(bt_prec);
	detach(bt_succ);
	delete(_win);
}

void Cap21Es15GUI::parole_di_lettere_n(const unsigned int& n) {
	// Lista delle parole di 4 lettere
	std::vector<std::string> words;
	std::map<std::string, int>::const_iterator navetta = _mappa->begin();
	while (navetta != _mappa->end()) {
		navetta = find_if(navetta, _mappa->end(), [n](std::pair<std::string, int> v) {return (v.first.size() == n); });
		if (navetta != _mappa->end()) {
			//cout << (*navetta).first << endl;
			words.push_back((*navetta).first);
			++navetta;
		}
	}
	std::ostringstream osmsg{ "" };
	osmsg << "Lista delle parole di " << n << " lettere:";
	_win = new winlist(Point{ 10, 50 }, (x_max() - 20), (y_max() - 100), osmsg.str());
	_win->set_dati(words);
	attach(*_win);
	attach(bt_prec);
	attach(bt_succ);
	wait_for_button();
	detach(*_win);
	detach(bt_prec);
	detach(bt_succ);
	delete(_win);
}