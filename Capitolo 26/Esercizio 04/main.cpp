/* 
* Capitolo 26 Esercizio 4
* Progettare un formato per i dati di prova in modo da poter definire una sequenza una volta
* ed eseguire diversi test su di essa.
*/

/* la prima idea è creare più sequenze: la prima indica i valori da cercare, la seconda il dominio dei valori da creare, la terza i risultati rispettivamente ai valori cercati.
*  Volendo si possono anche nidificare le sequenze e combinare ogni dato da ricercare in tutte le sequenze, in pratica una sequenza di sequenze.
* { "label" { "ELEMENTI" "da" "cercare" } {"elementi" "nel" "vettore" "sequenza" } { 0 0 0 } } 
* 
* Ad esempio abbiamo una sequenza di interi e vogliamo testare la ricerca agli estremi e nel mezzo;
* vogliamo testare la ricerca vicino agli estremi e la parte centrale;
* vogliamo testare i valori assenti minore di tutti gli elementi e maggiore di tutti gli elementi
* 
* { "multi" { 2 90 30 8 45 20 31 0 1 91 80 12 29 -1 200 } { 2 8 9 11 13 16 20 30 31 32 33 36 39 44 45 90 } { 1 1 1 1 1 1 1 0 0 0 0 0 0 0 0 } }
* Per fare questo dovremmo modificare Test.h in una nuova versione che utilizza 3 vettori di dati.
*/

#include "Test2.h"
#include <iostream>

// funzione di ricerca binaria scritta al paragrafo 26.1 versione template
template<class T>
bool ricerca_v(const std::vector<T>& v, const T& num, size_t& pos) {
	size_t start = 0;
	size_t end = (v.size() - 1);
	size_t middle = (end - start) / 2;

	// controlli preliminari: pos restituisce l'indice quando trovato o rimane invariato; la funzione ritorna true in caso di successo altrimenti false.
	if (v.size() == 0) return false; // nulla da cercare
	if (num < v[start] || num > v[end]) return false; // stiamo cercando un numero che si trova al di fuori del range di numeri contenuti.

	while (middle != start && middle != end) {
		if (v[middle] == num) {
			pos = middle;
			return true;
		}
		if (v[middle] < num) {
			// stiamo cercando in un range troppo piccolo, ci spostiamo più avanti
			start = middle;
		}
		else {
			// stiamo cercando in un range di numeri grandi, ci spostiamo più indietro
			end = middle;
		}
		middle = start + ((end - start) / 2);
	}

	// ultimo controllo nel caso middle sia uguale a start o end.
	if (v[middle] == num) {
		pos = middle;
		return true;
	}
	else if (v[start] == num) {
		pos = start;
		return true;
	}
	else if (v[end] == num) {
		pos = end;
		return true;
	}

	return false;
}

int main() {
	Test2<int> test2;
	size_t posizione{ 0 };
	bool risultato{ false };

	test2.label = "multi";
	test2.val = { 2, 90, 30, 8, 45, 20, 31, 0, 1, 91, 80, 12, 29, -1, 200 };
	test2.seq = { 2, 8, 9, 11, 13, 16, 20, 30, 31, 32, 33, 36, 39, 44, 45, 90 };
	test2.res = { 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0 };

	if (test2.val.size() != test2.res.size()) {
		std::cerr << "\n\n\nErrore: Numero di test diffrente dal numero di risultati attesi.\n\n\n";
		return 1;
	}

	for (size_t indice = 0; indice < test2.val.size(); ++indice) {
		std::cout << "Cerco " << test2.val[indice] << " nella sequenza { ";
		for (size_t indice = 0; indice < (test2.seq.size() - 1); ++indice) std::cout << test2.seq[indice] << ", ";
		std::cout << *(test2.seq.end() - 1);
		std::cout << " }. Risultato atteso: " << test2.res[indice] << "; ricerca_v restituisce: ";
		risultato = ricerca_v(test2.seq, test2.val[indice], posizione);
		std::cout << risultato;
		if (risultato == test2.res[indice]) std::cout << ".\n\n"; else std::cout << ". *** ERRORE ***\n\n\n\n";
	}

	return 0;
}