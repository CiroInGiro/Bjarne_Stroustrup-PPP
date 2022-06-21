/*
Capitolo 13 Esercizio 7
Crea un grafico di colori RGB.
Come esmpio cerca in Internet RGB Graph Charts.
*/

#include "../GUI/Simple_window.h"
#include "../GUI/Graph.h"

const int colori = 16;
const int caselle = colori * colori;


int color_step(int& r, int& g, int& b, int& select) {
	int pick = 256 / 8; // 8 combinazioni
	r += pick;
	
	//if ((r == (select * pick)) && (g == (select * pick)) && (b == (select * pick))) ++select;
	if (r == g && g == b) {
		//++select;
		r += pick;
	}

	if (select == 0 || select > 8) select = 1;

	if (r > (select * pick)) {
		r = 0;
		g += pick;
	}
	if (g > (select * pick)) {
		g = 0;
		b += pick;
	}
	if (b > (select * pick)) {
		//b = 0;
		++select;
		return color_step(r, g, b, select);
	}
	return ((r * 65536) + (g * 256) + b);
}

int main() {
	Simple_window win(Point{ 0,0 }, 800, 800, "Esercizio 7");
	win.color(Color::white);

	Vector_ref<Graph_lib::Rectangle> box;
	int r{ 0 };
	int g{ 0 };
	int b{ 0 };
	int w = win.x_max() / colori;
	int h = (win.y_max() - 20) / colori;
	int select{ 0 };

	for (int colonna = 0; colonna < colori; ++colonna) {
		int rosso = r;
		int green = g;
		int blue = b;
		for (int riga = 0; riga < colori; ++riga) {
			int indice = (colonna * colori) + riga;
			box.push_back(new Graph_lib::Rectangle(Point{ (colonna * w), ((riga * h) + 20) }, w, h));
			rosso += (256 / colori);
			if (rosso > 255) rosso = 255;
			green += (256 / colori);
			if (green > 255) green = 255;
			blue += (256 / colori);
			if (blue > 255) blue = 255;
			int colore = (rosso * 65536) + (green * 256) + blue;
			//colore = Color::white;
			box[indice].set_color(colore);
			box[indice].set_fill_color(colore);
			win.attach(box[indice]);
		}
		color_step(r, g, b, select);
	}

	win.wait_for_button();

	return 0;
}