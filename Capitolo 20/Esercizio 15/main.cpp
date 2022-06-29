/*
Capitolo 20 Esercizio 15
Definisci un pvector che sia simile a vector di puntatori eccetto per il fatto che 
contiene puntatori a oggetti e il distruttore cancella ogni oggetto.
*/

#include <vector>
#include <iostream>

template<typename T>
// requires T()
class pvector {
public:
	typedef unsigned long size_type;
	class iterator {
	public:
		iterator(T** i) {
			piterator = i;
		}
		T operator*() { return **piterator; }
		const T operator*() const { return **piterator; }
		iterator operator++() { ++piterator; return *this; }
		iterator operator--() { --piterator; return *this; }
		friend bool operator==(pvector<T>::iterator& l, pvector<T>::iterator& r) { return l.piterator == r.piterator; }
		friend bool operator!=(pvector<T>::iterator& l, pvector<T>::iterator& r) { return !(l == r); }
	private:
		T** piterator;
	};

	pvector() : mem() {}
	explicit pvector(size_type qty) : mem(qty) {
		for (size_type i = 0; i < mem.size(); ++i) { mem[i] = nullptr; }
	}
	~pvector() {
		for (T* p : mem) if (p) delete p;
	}
	iterator begin() { return iterator(&mem[0]); }
	iterator end() { return iterator((&mem[0]+mem.size())); }
	void push_back(const T& val) {
		mem.push_back(new T{ val });
	}
	T back() { return *(mem.back()); }
	// così per tutte le altre funzioni, esternamente vedo un vettore di valori  ma in realtà sto gestendo un vettore di puntatori allo stesso tipo
private:
	std::vector<T*> mem;
};

int main(int argc, char** argv) {
	pvector<double> pv;
	pv.push_back(8.9);
	pv.push_back(40.34);
	for (double d : pv) std::cout << "New record: " << d << std::endl;
	return 0;
}