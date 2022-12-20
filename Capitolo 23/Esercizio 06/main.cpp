/* Capitolo 23 Esercizio 6
* Scrivi un programma che cerca le date in un file di testo.
* Scrivi ogni linea che contenga almeno una data nel formato linea numero: line.
* Inizia con una espressione regolare di un formato semplice, esempio 12/24/2000,
* testa il programma con questa.
* Poi aggiungi altri formati.
*/

#include <iostream>
#include <regex>
#include <fstream>

int main(int agrc, char** argv) {
	int nLine{ 0 }; // numero di linea
	std::string nFile{ "INBOX" }; // nome del file
	std::regex data_italiana_breve{ R"( \d{1,2}/\d{1,2}/(\d{2}|\d{4}) )" };
	std::regex data_americana_breve{ R"( \d{1,2}-\d{1,2}-(\d{2}|\d{4}) )" };
	std::smatch match_data;
	std::ifstream ftxt{ nFile };
	std::string linea;

	if (!ftxt) return 1;

	for (std::string linea; std::getline(ftxt, linea); ++nLine) {
		if (std::regex_search(linea, match_data, data_italiana_breve)) {
			std::cout << "Data Italiana Breve, Linea\t" << nLine << " - (" << match_data[0] << "):\t" << linea << std::endl;
			std::cout << "########################################################\n";
		}
		if (std::regex_search(linea, match_data, data_americana_breve)) {
			std::cout << "Data Americana Breve, Linea\t" << nLine << " - (" << match_data[0] << "):\t" << linea << std::endl;
			std::cout << "########################################################\n";
		}
	}

	ftxt.close();
	
	return 0;
}