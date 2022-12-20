/* Capitolo 23 Esercizio 10
* Modifica il programma di controllo tabella del paragrafo 23.9 per scrivere una nuova tabella
* dove le righe sono con gli stessi numeri iniziali (indicano l'anno: il primo grado inizia con 1) raggruppati.
*/

#include <iostream>
#include <string>
#include <fstream>
#include <map> // utiliziamo una multimap per tenere ordinate le righe dello stesso grado
#include <regex>
#include <exception>

int main(int argc, char** argv) {
	std::multimap<std::string, std::string> new_table;
	std::ifstream ifile{ "table.txt" };
	std::ofstream ofile{ "new_table.txt" };
	std::regex head, row;
	std::string line;
	std::smatch match;

	try {
		if (!ifile) {
			std::cout << "Errore file di input.";
			exit(1);
		}
		if (!ofile) {
			std::cout << "Errore file di output.";
			exit(1);
		}
		head = R"(^([\w ]+)(\t[\w ]+)*$)";
		row = R"(^([\w ]+)(\t\d+)(\t\d+)(\t\d+)$)";
		if (!getline(ifile, line)) {
			std::cerr << "\n\n\nErrore nel leggere header dal file\n\n\n";
			exit(2);
		}
		if (!std::regex_match(line, match, head)) {
			std::cerr << "\n\n\nRecord Header errato...\n\n\n";
			exit(3);
		}
		ofile << line << std::endl;
		// gestione righe da ordinare nella mappa
		std::string key, val;
		while (!ifile.eof()) {
			std::getline(ifile, line);
			if (std::regex_match(line, match, row)) {
				if (key != "" && val != "") {
					new_table.insert(std::make_pair(key, val));
				}
			key = match[1].str();
			val = match[0].str();
			}
		}
		// output righe dalla mappa
		for (auto p : new_table) {
			ofile << p.second << std::endl;
		}
		// gestione ultima riga
		ofile << val;
		
		// gestione file e chiusura
		if (ifile.fail()) {
			if (ifile.bad()) {
				std::cerr << "\n\n\nErrore grave nella lettura del file...\n\n\n";
				exit(1);
			}
			if (ifile.eof()) ifile.setstate(std::ios_base::goodbit, true);
		}
		ifile.close();
		if (ofile.fail()) {
			if (ofile.bad()) {
				std::cerr << "\n\n\nErrore grave nella scrittura del file...\n\n\n";
				exit(1);
			}
			if (ofile.eof()) ofile.setstate(std::ios_base::goodbit, true);
		}
		ofile.close();
	}
	catch (std::regex_error e) {
		std::cerr << "\n\n\nErrore nell'espressione regolare " << e.what() << std::endl;
	}
	catch (...) {
		std::cerr << "\n\n\nErrore non gestito...\n\n\n";
		exit(1);
	}

	return 0;
}