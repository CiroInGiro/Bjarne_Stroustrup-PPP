/*
* Capitolo 26 Esercizio 12
* Scrivi un programma che genera numeri casuali a virgola mobile
* e ordinali utilizzando std::sort().
* Misura il tempo che ci vuole per ordinare 500.000 double e 5.000.000 di double.
*/

#include <iostream>
#include <sstream>
#include <algorithm> // sort()
#include <vector>
#include <chrono>
#include <random>
#include <limits>

// funzione che riempe il vettore di double
void riempi_vettore(std::vector<double>& v, size_t num_elem) {
	std::random_device rnd_device;
	std::default_random_engine rnd_engine(rnd_device());
	std::uniform_real_distribution<double> rnd_double(std::numeric_limits<double>::min(), std::numeric_limits<double>::max());

	while (num_elem > 0) {
		v.push_back(rnd_double(rnd_engine));
		--num_elem;
	}

}

std::chrono::nanoseconds misura_sort(std::vector<double>& v) {
	std::chrono::steady_clock::time_point start, end;

	start = std::chrono::steady_clock::now();
	std::sort(v.begin(), v.end());
	end = std::chrono::steady_clock::now();

	return (end - start);
}

std::string formatta_tempo(std::chrono::nanoseconds ns) {
	std::ostringstream oss;
	std::chrono::minutes min = std::chrono::duration_cast<std::chrono::minutes>(ns);
	std::chrono::seconds sec;
	std::chrono::milliseconds ms;
	std::chrono::microseconds us;

	if (min.count() > 0) {
		oss << min.count() << " minut";
		if (min.count() == 1) oss << "o"; else oss << "i";
		ns = ns % 60000000000;
		if (ns.count() > 0) oss << ", ";
	}

	sec = std::chrono::duration_cast<std::chrono::seconds>(ns);

	if (sec.count() > 0) {
		oss << sec.count() << " second";
		if (sec.count() == 1) oss << "o"; else oss << "i";
		ns = ns % 1000000000;
		if (ns.count() > 0) oss << ", ";
	}

	ms = std::chrono::duration_cast<std::chrono::milliseconds>(ns);

	if (ms.count() > 0) {
		oss << ms.count() << " millisecond";
		if (ms.count() == 1) oss << "o"; else oss << "i";
		ns = ns % 1000000;
		if (ns.count() > 0) oss << ", ";
	}

	us = std::chrono::duration_cast<std::chrono::microseconds>(ns);

	if (us.count() > 0) {
		oss << us.count() << " microsecond";
		if (us.count() == 1) oss << "o"; else oss << "i";
		ns = ns % 1000;
		if (ns.count() > 0) oss << ", ";
	}

	if (ns.count() > 0) {
		oss << ns.count() << " nanosecond";
		if (ns.count() == 1) oss << "o."; else oss << "i.";
	}

	return oss.str();
}

int main() {
	std::vector<double> vettore;
	std::chrono::nanoseconds time_diff;

	// riempi il vettore con 500K double
	riempi_vettore(vettore, 500000);

	// ordina il vettore
	time_diff = misura_sort(vettore);

	// stampa il risultato
	std::cout << "Ordinamento di un vettore di 500K double\n";
	std::cout << "tempo impiegato: " << formatta_tempo(time_diff) << std::endl << std::endl;

	// riempi il vettore con 5M double
	vettore.clear();
	riempi_vettore(vettore, 5000000);
	
	// ordina il vettore
	time_diff = misura_sort(vettore);

	// stampa il risultato
	std::cout << "Ordinamento di un vettore di 5M double\n";
	std::cout << "tempo impiegato: " << formatta_tempo(time_diff) << std::endl << std::endl;

	return 0;
}