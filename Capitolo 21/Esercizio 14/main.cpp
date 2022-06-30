/*
Capitolo 21 Esercizio 14
Scrivi un programma (utilizzando l'output del precedente esercizio) per rispondere a domande tipo:
Quante occorrenze ci sono di ship nel file?
Quale parola si ripete più spesso?
Qual'è la parola più lunga nel file?
Quale la più corta?
Lista di tutte le parole che iniziano con 's'
Lista di tutte le parole di 4 lettere
*/

#include <iostream>
#include <fstream>
#include <map>
#include "pulitore.h"
#include <vector>

int main(int argc, char* argv) {
	std::ifstream ifs{ "" };
	std::string nomefile{ "" };
	std::map<std::string, int>* mappa_di_parole;
	using std::cin;
	using std::cout;
	using std::endl;
	try {
		cout << "Capitolo 21 Esercizio 14:" << endl;
		while (!ifs) {
			cout << "File formato testo (.txt): "; // ho usato ..\host_centralino.txt
			cin >> nomefile;
			cout << endl;
			ifs.open(nomefile);
		}
		// la classe pulitore deve prendere un input file stream e restituire un puntatore ad una mappa di stringhe,
		// che ha come valore il numero di occorrenze trovate nel file per quella parola chiave.
		mappa_di_parole = pulitore(ifs).get_map();
		ifs.close();

		// 1. controlliamo quante volte è presente la parola 'host'
		auto p = mappa_di_parole->find("host");
		if (p != mappa_di_parole->end()) cout << "La parola host si ripete: " << p->second << endl;
		else cout << "parola host non trovata.\n";

		cout << "\nPremi invio per continuare." << endl;
		char c{ ' ' };
		cin.clear();
		cin.ignore(100, '\n');
		while (cin.get(c) && c != '\n');

		// 2. cerchiamo la parola che si ripete più spesso
		// ci serve sapere prima il numero di occorrenze più alto
		// poi elenchiamo tutte le parole con quel numero
		size_t max{ 0 };
		for (auto p : (*mappa_di_parole)) {
			if (p.second > max) max = p.second;
		}
		std::vector<std::map<std::string, int>::iterator> its_max;
		std::map<std::string, int>::iterator navetta = mappa_di_parole->begin();
		while (navetta != mappa_di_parole->end()) {
			if ((*navetta).second == max) its_max.push_back(navetta);
			++navetta;
		}
		cout << "\nElenco di tutte le parole più ripetute (" << max << " volte):" << endl;
		for (auto it : its_max) {
			cout << (*it).first << endl;
		}

		cout << "\nPremi invio per continuare." << endl;
		c = ' ';
		cin.clear();
		cin.ignore(100, '\n');
		while (cin.get(c) && c != '\n');

		// 3. Cerchiamo la parola più lunga
		// ci serve sapere prima il numero di caratteri più alto
		// poi elenchiamo tutte le parole con quella lunghezza
		max = 0;
		for (auto p : (*mappa_di_parole)) {
			if (p.first.size() > max) max = p.first.size();
		}
		its_max.clear();
		navetta = mappa_di_parole->begin();
		while (navetta != mappa_di_parole->end()) {
			if ((*navetta).first.size() == max) its_max.push_back(navetta);
			++navetta;
		}
		cout << "Elenco di tutte le parole più lunghe (" << max << " caratteri):" << endl;
		for (auto it : its_max) {
			cout << (*it).first << endl;
		}

		cout << "\nPremi invio per continuare." << endl;
		c = ' ';
		cin.clear();
		cin.ignore(100, '\n');
		while (cin.get(c) && c != '\n');

		// 4. Cerchiamo la parola più corta
		// ci serve sapere prima il numero di caratteri minimo
		// poi elenchiamo tutte le parole con quella lunghezza
		max = (*(*mappa_di_parole).begin()).first.size();
		for (auto p : (*mappa_di_parole)) {
			if (p.first.size() < max) max = p.first.size();
		}
		its_max.clear();
		navetta = mappa_di_parole->begin();
		while (navetta != mappa_di_parole->end()) {
			if ((*navetta).first.size() == max) its_max.push_back(navetta);
			++navetta;
		}
		cout << "Elenco di tutte le parole più corte (" << max << " caratteri):" << endl;
		for (auto it : its_max) {
			cout << (*it).first << endl;
		}

		cout << "\nPremi invio per continuare." << endl;
		c = ' ';
		cin.clear();
		cin.ignore(100, '\n');
		while (cin.get(c) && c != '\n');

		// 5. Lista delle parole che iniziano con 's'
		cout << "\nElenco Parole che iniziano con 's' " << endl;
		for (navetta = mappa_di_parole->begin(); 
			navetta != mappa_di_parole->end();
			navetta = find_if(navetta, mappa_di_parole->end(), [](std::pair<std::string, int> v) { return v.first[0] == 's'; })) {
			if (navetta != mappa_di_parole->end()) {
				cout << (*navetta).first << endl;
				++navetta;
			}
		}
		
		cout << "\nPremi invio per continuare." << endl;
		c = ' ';
		cin.clear();
		cin.ignore(100, '\n');
		while (cin.get(c) && c != '\n');

		// Lista delle parole di 4 lettere
		cout << "\nLista delle parole di 4 lettere:" << endl;
		navetta = mappa_di_parole->begin();
		while (navetta != mappa_di_parole->end()) {
			navetta = find_if(navetta, mappa_di_parole->end(), [](std::pair<std::string, int> v) {return (v.first.size() == 4); });
			if (navetta != mappa_di_parole->end()) {
				cout << (*navetta).first << endl;
				++navetta;
			}
		}
		cout << "\nPremi invio per continuare." << endl;
		c = ' ';
		cin.ignore(100, '\n');
		cin.clear();
		while (cin.get(c) && c != '\n');
	}
	catch (...) {
		std::cout << "\n\nErrore non gestito.\n";
	}
}