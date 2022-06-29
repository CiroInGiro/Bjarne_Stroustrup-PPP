#include "Wumpus.h"

Wumpus::Wumpus() {
	_max_rooms = 25;
	_max_wump = 1;
	_max_pit = 3;
	_max_bat = 3;
	_max_arrow = 5;
	_arrow_distance = 3; // 3 stanze
	winner = false;
	gameover = false;
	srand(time(0));
	// gestione grafica
	guigame = nullptr;
	_guimode = false;
	_in = &std::cin;
	_out = &std::cout;
	for (int i = 0; i < _max_rooms; ++i) {
		rooms.push_back(new Room);
		rooms[i]->numero = (i + 1);
	}

	// scegliamo la prima camera mai utilizzata
	Room* attuale = scegli_camera(nullptr);
	// le camere collegate finiscono nel vettore che disegna la caverna
	//caverna.push_back(attuale);
	// togliamo dalle disponibili la camera collegata
	//del_room(attuale);
	// colleghiamola ad altre camere che non hanno collegamenti ad altre camere, sempre che ne rimangono abbastanza
	collega(attuale);

	/*
	int conta{ 0 };
	while (conta < _max_rooms) {
		Room* attuale = scegli_camera();
		if (attuale) {
			++conta;
			collega(attuale);
			//caverna.push_back(attuale);
			// il vettore potrebbe essere cambiato, ricerco il puntatore e lo elimino
			//del_room(attuale);
		}
		else break;
	}
	*/

	// loop per finire di collegare tutte lecamere parzialmente collegate le une con le altre
	// versione 2
	/*
	int ctrl{ 0 };
	while (rooms.size() > 0 && ctrl != rooms.size()) {
		ctrl = rooms.size();
		for (Room* r : rooms) {
			if (r->front && r->right && r->rear && r->left) {
				caverna.push_back(r);
				del_room(r);
				break;
			}
			else if (r->front || r->right || r->rear || r->left) collega(r);
		}
	}
	// alla fine delle scelte possibili assicuriamoci di lavorare su un univo vettore
	for (Room* r : rooms) {
		if (r->front || r->right || r->rear || r->left) {
			caverna.push_back(r);
			//del_room(r);
			collega(r);
		}
	}
	rooms.clear();
	*/

	// versione 3
	int ctrl{ 0 };
	int cicli{ 0 }; // variabile per debug
	while (rooms.size() > 0 && ctrl != rooms.size()) {
		ctrl = rooms.size();
		++cicli;
		for (unsigned int indice = 0; indice < rooms.size(); ++indice) {
			Room* r = rooms[indice];
			if (r->front || r->right || r->rear || r->left) {
				collega(r);
				caverna.push_back(r);
				del_room(r);
			}
		}
	}
//	rooms.clear();

	// impostiamo le trappole
	using std::vector;
	vector<Room*> temp;
	for (Room* r : caverna) temp.push_back(r);
	// i pozzi
	int pits = _max_pit;
	srand(time(0));
	while (pits > 0 && temp.size() > 0) {
		int r = rand() % temp.size();
		Room* p = temp[r];
		p->pit = true;
		--pits;
		temp.erase(temp.begin() + r);
	}
	// i pipistrelli
	int bats = _max_bat;
	srand(time(0));
	while (bats > 0 && temp.size() > 0) {
		int r = rand() % temp.size();
		Room* b = temp[r];
		b->bat = true;
		--bats;
		temp.erase(temp.begin() + r);
	}
	// il mostro
	srand(time(0));
	int r = rand() % temp.size();
	wump = temp[r];
	wump->wump = true;
	temp.erase(temp.begin() + r);
	// la nostra stanza di partenza
	srand(time(0));
	r = rand() % temp.size();
	hero = temp[r];
	temp.clear();
}

Wumpus::~Wumpus() {
	for (Room* r : caverna) delete r;
	wump = nullptr;
	hero = nullptr;
	bat = nullptr;
}

