#include "SLink.h"

SLink* SLink::insert(SLink* l) {
	if (l == nullptr) return nullptr;
	l->succ = this;
	return l;
}

SLink* SLink::add(SLink* l) {
	if (!l) return nullptr;
	l->succ = succ;
	succ = l;
	// siccome la lista si muove solo in avanti per non perdere la testa della lista restituisco questo elemento perché l aggiunto è andato avanti a questo.
	return this;
}

SLink* SLink::find(const std::string& s) {
	if (name() == s) return this;
	SLink* p = succ;
	while (p) {
		if (p->name() == s) return p;
		p = p->succ;
	}
	return nullptr;
}

SLink* SLink::next() const { return succ; }

SLink* SLink::erase() {
	SLink* retVal{ nullptr };
	if (succ) {
		retVal = succ;
	}
	succ = nullptr;
	return retVal;
}

SLink::~SLink() {
	if (succ) {
		delete succ;
		succ = nullptr;
	}
}

SLink* SLink::end() {
	SLink* retVal = this;
	while (retVal->next()) retVal = retVal->next();
	return retVal;
}

std::string SLink::name() const { return godname.name; }
std::string SLink::mythology() const { return godname.mythology; }
std::string SLink::vehicle() const { return godname.vehicle; }
std::string SLink::weapon() const { return godname.weapon; }

SLink* SLink::add_ordered(SLink* l) {
	if (!l) return nullptr;
	SLink* lista = this;
	if (lista->name() == l->name()) return lista->insert(l);
	else if (lista->name() > l->name()) return lista->insert(l);
	else if (lista->name() < l->name()) {
		while (lista->next() && lista->next()->name() < l->name()) {
			lista = lista->next();
		}
		lista->add(l);
		return this;
	}
}
