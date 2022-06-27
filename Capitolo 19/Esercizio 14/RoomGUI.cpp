#include "RoomGUI.h"

// Al posto del minatore serve un esploratore che ricorda le camere create e le colleghi in un secondo momento come avviene per la creazione della caverna.
Minatore::Minatore(vector<RoomGUI*> *v, Minatore* p, Room* r, int x, int y, int margine, int dimensione) {
	provenienza = p;
	_stanza = r;
	_x = x;
	_y = y;
	_margine = margine;
	_dimensione = dimensione;
	roomgui = new RoomGUI(r, x, y, dimensione);
	v->push_back(roomgui);
}

// il minatore andava bene prima quando seguiva le camere collegate che non formavano un reticolo, adesso incatta in loop infiniti
RoomGUI* Minatore::vai(vector<RoomGUI*>* v) {
	if (_stanza->front) {
		// se c'è una stanza frontale
		if (!provenienza || (provenienza && _stanza->front != provenienza->_stanza)) {
			// se non c'è una provenienza o questa è diversa allora
			// costruiamo il prossimo minatore che andrà avanti lui, quando costruito significa cha da quel punto siamo a posto e continuiamo noi
			int newx = _x + _margine + _dimensione;
			int newy = _y;
			prossimo = new Minatore(v, this, _stanza->front, newx, newy, _margine, _dimensione);
			roomgui->front = prossimo->vai(v);
			delete prossimo;
			prossimo = nullptr;
		}
		else if (provenienza) {
			// in alternativa abbiamo trovata la stanza da cui proveniamo
			roomgui->front = provenienza->roomgui;
		}
	}

	if (_stanza->right) {
		if (!provenienza || (provenienza && _stanza->right != provenienza->_stanza)) {
			int newx = _x;
			int newy = _y + _margine + _dimensione;
			prossimo = new Minatore(v, this, _stanza->right, newx, newy, _margine, _dimensione);
			roomgui->right = prossimo->vai(v);
			delete prossimo;
			prossimo = nullptr;
		}
		else if (provenienza) { roomgui->right = provenienza->roomgui; }
	}

	if (_stanza->rear) {
		if (!provenienza || (provenienza && _stanza->rear != provenienza->_stanza)) {
			int newx = _x - _margine - _dimensione;
				int newy = _y;
				prossimo = new Minatore(v, this, _stanza->rear, newx, newy, _margine, _dimensione);
				roomgui->rear = prossimo->vai(v);
				delete prossimo;
				prossimo = nullptr;
		}
		else if (provenienza) { roomgui->rear = provenienza->roomgui; }
	}

	if (_stanza->left) {
		if (!provenienza || (provenienza && _stanza->left != provenienza->_stanza)) {
			int newx = _x;
			int newy = _y - _margine - _dimensione;
			prossimo = new Minatore(v, this, _stanza->left, newx, newy, _margine, _dimensione);
			roomgui->left = prossimo->vai(v);
			delete prossimo;
			prossimo = nullptr;
		}
		else if (provenienza) { roomgui->left = provenienza->roomgui; }
	}

	return roomgui;
}

Explorer::Explorer(Room* stanza, int x, int y, int margine, int dimensione) {
	_stanza_partenza = stanza;
	_x = x;
	_y = y;
	_margine = margine;
	_dimensione = dimensione;
}

