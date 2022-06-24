/*
Capitolo 15 Esercizio 11
Cerca le temperature massime di ogni mese dell'anno di 2 o più località e rappresentale assieme.
Come sempre presta attenzione alle etichette, i colori e agli assi.
*/

#include <string>
#include <fstream>
#include <sstream>
#include "../GUI/Simple_window.h"
#include "Bar2Chart.h"

class RecordDati {
public:
	RecordDati() {
		_stato = false;
		_paese = "";
		_provincia = "";
		_mese = "";
		_temperatura = -1000;
	}
	std::string paese() const { return _paese; }
	std::string mese() const { return _mese; }
	double temperatura() const { return _temperatura; }
	operator bool() { return _stato; }
	std::istream& operator<<(std::istream& in) {
		std::string buffer;
		std::getline(in, buffer, '\n');
		if (buffer.length()) {
			std::istringstream iss { buffer };
			std::getline(iss, _paese, ',');
			std::getline(iss, _provincia, ',');
			std::getline(iss, _mese, ',');
			iss >> _temperatura;
			if (_temperatura > -1000) _stato = true;
		}
		return in;
	}
private:
	bool _stato;
	std::string _paese;
	std::string _provincia;
	std::string _mese;
	double _temperatura;
};

int main() {
	//std::array<RecordDati, 12> dati;
	const std::string titolo{ "Capitolo 15 Esercizio 11" };
	const std::string file{ "temperature.txt" };
	RecordDati record;
	Simple_window win(Point{ 0,0 }, 1000, 1000, titolo);
	win.color(Color::white);
	Bar2Chart grafico(Point{ 10, 900 }, 900, 800);
	grafico.set_color(Color::blue);
	grafico.set_label("temperature max nell'anno di due città: Capo Palimuro in rosso e Grazzanise in verde.");

	try {
		std::ifstream ifile(file);
		if (ifile.bad()) throw std::exception("Errore nell'usare il file");
		// Raccolta dati dal file
		int indice1{ 0 };
		int indice2{ 0 };
		while (!ifile.eof()) {
			if (record << ifile) {
				if (record.paese() == "Capo Palimuro") {
					grafico.add_value(record.temperatura(), Graph_lib::Bar2Chart::Serie::y1);
					grafico.set_bar_color(Color::red, indice1, Graph_lib::Bar2Chart::Serie::y1);
					grafico.set_bar_fill_color(Color::red, indice1,Graph_lib::Bar2Chart::Serie::y1);
					std::ostringstream label;
					label << record.temperatura();
					grafico.set_bar_label(label.str(), indice1, Graph_lib::Bar2Chart::Serie::y1);
					label.str("");
					label << record.mese();
					grafico.set_bar_x_label(label.str(), indice1, Graph_lib::Bar2Chart::Serie::y1);
					++indice1;
				}
				else if (record.paese() == "Grazzanise") {
					grafico.add_value(record.temperatura(), Graph_lib::Bar2Chart::Serie::y2);
					grafico.set_bar_color(Color::green, indice2, Graph_lib::Bar2Chart::Serie::y2);
					grafico.set_bar_fill_color(Color::green, indice2, Graph_lib::Bar2Chart::Serie::y2);
					std::ostringstream label;
					label << record.temperatura();
					grafico.set_bar_label(label.str(), indice2, Graph_lib::Bar2Chart::Serie::y2);
					label.str("");
					label << record.mese();
					grafico.set_bar_x_label(label.str(), indice2, Graph_lib::Bar2Chart::Serie::y2);
					++indice2;
				}
			}
		}

		if (ifile.fail()) {
			if (ifile.eof()) ifile.clear();
			if (ifile.bad()) throw std::exception("Errore hardware durante l'utilizzo del file");
		}
		ifile.close();
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