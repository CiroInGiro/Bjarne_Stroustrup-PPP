/*
Capitolo 20 Esercizio 17
Definisci un ownership_vector che memorizza puntatori a oggetti tipo pvector
ma provvede un meccanismo per l'utente di decidere di quali oggetti sono raggruppati dal vettore
(esempio, quali oggetti saranno cancellati dal distruttore).
Suggerimento: Questo esercizio sarebbe semplice se fossi stato attento al capitolo 13.
*/

#include <vector>
#include <iostream>

// qui voglio memorizzare puntatori, quindi oggetti creati dall'utente e con due funzioni l'utente potrà memorizzare lasciando o meno la responsabilità di distruggere gli oggetti a questa classe
// anche se potrei creare un secondo vettore con l'elenco dei puntatori da distruggere ho creato uns truttura che contiene un flag per ognuno di essi
// una bool in più dovrebbe far risparmiare spazio rispetto ad un long int
template<typename T>
// requires T()
class ownership_vector {
public:
	typedef unsigned long size_type;
	struct powned {
		bool owned;
		T p;
		powned() : owned{ false }, p{ T() } {}
		// operatori
		friend bool operator==(const powned& l, const powned& r) { return l.p == r.p; }
		friend bool operator!=(const powned& l, const powned& r) { return !(l == r); }
	};
	class iterator {
	public:
		iterator(powned* i) {
			piterator = i;
		}
		T operator*() { return piterator->p; }
		const T operator*() const { return piterator->p; }
		iterator operator++() { ++piterator; return *this; }
		iterator operator--() { --piterator; return *this; }
		friend bool operator==(ownership_vector<T>::iterator& l, ownership_vector<T>::iterator& r) { return l.piterator == r.piterator; }
		friend bool operator!=(ownership_vector<T>::iterator& l, ownership_vector<T>::iterator& r) { return !(l == r); }
	private:
		powned* piterator;
	};

	ownership_vector() : mem() {}
	explicit ownership_vector(size_type qty) : mem(qty) {}
	~ownership_vector() {
		for (powned p : mem) if (p.owned && p.p) delete p.p;
	}
	iterator begin() { return iterator(&mem[0]); }
	iterator end() { return iterator(&mem[0]+mem.size()); }
	void push_back(const T& val) {
		powned o;
		o.owned = false;
		o.p = val;
		mem.push_back(o);
	}
	void push_back_owned(const T& val) {
		powned o;
		o.owned = true;
		o.p = val;
		mem.push_back(o);
	}
	T back() { return (mem.back().p); }
	T operator[](size_type i) { return mem[i].p; }
	// etc...
private:
	std::vector<powned> mem;
};

void f(double* p) {
	ownership_vector<double*> pv;
	pv.push_back(p);
	pv.push_back_owned(new double{ 40.34 });
	for (double* d : pv) std::cout << "New record: " << *d << std::endl;
	std::cout << std::endl << std::endl;
	std::cout << "Elemento 2: " << *pv[1] << std::endl;
}

int main(int argc, char** argv) {
	double* myp = new double{ 8.9 };
	f(myp);
	std::cout << "ownership_vector dead, myp is " << *myp << std::endl;
	delete myp;
	return 0;
}