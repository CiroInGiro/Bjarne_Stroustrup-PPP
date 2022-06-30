#include "pulitore.h"
pulitore::pulitore(std::ifstream& ifs) {
	_ifs = &ifs;
}

std::map<std::string, int>* pulitore::get_map() {
	std::string parola{ "" };
	std::string parola_trasformata{ "" };
	while (*_ifs >> parola) {
		for (unsigned int i = 0; i < parola.size(); i++) {
			unsigned char c = parola[i];
			if (isalnum(c)) {
				c = tolower(c);
				parola_trasformata += c;
			}
			if (c == '\'' && (i+1) < parola.size()) {
				if (tolower(parola[(i + 1)]) == 't') {
					// finiamo di leggere e sostituiamo le parole
					i++;
					++(*_parole)["not"];
					if (parola_trasformata == "don") ++(*_parole)["do"];
					else if (parola_trasformata == "ar") ++(*_parole)["are"];
					else ++(*_parole)[parola_trasformata];
					parola_trasformata.clear();
				}
			}
		}
		if (parola_trasformata.size() > 0) {
			if (parola_trasformata[(parola_trasformata.size() - 1)] == 's') {
				std::string temp{ "" };
				// size() restituisce un size_t che è il typedef di un unsigned int e quindi non contiene numeri negativi
				for (int i = 0; i < (int)(parola_trasformata.size() - 2); i++) {
					temp += parola_trasformata[i];
				}
				if (temp.size() > 0) ++(*_parole)[temp];
			} 
			else ++(*_parole)[parola_trasformata]; // nel caso incontriamo una punteggiatura tra due spazi
		}
		parola_trasformata.clear();
	}
	return _parole;
}