void Wumpus::debug() {
	if (_guimode) {
		if (!guigame) {
			guigame = new  WumpusGUI(Point{ 0,0 }, 800, 800, "Wumpus 2.0");
			guigame->set_hero(hero);
		}
		guigame->debug();
		while (!guigame->get_in_sense()) Fl::wait();
		guigame->reset_in_sense();
		return;
	}
	using std::endl;
	*_out << endl << "Debug rooms: " << endl;
	for (Room* r : caverna) {
		*_out << "- ";
		if (r->rear) *_out << "Proveniente da cam." << r->rear->numero << ", ";
		*_out << "Camera " << r->numero << " che collega: ";
		if (r->left) *_out << "Left: " << r->left->numero << ". ";
		if (r->front) *_out << "Front: " << r->front->numero << ". ";
		if (r->right) *_out << "Right: " << r->right->numero << ". ";
		*_out << endl;
		if (r->bat) *_out << "...Pipistrelli...\n";
		if (r->pit) *_out << "...Pozzi...\n";
		if (r->wump) *_out << "...Mostro...\n";
		if (r == hero) *_out << "...Qui ci sono io...\n";
	}
}

void Wumpus::guidebug() { _guimode = true;  debug(); }

void Wumpus::play() {
	play(false, std::cin, std::cout);
}

void Wumpus::play(const bool guimode = false, std::istream& in = std::cin, std::ostream& out = std::cout) {
	_in = &in;
	_out = &out;
	using std::endl;
	_guimode = guimode;
	if (!_guimode && guigame) { delete guigame; guigame = nullptr; }
	*_out << "Ciao, per una guida scrivi help seguito da invio. Mentre con exit esci dal gioco.";
	if (_guimode) *_out << "\nPremi il tasto VAI per continuare...";
	while (!(winner || gameover)) {
		std::string comando{ "" };
		//stampa_stato();
		// se in modalità grafica aggiorno la maschera
		if (_guimode) {
			guigame->refresh();
			while (!guigame->get_in_sense()) Fl::wait();
			guigame->reset_in_sense();
			//return;
		}
		std::getline(*_in, comando);
		_in->clear();
		if (comando == "exit") {
			*_out << "\n\n\nCiao, a presto!\n\n\n";
			break;
		}
		else if (comando == "") stampa_stato();
		else esegui(comando);
		//stampa_stato();
	}
	if (winner || gameover) {
		guigame->refresh();
		while (!guigame->get_in_sense()) Fl::wait();
	}
}

void Wumpus::guiplay() {
	// imposto l'ambiente grafico
	guigame = new  WumpusGUI(Point{ 0,0 }, 800, 800, "Wumpus 2.0");
	guigame->set_hero(hero);
	// parte il gioco
	play(true, guigame->cin(), guigame->cout());
}

void Wumpus::stampa_guida() {
	using std::endl;
	*_out << endl << "Ti trovi in una delle stanze nella caverna che sono collegate fra di loro. Bisogna esplorarle per scovare il mostro e ucciderlo con una freccia." << endl;
	*_out << "Puoi scoccare 5 freccie e ogni freccia può arrivare fino a 3 stanze lontano. Ogni freccia sveglia il mostro che si sposta." << endl;
	*_out << endl << "i comandi che puoi digitare sono: " << endl;
	*_out << "exit per uscire" << endl;
	*_out << "move 'numero camera' per spostarti in quella camera se è adiacente" << endl;
	*_out << "spara 'numero camera numero camera numero camera per sparare una freccia che passi per le tre camere elencate separate da spazio." << endl;
	*_out << "marca 'numero camera' seguito da uno tra 'pit' o 'bat' o 'wump' per marcare le stanze vicino con questi segni. (Solo in GUI)" << endl;
	*_out << "help ti stampa questa guida. Buon divertimento." << endl;
}

