/*
Capitolo 21 esercizio 8
Prendi l'esempio parole-frequenza dal paragrafo 21.6.1 e modificalo per stampare le sue linee in ordine di frequenza (invece di lessico-logico).
Un esempio di linea potrebbe essere: 3: C++ invece di: C++: 3 .-
*/

/*
Potrei creare un map<string, int> per avere la frequenza in base alla parola che è la chiave;
Dovrei poi riversare la mappa in un multimap<int, string> dove la frequenza è la chiave che viene mantenuta in ordine e la parola (ormai uniche) sono il valore.
Mi resta solo stampare la multimap.
Ma visto che non serve l'ordinamento per stringa potrei anche creare una struttura e memorizzare il tutto in un vettore, ordinarlo poi secondo la frequenza o partire da un map_unordered
Alla fine la soluzione più veloce credo sia utilizzare comunque la mappa ordinata anche per le parole perché ad ogni aggiornamento ci sarà una ricerca della chiave che risulterà più veloce se ilcontenitore è ordinato.
*/

#include <iostream>
#include <fstream>
#include <unordered_map>
#include <map>

int main(int argc, char** argv) {
	std::ifstream ifs("Equazione della retta.txt");
	if (!ifs) return 1;
	//std::unordered_map<std::string, int> parole;
	std::map<std::string, int> parole;
	std::string s{ "" };
	while (ifs >> s) ++parole[s];
	ifs.close();
	std::multimap<int, std::string> frequenze;
	for (auto p : parole) frequenze.insert({ p.second, p.first });
	for (auto f : frequenze) {
		std::cout << f.first << ": " << f.second << ";\n";
	}
	return 0;
}