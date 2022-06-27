/*
Capitolo 19 Esercizio 11
Progetta e implementa un counted_ptr<T> che è un tipo che memorizza 
un puntatore a un oggetto di tipo T e 
un puntatore a un "contatore di utilizzi" (un int) 
condiviso da tutti i puntatori contati delloo stesso oggetto di tipo T.
Il contatore dovrebbe memorizzare tutti gli utilizzi dei puntatori che puntatno al tipo T.
Lascia al costruttore l'allocazione dell'oggetto T e del contatore nella memoria libera.
Lascia che il costruttori prenda un valore per inizializzare gli elementi di tipo T.
Quando l'ultimmo counted_ptr è distrutto per T, allora il distruttore dovrebbe cancellare T.
Dai a counted_ptr le operazioni che ci consentono di utilizzarlo come un puntatore.
Questo è un esempio di "smart pointer" che ci assicura di non distruggere un oggetto finché l'ultimo utilizzatore non ha smesso di usarlo.
Scrivi un set di casi di test per counted_ptr utilizzandolo come un argomento nelle chiamate, contenitori ecc...
*/

#include "counted_ptr.h"
#include <iostream>

class SimpleObj {
	int dato;
public:
	SimpleObj() : dato{ 0 } {};
	~SimpleObj() { std::cout << "SimpleObj in f1 distrutto.\n"; }
};

int* f1() {
	counted_ptr<int> p1(2);
	int* pi = p1.release();
	std::cout << "Nella funzione ho creato p1 col valore 2: " << *pi << ", valore di f1::p1 usato da " << p1.users() << " utenti.\n";
	// qui o ritorno pi o distruggo pi e ritorno un nuovo puntatore, se non distruggo e non ritorno o il valore inutilizzado generando emmory leak
	// p1.destroy(pi);
	//return p1.release();
	SimpleObj so;
	counted_ptr<SimpleObj> cso(so);
	SimpleObj* pso = cso.release();
	return pi;
}

int main(int argc, char** argv) {
	counted_ptr<int> p1(20), p2(18), p3(12);
	using std::cout;
	int* pr = f1();
	cout << "Ho creato 3 counted_ptr che contengono i seguenti valori: " << *p1 << ", " << *p2 << " e " << *p3 << "\n\n";
	cout << "La funzione f1() mi restituisce un puntatore da un counted_ptr ormai distrutto ma il suo valore contenuto no ed è questo: " << *pr << "\n";
	int* pr2 = p2.release();
	// alla fine del main sarà distrutto prima p2 ma pr2 avrà ancora un valore, distrutto poi dalla fine di main()
	return 0;
}