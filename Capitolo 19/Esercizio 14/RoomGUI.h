#pragma once

#include "Room.h"
#include "../MyClass/TBox.h"


class RoomGUI
{
public:
	RoomGUI(Room* stanza, int x, int y, int dimensione);
	void set_visitata(bool);
	bool get_visitata() const;
	void toggle_hero();
	void toggle_pit();
	void toggle_bat();
	void toggle_wump();
	void toggle_markpit();
	void toggle_markbat();
	void toggle_markwump();
	void set_wump(bool w);
	bool get_wump();

	Room* get_stanza() const;
	int get_x() const;
	int get_y() const;
	Graph_lib::TBox* getgui();
	RoomGUI* rear;
	RoomGUI* front;
	RoomGUI* left;
	RoomGUI* right;
private:
	Room* _stanza{ nullptr };
	bool visitata;
	bool marcata;
	bool pit;
	bool bat;
	bool wump;
	bool markpit;
	bool markbat;
	bool markwump;
	int numero;
	bool hero;
	int _x, _y, _dimensione;
	Graph_lib::TBox* caverna;
	void formatta();
};

// usata per costruire la caverna della versione 1
class Minatore {
public:
	Minatore(vector<RoomGUI*>* v, Minatore* provenienza, Room* stanza, int x, int y, int margine, int dimensione);
	RoomGUI* vai(vector<RoomGUI*>* v);
private:
	Minatore* provenienza;
	Minatore* prossimo;
	RoomGUI* roomgui;
	int _x, _y, _margine, _dimensione;
	Room* _stanza;
};

// la uso adesso per costruire la caverna explorandola da una camera di partenza, senza la ricorsione di Minatore.
class Explorer {
public:
	Explorer(Room* stanza, int x, int y, int margine, int dimensione);
	RoomGUI* vai(vector<RoomGUI*>* v);
private:
	void collega(RoomGUI* rg);
	void collega_front(RoomGUI* rg);
	void collega_right(RoomGUI* rg);
	void collega_rear(RoomGUI* rg);
	void collega_left(RoomGUI* rg);
	vector<RoomGUI*> memoria;
	Room* _stanza_partenza{ nullptr };
	int _x{ 0 };
	int _y{ 0 };
	int _margine{ 0 };
	int _dimensione{ 0 };
};