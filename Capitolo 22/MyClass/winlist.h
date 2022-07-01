#pragma once
#include "..\GUI\Graph.h"
#include "..\GUI\Window.h"
#include <vector>

// Gli Shape non gestiscono i segnali che non ci servono
class winlist: public Graph_lib::Shape
{
public:
	winlist(Point xy, int width, int height, const std::string& label);
	// azioni sulle pagine
	void precedente();
	void successivo();
	// creazione righe
	void set_dati(std::vector<std::string>& v); // voglio muovere il contenuto tra i vettori
	// funzioni Shape
	void draw_lines() const override;
	void move(int dx, int dy) override;
	~winlist() override;
private:
	// titolo widget
	Graph_lib::Text* titolo;
	// Area del widget
	int width{ 0 };
	int height{ 0 };
	// dati delle linee
	std::vector<std::string> dati;
	// lista delle linee
	std::vector<Graph_lib::Text*> linee; // non avendo il costruttore di copia per Text
	// dimensioni
	const int _field_height{ 20 };
	const int _margin_height{ 5 };
	// gestione pagine
	int _linee_x_pagina{ 0 };
	int _pagine{ 0 };
	int _pagina_corrente{ 0 };
	// indici corrisponti nel vettore
	int _riga_start{ 0 };
	int _riga_stop{ 0 };
};

