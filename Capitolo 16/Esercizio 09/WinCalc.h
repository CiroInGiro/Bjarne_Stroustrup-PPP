#pragma once
#include "../GUI/Gui.H"
#include "../GUI/Graph.h"
#include "Calc.h"

using namespace Graph_lib;

class WinCalc : public Graph_lib::Window
{
public:
	WinCalc(Point pos, int width, int height, const std::string& titolo) : Window(pos, width, height, titolo),
		tastiera(Point{ pos.x + 100, pos.y + 10 }, (width - 200), 30, "Comandi "),
		display(Point{ pos.x + 100, pos.y + 60 }, (width - 200), 30, "Risultato: "),
		log(Point{ pos.x + 100, pos.y + 140 }, "Errori: "),
		bt_calcola(Point{ pos.x + width - 100, pos.y + 10 }, 80, 30, "Calcola", cb_calcola)
	{
		attach(tastiera);
		attach(bt_calcola);
		attach(display);
		attach(log);
		log.set_color(Color::red);
	}
	static void cb_calcola(Address, Address pw) {
		reinterpret_cast<WinCalc*>(pw)->calcola();
	}
private:
	In_box tastiera;
	Out_box display;
	Text log;
	Button bt_calcola;
	void calcola();
};

