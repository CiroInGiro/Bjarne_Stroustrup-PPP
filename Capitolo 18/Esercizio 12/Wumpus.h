#pragma once

#include <vector>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <sstream>

// Stanza
struct Room {
	// Collegamenti con altre stanze
	Room* front{ nullptr };
	Room* rear{ nullptr };
	Room* left{ nullptr };
	Room* right{ nullptr };
	// presenza di mostro, pozzo, pipistrello
	bool wump{ false };
	bool pit{ false };
	bool bat{ false };
	int numero{ 0 };
};

class Wumpus
{
public:
	Wumpus();
	~Wumpus();
	void debug();
	void play();
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
	std::vector<Room*> rooms;
	std::vector<Room*> caverna;
	bool winner, gameover;
	// attori
	Room* wump;
	Room* bat;
	Room* hero;
	// funzioni
	void del_room(Room* r);
	void collega(Room* r);
	void collega_back(Room* r, Room* l);
	Room* scegli_camera(Room* room_da = nullptr); // restituisce un indice dal vettore delle camere
	void sposta_mostro();
};

