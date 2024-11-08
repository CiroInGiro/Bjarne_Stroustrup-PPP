/*
* Capitolo 26 Esercizio 11
* Calcola il tempo dell'esempio di somma da §26.6 con m che sono matrici quadrate
* con dimensioni 100, 10.000, 1.000.000 e 10.000.000. 
* Usa valori di elementi casuali nell'intervallo [–10:10).
* Riscrivi il calcolo di v per usare un algoritmo più efficiente
* (non O(N2)) e confronta i tempi. 
*/

/*
* Creiamo le 5 matrici con le 5 dimensioni: 100, 10.000, 1.000.000, 10.000.000
* Creiamo una funzione che le riempe con valori casuali nell'intervallo [-10:10)
* Misuriamo il tempo che ci vuole nel calcolo di v con la funzione originale
* Misutiamo poi il tempo che ci vuole dopo le modifiche con la versione 2
*/

#include "..//PPP2code/Matrix.h"
#include <vector>
#include <random>
#include <iostream>
#include <fstream>
#include <chrono>

// motore random per double
std::random_device rnd_device;
std::default_random_engine rnd_engine(rnd_device());
std::uniform_real_distribution<double> rnd_double(-10.0, 10.0);

// riempe la matrice quadrata di valori casuali
void riempi_m(Numeric_lib::Matrix<double, 2>& matrix) {
	// reset per creare un nuovo insieme di double
	rnd_double.reset();
	std::cout << "Riempimento matrice: " << matrix.dim1() << " X " << matrix.dim2() << "\n\n";

	// matrice non quadrata
	if (matrix.dim1() != matrix.dim2()) std::cerr << "Matrice non quadrata\n\n\n";
	
	for (Numeric_lib::Index riga = 0; riga < matrix.dim1(); ++riga) {
		std::cout << "Riga " << riga << ": "; // output di controllo
		for (Numeric_lib::Index colonna = 0; colonna < matrix.dim2(); ++colonna) {
			std::cout << "*"; // output di controllo
			//double d = rnd_double(rnd_engine);
			matrix[riga][colonna] = rnd_double(rnd_engine);
		}
		std::cout << std::endl;
	}
}

double row_sum(Numeric_lib::Matrix<double, 2> m, int n) {
	double retVal{ 0 };

	for (int i = 0; i < m.dim2(); ++i) retVal += m[n][i];

	return retVal;
}

// Per le prestazioni sono stati aggiunti solo il passaggio per riferimento per eviare spostamenti in memoria dei dati.
double row_sum2(Numeric_lib::Matrix<double, 2>& m, const int n) {
	double retVal{ 0 };

	if (m.dim1() == 0) return retVal;
	if (m.dim2() == 0) return retVal;
	if (n < 0) return retVal;
	if (n >= m.dim1()) return retVal;

	for (Numeric_lib::Index i = 0; i < m.dim2(); ++i) retVal += m[n][i];

	return retVal;
}

// Questa funzione non è più necessaria
double row_accum(Numeric_lib::Matrix<double, 2> m, int n) {
	double s = 0;
	for (int i = 0; i < n; ++i) s += row_sum(m, i);
	
	return s;
}

bool riempi_v(Numeric_lib::Matrix<double, 2>& m, std::vector<double>& v) {
	std::chrono::steady_clock::time_point start, end;
	std::chrono::seconds tempo;

	for (Numeric_lib::Index i = 0; i < m.dim1(); ++i) {
		start = std::chrono::steady_clock::now();
		v.push_back(row_accum(m, (i + 1)));
		end = std::chrono::steady_clock::now();
		tempo = std::chrono::duration_cast<std::chrono::seconds>(end - start);
		if (tempo.count() > 1) {
			std::cout << "\n\Troppo tempo (" << tempo.count() << " secondi), matrice " << m.dim1() << " X " << m.dim2() << ", riga " << i << "\n\n";
			return false;
		}
	}
	
	return true;
}

// Per velocizzare è stato sfruttato il calcolo precedentemente accumulato
bool riempi2_v(Numeric_lib::Matrix<double, 2>& m, std::vector<double>& v) {
	// matrice vuota
	if (m.dim1() == 0) return false;

	// vettore già utilizzato
	if (v.size() > 0) return false;

	// Siccome già sappiamo quanti valori memorizzare evitiamo spostamenti multipli in memoria se allochiamo già lo spazio necessario
	v.resize(m.dim1());

	// inserimento della riga 0
	v[0] = row_sum2(m, 0);

	// inserimento somme altre righe controllando il tempo, ci limitiamo ad 1 minuto a riga.
	for (Numeric_lib::Index i = 1; i < m.dim1(); ++i) {
		auto start = std::chrono::steady_clock::now();
		v[i] = (v[(i - 1)] + row_sum2(m, i));
		auto end = std::chrono::steady_clock::now();
		std::chrono::minutes tempo = std::chrono::duration_cast<std::chrono::minutes>(end - start);
		if (tempo.count() >= 1) {
			std::cout << "\n\Troppo tempo (" << tempo.count() << " minuti), matrice " << m.dim1() << " X " << m.dim2() << ", riga " << i << "\n\n";
			return false;
		}
	}
	
	return true;
}

