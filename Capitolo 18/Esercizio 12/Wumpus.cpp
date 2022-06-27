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
	for (int i = 0; i < _max_rooms; ++i) {
		rooms.push_back(new Room);
		rooms[i]->numero = (i + 1);
	}
	
	while (caverna.size() < _max_rooms) {
		//int nroom = scegli_camera();
		Room* attuale = scegli_camera(); // rooms[nroom];
		if (attuale) {
			collega(attuale);
			caverna.push_back(attuale);
			// il vettore potrebbe essere cambiato, ricerco il puntatore e lo elimino
			del_room(attuale);
			//rooms.erase(rooms.begin() + nroom);
		}
		else break;
	}
	// alla fine delle scelte possibili assicuriamoci di lavorare su un univo vettore
	for (Room* r : rooms) {
		caverna.push_back(r);
		del_room(r);
	}
	// impostiamo le trappole
	std::vector<Room*> temp;
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
	using std::cout;
	using std::endl;
	for (Room* r : caverna) {
		cout << "- ";
		if (r->rear) cout << "Proveniente da cam." << r->rear->numero << ", ";
		cout << "Camera " << r->numero << " che collega: ";
		if (r->left) cout << "Left: " << r->left->numero << ". ";
		if (r->front) cout << "Front: " << r->front->numero << ". ";
		if (r->right) cout << "Right: " << r->right->numero << ". ";
		cout << endl;
		if (r->bat) cout << "...Pipistrelli...\n";
		if (r->pit) cout << "...Pozzi...\n";
		if (r->wump) cout << "...Mostro...\n";
		if (r == hero) cout << "...Qui ci sono io...\n";
	}
}

void Wumpus::play() {
	using std::cout;
	using std::cin;
	using std::endl;
	cout << "Ciao, per una guida scrivi help seguito da invio. Mentre con exit esci dal gioco.";
	while (!(winner || gameover)) {
		std::string comando{ "" };
		stampa_stato();
		std::getline(cin, comando);
		esegui(comando);
		if (winner) cout << "\n\n\nComplimenti ci hai salvato dal mostro!\n\n\n";
		if (gameover) cout << "\n\n\nOps...Non c'è l'hai fatta.\n\n\n";
		if (comando == "exit") {
			cout << "\n\n\nCiao, a presto!\n\n\n";
			break;
		}
	}
}

void Wumpus::stampa_guida() {
	using std::cout;
	using std::endl;
	cout << endl << "Ti trovi in una delle stanze nella caverna che sono collegate fra di loro. Bisogna esplorarle per scovare il mostro e ucciderlo con una freccia." << endl;
	cout << "Puoi scoccare 5 freccie e ogni freccia può arrivare fino a 3 stanze lontano. Ogni freccia sveglia il mostro che si sposta." << endl;
	cout << endl << "i comandi che puoi digitare sono: " << endl;
	cout << "exit per uscire" << endl;
	cout << "move 'numero camera' per spostarti in quella camera se è adiacente" << endl;
	cout << "spara ' numero camera numero camera numero camera per sparare una freccia che passi per le tre camere elencate separate da spazio." << endl;
	cout << "helpti stampa questa guida. Buon divertimento." << endl;
}

