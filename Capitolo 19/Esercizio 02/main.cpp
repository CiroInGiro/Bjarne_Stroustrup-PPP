/*
Capitolo 19 Esercizio 2
Scrivi un template di funzione che prende un vector<T> vt e un vector<U> vu come argomenti e ritorna la somma dei due vt[i] + vu[i].
*/

#include <vector>
#include <iostream>

template<typename T, typename U>
std::vector<T> f(std::vector<T>& vt, std::vector<U>& vu) {
	std::vector<T> retVal;
	int max = ((vt.size() > vu.size()) ? vu.size() : vt.size());
	for (int i = 0; i < max; ++i) {
		retVal.push_back((vt[i] + vu[i]));
	}
	if (vt.size() > vu.size()) {
		for (int i = vu.size(); i < vt.size(); ++i) retVal.push_back(vt[i]);
	}
	else if (vt.size() < vu.size()) {
		for (int i = vt.size(); i < vu.size(); ++i) retVal.push_back(vu[i]);
	}
	return retVal;
}

int main(int argc, char** argv) {
	std::vector<double> vd{ 2.3, 2.2, 5.8 };
	std::vector<int> vi{ 32, 80, 32, 21, 1 };
	std::vector<double> vsum = f(vd, vi);
	for (double val : vsum) std::cout << "Valore del vettore somma: " << val << ";\n";
	return 0;
}