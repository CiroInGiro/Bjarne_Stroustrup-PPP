/* Capitolo 23 Esercizio 9
* Utilizzando eof() (Appendice B.7.2), è possibile determinare quale linea della tabella è l'ultima.
* Usa questo (provaci) a semplificare il controllo tabella del paragrafo 23.9.
* Assicurati di testare il programma con file che finiscono con linee vuote dopo la tabella e con file che non hanno una nuova linea dopo.
*/

#include <fstream>
#include <iostream>
#include <string>
#include <regex>
#include "../GUI/std_lib_facilities.h"

using namespace std;

int main()
{
	ifstream in{ "table.txt" }; // input file
	if (!in) {
		error("no input file\n");
		exit(3);
	}

	string line; // input buffer
	int lineno = 0;

	try {
		//regex header{ R"(^[\w ]+(           [\w ]+)*$)" }; // header line
		regex header_tab{ R"(^[\w ]+(\t[\w ]+)*$)"};
		//regex row{ R"(^[\w ]+(              \d+)(  \d+)(   \d+)$)" }; // data line
		regex row_tab{ R"(^[\w ]+(\t\d+)(\t\d+)(\t\d+)$)" };

		if (getline(in, line)) { // check header line
			smatch matches;
			if (!regex_match(line, matches, header_tab))
				error("no header");
			std::cout << "Header: " << matches[0] << std::endl;
		}
		// invece di avere un ciclo ogni lettura leggiamo fino alla fine del file
		smatch last_match;
		std::string last_line;
		//while (getline(in, line)) { // check data line
		while (!in.eof()) {
			getline(in, line);
			++lineno;
			smatch matches;
			if (regex_match(line, matches, row_tab))
			{
				last_line = line;
				// se c'è una riga la stampi (in modo che anche righe vuote tra i record saltano ma non bloccano la lettura del file
				std::cout << "Riga " << lineno << ": " << matches[0] << std::endl;
			}
			else std::cout << "\nRiga Vuota\n";
			if (in.eof()) std::cout << "\nFine File...\n";
		}
		if (in.eof()) {
			if (lineno == 0)
				error("nessuna riga trovata: ");
			else {
				// operazioni su ultima riga contenuta in last_match
				std::regex_match(last_line, last_match, row_tab);
				std::cout << "Ultima riga valida: " << last_match[0] << std::endl;
			}
		}
	}
	catch (runtime_error re) {
		std::cout << "Runtime Error: " << re.what() << std::endl;
		exit(1);
	}
	catch (regex_error re) {
		std::cerr << "Regex Error: " << re.what() << std::endl;
		exit(2);
	}

	std::cout << "\n\n\nLette " << lineno << " righe\n";

	return 0;
}