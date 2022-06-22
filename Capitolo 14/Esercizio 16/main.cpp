/*
Capitolo 14 Esercizio 16
Definire una classe Controler con 4 funzioni virtuali:
on(), off(), set_level(int) e show().
Deriva almeno due classi da Controller.
La prima dovrebbe essere una semplice classe di test in cui show() stampa se la classe è attiva o disattivata e il suo livello.
La seconda classe dovrebbe in qualche modo controllare il colore della linea di un Shape, l'esatto significato di livello dipende da te.
Prova a creare una terza cosa da controllare con la classe Controller.
*/

#include <iostream>
#include "../GUI/Graph.h"
#include "../GUI/Simple_window.h"

class Controller {
public:
	Controller() {}
	virtual void on() { _on = 1; }
	virtual void off() { _on = 0; }
	virtual void set_level(int livello) { _livello = livello; }
	virtual void show() = 0;
	bool get_status() { return _on; }
	int get_level() { return _livello; }
private:
	bool _on{ 0 };
	int _livello{ 0 };
};

class Test_controller : public Controller {
public:
	Test_controller() {}
	void set_level(int livello) {
		if (livello >= 0 && livello <= 5) _livello = livello;
	}
	void show() {
		using std::cout;
		using std::endl;
		cout << "Hai chiamato Test_controller::show(): " << endl;
		cout << "Lo stato della classe è " << get_status() << endl;
		cout << "Il suo livello è " << _livello << endl;
	}
private:
	int _livello;
};

class Insegna : public Controller, public Graph_lib::Shape {
public:
	Insegna(Point pos, int level = 0, int power = 0) :_pos{ pos } {
		set_power(power);
		set_level(level);
	}
	void set_power(int power) {
		_power = power;
		if (_power < 0) _power = 0;
		if (_power > 10) _power = 10;
		if (_power > 0) on(); else off();
	}
	int get_power() const { return _power; }
	void set_level(int level) {
		_level = level;
		if (_level < 0) _level = 0;
		if (_level > 5) _level = 5;
	}
	int get_level() { return _level; }
	void draw_lines() const { show_control(); }
	void show() { show_control(); }
	void show_control() const {
		for (int p = _power; p > 0; --p) {
			int x = _pos.x;
			int y = _pos.y - (10 * p);
			Graph_lib::Rectangle* rect = new Graph_lib::Rectangle{ Point{x, y}, 10, 10 };
			rect->set_color(Graph_lib::Color::white);
			switch (_level) {
			case 0:
				rect->set_fill_color(Color::black);
				break;
			case 1:
				rect->set_fill_color(Color::dark_blue);
				break;
			case 2:
				rect->set_fill_color(Color::blue);
				break;
			case 3:
				rect->set_fill_color(Color::dark_green);
				break;
			case 4:
				rect->set_fill_color(Color::green);
				break;
			case 5:
				rect->set_fill_color(Color::cyan);
				break;
			default:
				rect->set_fill_color(Color::white);
				break;
			}
			rect->draw();
		}
	}
private:
	int _level{ 0 };
	int _power{ 0 };
	Point _pos;
};

int main(int argc, char** argv) {
	Test_controller tc;
	tc.set_level(4);
	tc.show();
	tc.on();
	tc.set_level(8);
	tc.show();
	std::cin.get();
	Insegna i( Point{400, 400}, 5, 7 );
	Simple_window win(Point{ 0,0 }, 800, 800, "Capitolo 14 Esercizio 16");
	win.color(Color::white);
	win.attach(i);
	win.wait_for_button();
	return 0;
}