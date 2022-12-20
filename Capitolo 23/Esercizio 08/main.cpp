/* Capitolo 23 esercizio 8
* Modifica il programma del paragrafo 23.8.7 in modo che prenda in input una pattern e un nome di file.
* In uscita dovrebbe rappresentare i numeri di linea: la linea corrispondente alla pattern.
* Se non ci sono corrispondenze non dovrebbe mandare niente in output.
*/

#include <fstream>
#include <iostream>
#include <string>
#include <regex>

int main(int argc, char* argv[]) {
	std::string nFile;
	std::string pattern;
	std::regex espressione;
	std::smatch matched;
	std::ifstream ifile{ "" };

	std::cout << "Ho bisogno del nome del file da leggere: " << std::endl;
	while (!ifile) {
		std::cout << "File? ";
		std::cin >> nFile;
		ifile.open(nFile, std::ios_base::in);
	 }

	if (!ifile.good()) {
		std::cerr << "\n\n\nErrore nell'aprire il file...\n\n\n";
		exit(1);
	}

	std::cout << "Ora ho bisogno di una pattern per le ricerche: ";
	std::cin.ignore(1, '\n');
	std::getline(std::cin, pattern);

	try {
		espressione = pattern;
	}
	catch (std::regex_error) {
		std::cerr << "\n\n\nErrore nelle regole di expressione regoalre...\n\n\n";
		exit(2);
	}

	std::string line;
	int nline{ 0 };

	while (std::getline(ifile, line)) {
		++nline;
		if (std::regex_search(line, matched, espressione)) {
			std::cout << "Linea " << nline << " (" << matched[0] << "):\t" << line << std::endl;
		}
	}

	// controllo stato file
	if (!ifile) {
		if (ifile.bad()) {
			std::cerr << "\n\n\nFile corrotto...\n\n\n";
			exit(2);
		}
		if (ifile.fail() && !ifile.eof()) {
			std::cerr << "\n\n\nErrore di lettura nel file...\n\n\n";
			exit(3);
		}
	}
	ifile.close();

	return 0;
}