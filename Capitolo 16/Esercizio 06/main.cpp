/*
Capitoloo 16 Esercizio 6
Crea un "Orologio analogico", cioè, un orologio con lancette che si muovono.
Prendi l'orario dall'orologio di sistema tramite una chiamata alla libreria.
La magior parte di questo esercizio è cercare le funzioni che ti servono per l'orario
e per aspettare un certo lasso di tempo, ad esempio un secondo, e impararle ad usarle secondo la documentazione che trovi,
ad esempio clock() e sleep().
*/

#include "../GUI/Graph.h"
#include "../GUI/GUI.h"
#include "../GUI/Window.h"
#include <chrono>
#include <ctime>
#include <thread>

using namespace Graph_lib;
// voglio creare più Shape in modo da non ridisegnare tutto l'orologio ma solo la lancetta.
class Lancetta : public Shape {
public:
	Lancetta(Point pos, int lunghezza, int ticks_totali)
	{
		add(pos);
		_size = lunghezza;
		_ticks = ticks_totali;
		_tick = 0;
	}
	void draw_lines() const {
		// la linea della lancetta parte dal suo punto di origine
		int x1 = point(0).x;
		int y1 = point(0).y;
		// e termina sulla circonferenza immaginaria che disegna durante la rotazione
		// l'angolo in fltk parte dalle ore 3 e gira in senso antiorario
		int angolo = 90 - ((360 / _ticks) * _tick);
		double radianti = angolo * _pi / 180;
		int x2 = x1 + _size * cos(radianti);
		int y2 = y1 - _size * sin(radianti);
		fl_line(x1, y1, x2, y2);
	}
	bool tick() {
		// muove la lancetta di un tick in rapporto all'angolo giro (360 / ticks_totali)
		++_tick;
		if (_tick == _ticks) {
			// ho fatto un giro completo
			_tick = 0;
			return true;
		}
		return false;
	}
	void set_tick(int ticks) {
		_tick = ticks % _ticks;
	}
private:
	int _size, _tick, _ticks;
	const double _pi = 3.14159265;
};

class Clock : public Shape {
public:
	Clock(Point pos, int diametro) : _secondi(pos, ((diametro * 0.8) / 2), 60),
		_minuti(pos, ((diametro * 0.7) / 2), 60),
		_ore(pos, ((diametro * 0.5) / 2), 12)
	{
		add(pos);
		_diametro = diametro;
		_secondi.set_color(Color::red);
		_minuti.set_color(Color::dark_green);
		_ore.set_color(Color::blue);
		_batteria = false;
	}
	void draw_lines() const {
		int x = point(0).x;// -(_diametro / 2);
		int y = point(0).y;// -(_diametro / 2);
		fl_circle(x, y, (_diametro / 2));
		_secondi.draw();
		_minuti.draw();
		_ore.draw();
	}
	void move(int dx, int dy) {
		Shape::move(dx, dy);
		_secondi.move(dx, dy);
		_minuti.move(dx, dy);
		_ore.move(dx, dy);
	}
	void start() {
		// avvia l'orologio
		_batteria = true;
		std::chrono::seconds step(1);
		std::chrono::system_clock::time_point adesso = std::chrono::system_clock::now();
		std::time_t orario = std::chrono::system_clock::to_time_t(adesso);
		std::tm* t_orario = new std::tm;
		localtime_s(t_orario, &orario);
		_secondi.set_tick(t_orario->tm_sec);
		_minuti.set_tick(t_orario->tm_min);
		_ore.set_tick(t_orario->tm_hour);
		while (_batteria) {
			if (_secondi.tick()) {
				if (_minuti.tick()) {
					_ore.tick();
				}
			}
			std::this_thread::sleep_for(step);
		}
	}
	void stop() {
		_batteria = false;
	}
	void set_orario(std::tm* orario) {
		_secondi.set_tick(orario->tm_sec);
		_minuti.set_tick(orario->tm_min);
		_ore.set_tick(orario->tm_hour);
	}
	void tick() {
		if (_secondi.tick()) {
			if (_minuti.tick()) {
				_ore.tick();
			}
		}
		//draw();
	}
private:
	int _diametro;
	Lancetta _secondi;
	Lancetta _minuti;
	Lancetta _ore;
	bool _batteria; // orologio in funzione (1), spento (0)
};

class Box_clock : public Window {
public:
	Box_clock(Point pos, int dimensione, const std::string& titolo) : Window(pos, dimensione, dimensione, titolo),
		bt_start(Point{ pos.x + 10, pos.y + 10 }, 70, 30, "Start", [](Address, Address pw) { reference_to<Box_clock>(pw).on(); }),
		bt_stop(Point{ x_max() - 100, pos.y + 10 }, 70, 30, "Stop", [](Address, Address pw) { reference_to<Box_clock>(pw).off(); }),
		time_machine(Point{ x_max() / 2, y_max() / 2 }, dimensione - 50)
	{
		_batteria = false;
		attach(bt_start);
		attach(bt_stop);
		time_machine.set_color(Color::black);
		attach(time_machine);
	}	
	void start() {
		std::chrono::seconds step(1);
		show();
		while (1) {
			Fl::wait(1000);
			std::this_thread::sleep_for(step);
			if (_batteria) time_machine.tick();
			Fl::redraw();
		}
	}
private:
	Button bt_start, bt_stop;
	Clock time_machine;
	void on() {
		// avvia l'orologio
		std::chrono::system_clock::time_point adesso = std::chrono::system_clock::now();
		std::time_t orario = std::chrono::system_clock::to_time_t(adesso);
		std::tm* t_orario = new std::tm;
		localtime_s(t_orario, &orario);
		time_machine.set_orario(t_orario);
		_batteria = true;
	}
	void off() {
		_batteria = false;
	}
	bool _batteria;
};

int main() {
	try {
		Box_clock win(Point{ 0,0 }, 500, "Capitolo 16 Esercizio 6");
		win.color(Color::white);
		//Clock orologgio(Point{ 250,250 }, 300);
		//orologgio.set_color(Color::green);
		//win.attach(orologgio);
		//Button bt_on(Point{ 10, 10 }, 70, 30, "Start()", [](Address, Address pw) { reference_to<Clock>(reference_to<Graph_lib::Window>(pw).child(1)).start(); });
		//win.attach(bt_on);
		win.start();
		//return gui_main();
	}
	catch (...) {

	}
}