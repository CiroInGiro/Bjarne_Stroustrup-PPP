#pragma once

#include <fstream>
#include <vector>
#include <string>

class RecordGrafo
{
public:
	// Costruttore di default
	RecordGrafo();
	// Costruttore di copia
	RecordGrafo(RecordGrafo&);
	// Costruttore per spostamento
	RecordGrafo(RecordGrafo&&);
	// inserimento dati del record
	void put(std::string linguaggio, int anno, std::vector<std::string>& antenati);
	// prelievo dei dati
	std::string getLinguaggio();
	const std::string getLinguaggio() const;
	int getAnno();
	const int getAnno() const;
	std::vector<std::string> getAntenati();
	const std::vector<std::string> getAntenati() const;
	// interagire con vettore antenati
	std::vector<std::string>::iterator getBegin_antenati() { return _antenati.begin(); }
	std::vector<std::string>::iterator getEnd_antenati() { return _antenati.end(); }


	// Reset dati
	void reset();

	// Operatore copia
	void operator=(const RecordGrafo&);

	// controllo validità del record
	operator bool();

	// operatore di input da filestream
	friend std::ifstream& operator>>(std::ifstream& ifs, RecordGrafo& rg);
private:
	std::string _linguaggio{ "" };
	int _anno{ 0 };
	std::vector<std::string> _antenati;
};

