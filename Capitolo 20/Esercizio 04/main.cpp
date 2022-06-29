/*
Capitolo 20 Esercizio 4
Trova e ripara gli errori nell'esempio di jack e jill paragrafo 20.3.1
utilizzando le tecniche dello Standard Template Library da pertutto.
*/


#include <iostream>
#include <vector>
#include <fstream>

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

template<typename T>
// requires T()
std::vector<T>* get_from_jill() {
	std::vector<T>* retVal = new std::vector<T>;
	std::ifstream ifs;
	ifs.open("jill_data.txt", std::ios_base::in);
	if (!ifs) return nullptr;
	T val = T();
	char delimiter{ ' ' };
	while (ifs >> val >> delimiter) { if (delimiter != '|') return nullptr; else retVal->push_back(val); }
	if (ifs.bad() && !ifs.eof()) return nullptr;
	if (ifs.fail() && !ifs.eof()) return nullptr;
	ifs.close();
	return retVal;
}

// tecnica polindrome: confronto di due puntatori
template <typename Iter>
// requires Input_Iterator<Iter>();
Iter high(Iter first, Iter last) {
	while (first != last) {
		if (*first > *last) --last;
		else ++first; // se i valori dovessero essere uguali scelgo di tentare col successivo di first
	}
	// alla fine first e last saranno uguali
	return first;
}

int main(int argc, char** argv) {
	int jack_count{ 0 };
	double* jack_data = get_from_jack<double>(jack_count);
	if (!jack_data) return 1;
	std::vector<double>& jill_data = *get_from_jill<double>();
	if (!&jill_data) return 2;
	double* jack_high = high(&jack_data[0], &jack_data[0] + jack_count);
	double* jill_high = high(&jill_data[0], &jill_data[0] + jill_data.size());
	std::cout << "\nJill max: " << *jill_high << ";\n";
	std::cout << "\nJack max: " << *jack_high << ".\n";
	delete[] jack_data;
	delete& jill_data;

	return 0;
}