#pragma once

#include "../GUI/Window.h"
#include "../GUI/Point.h"
#include "../GUI/GUI.h"
#include <iostream>
#include "Room.h"
//#include "../MyClass/TBox.h"
#include "RoomGUI.h"

using Graph_lib::Window;
using namespace Graph_lib;

class WumpusGUI : Graph_lib::Window
{
public:
	WumpusGUI(Point pos, int width, int height, const std::string& titolo);
	void action();
	istream& cin();
	ostream& cout();
	void refresh();
	bool get_in_sense() const;
	void reset_in_sense();
	void set_hero(Room* h);
	void set_wump(Room* w);
	void mark_pit(Room* p);
	void mark_bat(Room* b);
	void mark_wump(Room* w);
	void move_rooms(int dx, int dy);
	void move_rear();
	void move_front();
	void move_left();
	void move_right();
	void debug();
private:
	int xc, yc, margin, dim_room;
	// Imput box per i comandi
	Graph_lib::In_box cmd;
	// Testo in uscita come esiti e la guida
	Graph_lib::Out_box esito;
	// flussi stream
	std::istringstream iss;
	std::ostringstream oss;
	// Bottone invio comandi
	Graph_lib::Button vai;
	// controllo stream di input
	bool in_sense;
	Room* hero;
	//TBox* stanza_attuale;
	RoomGUI* stanza_attuale;
	//vector<TBox*> stanze;
	vector<RoomGUI*> stanze;

	void inizializza(Room* h);
	RoomGUI* trova_hero(Room* h);
};

