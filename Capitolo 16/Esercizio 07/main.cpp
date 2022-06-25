/*
Capitolo 16 Esercizio 7
Utilizzando la tecnica sviluppata nel precedente esercizio, crea una immagine di un aereplano che vola in giro per la finestra.
Aggiungi i bottoni start e stop.
*/

#include "../GUI/GUI.h"
#include "../GUI/Window.h"
#include "../GUI/Graph.h"
#include <thread>
#include <chrono>

using namespace Graph_lib;

// Immagine che svolazza in un quadrato di coordinate
class Fly : public Image {
public:
	Fly(Point pos, const std::string name, Graph_lib::Suffix::Encoding t_img, int width, int height, Point min, Point max) : Image(pos, name, t_img)
	{
		//set_mask(pos, width, height);
		set_mask(Point{ 0,0 }, width, height);
		_xmin = min.x;
		_xmax = max.x - width;
		_ymin = min.y;
		_ymax = max.y - height;
		_width = width;
		_height = height;
		random_event();
	}

	void avanza() {
		double radianti = _direzione * pi / 180;
		int newx = (int)(point(0).x + _velocita * cos(radianti));
		int newy = (int)(point(0).y - _velocita * sin(radianti));
		if (newx > _xmax || newx < _xmin || newy > _ymax || newy < _ymin) {
			// ricalcolo
			random_event();
		}
		else
		{
			int dx = newx - point(0).x;
			int dy = newy - point(0).y;
			move(dx, dy);
		}
	}

private:
	// recinto in cui volare
	int _xmin, _xmax, _ymin, _ymax;
	// numero di pixel di spostamento per volta, 0 sta fermo
	int _velocita;
	// angolo 0 - 350° che indica la direzione. 0 inddica le ore 3.00
	int _direzione;
	const double pi = 3.14159265;
	int _width, _height;
	void random_event() {
		_velocita = (rand() % 100) + 20;
		_direzione = rand() % 360;
	}
};

class WinFly : public Window {
public:
	WinFly(Point pos, int width, int height, const std::string& titolo) : Window(pos, width, height, titolo),
		bt_start(Point{ pos.x + 20, pos.y + 10 }, 70, 20, "START", cb_start),
		bt_stop(Point{ pos.x + 110, pos.y + 10}, 70, 20, "STOP", cb_stop),
		pallone(Point{ x_max() / 2, y_max() / 2 }, "pallone.jpg", Suffix::jpg, 71, 100, Point{ pos.x, pos.y }, Point{ x_max(), y_max() })
	{
		power = false;
		attach(bt_start);
		attach(bt_stop);
		attach(pallone);
	}

	static void cb_start(Graph_lib::Address, Graph_lib::Address pw) {
		Graph_lib::reference_to<WinFly>(pw).start();
	}

	static void cb_stop(Graph_lib::Address, Graph_lib::Address pw) {
		Graph_lib::reference_to<WinFly>(pw).stop();
	}

private:
	Graph_lib::Button bt_start;
	Graph_lib::Button bt_stop;
	Fly pallone;
	bool power;
	std::chrono::milliseconds step{ 500 };
	void start() {
		power = true;
		while (power) {
			pallone.avanza();
			Fl::wait(0.5);
			std::this_thread::sleep_for(step);
			Fl::redraw();
		}
	}
	void stop(){
		power = false;
	}
};

int main() {
	WinFly win(Point{ 0,0 }, 800, 800, "Capitolo 16 Esercizio 7");
	win.color(Color::dark_green);

	return Fl::run();
}