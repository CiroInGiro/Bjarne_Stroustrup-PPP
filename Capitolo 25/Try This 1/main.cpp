#include "../GUI/Graph.h"

void poor(Graph_lib::Shape* p, int sz) // poor interface design
{
	for (int i = 0; i < sz; ++i) p[i].draw();
}

// adattato con un vettore di puntatori visto che circle non ha il costruttore di copia
void f(Graph_lib::Shape* q, vector<Graph_lib::Circle>& s0) // very bad code
{
	using namespace Graph_lib;
	Graph_lib::Polygon s1[10];
	Shape s2[10];
	// Inizialize
	Shape* p1 = new Graph_lib::Rectangle{ Point{0,0}, Point{10,20} };
	poor(&s0[0], s0.size());	// #1 (pass the array from the vector)
	// #1 passiamo il primo elemento dell'array ma se il vettore cambia il suo pool interno cambierà l'indirizzo di partenza
	poor(s1, 10);				// #2
	// #2 lavoriamo su un array di poligoni della giusta dimensione ma sono inizializzati? NO

	poor(s2, 20);				// #3
	// #3 lavoriamo su un array di shape ma fuori range
	poor(p1, 1);				// #4
	// #4 passiamo il puntatore a un rectangle allocato nell'heap
	delete p1;
	p1 = 0;
	poor(p1, 1);				// #5
	// #5 utilizzo di un puntatore nullo
	poor(q, INT_MAX);				// #6
	// passiamo un puntatore sconosciuto ad un array di dimensione sconosciuta
}

int main() {
	Graph_lib::Shape* main_q = new Graph_lib::Shape[3]();
	vector<Graph_lib::Circle> main_s0;
	Graph_lib::Circle* c1 = new Graph_lib::Circle(Point{ 50, 50 }, 20);
	Graph_lib::Circle* c2 = new Graph_lib::Circle(Point{ 50, 100 }, 50);
	Graph_lib::Circle c3(Point{ 50, 200 }, 30);
	//main_s0.push_back(c1);
	//main_s0.push_back(c2);
	main_s0.push_back(c3);

	// chiamo f che farà casini
	f(main_q, main_s0);
	return 0;
}