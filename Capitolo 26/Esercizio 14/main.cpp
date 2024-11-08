/*
* Capitolo 26 Esercizio 14
* Ripeti l'eserizion precedente eccetto l'uso di map
* invece che un vector in modo che non abbiamo bisogno di ordinarlo
*/

#include <iostream>
#include <sstream> // per formattare il tempo
#include <map> // map al posto di vector
//#include <vector>
#include <random>
#include <chrono>
#include <algorithm>

// funzione che genera una stringa di lunghezza casuale
std::string genera_stringa(std::default_random_engine& rnd_engine, std::uniform_int_distribution<int>& rnd_caratteri, int lunghezza) {
	std::string retVal{ "" };

	while (lunghezza > 0) {
		retVal += char(rnd_caratteri(rnd_engine));
		--lunghezza;
	}

	return retVal;
}

// funzione che riempe una mappa con le stringhe
void riempi_mappa(std::map<std::string, int>& mappa, int lunghezza) {
	std::random_device rnd_device;
	std::default_random_engine rnd_engine(rnd_device());
	// funzione che genera caratteri casuali (codici stampabili dal 32 al 126)
	std::uniform_int_distribution<int> rnd_caratteri(32, 126);
	std::uniform_int_distribution<int> rnd_lunghezza(0, 99);

	while (lunghezza > 0) {
		int size = rnd_lunghezza(rnd_engine);
		mappa[genera_stringa(rnd_engine, rnd_caratteri, size)] = size;
		--lunghezza;
	}
}

// funzione che stampa il vettore
void stampa_mappa(const std::map<std::string, int>& mappa) {
	for (const std::pair<std::string, int> s : mappa) {
		std::cout << s.first << " : " << s.second << std::endl;
	}
}

// funzione che stampa il tempo
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
	std::map<std::string, int> stringhe; // mappa <string, lunghezza della stringa>
	int num_str[]{ 500000, 5000000 };
	std::chrono::steady_clock::time_point start, end;

	// Test per 500K e 5M di stringhe
	for (int num : num_str) {
		// riempi il vettore stringhe con num stringhe di lunghezza casuale
		// misura il tempo per inserirle ordinate
		start = std::chrono::steady_clock::now();
		riempi_mappa(stringhe, num);
		end = std::chrono::steady_clock::now();

		// stampa esito
		std::cout << "Tempo impiegato per inserimento ordinato di " << num << " elementi string nella mappa: " << formatta_tempo((end - start));
		std::cout << std::endl << std::endl;

		// Solo per test, stampa la mappa
		/*
		std::cout << "Stampa del vettore ordinato:\n";
		stampa_mappa(stringhe);
		std::cout << std::endl << std::endl;
		*/

		// azzera il vettore per il prossimo test
		stringhe.clear();
	}

	return 0;
}

/*
* 14 secondi per l'inserimento di 500 mila stringhe
* 2 minuti per l'inserimento di 5 milioni di stringhe
*/