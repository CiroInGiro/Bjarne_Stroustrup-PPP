/*
Capitolo 19 Esercizio 16
Alcune volte si vuole avere un vettore il più piccolo possibile.
Per esempio alcuni potrebbero usare vector<vector<vector<int>>> molti ma hanno la magior parte degli elementi vuoti.
Definisci un vettore in modo che la dimensione di un sizeof(vector<int>) sia uguale a size(int*), cioè in modo che il vettore stesso
sia rappresentato solo da un punatatore a se stesso che contiene un puntatore all'elemento, la dimensione e il puntatore dello spazio. 
*/

// Allocator si occupa solo di creare lo spazio di memoria mentre l'allocazione aggiuntiva viene fatta con reserve() dai modificatori che inserisconto i dati
// dobbiamo quindi creare una interfaccia a vector che una volta chiamati questi modificatori venga richiamato reserve() per garantire che lo spazio nel vettore sia solo quello occupato
// vector di std ha già una funzione per farlo shrink_to_fit() che riduce lo spazio allocato al solo spazio utilizzato

#include <iostream>
#include <vector>

using std::endl;
using std::cout;

template <class T, class A = std::allocator<T>>
class myvector
{
public:
	myvector() : pvect{ nullptr } { }
	void push_back(const T& val) {
		if (!pvect) pvect = new std::vector<T, A>;
		pvect->push_back(val);
		pvect->shrink_to_fit();
	}
	void push_back(const T&& val) {
		if (!pvect) pvect = new std::vector<T, A>;
		pvect->push_back(val);
		pvect->shrink_to_fit();
	}
	~myvector() { if (pvect) delete pvect; }
private:
	std::vector<T, A>* pvect;
};

int main(int argc, char** argv) {
	std::vector<int> vi;
	int* pi{ nullptr };
	std::vector<int*> vpi;
	std::vector<int>* pvi;
	myvector<int> myvi;

	cout << "Dimensioni:" << endl;
	cout << "sizeof(vector<int>) = " << sizeof(vi) << endl;
	cout << "sizeof(int*) = " << sizeof(pi) << endl;
	cout << "sizeof(vector<int*>) = " << sizeof(vpi) << endl;
	cout << "sizeof(vector<int>*) = " << sizeof(pvi) << endl; //creo un puntatore alla struttura che sarà inizializzata solo all'inserimento del primo elemento e mantenuto con spazio allocato = spazio utilizzato dagli elementi.
	cout << "sizeof(myvector<int>) = " << sizeof(myvi) << endl;

	std::cin.get();
return 0;
}