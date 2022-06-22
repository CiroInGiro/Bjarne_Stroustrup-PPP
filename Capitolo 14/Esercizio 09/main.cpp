/*
Capitolo 14 Esercizio 9
Definisci un Group a essere un contenitori di Shape con appropriate operazioni applicati ai vari membri del gruppo.
Suggerimento: Vector_ref.
Usa Group per creare una scacchiera e i pezzi possono muoversi sopra controllati dal programma.
*/

// disegno una scacchiera tipo dama e uso 2 Group per avere una fila di pezzi di un colore e una file di colore doverso.
// creo una funzione move che seleziona un elemento dal gruppo e gli applica un movimento, i movimenti sono enumerati: avanti, dietro, sinistra, destra.

#include "../GUI/Simple_window.h"

// funzione che crea la scacchiera

void crea_scacchiera(Simple_window& win, int num_righe, int num_col, int offset_x, int offset_y, Color colore1, Color colore2) {
	int dim_x = (win.x_max() - offset_x) / num_col;
	int dim_y = (win.y_max() - offset_y) / num_righe;
	Color colore = colore1;

	for (int r = 0; r < num_righe; r++) {
		for (int c = 0; c < num_col; c++) {
			int posx = c * dim_x + offset_x;
			int posy = r * dim_y + offset_y;
			Graph_lib::Rectangle* rect = new Graph_lib::Rectangle{ Point{ posx, posy }, dim_x, dim_y };
			rect->set_color(colore);
			rect->set_fill_color(colore);
			win.attach(*rect);
			if (colore.as_int() == colore1.as_int()) colore = colore2; else colore = colore1;
		}
		if (colore.as_int() == colore1.as_int()) colore = colore2; else colore = colore1;
	}
}

enum Movimenti
{
	avanti = 0,
	dietro = 1,
	destra = 2,
	sinistra = 3
};

class Group :public Shape {
public:
	//using Graph_lib::Shape::Shape;
	Group() {}

	void add(Shape& figura) {
		figure.push_back(figura);
	}
	int elementi() const {
		return figure.size();
	}
	void draw_lines() const {
		for (int i = 0; i < figure.size(); i++) {
			figure[i].draw();
		}
	}
	void move(int dx, int dy) {
		for (int i = 0; i < figure.size(); i++) {
			figure[i].move(dx, dy);
		}
	}
	void move(int dx, int dy, int elemento) {
		if (elemento < 0) elemento = 1;
		if (elemento > figure.size()) elemento = figure.size();
		elemento--;
		figure[elemento].move(dx, dy);
	}
	void move(Movimenti direzione, int elemento) {
		if (elemento < 0) elemento = 0;
		if (elemento >= figure.size()) elemento = (figure.size() - 1);
		switch (direzione) {
		case Movimenti::avanti:
			// non tutti gli shape possono darci la loro dimensione
			break;
		default:
			break;
		}
	}

private:
	Vector_ref<Shape> figure;
};

int main() {
	const string titolo{ "Capitolo 14 Esercizio 9" };
	Simple_window win(Point{ 0, 0 }, 800, 850, titolo);
	win.color(Color::dark_yellow);
	crea_scacchiera(win, 8, 8, 0, 50, Color::white, Color::black);

	win.wait_for_button();

	Group magenti;
	
	for (int p = 0; p < 7; p++) {
		Circle *pezzo = new Circle(Point{ (p * 100 + 50), 50 }, 50);
		pezzo->set_color(Color::dark_magenta);
		pezzo->set_fill_color(Color::dark_magenta);
		magenti.add(*pezzo);
		win.attach(magenti);
	}

	Circle *pezzo = new Circle(Point{ 750, 100 }, 50);
	pezzo->set_color(Color::dark_magenta);
	pezzo->set_fill_color(Color::dark_magenta);
	magenti.add(*pezzo);
	win.attach(magenti);
	
	win.wait_for_button();

	magenti.move(0, 50);
	win.wait_for_button();

	magenti.move(0, -50, 8);
	win.wait_for_button();

	return 0;
}