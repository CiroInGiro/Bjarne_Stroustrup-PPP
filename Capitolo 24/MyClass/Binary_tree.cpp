#include "Binary_tree.h"

Binary_tree::Binary_tree() :_livello{ 0 } {}

Binary_tree::Binary_tree(Point root, int level) {
	inizializza(root, level, Conn_verso::Nessuna, Graph_lib::Color::black);
}

Binary_tree::Binary_tree(Point root, int level, Conn_verso freccia, Graph_lib::Color colore_freccia) {
	inizializza(root, level, freccia, colore_freccia);
}

void Binary_tree::draw_lines() const {
	// bisogna seguire lo stesso schema di chiamate ricorsive utilizzato per creare le coordinate dei singoli nodi.
	// indice sarà creata qui e passata per riferimento in modo che possa essere aggiornata da tutte le funzioni ricorsive che disegnano il proprio nodo, contiente l'indice di lettura dal vettore di punti.
	int indice{ 0 };
	if (number_of_points() > 0) disegna_nodo(indice, 1);
	_nomina_nodi();
}

void Binary_tree::add_text(string percorso, string testo) {
	int indice{ 0 };
	// i indica anche il nostro livello
	for (int i = 0; i < percorso.length(); i++) {
		char direzione = percorso[i];
		switch (direzione) {
		case 'l':
			indice++;
			break;
		case 'r':
			if ((_livello - i) == 1) indice++;
			else if ((_livello - i) > 1) indice += pow(2, (_livello - i - 1));
			break;
		case 'o':
			indice = 0;
			break;
		default:
			break;
		}
	}
	Point pl{ (point(indice).x + _size_nodo), (point(indice).y + _size_nodo) };
	Graph_lib::Text* t = new Graph_lib::Text(pl, testo);
	t->set_color(_colore_freccia);
	t->set_fill_color(_colore_freccia);
	t->set_font_size(_size_nodo);
	_nomi_nodi.push_back(*t);
}

int Binary_tree::potenza(int base, int potenza) {
	int retVal{ base };
	for (int p = 1; p < potenza; p++) {
		retVal *= base;
	}
	return retVal;
}

void Binary_tree::inizializza(Point root, int level, Conn_verso freccia, Graph_lib::Color colore_freccia) {
	_livello = level;
	if (level < 0) _livello = 0;
	if (_livello != 0) crea_punti(root, 1);
	_colore_freccia = colore_freccia;
	_freccia = freccia;
}

void Binary_tree::crea_punti(Point& root, int livello_attuale) {
	// bisogna usare questa fuznione in modo ricorsivo disegnando solo i figli del nodo passato, lo spazio necessario è calcolato in base al numero di livelli sottostanti da disegnare ancora
	add(root);
	int livelli_rimanenti = _livello - livello_attuale;
	if (livelli_rimanenti > 0) {
		int sx_x, sx_y, dx_x, dx_y;
		sx_x = root.x - (potenza(2, livelli_rimanenti) * _size_nodo) - (potenza(2, livelli_rimanenti) * _margine_nodo);
		sx_y = root.y + _size_nodo + _margine_nodo_top;
		Point sx{ sx_x, sx_y };
		crea_punti(sx, (livello_attuale + 1));
		dx_x = root.x + (potenza(2, livelli_rimanenti) * _size_nodo) + (potenza(2, livelli_rimanenti) * _margine_nodo);
		dx_y = sx_y;
		Point dx{ dx_x, dx_y };
		crea_punti(dx, (livello_attuale + 1));
	}
}

