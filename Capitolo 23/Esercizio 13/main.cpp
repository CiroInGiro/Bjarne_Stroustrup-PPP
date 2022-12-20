/* Capitolo 23 esercizio 13
* Il '.' (punto) corrisponde a '\n'?
* Scrivi un programma per scoprirlo.
*/

// Direi che il punto sostituisce ogni carattere nell'espressione ma non il \n

#include <iostream>
#include <regex>
#include <string>
#include <sstream>

int main() try {
	std::string linetest{R"(Inizio rigo
		e vado a capo, poi 
di nuovo. Punto e basta.#)"};
	std::istringstream iss{ linetest };
	std::regex pattern_punto{ R"(\.)" };
	std::regex pattern_qualsiasi{ R"(.)" };
	std::regex pattern_compresoinvio{ R"((Inizio rigo)(.))" };
	std::regex pattern_invio{ R"((\n))" };
	int lineno{ 0 };
	
	for (std::string line; getline(iss, line, '#'); ++lineno) {
		std::smatch match;
		if (std::regex_search(line, match, pattern_invio)) {
			std::cout << "Invio " << lineno << " (" << match[0] << "): " << line << std::endl;
		} else
		if (std::regex_search(line, match, pattern_compresoinvio)) {
			std::cout << "Linea con invio " << lineno << " (" << match[0] << "): " << line << std::endl;
		}
		else if (std::regex_search(line, match, pattern_punto)) {
			std::cout << "Linea " << lineno << " (" << match[0] << "): " << line << std::endl;
		}
		else if (std::regex_search(line, match, pattern_qualsiasi)) {
			std::cout << "Linea " << lineno << " (" << match[0] << "): " << line << std::endl;
		}
	}
}
catch (...) {
	exit(1);
}