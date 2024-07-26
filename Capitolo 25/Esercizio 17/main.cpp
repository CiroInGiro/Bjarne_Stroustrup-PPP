/*
* In §25.4.3–4 abbiamo fornito una classe Array_ref dichiarata per rendere l'accesso agli elementi di un array più semplice e sicuro.
* In particolare, abbiamo affermato di gestire correttamente l'ereditarietà.
* Prova diversi modi per trasformare un Rectangle* in un vector<Circle*> utilizzando un Array_ref<Shape*> ma nessun cast o altre operazioni che implicano comportamenti indefiniti.
* Questo dovrebbe essere impossibile.
*/

#include<vector>
#include "../GUI/Graph.h"
#include <limits>

// Array_ref
template<class T>
class Array_ref {
public:
	Array_ref(T* pp, int s) : p{ pp }, sz{ s } { }
	
	T& operator[](int i) { return p[i]; }
	const T& operator[](int i) const { return p[i]; }

	// Operatore di conversione tipo
	template<class Q>
	operator const Array_ref<const Q>() {
		// controllo implicito della conversione dell'elemento
		static_cast<Q>(*static_cast<T*>(nullptr));
		// conversione
		return Array_ref<const Q>{reinterpret_cast<Q*>(p, sz)};
	}

	bool assign(Array_ref<T> a) {
		//if (sz != a.sz) return false;
		if (sz != a.size()) return false;

		for (int i = 0; i < sz; ++i) {
			p[i] = a[i];
		}
		return true;
	}

	void reset(T* pp, int s) {
		p = pp;
		sz = s;
	}

	void reset(Array_ref<T> a) {
		//reset(a.p; a.sz);
		reset(a.get_p(), a.size());
	}

	int size() const { return sz; }

	const T* p() const { return p; }

	// versione modificabile
	T* get_p() const { return p; }

	// copy construct
	// nessuna gestione di risorse
	// semantica di riferimento

// per accedere a questi dati con assign e reset bisognerà creare una interfaccia ad essi
private:
	T* p;
	int sz;
};

// Facility
template<class T>
Array_ref<T> make_ref(T* pp, int s) {
	return (pp) ? Array_ref<T>(pp, s) : Array_ref<T>(nullptr, 0);
}

template<class T>
Array_ref<T> make_ref(std::vector<T> v) {
	return (v.size()) ? Array_ref(&v[0], v.size()) : Array_ref(nullptr, 0);
}

template<class T, int s>
Array_ref<T> make_ref(T(&pp)[s]) {
	return Array_ref<T>(pp, s);
}

// TEST
void better(Array_ref<Graph_lib::Shape> a) {
	for (int i = 0; i < a.size(); ++i) a[i].draw();
}

// come better() ma prende un Array_ref con un puntatore
void better2(const Array_ref<Graph_lib::Shape* const> a) {
	for (int i = 0; i < a.size(); ++i) if (a[i]) a[i]->draw();
}

void f(Graph_lib::Shape* q, std::vector<Graph_lib::Circle>& s0) {
	using namespace Graph_lib;
	
	Polygon s1[10];
	Shape s2[20];

	// inizializzazione
	Shape* p1 = new Rectangle{ Point{0,0}, Point{10,20} };
	better(make_ref(s0)); // errore: Array_ref<Shape> è richiesto
	better(make_ref(s1)); // errore: Array_ref<Shape> è richiesto
	better(make_ref(s2)); // OK: s2 è un array di Shape
	better(make_ref(p1, 1)); // OK: 1 elemento Shape
	delete p1;
	p1 = 0;
	better(make_ref(p1, 1)); // OK: make_ref crea un referenza con 0 elementi perché p1 non è valido
	better(make_ref(q, numeric_limits<int>::max())); // OK se con max non si eccede negli indirizzi a partire da q
}

// versione di f() che utilizza i puntatori e la conversione tra puntatori in Array_ref
void f2(Graph_lib::Shape* q, std::vector<Graph_lib::Circle*>& s0) {
	using namespace Graph_lib;

	Polygon* s1[10];
	Shape* s2[20];

	// inizializzazione
	Shape* p1 = new Rectangle{ Point{0,0}, Point{10,20} };
	better2(make_ref(s0)); // OK: better2() vuole un Array_ref<Shape* const> e in Array_ref c'è l'operatore di conversione
	better2(make_ref(s1)); // OK: conversione da Polygon* a Shape* const
	better2(make_ref(s2)); // OK: s2 è un array di Shape*
	better2(make_ref(p1, 1)); // KO: make_ref restituisce un Array_ref<Shape> e non un Array_ref<Shape* const>
	better2(make_ref(q, numeric_limits<int>::max())); // KO: anche qui ci serve un Array_ref<Shape* const> e non di <Shape>
}

// trasformare un Rectangle* in un vector<Circle*> utilizzando un Array_ref<Shape*>
/* Gli elementi Rectangle* possono essere convertiti in Shape*
* ma poi non possiamo convertirli di nuovo in Circle*
* Ne tanto meno possimao convertire direttamente un Rectangle* in Circle*
*/

Array_ref<Graph_lib::Circle*> f3(std::vector<Graph_lib::Rectangle*> rec) {
	using namespace Graph_lib;

	// il cast implicito non funziona da una classe base alla sua derivata, solo il contrario
	Rectangle* rettangolo = new Rectangle{ Point{0, 0 }, Point{ 10, 10 } };
	Shape* figura = rettangolo;
	Circle* cerchio = figura;

	// anche passando per un puntatore indefinito non è implicito definirlo in altro tipo.
	void* r = new Rectangle{ Point{0, 0 }, Point{ 10, 10 } };
	Circle* c = r;

	// make_ref restituisce lo stesso tipo passato e anche la funzione membro assign lavora con il suo stesso tipo
	Array_ref<Rectangle> shapes = make_ref(rettangolo, 1);

}

int main(int argc, char** argv) {

	return 0;
}