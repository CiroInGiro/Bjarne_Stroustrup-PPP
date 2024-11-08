#pragma once

#include <list>
#include <vector>
#include <iostream>
#include "../GUI/std_lib_facilities.h"

using Line = std::vector<char>; // ogni linea è un vettore di caratteri.

template<class Iteratore>
void advance(Iteratore& p, int n) {
	while (n > 0) { ++p; --n; }
}

template<class Iterator>
bool match(Iterator first, Iterator last, const std::string& s) {
	
	if (s.size() == 0) return false; // nessuna stringa da cercare.
	
	//if ((last - first) < s.size()) return false; // la stringa non può essere contenuta nel range.
	
	size_t index{ 0 };

	while (first != last && index < s.size()) {
		if (*first != s[index]) return false; // se un carattere non coincide le stringhe non corrispondono.
		++first; ++index;
	}
	return true; // siamo arrivati alla fine del range col 100% delle corrispondenze.
}

class Text_Iterator {
public:
	typedef forward_iterator_tag iterator_category;
	typedef char* pointer;
	typedef char& reference;
	typedef size_t difference_type;
	typedef char value_type;
	Text_Iterator(std::list<Line>::iterator linea, Line::iterator colonna) : it_linea{ linea }, it_colonna{ colonna } {}
	char& operator*() { return *it_colonna; }
	Text_Iterator& operator++();
	bool operator==(const Text_Iterator& it_destro) const;
	bool operator!=(const Text_Iterator& it_destro) const;
private:
	std::list<Line>::iterator it_linea;
	Line::iterator it_colonna; // iteratore del vettore.
};

class Document
{
public:
	Document() { lines.push_back(Line{}); }
	void erase_line(int n);
	Text_Iterator find_text(Text_Iterator first, Text_Iterator last, const std::string& s);
	Text_Iterator find_and_replace(Text_Iterator first, Text_Iterator last, const std::string& from_text, const std::string& to_text);
	void print();
	int count_chars();
	int count_words_white();
	int count_words_white(const std::string& whites);
	int count_words_alpha();
	friend std::istream& operator>>(std::istream& is, Document& d);
	Text_Iterator begin();
	Text_Iterator end();
private:
	std::list<Line> lines;
};


