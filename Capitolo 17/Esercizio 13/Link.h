#pragma once

#include <iostream>

struct God {
	std::string name;
	std::string mythology;
	std::string vehicle;
	std::string weapon;
};

class Link {
public:
	Link(const std::string& n, const std::string& m, const std::string& v, const std::string& w) :godname{ n, m, v, w } {}
	Link* insert(Link* l); // aggiunge prima dell'elemento corrente
	Link* add(Link* l); // aggiunge dopo l'elemento corrente
	Link* find(const std::string& s);
	Link* next() const;
	Link* prev() const;
	Link* erase();
	~Link();
	Link* begin();
	Link* end();
	std::string name() const;
	std::string mythology() const;
	std::string vehicle() const;
	std::string weapon() const;
	Link* add_ordered(Link* l);
private:
	God godname;
	Link* succ{ nullptr };
	Link* prec{ nullptr };
};