/*
Capitolo 16 Esercizio 4
Crea un menu con elementi che formano un cerchio, un quadrato, un triangolo equilatero, un esagono rispettivamente.
Crea un input box o due per prendere una coppia di coordinate, poni il disegno che si crea premento un pulsante in queste coordinate.
Spiacente, non col drag e drop.
*/

#include "../GUI/GUI.h"
#include "../GUI/Window.h"
#include "../MyClass/Box.h"
#include "../MyClass/TriangoloRettangolo.h"
#include "../MyClass/Regular_Hexagon.h"

class Maker_shape : public Graph_lib::Window {
public:
	Maker_shape(Point pos, int width, int height, const std::string& titolo) : Window(pos, width, height, titolo),
		x_pos(Point{ pos.x + 25, pos.y + 2 }, 70, 30, "X: "),
		y_pos(Point{ pos.y + 120, pos.y + 2 }, 70, 30, "Y: "),
		figure(Point{pos.x + 215, pos.y + 2}, 70, 30, Graph_lib::Menu::Kind::horizontal, "Shapes")
	{
		attach(x_pos);
		attach(y_pos);
		figure.attach(new Graph_lib::Button(Point{ 0,0 }, 0, 0, "Circle", [](Graph_lib::Address, Graph_lib::Address pw) {Graph_lib::reference_to<Maker_shape>(pw).make_circle(); }));
		figure.attach(new Graph_lib::Button(Point{ 0,0 }, 0, 0, "Square", [](Graph_lib::Address, Graph_lib::Address pw) {Graph_lib::reference_to<Maker_shape>(pw).make_square(); }));
		figure.attach(new Graph_lib::Button(Point{ 0,0 }, 0, 0, "Triangle", [](Graph_lib::Address, Graph_lib::Address pw) {Graph_lib::reference_to<Maker_shape>(pw).make_triangle(); }));
		figure.attach(new Graph_lib::Button(Point{ 0,0 }, 0, 0, "Hexagon", [](Graph_lib::Address, Graph_lib::Address pw) {Graph_lib::reference_to<Maker_shape>(pw).make_hexagon(); }));
		attach(figure);
	}
private:
	Graph_lib::Menu figure;
	Graph_lib::In_box x_pos;
	Graph_lib::In_box y_pos;
	void make_circle() {
		int x = x_pos.get_int();
		int y = y_pos.get_int();
		int raggio = 100;
		Graph_lib::Circle* c = new Graph_lib::Circle(Point{ x, y }, raggio);
		c->set_color(Graph_lib::Color::blue);
		attach(*c);
		redraw();
	}
	void make_square() {
		int w = 100;
		int h = 100;
		int x = x_pos.get_int() - (w / 2);
		int y = y_pos.get_int() - (h / 2);
		Graph_lib::Box* q = new Graph_lib::Box(Point{ x,y }, w, h);
		q->set_color(Graph_lib::Color::blue);
		attach(*q);
		redraw();
	}
	void make_triangle() {
		int base = 100;
		int altezza = (int)sqrt(pow((base / 2), 2) + pow(base, 2));
		int x = x_pos.get_int();
		int y = y_pos.get_int() - (altezza / 2);
		Graph_lib::TriangoloRettangolo* t_dx = new Graph_lib::TriangoloRettangolo(Point{ x,y }, (base / 2), altezza, -90);
		Graph_lib::TriangoloRettangolo* t_sx = new Graph_lib::TriangoloRettangolo(Point{ x,y }, (-base / 2), altezza, -90);
		t_dx->set_color(Graph_lib::Color::blue);
		t_sx->set_color(Graph_lib::Color::blue);
		attach(*t_dx);
		attach(*t_sx);
		redraw();
	}
	void make_hexagon() {
		int x = x_pos.get_int();
		int y = y_pos.get_int();
		Graph_lib::Regular_Hexagon* h = new Graph_lib::Regular_Hexagon(Point{ x,y }, 100);
		h->set_color(Graph_lib::Color::blue);
		attach(*h);
		redraw();
	}
};

int main() {
	try {
		std::string titolo{ "Capitolo 16 Esercizio 4" };
		Maker_shape mk(Point{ 0,0 }, 800, 800, titolo);
		mk.color(Graph_lib::Color::white);
		return Graph_lib::gui_main();
	}
	catch (...) {

	}
}