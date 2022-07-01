#pragma once

#include "../GUI/Graph.h"
#include "RecordGrafo.h"
#include "../MyClass/Arrow.h"

// Nome del linguaggio racchiuso in un cerchio
class Grafo : public Graph_lib::Shape
{
public:
	Grafo(Point posizione, int diametro, RecordGrafo& rg);
	//void add_antenato(Grafo& g);
	//std::vector<Graph_lib::Arrow*>::iterator antenati_begin();
	//std::vector<Graph_lib::Arrow*>::iterator antenati_end();
	RecordGrafo& getRecord();
	const RecordGrafo& getRecord() const;
	~Grafo() override;
	void draw_lines() const override;
	void move(int dx, int dy) override;
	void move_to(int x, int y);
	Grafo(const Grafo&) = delete;
	Grafo& operator=(const Grafo&) = delete;
	friend bool operator<(const Grafo& left, const Grafo& right);
	Point getPos();
private:
	Point _posizione; // di default 0, 0
	int _diametro{ 0 };
	RecordGrafo _record; // costruttore di default presente
	Graph_lib::Circle* _cerchio;
	Graph_lib::Text* _testo;
	// Potrei avere la lista di puntatori antenati e successori
	// controllare la validità dei puntatori e cancellare quelli non più validi ad ogni utilizzo
	// creare i collegamenti tra antenati e me e avvisare i successori quando cambio posizione.
	//std::vector<Grafo*> _antenati;
	
	// Non si edita il disegno quindi ho un elenco freccie dagli antenati a me 
	// e ricreo le freccie ad ogni inserimento dati nello schema, più rozzo.
	// std::vector<Graph_lib::Arrow*> _collegamenti; // Alla fine ho deciso di gestire le Arrow dalla finestra in modo da disporre tutti gli elementi grafici da un posto solo.
};

