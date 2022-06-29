/*
Capitolo 20 Esercizio 16
Definisci un ovector che è simile a pvector tranne per gli operatori [] e * che restituiscono una referenza ad un oggetto puntatore ad un elemento invece del puntatore.
*/

#include <vector>
#include <iostream>

template<typename T>
// requires T()
class ovector {
public:
	typedef unsigned long size_type;
	class iterator {
	public:
		iterator(T** i) {
			piterator = i;
		}
		T& operator*() { return (**piterator); }
		const T& operator*() const { return (**piterator); }
		iterator operator++() { ++piterator; return *this; }
		iterator operator--() { --piterator; return *this; }
		friend bool operator==(ovector<T>::iterator& l, ovector<T>::iterator& r) { return l.piterator == r.piterator; }
		friend bool operator!=(ovector<T>::iterator& l, ovector<T>::iterator& r) { return !(l == r); }
	private:
		T** piterator;
	};

	ovector() : mem() {}
	explicit ovector(size_type qty) : mem(qty) {
		for (size_type i = 0; i < mem.size(); ++i) { mem[i] = nullptr; }
	}
	~ovector() {
		for (T* p : mem) if (p) delete p;
	}
	iterator begin() { return iterator(&mem[0]); }
	iterator end() { return iterator((&mem[0] + mem.size())); }
	void push_back(const T& val) {
		mem.push_back(new T{ val });
	}
	T back() { return *(mem.back()); }
	T& operator[](size_type i) { return *mem[i]; }

	// così per tutte le altre funzioni, esternamente vedo un vettore di valori  ma in realtà sto gestendo un vettore di puntatori allo stesso tipo
private:
	std::vector<T*> mem;
};

int main(int argc, char** argv) {
	ovector<double> pv;
	pv.push_back(8.9);
	pv.push_back(40.34);
	for (double d : pv) std::cout << "New record: " << d << std::endl;
	std::cout << std::endl << std::endl;
	std::cout << "Elemento 2: " << pv[1] << std::endl;
	return 0;
}