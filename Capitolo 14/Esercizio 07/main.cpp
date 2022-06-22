/*
Capitolo 14 Esercizio 7
Crea una Striped_closed_polyline utilizzando la tecinca in Striped_rectangle (ciò richiede un pò di inventiva algoritmica).
*/

#include "../GUI/Simple_window.h"
#include "../GUI/Graph.h"
#include "../GUI/GUI.h"

class Striped_closed_polyline :public Closed_polyline {
public:
	using Closed_polyline::Closed_polyline;
	void draw_lines() const {
		if (fill_color().visibility()) {
			fl_color(fill_color().as_int());
			// cerchiamo i punti di un rectangolo immaginario che racchiude tutti i punti della closed_polyline
			int startx, starty, endx, endy;
			startx = point(0).x;
			starty = point(0).y;
			endx = startx;
			endy = starty;
			for (int i = 1; i < (number_of_points() - 1); i++) {
				if (point(i).x < startx) startx = point(i).x;
				if (point(i).x > endx) endx = point(i).x;
				if (point(i).y < starty) starty = point(i).y;
				if (point(i).y > endy) endy = point(i).y;
			}
			// Ne ricaviamo il centro
			Point centro{ ((endx - startx) / 2), ((endy - starty) / 2) };
			// impostiamo un delta crescente che calcola i punti di una polyline più piccola a partire dai punti originali
			// i nuovi punti dovrebbero essere calcolati con la formula della retta perché dovranno trovarsi sulla retta che va dal punto originale al centro
			// in modo da rimpicciolire il disegno. Qui abbiamo barato.
			int dx = 0;
			int dy = 0;
			bool cicla = true;
			while (cicla) {
				for (int i = 0; i < (number_of_points() - 2); i++) {
					// primo punto
					if ((point(i).x + dx) < (centro.x - 5)) startx = point(i).x + dx;
					else if ((point(i).x - dx) > (centro.x + 5)) startx = point(i).x - dx;
					else cicla = false;
					if ((point(i).y + dy) < (centro.y - 5)) starty = point(i).y + dy;
					else if ((point(i).y - dy) > (centro.y + 5)) starty = point(i).y - dy;
					else cicla = false;
					// secondo punto
					if ((point((i+1)).x + dx) < (centro.x - 5)) endx = point((i+1)).x + dx;
					else if ((point((i+1)).x - dx) > (centro.x + 5)) endx = point((i+1)).x - dx;
					else cicla = false;
					if ((point((i+1)).y + dy) < (centro.y - 5)) endy = point((i+1)).y + dy;
					else if ((point((i+1)).y - dy) > (centro.y + 5)) endy = point((i+1)).y - dy;
					else cicla = false;
					// tracciamo la linea
					if (cicla) fl_line(startx, starty, endx, endy);
				}
				// chiudiamo la polyline
				// primo punto
				Point p1{ point((number_of_points() - 1)) };
				Point p2{ point(0) };
				if ((p1.x + dx) < (centro.x - 5)) startx = p1.x + dx;
				else if ((p1.x - dx) > (centro.x + 5)) startx = p1.x - dx;
				else cicla = false;
				if ((p1.y + dy) < (centro.y - 5)) starty = p1.y + dy;
				else if ((p1.y - dy) > (centro.y + 5)) starty = p1.y - dy;
				else cicla = false;
				// secondo punto
				if ((p2.x + dx) < (centro.x - 5)) endx = p2.x + dx;
				else if ((p2.x - dx) > (centro.x + 5)) endx = p2.x - dx;
				else cicla = false;
				if ((p2.y + dy) < (centro.y - 5)) endy = p2.y + dy;
				else if ((p2.y - dy) > (centro.y + 5)) endy = p2.y - dy;
				else cicla = false;
				if (cicla) fl_line(startx, starty, endx, endy);
				dx += 5;
				dy += 5;
			}
		}
		if (color().visibility()) {
			// se chiamo draw_lines() nella base mi riempirà anche col colore fill_color()
			// non posso modificare il colore di riempimento momentaneamente perché la funzione draw_lines() è const, quindi non può modificare l'oggetto.
			//Closed_polyline::draw_lines();

			int startx, starty, endx, endy;
			int lastpoint = number_of_points() - 1;
			startx = point((lastpoint - 1)).x;
			starty = point((lastpoint - 1)).y;
			endx = point(lastpoint).x;
			endy = point(lastpoint).y;
			fl_color(color().as_int());
			fl_line(startx, starty, endx, endy);
		}
	}
};

int main() {
	Simple_window win(Point{ 0, 0 }, 500, 500, "Capitolo 14 Esercizio 7");
	win.color(Color::white);

	Striped_closed_polyline spoly;
	spoly.set_color(Color::blue);
	spoly.set_fill_color(Color::red);
	spoly.add(Point{ 140, 10 });
	spoly.add(Point{ 120, 120 });
	spoly.add(Point{ 130, 160 });
	spoly.add(Point{ 20, 140 });
	spoly.add(Point{ 20, 40 });
	spoly.add(Point{ 10, 10 });

	win.attach(spoly);

	win.wait_for_button();
}