void stampa_v(const std::vector<double>& v) {
	constexpr size_t max_col = 40;
	size_t colonne{ 0 };

	std::cout << "Valori di v: ";

	for (const double d : v)
	{
		std::cout << d << "; ";
		++colonne;
		if (colonne == max_col) std::cout << "\n\t";
	}

	std::cout << std::endl;
}

int main() {
	constexpr Numeric_lib::Index cento = 10; // 10x10
	constexpr Numeric_lib::Index diecimila = 100; // 100x100
	constexpr Numeric_lib::Index milione = 1000; // 1000x1000
	constexpr Numeric_lib::Index diecimilioni = 3163; // circa 3163x3163
	Numeric_lib::Matrix<double, 2> m100(cento, cento);
	Numeric_lib::Matrix<double, 2> m10K(diecimila, diecimila);
	Numeric_lib::Matrix<double, 2> m1M(milione, milione);
	Numeric_lib::Matrix<double, 2> m10M(diecimilioni, diecimilioni);
	// vettore di matrici in modo da poter chiudere il codice di test in un loop
	std::vector<Numeric_lib::Matrix<double, 2>*> matrici;
	std::vector<double> v;
	std::ofstream file_log("log.txt");

	// Libreria chrono
	std::chrono::steady_clock::time_point start, end;
	// Prepariamo le matrici per i test
	matrici.push_back(&m100);
	matrici.push_back(&m10K);
	// Comunque il tempo che ci sarebbe voluto e anche la RAM sono fuori portata per la mia macchina virtuale.
	matrici.push_back(&m1M);
	matrici.push_back(&m10M);
	
	// Riempimento matrici
	std::cout << "Riempimento delle matrici:\n\n";
	
	for (Numeric_lib::Matrix<double, 2> *m : matrici)
	{
		// Tempo iniziale pr la creazione della matrice
		start = std::chrono::steady_clock::now();
		std::cout << "Inizio riempimento matrice " << m->dim1() << " X " << m->dim2() << std::endl;

		// riempimento
		riempi_m(*m);

		// Tempo finale per la creazione della matrice
		end = std::chrono::steady_clock::now();
		std::cout << "Fine riempimento matrice." << std::endl;

		// stampa tempo impiegato.
		std::chrono::milliseconds tempo_trascorso = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
		std::cout << "Tempo impiegato (ms): " << tempo_trascorso.count() << std::endl << std::endl;
		file_log << "Tempo impiegato per riempire la matrice " << m->dim1() << " X " << m->dim2() << " " << tempo_trascorso.count() << " ms\n";
	}
	
	// Esecuzione dei test con le versioni standard di calcolo
	std::cout << "Misurazione tempo con funzioni standard:\n\n";
	file_log << "\nTest con funzioni standard\n";
	
	for (Numeric_lib::Matrix<double, 2> *m : matrici)
	{
		// Tempo iniziale pr la creazione della matrice
		start = std::chrono::steady_clock::now();
		std::cout << "Inizio misurazione matrice " << m->dim1() << " X " << m->dim2() << std::endl;

		// calcolo v
		bool esito = riempi_v(*m, v);

		// Tempo finale per la creazione della matrice
		end = std::chrono::steady_clock::now();
		std::cout << "Fine calcolo." << std::endl;

		// stampa tempo impiegato.
		std::chrono::milliseconds tempo_trascorso = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
		std::cout << "Tempo impiegato (ms): " << tempo_trascorso.count() << std::endl << std::endl;
		file_log << "Tempo impiegato per riempire v con una matrice " << m->dim1() << " X " << m->dim2() << " " << tempo_trascorso.count() << " ms, esito ";
		if (esito) file_log << "positivo\n"; else file_log << "negativo\n";

		// stampa v
		if (esito) stampa_v(v);
		std::cout << "\n\n";

		// azzera v
		v.clear();
	}

	// Esecuzione dei test con le versioni nuove: row_accum abolita, codificata in riempi2_v()
	v.clear();
	std::cout << "Misurazione tempo con funzioni nuove:\n\n";
	
	for (Numeric_lib::Matrix<double, 2> *m : matrici)
	{
		// Tempo iniziale pr la creazione della matrice
		start = std::chrono::steady_clock::now();
		std::cout << "Inizio misurazione matrice " << m->dim1() << " X " << m->dim2() << std::endl;

		// calcolo v
		bool esito = riempi2_v(*m, v);

		// Tempo finale per la creazione della matrice
		end = std::chrono::steady_clock::now();
		std::cout << "Fine calcolo." << std::endl;

		// stampa tempo impiegato.
		std::chrono::milliseconds tempo_trascorso = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
		std::cout << "Tempo impiegato (ms): " << tempo_trascorso.count() << std::endl << std::endl;
		file_log << "Tempo impiegato per riempire v con una matrice " << m->dim1() << " X " << m->dim2() << " " << tempo_trascorso.count() << " ms, esito ";
		if (esito) file_log << "positivo\n"; else file_log << "negativo\n";

		// stampa v
		if (esito) stampa_v(v);
		std::cout << "\n\n";

		// azzera v
		v.clear();
	}

	file_log.close();

	return 0;
}