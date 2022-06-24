/*
Capitolo 15 Esercizio 9
Prendi un altro campioni di altezze dal web (1 pollice = 2,54 cm) escludendo tanta spazzatura o chiedi le altezze ai tuoi amici.
Usa il programma dall'esercizio precedente, potresti anche usare le etichette dai dati in lettura in modo da riutilizzare il codice.
Adatta la scala ai nuovi valori.
*/

#include "../GUI/Simple_window.h"
#include "../MyClass/BarChart.h"
#include <iostream>
#include <fstream>
#include <sstream>


class RecordData {
public:
	RecordData() {
		// ci interessa Italy
		_country = "";
		_ISO = "";
		// Men e Women
		_sex = "";
		// ci interessano gli anni dal 1976
		_year = 0;
		// ci interessa solo _height
		_height = 0;
		_low_height = 0;
		_high_height = 0;
	}
	std::string country() const { return _country; }
	std::string iso() const { return _ISO; }
	std::string sex() const { return _sex; }
	int year() const { return _year; }
	double height() const { return _height; }
	double lo_height() const { return _low_height; }
	double hi_height() const { return _high_height; }
	operator bool() const { return _lettura; }
	const std::ifstream& operator<<(std::ifstream& ifs) {
		_lettura = false;
		char delimitatore{ ' ' };
		std::getline(ifs, _country, ',');
		std::getline(ifs, _ISO, ',');
		std::getline(ifs, _sex, ',');
		ifs >> _year;
		ifs >> delimitatore;
		if (delimitatore != ',' && !ifs.eof()) throw exception("file non conforme, non trovo l'altezza media.", delimitatore);
		ifs >> _height;
		ifs >> delimitatore;
		if (delimitatore != ',' && !ifs.eof()) throw exception("file non conforme, non trovo l'altezza al di sotto del 95%", delimitatore);
		ifs >> _low_height;
		ifs >> delimitatore;
		if (delimitatore != ',' && !ifs.eof()) throw exception("file non conforme, non trovo l'altezza al di sopra del 95%", delimitatore);
		ifs >> _high_height;
		ifs.get(delimitatore);
		if (delimitatore != '\n' && !ifs.eof()) throw exception("file non conforme: record eccede in lunghezza.", delimitatore);
		//ifs.unget();
		if (!ifs.eof()) _lettura = true;
		return ifs;
	}
private:
	string _country;
	string _ISO;
	string _sex;
	int _year;
	double _height;
	double _low_height;
	double _high_height;
	bool _lettura{ false };
};



int main() {
	const string titolo{ "Capitolo 15 Esercizio 9" };
	Simple_window win(Point{ 0,0 }, 800, 800, titolo);
	win.color(Color::white);
	string head{ "" };
	RecordData record;
	BarChart grafico(Point{ 10, 750 }, 750, 700, 10);
	grafico.set_color(Color::blue);
	grafico.set_label("Altezze medie uomini in Italia dal '76 all'80:");
	try {
		std::ifstream filedati("NCD_RisC_eLife_2016_height_age18_countries.csv");
		if (!filedati.good()) throw exception("Errore nel trovare il file di dati");
		std::getline(filedati, head);
		int indice{ 0 };
		std::ostringstream etichetta;
		while (!filedati.eof()) {
			if (record << filedati) {
				if (record.country() == "Italy"
					&& record.sex() == "Men"
					&& (record.year() >= 1976 && record.year() <= 1980)) {
					grafico.set_bar_color(Color::dark_red, indice);
					grafico.set_bar_fill_color(Color::dark_green, indice);
					etichetta << record.height();
					grafico.set_bar_label(etichetta.str(), indice);
					etichetta.str("");
					etichetta << record.year();
					grafico.set_bar_x_label(etichetta.str(), indice);
					etichetta.str("");
					grafico.set_value(record.height(), indice);
					++indice;
				}
			}
			else break;
		}
		if (filedati.fail()) {
			if (filedati.bad()) throw exception("Problemi hardware sul file dati");
			if (!filedati.eof()) throw exception("Problema sconosciuto col file dati");
			else filedati.clear();
		}
		filedati.close();
		win.attach(grafico);
		win.wait_for_button();
	}
	catch (exception e) {
		std::cout << "Errore: " << e.what() << std::endl;
	}
	catch (...) {
		std::cout << "Errore non gestito" << std::endl;
	}
}