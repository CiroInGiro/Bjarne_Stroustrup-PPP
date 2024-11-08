#include "Document.h"

void Document::erase_line(int n) {
	if (n < 0 || n >= (lines.size() - 1)) return; // fuori dal range di linee presenti.
	std::list<Line>::iterator p = lines.begin(); // partiamo dall'inizio della lista
	//std::advance(p, n); // avanziamo nella lista per n posizioni
	advance(p, n); // propria funzione di avanzamento.
	lines.erase(p); // cancelliamo la riga dalla lista
}

Text_Iterator Document::find_text(Text_Iterator first, Text_Iterator last, const std::string& s) {
	
	if (s.size() == 0) return last; // nulla da cercare
	
	char first_char = s[0]; // il primo carattere con cui iniziare la ricerca
	
	while (true) {
		Text_Iterator p = std::find(first, last, first_char); // cerchiamo un possibile punto nel range in cui inizia la stringa da cercare.
	
		if (p == last || match(p, last, s)) return p; // se siamo alla fine o dal punto di inizio i caratteri successivi formano la stringa cercata ritorna.
		
		first = ++p; // in caso di fallimento impostiamo l'inizio del range in cui cercare al prossimo carattere.
	}
}

Text_Iterator Document::find_and_replace(Text_Iterator first, Text_Iterator last, const std::string& from_text, const std::string& to_text) {
	Text_Iterator p = find_text(first, last, from_text);
	
	if (p == last) return p;

	//first = p;

//	while (first != last) { // aggiungo lo scorrimento di tutto il documento
		int counter{ 0 };

		if (from_text.size() <= to_text.size()) counter = from_text.size(); else counter = to_text.size();

		std::string::const_iterator si = to_text.begin();

		// sostituisco la stringa trovata
		for (Text_Iterator pos = p; counter > 0; --counter) {
			*p = *si;
			++p;
			++si;
		}

		if (from_text.size() > to_text.size()) {
			// cancella il numero di caratteri pari alla differenza

		}

		if (from_text.size() < to_text.size()) {
			// inserisci la restante stringa qui

		}

//		p = find_text(first, last, from_text);
//		first = p; // avanzamento di first a dopo l'ultimo riscontro
//	} // ciclo while

	return p;
}

void Document::print() {
	for (Text_Iterator p = begin(); p != end(); ++p) { std::cout << *p; }
}

int Document::count_chars() {
	int retVal{ 0 };
	
	for (std::list<Line>::iterator p = lines.begin(); p != lines.end(); ++p) { retVal += (*p).size(); }

	return retVal;
}

int Document::count_words_white() {
	int retVal{ 0 };
	Text_Iterator t = begin();
	std::string parola{ "" };

	while (t != end()) {
		// Bug: char non può essere negativo ma tra 0 e 255
		unsigned char test = (unsigned char)*t;
		if (std::isalnum(test)) parola += *t;
		else if (parola.size() > 0) {
			++retVal;
			parola = "";
		}
		++t;
	}

	// Bug: nel caso si completa la ricerca e non si termina con uno spazio, retVal non sarà incrementato.
	if (parola.size()) ++retVal;
	
	return retVal;
}

int Document::count_words_white(const std::string& whites) {
	int retVal{ 0 };
	Text_Iterator t = begin();
	std::string parola{ "" };
	bool whitespace{ false };

	while (t != end()) {
		for (const char c : whites) {
			if (c == *t) {
				// con questo confronto salto più caratteri bianchi di seguito
				if (parola.size() > 0) {
					++retVal;
					parola = "";
					whitespace = true;
					break;
				}
			}
		}

		if (!whitespace) parola += *t;
		else whitespace = false;
	
		++t;
	}

	// Bug: nel caso si completa la ricerca e non si termina con uno spazio, retVal non sarà incrementato.
	if (parola.size()) ++retVal;

	return retVal;
}

int Document::count_words_alpha() {
	int retVal{ 0 };
	std::string parola{ "" };
	Text_Iterator t = begin();

	while (t != end()) {
		
		// Bug: char non può essere negativo ma tra 0 e 255
		unsigned char test = (unsigned char)*t;
		
		if (std::isalpha(test)) parola += *t;
		else if (parola.size() > 0) {
			++retVal;
			parola = "";
		}

		++t;
	}

	// Bug: nel caso si completa la ricerca e non si termina con uno spazio, retVal non sarà incrementato.
	if (parola.size()) ++retVal;

	return retVal;
}

std::istream& operator>>(std::istream& is, Document& d) {
	
	for (char ch; is.get(ch);) {
		d.lines.back().push_back(ch); // inserische il carattere alla fine del documento.
		if (ch == '\n') d.lines.push_back(Line{}); // se incontriamo un invio aggiungiamo una nuova linea.
	}
	
	if (d.lines.back().size()) d.lines.push_back(Line{}); // se l'ultima linea è utilizzata allora ne aggiungiamo una vuota per chiudere il documento.

	return is;
}

Text_Iterator& Text_Iterator::operator++() {
	++it_colonna; // prossimo carattere

	if (it_colonna == (*it_linea).end()) {
		++it_linea; // se siamo alla fine della riga avanza di una riga e
		it_colonna = (*it_linea).begin(); // assegna il primo carattere della nuova riga.
	}

	return *this; // ritorna l'iteratore aggiornato.
}

bool Text_Iterator::operator==(const Text_Iterator& it_destro) const {
	return (it_linea == it_destro.it_linea && it_colonna == it_destro.it_colonna);
}

bool Text_Iterator::operator!=(const Text_Iterator& it_destro) const { return !(*this == it_destro); }

Text_Iterator Document::begin() {
	// ritorno un iteratore costruito con l'iteratore alla prima riga nella lista e l'iteratore al primo carattere di quella prima riga.
	return Text_Iterator(lines.begin(), (*lines.begin()).begin());
}

Text_Iterator Document::end() {
	// restituisco la posizione dopo l'ultimo carattere dell'ultima riga.
	std::list<Line>::iterator ultimo = lines.end();
	--ultimo; // sappiamo che il documento ha sempre almeno una linea vuota.
	return Text_Iterator(ultimo, (*ultimo).end()); // ritorniamo la fine della linea.
}