void Binary_tree::disegna_nodo(int& indice, int livello_attuale) const {
	if (color().visibility()) {
		fl_color(color().as_int());
		int x = point(indice).x - (_size_nodo / 2);
		int y = point(indice).y - (_size_nodo / 2);
		fl_arc(x, y, _size_nodo, _size_nodo, 0, 360);
	}
	if (fill_color().visibility()) {
		fl_color(fill_color().as_int());
		int x = point(indice).x - (_size_nodo / 2);
		int y = point(indice).y - (_size_nodo / 2);
		fl_pie(x, y, _size_nodo, _size_nodo, 0, 360);
	}
	int livelli_rimanenti = _livello - livello_attuale;
	if (livelli_rimanenti > 0) {
		// nodo sinistro
		int x1 = point(indice).x;
		int y1 = point(indice).y;
		indice++;
		int x2 = point(indice).x;
		int y2 = point(indice).y;
		switch (_freccia) {
		case Conn_verso::Down:
		{
			int l, a;
			parametri_freccia(Point{ x1, y1 }, Point{ x2, y2 }, l, a);
			Graph_lib::Arrow freccia(Point{ x1, y1 }, l, a);
			freccia.set_color(_colore_freccia);
			freccia.draw();
			break;
		}
		case Conn_verso::Up:
		{
			int l, a;
			parametri_freccia(Point{ x2, y2 }, Point{ x1, y1 }, l, a);
			Graph_lib::Arrow freccia(Point{ x2, y2 }, l, a);
			freccia.set_color(_colore_freccia);
			freccia.draw();
			break;
		}
		default:
		{
			fl_line(x1, y1, x2, y2);
			break;
		}
		}
		disegna_nodo(indice, (livello_attuale + 1));
		// nodo destro
		indice++;
		x2 = point(indice).x;
		y2 = point(indice).y;
		switch (_freccia) {
		case Conn_verso::Down:
		{
			int l, a;
			parametri_freccia(Point{ x1, y1 }, Point{ x2, y2 }, l, a);
			Graph_lib::Arrow freccia(Point{ x1, y1 }, l, a);
			freccia.set_color(_colore_freccia);
			freccia.draw();
			break;
		}
		case Conn_verso::Up:
		{
			int l, a;
			parametri_freccia(Point{ x2, y2 }, Point{ x1, y1 }, l, a);
			Graph_lib::Arrow freccia(Point{ x2, y2 }, l, a);
			freccia.set_color(_colore_freccia);
			freccia.draw();
			break;
		}
		default:
		{
			fl_line(x1, y1, x2, y2);
			break;
		}
		}
		//fl_line(x1, y1, x2, y2);
		disegna_nodo(indice, (livello_attuale + 1));
	}
}

void Binary_tree::parametri_freccia(const Point p1, const Point p2, int& l, int& a) const {
	// calcolo della lunghezza linea
	double c1 = p1.x - p2.x;
	if (c1 < 0) c1 *= -1;
	double c2 = p1.y - p2.y;
	if (c2 < 0) c2 *= -1;
	// teorema di pitagora, calcolo della ipotenusa dai cateti rappresentati dalle distanze tra i due punti sulle ascisse e l'ordinaria
	l = (int)sqrt((pow(c1, 2) + pow(c2, 2)));
	// calcolo della sua inclinazione
	double angolo{ 0.0 };
	double dx = p1.x - p2.x;
	double dy = p1.y - p2.y;
	//double m = dy / dx;
	//if (m < 0) angolo = atan((dy / -dx));
	//else angolo = atan((dy / dx));
	// calcolo arco tangente con rilevazione quadrante in base alla distanza su x e distanza du y dei due punti (il coefficiente angolare m della retta è dato da deltaY su deltaX
	angolo = atan2(dx, dy);
	const double pi = 3.14159265;
	//angolo = (angolo * 180) / pi;
	// convertiamo l'angolo radiante in gradi e aggiungiamo 90° perché fltk ha l'angolo 0° sulle ore 3
	a = 90 + ((angolo * 180) / pi);
	//if (m < 0) a = 360 - angolo;
	//else a = 180 + angolo;
}

void Binary_tree::_nomina_nodi() const {
	for (int i = 0; i < _nomi_nodi.size(); i++) {
		_nomi_nodi[i].draw();
	}
}