void Wumpus::stampa_stato() {
	using std::endl;
	if (hero->pit) {
		gameover = true;
		*_out << "\n\n\nOps sei caduto in un pozzo senza fondo... Game Over...\n\n\n";
	}
	else if (hero->bat) {
		*_out << "\n\n\nOps ci sono pipistrelli giganti che ti hanno portato nella stanza ";
		srand(time(0));
		bool trovata = false;
		while (!trovata) {
			int r = rand() % caverna.size();
			if (!(caverna[r]->bat || caverna[r]->pit || caverna[r]->wump || caverna[r]->numero == hero->numero)) {
				trovata = true;
				hero = caverna[r];
				guigame->set_hero(hero);
			}
		}
		//stampa_stato();
	}
	else if (hero->wump) {
		gameover = true;
		*_out << "\n\n\nOps sei caduto nelle grinfie del mostro... Game Over...\n\n\n";
	}
	if (!(gameover || winner)) {
		*_out << "\nTi trovi nella camera " << hero->numero << endl;
		if (hero->rear || hero->left || hero->front || hero->right) *_out << "Puoi andare nelle camere: ";
		if (hero->rear) *_out << hero->rear->numero << "; ";
		if (hero->left) *_out << hero->left->numero << "; ";
		if (hero->front) *_out << hero->front->numero << "; ";
		if (hero->right) *_out << hero->right->numero << "; ";
		*_out << endl;
		if ((hero->rear && hero->rear->wump) || (hero->left && hero->left->wump) || (hero->front && hero->front->wump) || (hero->right && hero->right->wump)) {
			*_out << "\nUhm che puzza di mostro che c'è qui...\n";
		}
		if ((hero->rear && hero->rear->bat) || (hero->left && hero->left->bat) || (hero->front && hero->front->bat) || (hero->right && hero->right->bat)) {
			*_out << "\nUhm sento pipistrelli nelle vicinanze...\n";
		}
		if ((hero->rear && hero->rear->pit) || (hero->left && hero->left->pit) || (hero->front && hero->front->pit) || (hero->right && hero->right->pit)) {
			*_out << "\nUhm del muschio, c'è un pozzo vicino a me...\n";
		}
	}
}

void Wumpus::esegui(const std::string& c) {
	std::istringstream iss;
	iss.str(c);
	if (c == "help") {
		stampa_guida();
	}
	std::string parola;
	iss >> parola;
	if (parola == "move") {
		int camera{ 0 };
		iss >> camera;
		if (hero->rear && hero->rear->numero == camera) {
			hero = hero->rear;
			if (_guimode) guigame->move_rear();
		}
		else if (hero->left && hero->left->numero == camera) {
			hero = hero->left;
			if (_guimode) guigame->move_left();
		}
		else if (hero->front && hero->front->numero == camera) {
			hero = hero->front;
			if (_guimode) guigame->move_front();
		}
		else if (hero->right && hero->right->numero == camera) {
			hero = hero->right;
			if (_guimode) guigame->move_right();
		}
		stampa_stato();
	}
	if (parola == "spara") {
		int camera{ 0 };
		int distanza{ _arrow_distance };
		if (_max_arrow > 0) {
			--_max_arrow;
			while (iss >> camera) {
				if (distanza > 0) {
					--distanza;
					if (hero->rear && hero->rear->numero == camera) {
						if (hero->rear->wump) winner = true; 
						else *_out << "\n\nMostro mancato nella camera " << camera << std::endl;
					}
					else if (hero->left && hero->left->numero == camera) {
						if (hero->left->wump) winner = true;
						else *_out << "\n\nMostro mancato nella camera " << camera << std::endl;
					}
					else if (hero->front && hero->front->numero == camera) {
						if (hero->front->wump) winner = true;
						else *_out << "\n\nMostro mancato nella camera " << camera << std::endl;
					}
					else if (hero->right && hero->right->numero == camera) {
						if (hero->right->wump) winner = true;
						else *_out << "\n\nMostro mancato nella camera " << camera << std::endl;
					}
					else *_out << "\n\nCamera " << camera << " non trovata.\n\n";
				}
			}
			if (!winner) sposta_mostro();
		}
		if (winner) *_out << "\nComplimenti hai sconfitto il mostro !!!"; else *_out << "\nFreccie rimanenti: " << _max_arrow << std::endl;
	}
	if (parola == "marca" && _guimode) {
		int camera{ 0 };
		std::string cosa{ "" };
		iss >> camera;
		iss >> cosa;

		if (hero->rear && hero->rear->numero == camera) {
			if (cosa == "pit") guigame->mark_pit(hero->rear);
			if (cosa == "bat") guigame->mark_bat(hero->rear);
			if (cosa == "wump") guigame->mark_wump(hero->rear);
		}
		else if (hero->left && hero->left->numero == camera) {
			if (cosa == "pit") guigame->mark_pit(hero->left);
			if (cosa == "bat") guigame->mark_bat(hero->left);
			if (cosa == "wump") guigame->mark_wump(hero->left);
		}
		else if (hero->front && hero->front->numero == camera) {
			if (cosa == "pit") guigame->mark_pit(hero->front);
			if (cosa == "bat") guigame->mark_bat(hero->front);
			if (cosa == "wump") guigame->mark_wump(hero->front);
		}
		else if (hero->right && hero->right->numero == camera) {
			if (cosa == "pit") guigame->mark_pit(hero->right);
			if (cosa == "bat") guigame->mark_bat(hero->right);
			if (cosa == "wump") guigame->mark_wump(hero->right);
		}
		else if (hero->numero == camera) {
			if (cosa == "pit") guigame->mark_pit(hero);
			if (cosa == "bat") guigame->mark_bat(hero);
			if (cosa == "wump") guigame->mark_wump(hero);
		}
		stampa_stato();
	}
}

