#pragma once

#include "../GUI/Graph.h"
#include "../MyClass/Arrow.h"
#include <math.h>

enum Conn_verso {
	Nessuna = 0,
	Up = 1,
	Down = 2
};

class Binary_tree :public Graph_lib::Shape {
public:
	Binary_tree();
	Binary_tree(Point root, int level);
	Binary_tree(Point root, int level, Conn_verso freccia, Graph_lib::Color colore_freccia);
	void draw_lines() const;
	void add_text(string percorso, string testo);
protected:
	int _livello;
	int _size_nodo{ 10 };
	int _margine_nodo{ 5 };
	int _margine_nodo_top{ 50 };
	int potenza(int base, int potenza);
	virtual void disegna_nodo(int& indice, int livello_attuale) const;
private:
	void inizializza(Point root, int level, Conn_verso freccia, Graph_lib::Color colore_freccia);
	void crea_punti(Point& root, int livello_attuale);
	Graph_lib::Color _colore_freccia{ 0 };
	Conn_verso _freccia{ Conn_verso::Nessuna };
	void parametri_freccia(const Point p1, const Point p2, int& lunghezza, int& angolo) const;
	Graph_lib::Vector_ref<Graph_lib::Text> _nomi_nodi;
	void _nomina_nodi() const;
};