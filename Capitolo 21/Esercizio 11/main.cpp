/*
Capitolo 21 Esercizio 11
Provvedi una interfaccia grafica per l'inserimento degli ordini all'esercizio precedente.
*/

#include "OrdiniGUI.h"
#include <fstream>

// stampa gli ordini contenuti in un file
void stampa_ordini(std::ifstream& ifs) {
	if (!ifs) throw Logger("Errore file ordini da stampare.");
	Order buff;
	while (ifs >> buff) {
		if (ifs.eof()) return;
		std::cout << buff << std::endl << std::endl;
	}
}

int main(int argc, char** argv) {
	std::ofstream ofs{ "Ordini.txt" };
	if (!ofs) return 1;
	Order myorder;
	InserimentoOrdini win(Point{ 300, 10 }, 800, 600, "Inserimento Ordini", myorder);
	//Fl::run();
	win.go();
	if (!myorder) return 2;
	ofs << myorder;
	ofs.close();

	// stampa dell'ordine acquisito
	std::ifstream ifs{ "Ordini.txt" };
	if (!ifs) return 3;
	stampa_ordini(ifs);
	ifs.close();
	return 0;
}