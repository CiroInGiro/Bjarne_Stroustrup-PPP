#pragma once

#include "Point.h"
#include "../GUI/GUI.h"
#include "../GUI/Window.h"
#include <iostream>
#include <sstream>
#include <vector>

using namespace Graph_lib;

// Finestra con interprete dell'input stream che permette di disegnare.
class Lavagna : public Window
{
private:
	// struttura che aggiunge l'id per ogni shape creato.
	struct Disegno {
		std::string name;
		Graph_lib::Shape* pshape{ nullptr };
		unsigned int id{ 0 };
		friend std::ostream& operator<<(std::ostream& os, Lavagna::Disegno& disegno);
	};
public:
	Lavagna(Point xy, int w, int h, const std::string& t) : Window(xy, w, h, t) {
		running = true;
		p_ostream = nullptr;
	}
	// avvio applicazione, restituisce l'exit code
	int run(); // non multithread quindi alterna il disegno della finestra all'input dello stream.
	friend std::istream& operator>>(std::istream& is, Lavagna& lavagna);
	friend std::ostream& operator<<(std::ostream& os, Lavagna& lavagna);
	friend std::ostream& operator<<(std::ostream& os, Lavagna::Disegno& disegno);
private:
	static unsigned int uid; // ogni shape creato avrà un id per identificarlo in seguito per comandare modifiche o cancellazione.
	Color colore{ Color::black };
	bool running;
	std::vector<Disegno> disegni;
	std::ostream* p_ostream;
	// costruttore di funzioni
	void chiamata(const std::string& comando, const std::string& parametri);
	void print() const; // stampa le info dei disegni sulla lavagna.
	void print_guida() const;
};
