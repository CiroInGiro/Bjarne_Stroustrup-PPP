/* Capitolo 23 esercizio 7
* Scrivi un programma simile ad uno di queli tra gli esercizi precedenti, per cercare i numeri di carte di credito, in un file.
* Fai una piccola ricerca sui formati dei numeri delle carte di credito realmente utilizzati.
*/

/* NUMERI DI CARTE DI CREDITO: da 13 a 16 cifre.
* Cifra 1:
* 5 = Mastercard
* 4 = Visa
* 3 = American Express e Diners Club
* Cifra 2-6: Identificazione Banca
* Cifra 7-12 o 15: Numero di Conto
* Ultima Cifra: Numero di Controllo
*/

#include <fstream>
#include <iostream>
#include <string>
#include <regex>

int main(int argc, char* argv[]) {
	std::string nFile{ "INBOX" };
	std::regex mastercard, visa, diners;
	std::smatch card_match;
	std::ifstream ifile{ nFile };

	if (!ifile) {
		std::cerr << "\n\n\nErrore nell'aprire il file...\n\n\n";
		exit(1);
	}

	try {
		mastercard = R"( 5\d{12,15} )";
		visa = R"( 4\d{12,15} )";
		diners = R"( 3\d{12,15} )";
	}
	catch (std::regex_error) {
		std::cerr << "\n\n\nErrore nelle regole di expressione regoalre...\n\n\n";
		exit(2);
	}

	std::string line;
	int nline{ 0 };

	while (std::getline(ifile, line)) {
		++nline;
		if (std::regex_search(line, card_match, mastercard)) {
			std::cout << "MasterCard in linea " << nline << ":\t" << card_match[0] << std::endl;
		}
		if (std::regex_search(line, card_match, visa)) {
			std::cout << "VISA in linea " << nline << ":\t" << card_match[0] << std::endl;
		}
		if (std::regex_search(line, card_match, diners)) {
			std::cout << "A.Express o Diners in linea " << nline << ":\t" << card_match[0] << std::endl;
		}
	}

	// controllo stato file
	if (ifile.fail()) {
		if (ifile.bad()) {
			std::cerr << "\n\n\nFile corrotto...\n\n\n";
			exit(2);
		}
		if (ifile.eof()) ifile.setstate(std::fstream::goodbit);
	}
	ifile.close();

	return 0;
}