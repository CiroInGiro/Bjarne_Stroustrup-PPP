/*
Capitolo 20 Esercizio 14
Definisci una single linked list slist in stile std::list.
Quali operazioni da slist potresti ragionevolmente togliere perché in essa non c'è un puntatore per tornare indietro?
*/

#include <vector>
#include <iostream>
#include <fstream>
#include <istream>
#include <ostream>

template<typename T>
class slist {
	// celle di memorizzazione
	struct Elem {
		Elem* next;
		//Elem* prev;
		T dato;
		Elem(const T& d = T(), Elem* n = 0) : dato{ d }, next{ n } {}
	};
public:
	// iteratore
	class iterator {
	public:
		iterator(Elem* p) : cur{ p } {}
		T operator*() { return cur->dato; }
		iterator operator++() { cur = cur->next; return *this; }
		//iterator operator--() { cur = cur->prev; return *this; }
		friend bool operator==(const iterator& l, const iterator& r) {
			return l.cur == r.cur;
		}
		friend bool operator!=(const iterator& l, const iterator& r) {
			return !(l == r);
		}
	private:
		Elem* cur;
	};
	// core della lista
	slist() : primo{ new Elem(T(), nullptr) }, ultimo{ nullptr } {}
	iterator begin() {
		// return begin; non deve usare il mio puntatore
		return iterator(primo);
	}
	iterator end() { if (ultimo) return iterator(ultimo); else return iterator(primo); }
	void push_back(const T& val) {
		if (!ultimo) ultimo = primo;
		ultimo->next = new Elem(T(), 0);
		ultimo->dato = val;
		ultimo = ultimo->next;
	}
private:
	Elem* primo;
	Elem* ultimo;
};


template<typename TT>
// requires T();
std::istream& operator>>(std::istream& in, std::vector<TT>& v) {
	TT val = TT();
	if (in >> val) v.push_back(val);
	return in;
}

template<typename TT>
// requires TT()
std::ostream& operator<<(std::ostream& out, std::vector<TT>& v) {
	if (v.size() > 0) {
		TT val = v.back();
		v.pop_back();
		out << val;
	}
	return out;
}


// Bug: i separatori di dati cadono come 0 in un vettore di double raddoppiando i valori
template<typename T>
// requires T()
std::vector<T>* get_from_jill() {
	std::vector<T>* retVal = new std::vector<T>;
	std::ifstream ifs;
	ifs.open("jill_data.txt", std::ios_base::in);
	if (!ifs) return nullptr;
	T val = T();
	char delimiter{ ' ' };
	while (ifs >> *retVal >> delimiter) { if (delimiter != '|') return nullptr; } // else retVal->push_back(val); } // doppio inserimento nel vettore
	if (ifs.bad() && !ifs.eof()) return nullptr;
	if (ifs.fail() && !ifs.eof()) return nullptr;
	ifs.close();
	return retVal;
}

// tecnica polindrome: confronto di due puntatori
template <typename Iter>
// requires Input_Iterator<Iter>();
Iter high(Iter first, Iter last) {
	Iter h = first;
	++first;
	while (first != last) {
		if (*first > *h) h = first;
		++first;
	}
	// alla fine first e last saranno uguali
	return h;
}

template<typename T>
// requires T();
T* get_from_jack(int& data_count) {
	std::ifstream ifs;
	ifs.open("jack_data.txt", std::ios_base::in);
	if (!ifs) return nullptr;
	T val = T();
	char delimiter{ ' ' };
	while (ifs >> val >> delimiter) { if (delimiter != '|') return nullptr; ++data_count; }
	if (data_count == 0) return nullptr;
	if (ifs.bad() && !ifs.eof()) return nullptr;
	if (ifs.fail() && !ifs.eof()) return nullptr;
	T* retVal = new T[data_count];
	int posi{ 0 };
	while (posi < data_count) {
		retVal[posi] = T();
		++posi;
	}
	posi = 0;
	ifs.clear();
	ifs.seekg(0);
	while (ifs >> val >> delimiter) {
		retVal[posi] = val;
		++posi;
	}
	ifs.close();
	return retVal;
}

int main(int argc, char* argv[]) {
	int jack_count{ 0 };
	double* jack_data = get_from_jack<double>(jack_count);
	if (!jack_data) return 1;
	std::vector<double>& jill_data = *get_from_jill<double>();
	if (!&jill_data) return 2;
	// travaso i dati in liste di questo tipo e testo passandole ad high()
	slist<double> jill_list;
	slist<double> jack_list;
	for (std::vector<double>::iterator p = jill_data.begin(); p != jill_data.end(); ++p) {
		jill_list.push_back(*p);
	}
	for (unsigned int i = 0; i < jack_count; ++i) {
		jack_list.push_back(jack_data[i]);
	}
	slist<double>::iterator jack_high = high(jack_list.begin(), jack_list.end());
	slist<double>::iterator jill_high = high(jill_list.begin(), jill_list.end());
	std::cout << "\nJill max: " << *jill_high << ";\n";
	std::cout << "\nJack max: " << *jack_high << ".\n";
	delete[] jack_data;
	delete& jill_data;
	return 0;
}