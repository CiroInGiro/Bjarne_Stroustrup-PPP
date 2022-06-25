#include "Link.h"

Link* Link::insert(Link* l) {
	if (l == nullptr) return nullptr;
	if (prec) {
		prec->succ = l;
	}
	l->prec = prec;
	prec = l;
	l->succ = this;
	return l;
}

Link* Link::add(Link* l) {
	if (l == nullptr) return nullptr;
	if (succ) succ->prec = l;
	l->succ = succ;
	succ = l;
	l->prec = this;
	return l;
}

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

Link* Link::next() const { return succ; }
Link* Link::prev() const { return prec; }

Link* Link::erase() {
	Link* retVal{ nullptr };
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

Link::~Link() {
	if (prec) delete begin();
	else if (succ) {
		succ->prec = nullptr;
		delete succ;
		succ = nullptr;
	}
}

Link* Link::begin() {
	Link* retVal = this;
	while (retVal->prev()) retVal = retVal->prev();
	return retVal;
}

Link* Link::end() {
	Link* retVal = this;
	while (retVal->next()) retVal = retVal->next();
	return retVal;
}

std::string Link::name() const { return godname.name; }
std::string Link::mythology() const { return godname.mythology; }
std::string Link::vehicle() const { return godname.vehicle; }
std::string Link::weapon() const { return godname.weapon; }

Link* Link::add_ordered(Link* l) {
	if (!l) return nullptr;
	Link* lista = this;
	if (lista->name() == l->name()) return lista->insert(l);
	if (lista->name() > l->name()) {
		while (lista->prev() && lista->name() > l->name()) {
			lista = lista->prev();
		}
		//return lista->insert(l);
	}
	if (lista->name() < l->name()) {
		while (lista->next() && lista->name() < l->name()) {
			lista = lista->next();
		}
		//return lista->add(l);
	}
	if (lista->name() > l->name()) return lista->insert(l); else return lista->add(l);
}