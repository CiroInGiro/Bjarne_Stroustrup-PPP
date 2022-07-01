#include "../MyClass/Link.h"

/*
template<class T> Link<T>* Link<T>::insert(Link<T>* l) {
	if (l == nullptr) return nullptr;
	if (prec) {
		prec->succ = l;
	}
	l->prec = prec;
	prec = l;
	l->succ = this;
	return l;
}
*/

/*
template<class T> 
Link<T>* Link<T>::add(Link* l) {
	if (l == nullptr) return nullptr;
	if (succ) succ->prec = l;
	l->succ = succ;
	succ = l;
	l->prec = this;
	return l;
}
*/

/*
Link* Link::find(const std::string& s) {
	if (name() == s) return this;
	Link* p = succ;
	while (p) {
		if (p->name() == s) return p;
		p = p->succ;
	}
	p = prec;
	while (p) {
		if (p->name() == s) return p;
		p = p->prec;
	}
	return nullptr;
}
*/

//template<class T> Link<T>* Link<T>::next() const { return succ; }

//template<class T> Link<T>* Link<T>::prev() const { return prec; }

template<class T>
Link<T>* Link<T>::erase() {
	Link<T>* retVal{ nullptr };
	if (succ) {
		succ->prec = prec;
		retVal = succ;
	}
	if (prec) {
		prec->succ = succ;
		if (!retVal) retVal = prec;
	}
	succ = nullptr;
	prec = nullptr;
	return retVal;
}

template<class T>
Link<T>::~Link<T>() {
	if (prec) delete begin();
	else if (succ) {
		succ->prec = nullptr;
		delete succ;
		succ = nullptr;
		delete obj;
		obj = nullptr;
	}
}

/*
template<class T>
Link<T>* Link<T>::begin() {
	Link<T>* retVal = this;
	while (retVal->prev()) retVal = retVal->prev();
	return retVal;
}
*/

template<class T>
Link<T>* Link<T>::end() {
	Link<T>* retVal = this;
	while (retVal->next()) retVal = retVal->next();
	return retVal;
}

//std::string Link::name() const { return godname.name; }
//std::string Link::mythology() const { return godname.mythology; }
//std::string Link::vehicle() const { return godname.vehicle; }
//std::string Link::weapon() const { return godname.weapon; }

/*
template<class T>
T* Link<T>::get() {
	return obj;
}
*/

template<class T>
void Link<T>::set(T* o) { obj = o; }

/*
template <class T>
Link<T>* Link<T>::add_ordered(Link<T>* l) {
	if (!l) return nullptr;
	Link<T>* lista = this;
	if (lista->get() == l->get()) return lista->insert(l);
	if (lista->get() > l->get()) {
		while (lista->prev() && lista->get() > l->get()) {
			lista = lista->prev();
		}
	}
	if (lista->get() < l->get()) {
		while (lista->next() && lista->get() < l->get()) {
			lista = lista->next();
		}
	}
	if (lista->get() > l->get()) return lista->insert(l); else return lista->add(l);
}
*/