/*
Capitolo 20 Esercizio 2
Prendi l'esempio per Jack e Jill del paragrafo 20.1.2 a farlo funzionare.
Usa qualche piccolo file di input per testarlo.
*/

#include <iostream>
#include <vector>
#include <fstream>

double* get_from_jack(int& data_count) {
	std::ifstream ifs;
	ifs.open("jack_data.txt", std::ios_base::in);
	if (!ifs) return nullptr;
	double val{ 0.0 };
	char delimiter{ ' ' };
	while (ifs >> val >> delimiter) { if (delimiter != '|') return nullptr; ++data_count; }
	if (data_count == 0) return nullptr;
	if (ifs.bad() && !ifs.eof()) return nullptr;
	if (ifs.fail() && !ifs.eof()) return nullptr;
	double* retVal = new double[data_count];
	int posi{ 0 };
	while (posi < data_count) {
		retVal[posi] = 0.0;
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

std::vector<double>* get_from_jill() {
	std::vector<double>* retVal = new std::vector<double>;
	std::ifstream ifs;
	ifs.open("jill_data.txt", std::ios_base::in);
	if (!ifs) return nullptr;
	double val{ 0.0 };
	char delimiter{ ' ' };
	while (ifs >> val >> delimiter) { if (delimiter != '|') return nullptr; else retVal->push_back(val); }
	if (ifs.bad() && !ifs.eof()) return nullptr;
	if (ifs.fail() && !ifs.eof()) return nullptr;
	ifs.close();
	return retVal;
}

double* high(double* first, double* last) {
	double h = *first;
	double* high = first;
	for (double* p = first; p != last; ++p)
		if (h < *p) { high = p; h = *p; }
	return high;
}

int main(int argc, char** argv) {
	int jack_count{ 0 };
	double* jack_data = get_from_jack(jack_count);
	if (!jack_data) return 1;
	std::vector<double>& jill_data = *get_from_jill();
	if (!&jill_data) return 2;
	double* jack_high = high(&jack_data[0], &jack_data[0] + jack_count);
	double* jill_high = high(&jill_data[0], &jill_data[0] + jill_data.size());
	std::cout << "\nJill max: " << *jill_high << ";\n";
	std::cout << "\nJack max: " << *jack_high << ".\n";
	delete[] jack_data;
	delete &jill_data;

	return 0;
}