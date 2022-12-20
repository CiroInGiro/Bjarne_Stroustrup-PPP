/* Capitolo 23 Esercizio 11
* Modifica il programma di controllo tabella dal paragrafo 23.9 per vedere se i numeri degli studenti aumenta o diminuisce negli anni in questione.
*/

#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <regex>
#include <exception>
#include <sstream>

int to_int(const std::string& s) {
	std::istringstream is{ s };
	int retVal{ 0 };
	is >> retVal;
	return retVal;
}

// Creiamo una nuova tabella con una nuova colonna che indica la variazione sul precedente anno

int main(int argc, char** argv) {
	std::map<int, int> alunni; // <anno, numero di alunni>
	std::ifstream ifile{ "table.txt" };
	std::regex row;
	std::string line;
	std::smatch match;

	try {
		if (!ifile) {
			std::cout << "Errore file di input.";
			exit(1);
		}
		// modifico la pattern per ricavare l'anno numerico
		row = R"(^(\d+)([\w ]+)(\t\d+)(\t\d+)(\t\d+)$)";
		// gestione righe da ordinare nella mappa
		while (!ifile.eof()) {
			std::getline(ifile, line);
			if (std::regex_match(line, match, row)) alunni[to_int(match[1])] += to_int(match[5]);
		}
		// output righe dalla mappa
		int prec = alunni.begin()->second;
		for (auto p : alunni) {
			std::cout << "Anno: " << p.first << "\tTotale: " << p.second << ";\tVariazione su anno precedente: " << (p.second - prec) << std::endl;
			prec = p.second;
		}

		// gestione file e chiusura
		if (ifile.fail()) {
			if (ifile.bad()) {
				std::cerr << "\n\n\nErrore grave nella lettura del file...\n\n\n";
				exit(1);
			}
			if (ifile.eof()) ifile.setstate(std::ios_base::goodbit, true);
		}

		ifile.close();
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