RoomGUI* Explorer::vai(vector<RoomGUI*>* v) {
	// Esploro la mappa Room partendo dalla principale che metto in memoria
	// prelevo Room dalla memoria, gli creo RoomGUI e la collego
	// quelle collegate le sposto in v, le nuove che creo adiacenti le metto in memoria per controllarle successivamente
	RoomGUI* retVal = new RoomGUI(_stanza_partenza, _x, _y, _dimensione);
	RoomGUI* rgui;
	// memoria è il nostro vettore temporaneo dove ci vanno le stanze ancora da esplorare
	// inizialmente troviamo solo la stanza di partenza che una volta esplorata viene spostata nel vettore v
	// intando durante l'esplorazione dei 4 collegamenti si sono create altre stanza nel vettore memoria da esplorare e finchè non resterà vuoto viene riletto
	memoria.push_back(retVal);
	while (!memoria.empty()) {
		// con push_back() e pop_back() di vector modifichiamo le camenre nel vettore da esplorare
		rgui = memoria.front();
		v->push_back(rgui);
		memoria.erase(memoria.begin());
		// collega rg creando le stanze attorno a se
		// le stanze create vanno ricordate in memoria
		// rg va spostata in v
		//if (!(rgui->front && rgui->right && rgui->rear && rgui->left)) {
		collega(rgui);
		//}
	}
	return retVal;
}

void Explorer::collega(RoomGUI* rg) {
	Room* r = rg->get_stanza();
	if (r->front) {
		if (!rg->front) collega_front(rg);
	}
	if (r->right) {
		if (!rg->right) collega_right(rg);
	}
	if (r->rear) {
		if (!rg->rear) collega_rear(rg);
	}
	if (r->left) {
		if (!rg->left) collega_left(rg);
	}
}

void Explorer::collega_front(RoomGUI* rg) {
	Room* r = rg->get_stanza();
	bool trovata{ false };
	RoomGUI* caso{ nullptr };
	// cerco se già presente
	// da sinistra
	caso = rg->left;
	if (caso) {
		caso = caso->front;
		if (caso) {
			caso = caso->right;
			if (caso) trovata = true;
		}
	}
	// da destra
	if (!trovata) {
		caso = rg->right;
		if (caso) {
			caso = caso->front;
			if (caso) {
				caso = caso->left;
				if (caso) trovata = true;
			}
		}
	}
	// la creo altrimenti
	if (!trovata) {
		caso = new RoomGUI(r->front, (rg->get_x() + _dimensione + _margine), rg->get_y(), _dimensione);
		memoria.push_back(caso); // solo le nuove sono da collegare altrimenti significa che già sono in memoria
	}
	rg->front = caso;
	rg->front->rear = rg;
}

void Explorer::collega_right(RoomGUI* rg) {
	Room* r = rg->get_stanza();
	bool trovata{ false };
	RoomGUI* caso{ nullptr };
	// cerco se già presente
	// da frontale
	caso = rg->front;
	if (caso) {
		caso = caso->right;
		if (caso) {
			caso = caso->rear;
			if (caso) trovata = true;
		}
	}
	// da dietro
	if (!trovata) {
		caso = rg->rear;
		if (caso) {
			caso = caso->right;
			if (caso) {
				caso = caso->front;
				if (caso) trovata = true;
			}
		}
	}
	// la creo altrimenti
	if (!trovata) {
		caso = new RoomGUI(r->right, rg->get_x(), (rg->get_y() + _dimensione + _margine), _dimensione);
		memoria.push_back(caso);
	}
	rg->right = caso;
	rg->right->left = rg;
}

void Explorer::collega_rear(RoomGUI* rg) {
	Room* r = rg->get_stanza();
	bool trovata{ false };
	RoomGUI* caso{ nullptr };
	// cerco se già presente
	// da sinistra
	caso = rg->left;
	if (caso) {
		caso = caso->rear;
		if (caso) {
			caso = caso->right;
			if (caso) trovata = true;
		}
	}
	// da destra
	if (!trovata) {
		caso = rg->right;
		if (caso) {
			caso = caso->rear;
			if (caso) {
				caso = caso->left;
				if (caso) trovata = true;
			}
		}
	}
	// la creo altrimenti
	if (!trovata) {
		caso = new RoomGUI(r->rear, (rg->get_x() - _dimensione - _margine), rg->get_y(), _dimensione);
		memoria.push_back(caso);
	}
	rg->rear = caso;
	rg->rear->front = rg;
}

