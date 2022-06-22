/*
Capitolo 14 Esercizio 15
Molte gerarchie di classi non hanno niente a che vedere con la grafica.
Definisci una classe Iterator con una funzione virtuale pura next() che restituisce un double* (vedi il capitolo 17).
Ora deriva Vector_iterator e List_iterator da Iterator in modo che next() conserva per Vector_iterator un puntatore al prossimo elemento di vector<double>
e List_iterator fa lostesso con list<double>
Inizializza un Vector_iterator con un vector<double> e alla prima chiamata di next() conserva un puntatore al suo primo elemento, se c'è.
Se non ci sono elementi ritorna 0.
Testa con una funzione void print(Iterator&) per stampare gli elementi di un vector<double> e una list<double>.
*/

#include <vector>
#include <list>
#include <iostream>

class Iterator {
public:
	Iterator() {}
	virtual double* next() = 0;
};

class Vector_iterator : public Iterator {
public:
	Vector_iterator() {}
	void add(double valore) {
		vettore.push_back(valore);
		/*
		if (indice == -1) {
			indice++;
			p = &vettore[indice];
		}
		*/
	}
	double* next() {
		//double* attuale = p;
		int size = vettore.size();
		size--;
		if (indice < size) {
			indice++;
			// uso la matematica dei puntatori oppure sfrutto indice
			//p++;
			p = &vettore[indice];
			return p;
		}
		return nullptr;
	}
private:
	std::vector<double> vettore;
	double* p{ 0 };
	int indice{ -1 };
};

// come si va avanti in queste liste???
class List_iterator : public Iterator {
public:
	List_iterator() {}
	void add(double valore) {
		lista.push_back(valore);
	}
	double* next() {
		int size = lista.size();
		//size--;
		if (size == 0) return nullptr;
		if (p == nullptr) {
			i = lista.begin();
			p = &(*i);
			return p;
		}
		else if (++i != lista.end()) {
			//i++;
			p = &(*i);
			return p;
		}
		return nullptr;
	}
private:
	std::list<double> lista;
	std::list<double>::iterator i;
	double* p{ 0 };
	int indice{ -1 };
};

void print(Iterator& elementi) {
	double* p = elementi.next();
	std::cout << "Stampo gli elementi:" << std::endl;
	int indice{ 0 };
	while (p) {
		std::cout << "Elemenro con indice " << indice++ << ": " << *p << "; " << std::endl;
		p = elementi.next();
	}
}

int main(int argc, char* argv[]) {
	Vector_iterator vi;
	vi.add(2.0);
	vi.add(2.1);
	vi.add(2.3);
	using std::cout;
	using std::endl;
	cout << "Ho creato un Vector_iterator vi e riempito con i valori 2.0, 2.1 e 2.3;" << endl;
	List_iterator li;
	li.add(2.0);
	li.add(2.1);
	li.add(2.3);
	cout << "Ora la stessa cosa ma con List_iterator che é riempito con gli stessi valori 2.0, 2.1 e 2.3;" << endl;
	cout << endl << endl << "Ora uso la funtione void print(Iterator&) per stampare il Vector_iterator:" << endl;
	print(vi);
	std::cin.get();
	cout << endl << endl << "Ora uso la funtione void print(Iterator&) per stampare il List_iterator:" << endl;
	print(li);
	std::cin.get();
	return 0;
}