void Wumpus::sposta_mostro() {
	srand(time(0));
	bool trovata = false;
	while (!trovata) {
		int r = rand() % 3; // le direzioni possibili
		Room* ro{ nullptr };
		trovata = true;
		switch (r) {
		case 0:
			ro = wump->rear;
			break;
		case 1:
			ro = wump->left;
			break;
		case 2:
			ro = wump->front;
			break;
		case 3:
			ro = wump->right;
			break;
		}
		if (!ro) trovata = false;
		else if (ro->numero == hero->numero) gameover = true;
		else {
			wump->wump = false;
			ro->wump = true;
			wump = ro;
			if (_guimode) guigame->set_wump(wump);
		}
	}
}

// scegliamo una camera mai utilizzata
Room* Wumpus::scegli_camera(Room* room_da) {
	bool trovata = false;
	Room* room_a{ nullptr };
	vector<Room*> temp;
	for (Room* r : rooms) temp.push_back(r);
	while (!trovata && temp.size() > 0) {
		int r = rand() % temp.size();
		room_a = temp[r];
		trovata = true;

		if (room_a->rear || room_a->front || room_a->left || room_a->right) {
			trovata = false;
		}

		/*
		// queste 2 condizioni sono ora inutili
		if (room_a->rear && room_a->front && room_a->left && room_a->right) {
			trovata = false;
			// se già collegata potrei cancellarla qui dal vettore delle camere rooms
		}*/
		
		if (room_da && trovata) {
			if (room_da->numero == room_a->numero) trovata = false;
			if (room_da->rear && room_da->rear->numero == room_a->numero) trovata = false; 
			if (room_da->front && room_da->front->numero == room_a->numero) trovata = false;
			if (room_da->left && room_da->left->numero == room_a->numero) trovata = false;
			if (room_da->right && room_da->right->numero == room_a->numero) trovata = false;
		}
		temp.erase(temp.begin() + r);
	}
	if (trovata) return room_a; else return nullptr;
}

void Wumpus::collega(Room* r) {
	// collego le camere considerando che sono messe in maniera ordinate come in una griglia e tutte rivolte nella stessa direzione.
		if (!r->left) {
			collega_left(r);
			/*
			Room* caso = scegli_camera(r);
			r->left = caso;
			if (caso) collega_back(r, caso);
			*/
		}
		if (!r->front) {
			collega_front(r);
			/*
			Room* caso = scegli_camera(r);
			r->front = caso;
			if (caso) collega_back(r, caso);
			*/
		}
		if (!r->right) {
			collega_right(r);
			/*
			Room* caso = scegli_camera(r);
			r->right = caso;
			if (caso) collega_back(r, caso);
			*/
		}
		if (!r->rear) {
			collega_rear(r);
		}
}

