#include "Grafo.h"

Grafo::Grafo(Point posizione, int diametro, RecordGrafo& rg) {
	_posizione = posizione;
	_diametro = diametro;
	_record = rg;
	_cerchio = new Graph_lib::Circle(posizione, (diametro / 2));
	Point posTesto{ (posizione.x - (diametro / 2)), (posizione.y + 5) };
	_testo = new Graph_lib::Text(posTesto, rg.getLinguaggio());
	_cerchio->set_color(Graph_lib::Color::blue);
	_testo->set_color(Graph_lib::Color::black);
}

RecordGrafo& Grafo::getRecord() { return _record; }

const RecordGrafo& Grafo::getRecord() const { return _record; }

Grafo::~Grafo() {
	if (_cerchio) delete _cerchio;
	if (_testo) delete _testo;
	//_collegamenti.clear(); // chiamate ai distruttori a catena
}

void Grafo::draw_lines() const {
	if (_cerchio) _cerchio->draw_lines();
	if (_testo) _testo->draw_lines();
}

void Grafo::move(int dx, int dy) {
	_posizione = Point((_posizione.x + dx), (_posizione.y + dy));
	if (_cerchio) _cerchio->move(dx, dy);
	if (_testo) _testo->move(dx, dy);
}

void Grafo::move_to(int x, int y) {
	move((x - _posizione.x), (y - _posizione.y));
	//_posizione = Point(x, y);
}

bool operator<(const Grafo& left, const Grafo& right) {
//	if (left.getRecord().getLinguaggio() == right.getRecord().getLinguaggio()) return (left.getRecord().getAnno() < right.getRecord().getAnno());
	if (left.getRecord().getAnno() == right.getRecord().getAnno()) return (left.getRecord().getLinguaggio() < right.getRecord().getLinguaggio());
	return (left.getRecord().getAnno() < right.getRecord().getAnno());
}

Point Grafo::getPos() { return _posizione; }
