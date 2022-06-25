/*
Capitolo 16 Esercizio 2
Crea una finestra basata su My_window con una scacchiera di 4x4 pulsanti quadrati.
Quando premuto, un pulsante esegue una semplice azione, come stampare le sue coordinate in una casella di output
o assume un colore leggermente differente finché non viene premuto un altro pulsante.
*/

#include "My_window.h"

class Square_buttons : public My_window {
public:
	Square_buttons(Point pos, int width, int height, const std::string& titolo) : My_window(pos, width, height, titolo),
		bt1(Point{ pos.x + 10, pos.y + 10 }, 70, 70, "Rosso", [](Graph_lib::Address, Graph_lib::Address pw) {Graph_lib::reference_to<Square_buttons>(pw).bt1_action(); }),
		bt2(Point{ pos.x + 80, pos.y + 10 }, 70, 70, "Scrivo", [](Graph_lib::Address, Graph_lib::Address pw) {Graph_lib::reference_to<Square_buttons>(pw).bt2_action(); }),
		bt3(Point{ pos.x + 10, pos.y + 80 }, 70, 70, "Blue", [](Graph_lib::Address, Graph_lib::Address pw) {Graph_lib::reference_to<Square_buttons>(pw).bt3_action(); }),
		bt4(Point{ pos.x + 80, pos.y + 80 }, 70, 70, "Quit", [](Graph_lib::Address, Graph_lib::Address pw) {Graph_lib::reference_to<Square_buttons>(pw).bt4_action(); }),
		quit(Point{ pos.x + 160, pos.y + 80 }, 70, 70, "Termina", [](Graph_lib::Address, Graph_lib::Address pw) {Graph_lib::reference_to<Square_buttons>(pw).quit_action(); }),
		coordinate(Point{(x_max()/2),(y_max()/2)},100,30,"Coordinate"),
		note(Point{(x_max()/2) - 100,(y_max()/2) + 100}, "Note")
	{
		attach(bt1);
		attach(bt2);
		attach(bt3);
		attach(bt4);
		attach(quit);
		attach(coordinate);
		attach(note);
		inizializza();
	}
private:
	Graph_lib::Button bt1, bt2, bt3, bt4, quit;
	Graph_lib::Out_box coordinate;
	Graph_lib::Text note;
	void bt1_action() {
		note.set_color(Graph_lib::Color::red);
		note.set_label("Bottone 1, testo rosso");
		std::ostringstream oss;
		oss << '(' << bt1.loc.x << ',' << bt1.loc.y << ')';
		coordinate.put(oss.str());
		quit.hide();
		redraw();
	}
	void bt2_action() {
		note.set_color(Graph_lib::Color::black);
		note.set_label("Bottone 2");
		std::ostringstream oss;
		oss << '(' << bt2.loc.x << ',' << bt2.loc.y << ')';
		coordinate.put(oss.str());
		quit.hide();
		redraw();
	}
	void bt3_action() {
		note.set_color(Graph_lib::Color::blue);
		note.set_label("Bottone 3, testo blue");
		std::ostringstream oss;
		oss << '(' << bt3.loc.x << ',' << bt3.loc.y << ')';
		coordinate.put(oss.str());
		quit.hide();
		redraw();
	}
	void bt4_action() {
		note.set_color(Graph_lib::Color::black);
		note.set_label("Quit Abilitato");
		std::ostringstream oss;
		oss << '(' << bt4.loc.x << ',' << bt4.loc.y << ')';
		coordinate.put(oss.str());
		quit.show();
		redraw();
	}
	void quit_action() {
		hide();
	}
	void inizializza() {
		note.set_color(Graph_lib::Color::black);
		note.set_label("Scrivo qualcosa qui");
		coordinate.put("(0,0)");
		quit.hide();
	}
};

int main() {
	Square_buttons bottoni(Point{ 0,0 }, 500, 500, "Capitolo 16 Esercizio 2");
	bottoni.color(Graph_lib::Color::white);
	bottoni.color2(Graph_lib::Color::green);
	bottoni.labelcolor(Graph_lib::Color::red);
	bottoni.selection_color(Graph_lib::Color::cyan);
	return Graph_lib::gui_main();
}