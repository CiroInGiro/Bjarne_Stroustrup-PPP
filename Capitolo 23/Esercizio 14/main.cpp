/* Capitolo 23 Esercizio 14
* Scrivi un programma come quello del paragrafo 23.8.7 che può essere usato per sperimentare le pattern matching digitado delle pattern.
* Comunque, letto un file in memoria (rappresentando l'interruzione di nuova linea col carattere '\n'), in modo che possa sperimentare modeli di interruzioni.
* Testalo e documenta una dozzina di pattern.
*/

/*
* 1. pattern ".*" corrisponde all'intera riga
* 2. pattern ".*." il punto finale non corrisponderà al carattere speciale \n (carrier return)
* 3. pattern "\n" cerca la riga che contiene solo carrier return ma deve essere aggiunto perché di default getline ha come separatore proprio questo carattere.
* 4. pattern "\\n" cerca i caratteri scritti nella stringa '\' e 'n' e non il carrier return
* 5. pattern "int" non trova nessuna riga perché regex_match cerca una riga esattamente corrispondente alla pattern
* 6. pattern "int+.*" non trova nulla se aggiungiamo carrier return il punto salta i carrier return
* 7. pattern ".+main.*\n" trova la riga del main
* 8. pattern "int main() {" solleva eccezione perché interpreta la parentesi graffa come comando di contatore
* 9. pattern "\t.*\n" trova tutte le linee rientrate
* 10. pattern ".*\}.*\n" trova tutte le righe che hanno una parentesi graffa chiusa
* 11. pattern ".*".*\n" tutte le righe che hanno apici
* 12. pattern "^\}" se fosse regex_search tutte le righe che iniziano con una parentesi graffa
*/

/* Capitolo 23 Esercizio 15
* Descrivi una pattern che non può essere una espressione regolare.
*/

// con i carateri speciali copriamo tutti i simboli e col prefisso '\' possiamo utilizzare come caratteri da ricercare anche gli stessi caratteri speciali, quindi non saprei.

#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <vector>

int main() {
	std::ifstream ifs{ "file.txt" };
	std::vector<std::string> linee;
	if (!ifs) exit(1);

	for (std::string linea; std::getline(ifs, linea);) {
		linea += "\\a";
		linea += "\n";
		linee.push_back(linea);
	}

	ifs.close();

	try {
		std::cout << "Pattern? ";
		for (std::string pat; std::getline(std::cin, pat);) {
			std::regex pattern{ pat };
			std::smatch match;
			int Nlinea{ 0 };
			for (auto p : linee) {
				++Nlinea;
				if (std::regex_search(p, match, pattern)) {
					std::cout << "Linea " << Nlinea << ": " << p << std::endl;
					for (size_t i = 1; i < match.size(); ++i) {
						std::cout << "Match " << i << ": " << match[i] << std::endl;
					}
				}
			}
			std::cout << std::endl << "nuova pattern: ";
		}
	}
	catch (std::regex_error e) {
		std::cerr << "\n\n\nRegex error: " << e.what() << std::endl;
	}
	catch (...) {
		std::cerr << "\n\n\nErrore non gestito." << std::endl;
	}

	return 0;
}