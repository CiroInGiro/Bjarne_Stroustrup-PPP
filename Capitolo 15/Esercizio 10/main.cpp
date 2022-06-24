/*
Capitolo 15 Esercizio 10
Che tipo di dati non sono adatti per un grafico a linee o a barre.
trova un esempio e trova il modo di visualizzarlo, ad esempio una serie di punti etichettati.
*/

// Tracciato record: 2020.06.29	2020.06.29	2020.06.29 15:50:01:967		Global Service 3000	X	Ciro	Carburante PANDA.	-20.00
// creiamo un grafico dell'andamento della mia tasca nel 2020 raggruppato per mese.
// ci sono altri record nel file che il programma dovrà scartare.

// GRAFICO: voglio creare un grafico che
// sull'asse x rappresenta i mesi dell'anno
// sull'asse y rappresenta l'ammontare
// il dato sarà rappresentato da un cerchio pieno del diametro proprorzionale alla giacenza media nel mese così da indicare più di un dato nello stesso grafico.

#include <iostream>
#include <fstream>
#include <sstream>
#include "StainChart.h"
#include <array>
#include "../GUI/Simple_window.h"

class DataMovimento {
public:
	DataMovimento() :_anno{ 2000 }, _mese{ 1 }, _giorno{ 1 } {}
	int anno() const { return _anno; }
	int mese() const { return _mese; }
	int giorno() const { return _giorno; }
	void anno(int a) {
		_anno = a;
	}
	void mese(int m) {
		if (m <= 12 && m > 0) _mese = m;
		else throw std::exception("Il mese deve essere compreso tra 1 e 12");
	}
	void giorno(int g) {
		if (g > 0 && g <= 31) _giorno = g;
		else throw std::exception("giorno impossibile");
	}
private:
	int _anno;
	int _mese;
	int _giorno;
};

class RecordMovimento {
public:
	RecordMovimento() :_data(), _descrizione{ "" }, _conto{ "" }, _note{ "" }, _ammontare{ 0.0 } {};
	int anno() const { return _data.anno(); }
	int mese() const { return _data.mese(); }
	int giorno() const { return _data.giorno(); }
	double ammontare() const { return _ammontare; }
	operator bool() const {
		if (_conto != "") return true;
		return false;
	}
	std::istream& operator<<(std::istream& in) {
		// leggo la data
		int anno{ 0 }, mese{ 0 }, giorno{ 0 };
		char p1{ ' ' }, p2{ ' ' };
		std::string escludi;
		in >> anno;
		if (anno == 0) {
			//std::getline(in, escludi);
			return in;
		}
		in >> p1 >> mese >> p2 >> giorno;
		if (anno == 0 || mese == 0 || giorno == 0 && (p1 != '.' && p2 != '.')) return in;
		_data.anno(anno);
		_data.mese(mese);
		_data.giorno(giorno);
		// escludi tab della data
		std::getline(in, escludi, '\t');
		// escludi data tassa
		std::getline(in, escludi, '\t');
		// escludi data inserimento
		std::getline(in, escludi, '\t');
		// escludi check id
		std::getline(in, escludi, '\t');
		// prendi descrizione
		std::getline(in, _descrizione, '\t');
		// escludi lo stato
		std::getline(in, escludi, '\t');
		// prendi il conto
		std::getline(in, _conto, '\t');
		// note
		std::getline(in, _note, '\t');
		in >> _ammontare;
		if (in.fail()) _conto = "";
		return in;
	}
private:
	DataMovimento _data;
	// data tassa
	// data inserimento
	// check number
	std::string _descrizione;
	// status
	std::string _conto;
	std::string _note;
	double _ammontare;
	std::string buffer;
};

struct RecordDati {
	double somma{ 0 };
	int count{ 0 };
};

int main(int argc, char** argv) {
	std::array<RecordDati, 12> dati;
	const std::string titolo{ "Capitolo 15 Esercizio 10" };
	const std::string file{ "Ciro.txt" };
	RecordMovimento record;
	Simple_window win(Point{ 0,0 }, 1000, 1000, titolo);
	win.color(Color::white);
	StainChart grafico(Point{ 100, 500 }, 700, 700);
	grafico.set_color(Color::blue);
	grafico.set_label_x("Mesi");
	grafico.set_label_y("Saldo");

	try {
		std::ifstream ifile(file);
		if (ifile.bad()) throw std::exception("Errore nell'usare il file");
		// cerchiamo dove iniziano i record di movimenti
		while (!ifile.eof()) {
			std::string line;
			std::getline(ifile, line);
			if (line.find("#Date") != std::string::npos) {
				break;
			}
		}
		// Raccolta dati dal file
		while (!ifile.eof()) {
			std::string line;
			std::getline(ifile, line);
			std::istringstream in{ line };
			if (record << in && record.anno() == 2020) {
				++dati[(record.mese() - 1)].count;
				dati[(record.mese() - 1)].somma += record.ammontare();
			}
		}
		
		if (ifile.fail()) {
			if (ifile.eof()) ifile.clear();
			if (ifile.bad()) throw std::exception("Errore hardware durante l'utilizzo del file");
		}
		ifile.close();
		// aggiunta dei dati al grafico
		int mese{ 1 };
		for (RecordDati dato : dati) {
			double media = dato.somma / dato.count;
			grafico.set_value(mese, dato.somma, media);
			++mese;
		}
		grafico.calcola();
		win.attach(grafico);
		win.wait_for_button();
	}
	catch (std::exception e) {
		std::cout << "\nErrore: " << e.what() << std::endl;
	}
	catch (...) {
		std::cout << "\nEccezione non gestita\n";
	}
	return 0;
}