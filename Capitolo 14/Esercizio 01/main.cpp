/*
Capitolo 14 Esercizio 1
Creare due classi: Smiley e Frowny che derivano da un Circle e aggiungono due occhi e la bocca.
Poi creare delle classi che ereditano da queste e aggiungono un cappello.
*/

#include "../GUI/Simple_window.h"
#include "../GUI/Graph.h"
#include "../GUI/GUI.h"
#include "../GUI/fltk.h"

namespace Graph_lib {

	class Smiley :public Graph_lib::Circle {
		// Viso sorridente
	public:
		Smiley(Point centro, int raggio) :Circle(centro, raggio) {
			x = centro.x;
			y = centro.y;
			r = raggio;
		}
		void draw_lines() const {
			fl_color(color().as_int());

			// Occhio sinistro
			int raggio = (r / 100) * 20;
			int pos_x = x - (r / 2);
			pos_x -= raggio;
			int pos_y = y - (r / 2);
			pos_y -= raggio;
			int w = raggio * 2;
			int h = raggio * 2;
			fl_arc(pos_x, pos_y, w, h, 0, 360);
			
			// occhio destro
			raggio = (r / 100) * 20;
			pos_x = x + (r / 2);
			pos_x -= raggio;
			pos_y = y - (r / 2);
			pos_y -= raggio;
			w = raggio * 2;
			h = raggio * 2;
			fl_arc(pos_x, pos_y, w, h, 0, 360);

			// bocca
			raggio = (r / 100) * 30;
			pos_x = x;
			pos_x -= raggio;
			pos_y = y + (r / 2);
			pos_y -= raggio;
			w = raggio * 2;
			h = raggio * 2;
			fl_arc(pos_x, pos_y, w, h, 180, 360);

			// Cerchio
			//pos_x = x - r;
			//pos_y = y - r;
			//w = r * 2;
			//h = r * 2;
			//fl_arc(pos_x, pos_y, w, h, 0, 360);
			Circle::draw_lines();
		}

		void move(int dx, int dy) {
			x += dx;
			y += dy;
			Circle::move(dx, dy);
		}

	private:
		int x, y;
		int r;
	};

	class Frowny :public Graph_lib::Circle {
		// Viso triste
	public:
		Frowny(Point centro, int raggio) :Circle(centro, raggio) {
			x = centro.x;
			y = centro.y;
			r = raggio;
		}
		void draw_lines() const {
			fl_color(color().as_int());

			// Occhio sinistro
			int raggio = (r / 100) * 20;
			int pos_x = x - (r / 2);
			pos_x -= raggio;
			int pos_y = y - (r / 2);
			pos_y -= raggio;
			int w = raggio * 2;
			int h = raggio * 2;
			fl_arc(pos_x, pos_y, w, h, 0, 360);

			// occhio destro
			raggio = (r / 100) * 20;
			pos_x = x + (r / 2);
			pos_x -= raggio;
			pos_y = y - (r / 2);
			pos_y -= raggio;
			w = raggio * 2;
			h = raggio * 2;
			fl_arc(pos_x, pos_y, w, h, 0, 360);

			// bocca
			raggio = (r / 100) * 30;
			pos_x = x;
			pos_x -= raggio;
			pos_y = y + (r / 2);
			pos_y -= raggio;
			w = raggio * 2;
			h = raggio * 2;
			fl_arc(pos_x, pos_y, w, h, 0, 180);

			// Cerchio
			//pos_x = x - r;
			//pos_y = y - r;
			//w = r * 2;
			//h = r * 2;
			//fl_arc(pos_x, pos_y, w, h, 0, 360);
			Circle::draw_lines();
		}

		void move(int dx, int dy) {
			x += dx;
			y += dy;
			Circle::move(dx, dy);
		}

	private:
		int x, y;
		int r;
	};

