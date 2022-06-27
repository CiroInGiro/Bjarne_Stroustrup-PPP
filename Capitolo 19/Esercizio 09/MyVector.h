#pragma once

#include "MyAllocator.h"

template<class T, class A = std::allocator<T>>
//requires (Element<T>(),	Allocator<A>())
class MyVector {
	/*
	requires Number<T>()
	Invariant:
	if 0<=n<=sz elem[n] è l'ennessimo elemento
	sz <= space
	Se sz < space allora c'è ancora space-sz spazio dopo elem[sz-1]
	*/
	int sz;
	int space;
	T* elem;
	A alloc;
public:
	MyVector() : sz{ 0 }, space{ 0 }, elem{ nullptr } {} // default costructor
	explicit MyVector(int n) : sz{ n }, space{ n }, elem{ alloc.allocate(n) } {
		for (int i = 0; i < n; ++i) {
			//elem[i] = T();
			alloc.construct(&elem[i], T());
		}
	}
	// copy costructor
	MyVector(const MyVector<T>& v) {
		//elem = new T[v.size()];
		elem = alloc.allocate(v.size());
		for (int i = 0; i < v.size(); ++i) {
			//elem[i] = v[i];
			alloc.construct(&elem[i], v[i]);
		}
		sz = space = v.size();
	}
	// copy assignement
	MyVector<T>& operator=(const MyVector<T>& v) {
		if (this == v) return *v; // auto assegnazione, lavoro inutile
		if (v.size() <= space) {
			// spazio sufficiente
			for (int i = 0; i < v.size(); ++i) {
				alloc.construct(&elem[i], v[i]);
			}
			sz = v.size();
			return *this;
		}
		T* p = alloc.allocate(v.size());
		for (int i = 0; i < v.size(); ++i) {
			alloc.construct(&p[i], v[i]);
		}
		for (int i = 0; i < sz; ++i) alloc.destroy(&elem[i]);
		alloc.deallocate(elem, space);
		sz = space = v.size();
		elem = p;
		return *this;
	}
	// move costructor
	MyVector(MyVector<T>&& v) {
		this = v;
		v.resize(0);
	}
	// move assignement
	MyVector<T>& operator=(MyVector<T>&& v) {
		this = v;
		v.resize(0);
		return this;
	}
	// distruttore
	~MyVector() {
		//delete[] elem;
#pragma warning(suppress : 4996)
		alloc.destroy(elem);
	}
	T& operator[](int n) {
		if (n < 0) throw;
		if (n >= sz) throw;
		return elem[n];
	} // access, ritorna un riferimento all'ennesinmo elemento
	const T& operator[](int n) const {
		if (n < 0) throw;
		if (n >= sz) throw;
		return elem[n];
	}
	int size() const { return sz; }
	int capacity() const { return space; }
	// ridimensiona il vettore solo per dimensioni crescenti
	void resize(int newsize, T val = T()) {
		if (newsize < 0) return;
		reserve(newsize);
		for (int i = sz; i < newsize; ++i) {
			//elem[i] = val; // inizializzazione al valore di default
#pragma warning(suppress : 4996)
			alloc.construct(&elem[i], val);
		}
		for (int i = newsize; i < sz; ++i) alloc.destroy(&elem[i]);
		sz = newsize;
	}
	void push_back(T dato) {
		if (space == 0) reserve(8);
		else if (sz == space) reserve(space * 2);
		//elem[sz] = dato;
#pragma warning(suppress : 4996)
		alloc.construct(&elem[sz], dato);
		++sz;
	}
	void reserve(int newalloc) {
		if (newalloc <= space) return;
		//T* p = new T[newalloc];
		T* p = alloc.allocate(newalloc);
		for (int i = 0; i < sz; ++i) {
			//p[i] = elem[i];
// #pragma warning(suppress : 4996) serve a togliere il warning del compilatore visto che è deprecato chiamare direttamente construct
#pragma warning(suppress : 4996)
			alloc.construct(&p[i], elem[i]);
		}
		//delete[] elem;
		alloc.deallocate(elem, space);
		elem = p;
		space = newalloc;
	}
};


