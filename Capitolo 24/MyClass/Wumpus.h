#pragma once

#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <sstream>
#include "../Esercizio 14/WumpusGUI.h"
#include "../Esercizio 14/Room.h"
#include "../Esercizio 14/RoomGUI.h"
#include <vector>

class Wumpus
{
public:
	Wumpus();
	~Wumpus();
	void debug();
	void guidebug();
	void play();
	void play(const bool, std::istream&, std::ostream&);
	// guiplay() imposta un bool per capire se siamo in modalità grafica
	// imposta gli streaming a cin e cout o WunpusGUI.gui_in e Wumpus.gui_out
	void guiplay();
	void stampa_guida();
	void stampa_stato();
	void esegui(const std::string&);
private:
	int _max_rooms;
	int _max_wump;
	int _max_pit;
	int _max_bat;
	int _max_arrow;
	int _arrow_distance;
	//using vector = std::vector<T, std::allocator<T>>;
	vector<Room*> rooms;
	vector<Room*> caverna;
	bool winner, gameover;
	// attori
	Room* wump;
	Room* bat;
	Room* hero;
	// funzioni
	void del_room(Room* r);
	void collega(Room* r);
	//void collega_back(Room* r, Room* l);
	void collega_left(Room* r);
	void collega_right(Room* r);
	void collega_front(Room* r);
	void collega_rear(Room* r);
	Room* scegli_camera(Room* room_da = nullptr); // restituisce una camera dal vettore delle camere
	void sposta_mostro();
	// grafica
	WumpusGUI* guigame;
	bool _guimode;
	// streaming
	std::istream* _in;
	std::ostream* _out;
};

