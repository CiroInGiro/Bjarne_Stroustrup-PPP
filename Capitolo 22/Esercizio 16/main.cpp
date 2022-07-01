/* 
Capitolo 22 Esercizio 16
Modificare il programma dell'esercizio precedente in modo che legga un file di tuple (nome,anno,(antenati)), 
come (Fortran,1956,()), (Algol,1960,(Fortran)) e (C++, 1985,(C,Simula)),
e li rappresenta graficamente su una linea temporale con le frecce dagli antenati ai discendenti.
Utilizzare questo programma per disegnare versioni migliorate dei diagrammi in §22.2.2 e §22.2.7. 
*/

#include <string>
#include <fstream>
#include <iostream>
#include "RecordGrafo.h"
#include "WinLinguaggi.h"
#include "../GUI/GUi.h" // per enumerazione colori

int main(int argc, char** argv) {
	RecordGrafo rg;

	// lettura dati dal file
	std::string nomefile{ "" };
	std::ifstream ifs{ "" };
	std::cout << "Ho bisogno del nome file contenente i dati della mappa sui linguaggi di programmazione." << std::endl;
	std::cout << "Record di esempio: (Lisp,1950,()) oppure (PL/I,1960,(Algol60,Fortran,Cobol)): " << std::endl;

	while (!ifs) {
		std::cout << "\nFile?: "; // ho usato diagrammi_today.txt
		std::cin >> nomefile;
		ifs.open(nomefile, std::ios_base::in);
	}

	try {
		// preparo la finestra
		WinLinguaggi finestra(Point{ 10, 10 }, 1920, 920, "Storia dei linguaggi");
		finestra.color(Graph_lib::Color::white);

		// estrazione dei dati
		while (ifs >> rg) {
			// controllo e aggiunta del record alla finestra
			if (rg) {
				finestra.add(rg); 
				//finestra.disponi();
			}
			rg.reset();
		}

		// il file non serve più, controllo buon fine e chiusura
		if (!ifs) {
			if (ifs.bad()) {
				std::cout << "\n\nfile bad!\n\n";
				return 1;
			}
			if (ifs.fail() && !ifs.eof()) {
				std::cout << "\n\nread failed...\n\n";
				return 2;
			}
		}
		ifs.close();

		// ho messo a parte il comando per posizionare la grafica per non riposizionare ad ogni inserimento
		finestra.disponi();

		// si parte !
		Fl::run();
	}
	catch (std::exception e) {
		std::cout << "\n\n\nEccezzione: " << e.what() << std::endl;
	}

	return 0;
}