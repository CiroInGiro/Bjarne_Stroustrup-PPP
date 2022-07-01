#include "RecordGrafo.h"

RecordGrafo::RecordGrafo() {
	_linguaggio = "";
	_anno = 0;
}

RecordGrafo::RecordGrafo(RecordGrafo& rg) {
	_linguaggio = rg.getLinguaggio();
	_anno = rg.getAnno();
	_antenati = rg.getAntenati();
}

RecordGrafo::RecordGrafo(RecordGrafo&& rg) {
	_linguaggio = rg.getLinguaggio();
	_anno = rg.getAnno();
	_antenati = rg.getAntenati();
}

void RecordGrafo::put(std::string linguaggio, int anno, std::vector<std::string>& antenati) {
	_linguaggio = linguaggio;
	_anno = anno;
	_antenati = antenati;
}

std::string RecordGrafo::getLinguaggio() {
	return _linguaggio;
}

const std::string RecordGrafo::getLinguaggio() const {
	return _linguaggio;
}

int RecordGrafo::getAnno() {
	return _anno;
}

const int RecordGrafo::getAnno() const {
	return _anno;
}

std::vector<std::string> RecordGrafo::getAntenati() { return _antenati; }
const std::vector<std::string> RecordGrafo::getAntenati() const {
	return _antenati;
}

void RecordGrafo::reset() {
	_linguaggio = "";
	_anno = 0;
	_antenati.clear();
}

void RecordGrafo::operator=(const RecordGrafo& rg) {
	_linguaggio = rg._linguaggio;
	_anno = rg._anno;
	_antenati = rg._antenati;
}

RecordGrafo::operator bool() {
	if (_linguaggio != "" && _anno > 0) return true;
	return false;
}

std::ifstream& operator>>(std::ifstream& ifs, RecordGrafo& rg) {
	char parentesi{ ' ' }, virgola{ ' ' };
	std::string buffLinguaggio{ "" };
	int buffAnno{ 0 };
	std::string buffAntenato{ "" };
	std::vector<std::string> buffAntenati;
	
	// lettura linguaggio
	ifs >> parentesi;
	if (parentesi != '(') return ifs;
	while (ifs.get(virgola) && virgola != ',') {
		buffLinguaggio += virgola;
	}
	if (virgola != ',') return ifs; 
	if (ifs.peek() == ' ') {
		while (ifs.get() == ' ');
		ifs.unget();
	}
	// lettura anno
	virgola = ' ';
	parentesi = ' ';
	ifs >> buffAnno >> virgola >> parentesi;
	if (virgola != ',' || parentesi != '(') return ifs;
	if (ifs.peek() == ' ') {
		while (ifs.get() == ' ');
		ifs.unget();
	}
	// lettura antenati
	virgola = ' ';
	parentesi = ' ';
	while (parentesi != ')') {
		while (ifs.get(virgola) && virgola != ',' && virgola != ')') {
			buffAntenato += virgola;
		}
		if (virgola != ',' && virgola != ')') return ifs;
		if (ifs.peek() == ' ') {
			while (ifs.get() == ' ');
			ifs.unget();
		}
		if (buffAntenato != "") buffAntenati.push_back(buffAntenato);
		buffAntenato = "";
		if (virgola == ')') parentesi = virgola;
		virgola = ' ';
	}
	rg.put(buffLinguaggio, buffAnno, buffAntenati);
	return ifs;
}