void Explorer::collega_left(RoomGUI* rg) {
	Room* r = rg->get_stanza();
	bool trovata{ false };
	RoomGUI* caso{ nullptr };
	// cerco se già presente
	// da rear
	caso = rg->rear;
	if (caso) {
		caso = caso->left;
		if (caso) {
			caso = caso->front;
			if (caso) trovata = true;
		}
	}
	// da front
	if (!trovata) {
		caso = rg->front;
		if (caso) {
			caso = caso->left;
			if (caso) {
				caso = caso->rear;
				if (caso) trovata = true;
			}
		}
	}
	// la creo altrimenti
	if (!trovata) {
		caso = new RoomGUI(r->left, rg->get_x(), (rg->get_y() - _dimensione - _margine), _dimensione);
		memoria.push_back(caso);
	}
	rg->left = caso;
	rg->left->right = rg;
}

RoomGUI::RoomGUI(Room* r, int x, int y, int dimensione) {
	_stanza = r;
	visitata = false;
	marcata = false;
	hero = false;
	pit = false;
	bat = false;
	wump = false;
	markpit = false;
	markbat = false;
	markwump = false;
	numero = 0;
	rear = nullptr;
	front = nullptr;
	left = nullptr;
	right = nullptr;
	_x = x;
	_y = y;
	_dimensione = dimensione;
	caverna = new Graph_lib::TBox(Point{ _x, _y }, std::to_string(_stanza->numero));
	if (_stanza->pit) { caverna->add_line("PIT"); }
	if (_stanza->bat) { caverna->add_line("BAT"); }
	if (_stanza->wump) { caverna->add_line("WUMP"); }
	caverna->set_color(Graph_lib::Color::white);
	caverna->set_height(_dimensione);
	caverna->set_width(_dimensione);
}

void RoomGUI::set_visitata(bool v) {
	visitata = v; 
	formatta();
}

bool RoomGUI::get_visitata() const { return visitata; }

Room* RoomGUI::get_stanza() const { return _stanza; }

void RoomGUI::toggle_hero() {
	// inverte lo stato di hero
	hero = !hero;
	if (hero) visitata = true;
	formatta();
}

void RoomGUI::toggle_pit() {
	pit = !pit;
	formatta();
}

void RoomGUI::toggle_bat() {
	bat = !bat;
	formatta();
}

void RoomGUI::toggle_wump() {
	wump = !wump;
	formatta();
}

void RoomGUI::toggle_markpit() {
	markpit = !markpit;
	formatta();
}

void RoomGUI::toggle_markbat() {
	markbat = !markbat;
	formatta();
}

void RoomGUI::toggle_markwump() {
	markwump = !markwump;
	formatta();
}

void RoomGUI::set_wump(bool w) {
	wump = w;
	formatta();
}

bool RoomGUI::get_wump() { return wump; }

void RoomGUI::formatta() {
	// ci sono 3 colori
	// black quelle non visitate
	// verdi quelle visitate
	// blue quella occupata dall'eroe
	if (markpit || markbat || markwump) marcata = true; else marcata = false;
	
	Graph_lib::Color nuovo{ Graph_lib::Color::white };
	caverna->clear_line();
	
	if (visitata) {
		nuovo = Graph_lib::Color::green;
		if (_stanza->pit) { caverna->add_line("PIT"); }
		if (_stanza->bat) { caverna->add_line("BAT"); }
		if (_stanza->wump) { caverna->add_line("WUMP"); }
	} else if (marcata) nuovo = Graph_lib::Color::black;

	if (hero) {
		nuovo = Graph_lib::Color::blue;
		caverna->add_line("HERO");
	}
	
	if (markpit) caverna->add_line("? PIT ?");
	if (markbat) caverna->add_line("? BAT ?");
	if (markwump) caverna->add_line("? WUMP ?");

	caverna->set_height(_dimensione);
	caverna->set_width(_dimensione);
	caverna->set_color(nuovo);
}

int RoomGUI::get_x() const { return _x; }

int RoomGUI::get_y() const { return _y; }

Graph_lib::TBox* RoomGUI::getgui() { return caverna; }