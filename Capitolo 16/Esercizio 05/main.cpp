/*
Capitolo 16 Esercizio 5
Scrivi un programma che disegni una figura di tua scelta e la muove in un nuovo punto ogni volta che premi Next.
Il nuovo punto dovrebbe essere determinato da quello che legge in input da stream.
*/

#include "../GUI/GUI.h"
#include "../GUI/Window.h"
#include "../MyClass/Box.h"
#include "../MyClass/TriangoloRettangolo.h"
#include "../MyClass/Regular_Hexagon.h"

class Triangolo : public Graph_lib::Shape {
public:
	Triangolo(Point vertice, int base, int angolo) {
		int altezza = (int)sqrt(pow((base / 2), 2) + pow(base, 2));
		add(Point{ vertice.x, (vertice.y - (altezza / 2)) });
		if (angolo < -360 || angolo > 360) angolo = 0;
		tr_dx = new Graph_lib::TriangoloRettangolo(vertice, (base / 2), altezza, angolo);
		tr_sx = new Graph_lib::TriangoloRettangolo(vertice, (-base / 2), altezza, angolo);
	}
	void draw_lines() const {
		tr_dx->draw_lines();
		tr_sx->draw_lines();
	}
	void move(int dx, int dy) {
		Shape::move(dx, dy);
		tr_dx->move(dx, dy);
		tr_sx->move(dx, dy);
	}
private:
	Graph_lib::TriangoloRettangolo* tr_dx;
	Graph_lib::TriangoloRettangolo* tr_sx;
	int _base;
	int _altezza;
	int _angolo;
};

class Maker_shape : public Graph_lib::Window {
public:
	Maker_shape(Point pos, int width, int height, const std::string& titolo) : Window(pos, width, height, titolo),
		x_pos(Point{ pos.x + 25, pos.y + 2 }, 70, 30, "X: "),
		y_pos(Point{ pos.y + 120, pos.y + 2 }, 70, 30, "Y: "),
		figure(Point{ pos.x + 215, pos.y + 2 }, 70, 30, Graph_lib::Menu::Kind::horizontal, "Shapes"),
		bt_next(Point{ x_max() - 100, pos.y + 2 }, 70, 30, "Next", [](Graph_lib::Address, Graph_lib::Address pw) { Graph_lib::reference_to<Maker_shape>(pw).next(); })
	{
		attach(x_pos);
		attach(y_pos);
		figure.attach(new Graph_lib::Button(Point{ 0,0 }, 0, 0, "Circle", [](Graph_lib::Address, Graph_lib::Address pw) {Graph_lib::reference_to<Maker_shape>(pw).make_circle(); }));
		figure.attach(new Graph_lib::Button(Point{ 0,0 }, 0, 0, "Square", [](Graph_lib::Address, Graph_lib::Address pw) {Graph_lib::reference_to<Maker_shape>(pw).make_square(); }));
		figure.attach(new Graph_lib::Button(Point{ 0,0 }, 0, 0, "Triangle", [](Graph_lib::Address, Graph_lib::Address pw) {Graph_lib::reference_to<Maker_shape>(pw).make_triangle(); }));
		figure.attach(new Graph_lib::Button(Point{ 0,0 }, 0, 0, "Hexagon", [](Graph_lib::Address, Graph_lib::Address pw) {Graph_lib::reference_to<Maker_shape>(pw).make_hexagon(); }));
		attach(figure);
		attach(bt_next);
	}
private:
	Graph_lib::Menu figure;
	Graph_lib::In_box x_pos;
	Graph_lib::In_box y_pos;
	Graph_lib::Shape* last;
	Graph_lib::Button bt_next;
	void make_circle() {
		int x = x_pos.get_int();
		int y = y_pos.get_int();
		int raggio = 100;
		//Graph_lib::Circle* c = new Graph_lib::Circle(Point{ x, y }, raggio);
		last = new Graph_lib::Circle(Point{ x, y }, raggio);
		last->set_color(Graph_lib::Color::blue);
		attach(*last);
		redraw();
	}
	void make_square() {
		int w = 100;
		int h = 100;
		int x = x_pos.get_int() - (w / 2);
		int y = y_pos.get_int() - (h / 2);
		last = new Graph_lib::Box(Point{ x,y }, w, h);
		last->set_color(Graph_lib::Color::blue);
		attach(*last);
		redraw();
	}
	void make_triangle() {
		int base = 100;
		int x = x_pos.get_int();
		int y = y_pos.get_int();
		last = new Triangolo(Point{ x,y }, base, -90);
		attach(*last);
		redraw();
	}
	void make_hexagon() {
		int x = x_pos.get_int();
		int y = y_pos.get_int();
		last = new Graph_lib::Regular_Hexagon(Point{ x,y }, 100);
		last->set_color(Graph_lib::Color::blue);
		attach(*last);
		redraw();
	}
	void next() {
		int x = x_pos.get_int();
		int y = y_pos.get_int();
		int dx = x - last->point(0).x;
		int dy = y - last->point(0).y;
		last->move(dx, dy);
		redraw();
	}
};

int main() {
	try {
		std::string titolo{ "Capitolo 16 Esercizio 5" };
		Maker_shape mk(Point{ 0,0 }, 800, 800, titolo);
		mk.color(Graph_lib::Color::white);
		return Graph_lib::gui_main();
	}
	catch (...) {

	}
}