void Wumpus::stampa_stato() {
	using std::cout;
	using std::endl;
	cout << "\nTi trovi nella camera " << hero->numero << endl;
	if (hero->rear || hero->left || hero->front || hero->right) cout << "Puoi andare nelle camere: ";
	if (hero->rear) cout << hero->rear->numero << "; ";
	if (hero->left) cout << hero->left->numero << "; ";
	if (hero->front) cout << hero->front->numero << "; ";
	if (hero->right) cout << hero->right->numero << "; ";
	cout << endl;
	if (hero->pit) {
		gameover = true;
		cout << "\n\n\nOps sei caduto in un pozzo senza fondo... Game Over...\n\n\n";
	}
	if (hero->bat) {
		cout << "\n\n\nOps ci sono pipistrelli giganti che ti hanno portato nella stanza ";
		srand(time(0));
		bool trovata = false;
		while (!trovata) {
			int r = rand() % caverna.size();
			if (!(caverna[r]->bat || caverna[r]->pit || caverna[r]->wump || caverna[r]->numero == hero->numero)) {
				trovata = true;
				hero = caverna[r];
			}
		}
		//cout << hero->numero << endl;
		stampa_stato();
	}
	if (hero->wump) {
		gameover = true;
		cout << "\n\n\nOps sei caduto nelle grinfie del mostro... Game Over...\n\n\n";
	}
	if ((hero->rear && hero->rear->wump) || (hero->left && hero->left->wump) || (hero->front && hero->front->wump) || (hero->right && hero->right->wump)) {
		cout << "\nUhm che puzza di mostro che c'è qui...\n";
	}
	if ((hero->rear && hero->rear->bat) || (hero->left && hero->left->bat) || (hero->front && hero->front->bat) || (hero->right && hero->right->bat)) {
		cout << "\nUhm sento pipistrelli nelle vicinanze...\n";
	}
	if ((hero->rear && hero->rear->pit) || (hero->left && hero->left->pit) || (hero->front && hero->front->pit) || (hero->right && hero->right->pit)) {
		cout << "\nUhm del muschio, c'è un pozzo vicino a me...\n";
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
			//stampa_stato();
		}
		else if (hero->left && hero->left->numero == camera) {
			hero = hero->left;
			//stampa_stato();
		}
		else if (hero->front && hero->front->numero == camera) {
			hero = hero->front;
			//stampa_stato();
		}
		else if (hero->right && hero->right->numero == camera) {
			hero = hero->right;
			//stampa_stato();
		}
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
						else std::cout << "\n\nMostro mancato nella camera " << camera << std::endl;
					}
					else if (hero->left && hero->left->numero == camera) {
						if (hero->left->wump) winner = true;
						else std::cout << "\n\nMostro mancato nella camera " << camera << std::endl;
					}
					else if (hero->front && hero->front->numero == camera) {
						if (hero->front->wump) winner = true;
						else std::cout << "\n\nMostro mancato nella camera " << camera << std::endl;
					}
					else if (hero->right && hero->right->numero == camera) {
						if (hero->right->wump) winner = true;
						else std::cout << "\n\nMostro mancato nella camera " << camera << std::endl;
					}
					else std::cout << "\n\nCamera " << camera << " non trovata.\n\n";
				}
			}
			if (!winner) sposta_mostro();
		}
		std::cout << "\nFreccie rimanenti: " << _max_arrow << std::endl;
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
		}
	}
}

Room* Wumpus::scegli_camera(Room* room_da) {
	bool trovata = false;
	Room* room_a{ nullptr };
	std::vector<Room*> temp;
	for (Room* r : rooms) temp.push_back(r);
	while (!trovata && temp.size() > 0) {
		int r = rand() % temp.size();
		room_a = temp[r];
		trovata = true;
		if (room_a->rear && room_a->front && room_a->left && room_a->right) {
			trovata = false;
			//caverna.push_back(room_a);
			//rooms.erase(rooms.begin() + r);
		}
		if (room_da && trovata) {
			if (room_da->numero == room_a->numero) trovata = false;
			if (room_da->rear && room_da->rear->numero == room_a->numero) trovata = false; 
			if (room_da->front && room_da->front->numero == room_a->numero) trovata = false;
			if (room_da->left && room_da->left->numero == room_a->numero) trovata = false;
			if (room_da->right && room_da->right->numero == room_a->numero) trovata = false;
			//if (room_a->rear && room_a->rear->numero == room_da->numero) trovata = false;
			//if (room_a->front && room_a->front->numero == room_da->numero) trovata = false;
			//if (room_a->left && room_a->left->numero == room_da->numero) trovata = false;
			//if (room_a->right && room_a->right->numero == room_da->numero) trovata = false;
		}
		temp.erase(temp.begin() + r);
	}
	if (trovata) return room_a; else return nullptr;
}

void Wumpus::collega(Room* r) {
		if (!r->left) {
			//int nroom = scegli_camera();
			//while ((r->front && r->front->numero == caso->numero) || (r->right && r->right->numero == caso->numero) || (r->rear && r->rear->numero == caso->numero) || r->numero == caso->numero) {
			//	nroom = scegli_camera();
			//	caso = rooms[nroom];
			//}
			Room* caso = scegli_camera(r); // rooms[nroom];
			r->left = caso;
			if (caso) collega_back(r, caso);
			//if (caso->rear && caso->left && caso->front && caso->right) {
				//caverna.push_back(caso);
				//del_room(caso);

				//rooms.erase((rooms.begin() + nroom));
			//}
		}
		if (!r->front) {
			Room* caso = scegli_camera(r); // rooms[nroom];
			r->front = caso;
			if (caso) collega_back(r, caso);
		}
		if (!r->right) {
			Room* caso = scegli_camera(r); // rooms[nroom];
			r->right = caso;
			if (caso) collega_back(r, caso);
		}
}

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