#include "winlist.h"

winlist::winlist(Point xy, int w, int h, const std::string& label) { 
	width = w;
	height = h;
	// stampare la label
	int ypos{ _margin_height + _field_height }; // posizione di partenza (il testo disegna dal basso verso l'alto)
	titolo = new Graph_lib::Text{ Point{30, ypos}, label };
	titolo->set_label(label);
	titolo->set_color(Graph_lib::Color::blue);
	titolo->set_font_size(14);
	// creare le righe vuote
	// numero di righe inseribili nello spazio a disposizione
	// togliamo anche lo spazio per il titolo
	_linee_x_pagina = (height - 30) / (_field_height + _margin_height);
	_pagine = 0;
	_pagina_corrente = 0;
	_riga_start = 0;
	_riga_stop = 0;
	for (unsigned int i = 0; i < _linee_x_pagina; ++i) {
		ypos += (_margin_height + _field_height);
		Graph_lib::Text* t = new Graph_lib::Text(Point{ 0, ypos }, "");
		t->set_color(Graph_lib::Color::blue);
		t->set_font_size(12);
		linee.push_back(t);
	}
}

void winlist::precedente() {
	if (_pagina_corrente > 0) {
		--_pagina_corrente;
		// riempo le righe precedenti
		_riga_start -= _linee_x_pagina;
		_riga_stop = _riga_start + _linee_x_pagina;
		std::vector<Graph_lib::Text*>::iterator lp = linee.begin();
		for (unsigned int i = _riga_start; i < _riga_stop; ++i) {
			(*lp)->set_label(dati[i]);
			++lp;
		}
	}
}

void winlist::successivo() {
	// quando premi il bottono _pagine si è modificato !?!?
	if (_pagina_corrente < _pagine) {
		++_pagina_corrente;
		// riempo le righe con la prossima pagina
		_riga_start += _linee_x_pagina;
		_riga_stop = ((_riga_start + _linee_x_pagina) > dati.size()) ? dati.size() : (_riga_start + _linee_x_pagina);
		std::vector<Graph_lib::Text*>::iterator lp = linee.begin();
		for (unsigned int i = _riga_start; i < _riga_stop; ++i) {
			(*lp)->set_label(dati[i]);
			++lp;
		}
		// se ci sono altre righe della pagina precedente vanno azzerate
		while (lp != linee.end()) { (*lp)->set_label(""); lp++; }
	}
}

void winlist::set_dati(std::vector<std::string>& v) {
	// azzeriamo i dati attuali
	dati.clear();
	// riempiamo i dati
	dati.swap(v);
	if (dati.size() == 0) _pagine = 0; else _pagine = (dati.size() / _linee_x_pagina);
	_pagina_corrente = 0;
	_riga_start = 0;
	_riga_stop = (dati.size() < _linee_x_pagina) ? dati.size() : _linee_x_pagina;
	// riempiamo la pagina iniziale
	std::vector<Graph_lib::Text*>::iterator lp = linee.begin();
	for (unsigned int i = 0; i < _riga_stop; ++i) {
		(*lp)->set_label(dati[i]);
		(*lp)->set_color(Graph_lib::Color::blue);
		(*lp)->set_font_size(12);
		++lp;
	}
}

void winlist::draw_lines() const {
	titolo->draw();
	for (unsigned int i = 0; i < linee.size(); ++i) {
		linee[i]->draw();
	}
}

void winlist::move(int dx, int dy) {
	titolo->move(dx, dy);
	for (unsigned int i = 0; i < linee.size(); ++i) {
		linee[i]->move(dx, dy);
	}
}

winlist::~winlist() {
	delete titolo;
	dati.clear();
	linee.clear();
	Shape::~Shape();
}