void Wumpus::collega_left(Room* r) {
	bool trovata{ false };
	// controllo se già c'è una camera presente
	// da rear
	Room* caso = r->rear;
	if (caso) {
		caso = caso->left;
		if (caso) {
			caso = caso->front;
			// trovata già esistente
			if (caso) trovata = true;
		}
	}
	// da front
	if (!trovata) {
		caso = r->front;
		if (caso) {
			caso = caso->left;
			if (caso) {
				caso = caso->rear;
				if (caso) trovata = true;
			}
		}
	}
	if (!trovata) caso = scegli_camera(r);
	r->left = caso;
	if (caso) {
		caso->right = r;
		//caverna.push_back(caso);
		//del_room(caso);
	}
}

void Wumpus::collega_front(Room* r) {
	bool trovata{ false };
	// controllo se già c'è una camera presente
	// da left
	Room* caso = r->left;
	if (caso) {
		caso = caso->front;
		if (caso) {
			caso = caso->right;
			// trovata già esistente
			if (caso) trovata = true;
		}
	}
	// da right
	if (!trovata) {
		caso = r->right;
		if (caso) {
			caso = caso->front;
			if (caso) {
				caso = caso->left;
				if (caso) trovata = true;
			}
		}
	}
	if (!trovata) caso = scegli_camera(r);
	r->front = caso;
	if (caso) {
		caso->rear = r;
		//caverna.push_back(caso);
		//del_room(caso);
	}
}

void Wumpus::collega_right(Room* r) {
	bool trovata{ false };
	// controllo se già c'è una camera presente
	// da front
	Room* caso = r->front;
	if (caso) {
		caso = caso->right;
		if (caso) {
			caso = caso->rear;
			// trovata già esistente
			if (caso) trovata = true;
		}
	}
	// da rear
	if (!trovata) {
		caso = r->rear;
		if (caso) {
			caso = caso->right;
			if (caso) {
				caso = caso->front;
				if (caso) trovata = true;
			}
		}
	}
	if (!trovata) caso = scegli_camera(r);
	r->right = caso;
	if (caso) {
		caso->left = r;
		//caverna.push_back(caso);
		//del_room(caso);
	}
}

void Wumpus::collega_rear(Room* r) {
	bool trovata{ false };
	// controllo se già c'è una camera presente
	// da right
	Room* caso = r->right;
	if (caso) {
		caso = caso->rear;
		if (caso) {
			caso = caso->left;
			// trovata già esistente
			if (caso) trovata = true;
		}
	}
	// da left
	if (!trovata) {
		caso = r->left;
		if (caso) {
			caso = caso->rear;
			if (caso) {
				caso = caso->right;
				if (caso) trovata = true;
			}
		}
	}
	if (!trovata) caso = scegli_camera(r);
	r->rear = caso;
	if (caso) {
		caso->front = r;
		//caverna.push_back(caso);
		//del_room(caso);
	}
}

/*
void Wumpus::collega_back(Room* r, Room* l) {
	bool collegato = false;
	if (!l->rear && !collegato) {
		l->rear = r;
		collegato = true;
	}
	if (!l->left && !collegato) {
		l->left = r;
		collegato = true;
	}
	if (!l->front && !collegato) {
		l->front = r;
		collegato = true;
	}
	if (!l->right && !collegato) {
		l->right = r;
		collegato = true;
	}
	if (l->rear && l->front && l->left && l->right) del_room(l);
}
*/

void Wumpus::del_room(Room* r) {
	int i{ 0 };
	while (i < rooms.size()) {
		if (rooms[i] == r) {
			rooms.erase(rooms.begin() + i);
			break;
		}
		++i;
	}
}