#pragma once

#include "../GUI/Window.h"
#include "../GUI/Point.h"
#include <string>
#include <set>
#include <map>
#include "RecordGrafo.h"
#include "Grafo.h"
#include <sstream>

// siccome deferenziando gli iteratori di set ci troviamo indirizzi di memoria usiamo una funzione less che confronta gli oggetti puntati e non gli indirizzi.
class lessGrafoPtr {
public:
	bool operator()(const Grafo* left, const Grafo* right) const {
		//if (left->getRecord().getLinguaggio() == right->getRecord().getLinguaggio()) return (left->getRecord().getAnno() < right->getRecord().getAnno());
		if (left->getRecord().getAnno() == right->getRecord().getAnno()) return (left->getRecord().getLinguaggio() < right->getRecord().getLinguaggio());
		return (left->getRecord().getAnno() < right->getRecord().getAnno());
	}
};

class WinLinguaggi : public Graph_lib::Window
{
public:
	WinLinguaggi(Point posizione, int width, int height, const std::string& titolo);
	~WinLinguaggi() override;
	// aggiungiamo un nuovo RecordGrafo, crea e aggiunge un Grafo nel vettore _linguaggi
	void add(RecordGrafo& rg);
	Point find_pos(const std::string& linguaggio);
	// disegna la freccia tra 2 punti
	void collega(Point start, Point end);
	// dispone i Grafi e li collega, quindi dobbiamo poter:
	// posizionare un grafo
	// comandarlo di crearsi i collegamenti agli antenati
	// avere una funzione di ordinamento dei grafi
	void disponi();
private:
	// una lista di shape di RecordGrafo e la funzione di ordinamento che prende due puntatori ad essi
	std::set<Grafo*, lessGrafoPtr> _grafi;
	// contiamo le occorrenze dello stesso anno (sarebbe il numero di grafi sull'asse y in quel punto x
	std::map<int, int> _occorrenze; // anno, occorrenze
	std::vector<Graph_lib::Arrow*> _collegamenti;
	// aggiungere le etichette degli anni in fondo alla finestra
	std::vector<Graph_lib::Text*> _etichette;
	// parametri grafici
	int _diametro{ 70 };
	int _margine{ 5 };
};

