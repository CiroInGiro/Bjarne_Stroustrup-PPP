#include "WinLinguaggi.h"

WinLinguaggi::WinLinguaggi(Point posizione, int width, int height, const std::string& titolo) : Window(posizione, width, height, titolo) {
	
}

WinLinguaggi::~WinLinguaggi() { 
	auto nuvola = _grafi.begin();
	while (nuvola != _grafi.end()) {
		detach(*(*nuvola));
		++nuvola;
	}
	_grafi.clear(); // dovrebbe chiamare i distruttori di ogni elemento.
	_occorrenze.clear();
}

void WinLinguaggi::add(RecordGrafo& rg) {
	// qui aggiungiamo un grafo e poi li riposizioniamo tutti e creiamo i collegamenti
	Grafo* newGrafo = new Grafo(Point{ 0,0 }, _diametro, rg); // passo direttamente il record per evitare copie dei singoli dati in memoria
	// imposta colore
	_grafi.insert(newGrafo); // sempre meglio usare un set che ordina al momento
	attach(*newGrafo);
}

Point WinLinguaggi::find_pos(const std::string& linguaggio) {
	auto nave = _grafi.begin();
	while (nave != _grafi.end()) {
		if (linguaggio == (*nave)->getRecord().getLinguaggio()) return (*nave)->getPos();
		++nave;
	}
	return Point{ 0, 0 };
}

void WinLinguaggi::collega(Point start, Point end) {
	// start ed end sono la posizione dei grafi da collegare, facciamo i collegamenti sulla circonferenza piuttosto.

	Graph_lib::Arrow* ar = new Graph_lib::Arrow(Point{ (start.x + (_diametro / 2)), start.y }, Point{ (end.x - (_diametro / 2)), end.y});
	ar->set_color(Graph_lib::Color::dark_magenta);
	attach(*ar);
	_collegamenti.push_back(ar);
}

void WinLinguaggi::disponi() {
	// nel caso aggiungiamo qualcosa dopo e dobbiamo ridisporre:
	_occorrenze.clear();
	if (_collegamenti.size() > 0) {
		for (Graph_lib::Arrow* a : _collegamenti) {
			detach(*a);
			delete a;
		}
		_collegamenti.clear();
	}
	if (_etichette.size() > 0) {
		for (Graph_lib::Text* t : _etichette) {
			detach(*t);
			delete t;
		}
		_etichette.clear();
	}

	// cordinate x e y
	int pos_x{ 0 }, pos_y{ 0 };
	
	// gestione dello spazio
	int notches_x{ 0 };
	int notches_y{ 0 };

	// creiamo la mappa delle occorrenze
	auto nuvola = _grafi.begin();
	while (nuvola != _grafi.end()) {
		_occorrenze[(*nuvola)->getRecord().getAnno()]++;
		if (notches_y < _occorrenze[(*nuvola)->getRecord().getAnno()]) notches_y = _occorrenze[(*nuvola)->getRecord().getAnno()];
		++nuvola;
	}

	notches_x = _occorrenze.size() + 1;
	int step_x = (x_max() / notches_x);
	int step_y = (y_max() / ++notches_y);
	if (step_x <= (_diametro + _margine + _margine)) throw exception("Siamo troppi!");
	if (step_y <= (_diametro + _margine + _margine)) throw exception("Siamo troppi!");

	// ora scorrendo la lista e la mappa _occorrenze sapremo esattamente quanti grafi posizionare per ogni x, la y verrà solo scalata ad ogni posizionamento
	nuvola = _grafi.begin();
	auto occorrenza = _occorrenze.begin();
	
	while (nuvola != _grafi.end()) {
		++pos_x;
		int x = pos_x * step_x;
		// la label dell'anno va posizionata in basso per prima
		std::ostringstream os{ "" };
		os << (*nuvola)->getRecord().getAnno();
		Graph_lib::Text* etichetta = new Graph_lib::Text(Point{ x, (y_max() - _margine) }, os.str());
		etichetta->set_color(Graph_lib::Color::dark_red);
		attach(*etichetta);
		_etichette.push_back(etichetta);
		pos_y = _occorrenze[(*nuvola)->getRecord().getAnno()];
		while (pos_y > 0) {
			int y = (y_max() - (pos_y * step_y) - (_margine * (*nuvola)->getRecord().getAntenati().size()));
			(*nuvola)->move_to(x, y);
			--pos_y;
			++nuvola;
		}
	}

	// gli antenati vanno cercati e dalla loro posizione partirà una freccia verso il nuovo grafo
	// creeremo prima la versione2 della freccia a cui passare il punto di partenza e il punto finale dove la freccia arriva.
	auto nave_grafi = _grafi.begin();
	while (nave_grafi != _grafi.end()) {
		auto nave_antenati = (*nave_grafi)->getRecord().getBegin_antenati();
		while (nave_antenati != (*nave_grafi)->getRecord().getEnd_antenati()) {
			Point p1 = find_pos((*nave_antenati));
			if (p1.x != 0 && p1.y != 0) collega(p1, (*nave_grafi)->getPos());
			++nave_antenati;
		}
		++nave_grafi;
	}
}
