#pragma once

template<class T>
class Link {
public:
	//Link(const std::string& n, const std::string& m, const std::string& v, const std::string& w) :godname{ n, m, v, w } {}
	Link(T* o) : obj{ o } {}
	//Link<T>* insert(Link<T>* l); // aggiunge prima dell'elemento corrente
	Link<T>* insert(Link<T>* l) {
		if (l == nullptr) return nullptr;
		if (prec) {
			prec->succ = l;
		}
		l->prec = prec;
		prec = l;
		l->succ = this;
		return l;
	}
	//Link* add(Link* l); // aggiunge dopo l'elemento corrente
	Link<T>* add(Link<T>* l) {
		if (l == nullptr) return nullptr;
		if (succ) succ->prec = l;
		l->succ = succ;
		succ = l;
		l->prec = this;
		return l;
	}
	//Link* find(const std::string& s);
	//Link<T>* next() const;
	Link<T>* next() const { return succ; }
	//Link* prev() const;
	Link<T>* prev() const { return prec; }
	Link* erase();
	~Link();
	//Link* begin();
	Link<T>* begin() {
		Link<T>* retVal = this;
		while (retVal->prev()) retVal = retVal->prev();
		return retVal;
	}
	Link* end();
	//std::string name() const;
	//std::string mythology() const;
	//std::string vehicle() const;
	//std::string weapon() const;
	//Link<T>* add_ordered(Link<T>* l);
	Link<T>* add_ordered(Link<T>* l) {
		if (!l) return nullptr;
		Link<T>* lista = this;
		if (*lista->get() == *l->get()) return lista->insert(l);
		if (*lista->get() > *l->get()) {
			while (lista->prev() && *lista->get() > *l->get()) {
				lista = lista->prev();
			}
		}
		if (*lista->get() < *l->get()) {
			while (lista->next() && *lista->get() < *l->get()) {
				lista = lista->next();
			}
		}
		if (*lista->get() > *l->get()) return lista->insert(l); else return lista->add(l);
	}
	//T* get();
	T* get() { return obj; }
	void set(T*);
private:
	T* obj;
	Link* succ{ nullptr };
	Link* prec{ nullptr };
};