	class Hat_smiley :public Smiley {
	public:
		Hat_smiley(Point centro, int raggio) : Smiley(centro, raggio) {
			x = centro.x;
			y = centro.y;
			r = raggio;
		}

		void draw_lines() const {
			// disegno il cappello
			
			// archetto
			int raggio = (r / 100) * 8;
			int w = r * 2;
			int h = raggio * 2;
			int pos_x = x;
			int pos_y = y - r;
			pos_x -= w / 2;
			pos_y -= h / 2;
			fl_arc(pos_x, pos_y, w, h, 130, 50);

			// cilindro
			int start_x, start_y, end_x, end_y;
			start_x = x - (r / 2);
			start_y = y - r;
			end_x = start_x;
			end_y = start_y - ((r / 100) * 50);
			fl_line(start_x, start_y, end_x, end_y);
			
			start_x = x + (r / 2);
			start_y = y - r;
			end_x = start_x;
			end_y = start_y - ((r / 100) * 50);
			fl_line(start_x, start_y, end_x, end_y);

			start_x = x - (r / 2);
			start_y = y - r - ((r / 100) * 50);
			end_x = start_x + r;
			end_y = start_y;
			fl_line(start_x, start_y, end_x, end_y);

			// Disegno la faccina
			Smiley::draw_lines();
		}

		void move(int dx, int dy) {
			x += dx;
			y += dy;
			Smiley::move(dx, dy);
		}

	private:
		int x, y;
		int r;
	};

	class Hat_frowny :public Frowny {
	public:
		Hat_frowny(Point centro, int raggio) :Frowny(centro, raggio) {
			x = centro.x;
			y = centro.y;
			r = raggio;
		}

		void draw_lines() const {
			// disegno il cappello

			// archetto
			int raggio = (r / 100) * 8;
			int w = r * 2;
			int h = raggio * 2;
			int pos_x = x;
			int pos_y = y - r;
			pos_x -= w / 2;
			pos_y -= h / 2;
			fl_arc(pos_x, pos_y, w, h, 130, 50);

			// cilindro
			int start_x, start_y, end_x, end_y;
			start_x = x - (r / 2);
			start_y = y - r;
			end_x = start_x;
			end_y = start_y - ((r / 100) * 50);
			fl_line(start_x, start_y, end_x, end_y);

			start_x = x + (r / 2);
			start_y = y - r;
			end_x = start_x;
			end_y = start_y - ((r / 100) * 50);
			fl_line(start_x, start_y, end_x, end_y);

			start_x = x - (r / 2);
			start_y = y - r - ((r / 100) * 50);
			end_x = start_x + r;
			end_y = start_y;
			fl_line(start_x, start_y, end_x, end_y);

			// Disegno la faccina
			Frowny::draw_lines();
		}

		void move(int dx, int dy) {
			x += dx;
			y += dy;
			Frowny::move(dx, dy);
		}

	private:
		int x, y;
		int r;
	};
}

int main() {
	using namespace Graph_lib;
	const string titolo{ "Capitolo 14 - Esercizio 1" };
	Simple_window win(Point{ 10, 10 }, 600, 600, titolo);
	win.color(Color::white);

	Smiley sorriso(Point{ 100, 100 }, 100);
	sorriso.set_color(Color::blue);
	win.attach(sorriso);

	Frowny broncio(Point{ 300, 100 }, 100);
	broncio.set_color(Color::blue);
	win.attach(broncio);
	
	win.wait_for_button();
	broncio.move(0, 50);
	win.wait_for_button();
	win.detach(sorriso);
	win.detach(broncio);

	Hat_smiley sorriso_cappellato(Point{ 110, 300 }, 100);
	sorriso_cappellato.set_color(Color::blue);
	win.attach(sorriso_cappellato);

	Hat_frowny broncio_cappellato(Point{ 420, 300 }, 100);
	broncio_cappellato.set_color(Color::blue);
	win.attach(broncio_cappellato);

	win.wait_for_button();

}