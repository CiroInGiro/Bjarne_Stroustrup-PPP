/* Capitolo 25 Esercizio 15
Misura il tempo (26.6.1) che impiega ad allocare 10000 oggetti di dimensione casuale [1000:0)-byte di range usando new;
poi misura il tempo che ci vuole per deallocarli usando delete.
Fallo un paio di volte, una deallocando nell'ordine inverso alla allocazione
e uno deallocando in maniera casuale.
Poi, fai lo stesso allocando 10000 oggetti di 500 byte dal pool e liberandoli.
Poi, fai l'equivalente allocando 10000 oggetti di dimensione casuale [1000:0)-byte di range in una pila e poi liberando gli stessi (in ordine inverso).
Confronta le misurazioni.
Fai ogni misurazione almeno 3 volte per essere sicuro di un risultato consistente.
*/

#include <iostream>
#include <chrono> // per la misura del tempo
#include <time.h> // per i formati data e ora
#include <random> // per i numeri casuali
#include <vector> // conserviamo i puntatori in un vettore
#include <string>
#include <unordered_set> // conserviamo gli indici del vettore da uasre per delete[]
#include "../MyClass/MyVector_Pool.h" // gestione del Pool
#include <stack> // per archiviare in una pila LIFO

// struttura dati per i test
struct test {
	std::string nome_test;
	std::vector<long long> risultati;
	test(const std::string& nome) : nome_test{ nome } {};
	void add(const long long& risultato) { risultati.push_back(risultato); }
	double media() {
		if (risultati.size() == 0) return 0.0;
		long long somma{ 0 };
		double media{ 0.0 };
		for (long long risultato : risultati) somma += risultato;
		media = (double)somma / (double)risultati.size();
		return media;
	}
	std::ostream& stampa_nome(std::ostream& out) {
		out << nome_test;
		return out;
	}
	std::ostream& stampa_risultati(std::ostream& out) {
		if (risultati.size() == 0) return out;
		for (long long risultato : risultati) out << risultato << "; ";
		return out;
	}
};

// struttura di 500 byte
struct struct_500 {
	// 500 byte di dati
	char byte_500[500];
	// costruttore di default, prerequisito di tipo da memorizzare in MyVector_Pool
	struct_500() {
		for (size_t i = 0; i < 500; ++i) { byte_500[i] = '\0'; }
	}
};

// funzione che elimina i puntatori dal vettore sempre con lo stesso metodo
void delete_puntatori(std::vector<char*>& v) {
	for (char* p : v) {
		delete[] p;
		p = nullptr;
	}
}

// funzione che libera i puntatori dal Pool leggendoli da un vettore
template<class T, size_t N> 
void delete_puntatori(std::vector<T*>& v, MyVector_Pool<T, N>& pool)
{
	if (v.size() == 0 || pool.size() == 0 || v.size() > pool.size()) return;

	for (auto p : v) {
		pool.del(p);
		p = nullptr;
	}
};

int main(int argc, char** argv) {
	// dimensione di un byte
	//char carattere{ '\0' };
	//std::cout << "Dimensione di un carattere: " << sizeof(carattere) << " byte." << std::endl << std::endl;

	std::vector<char*> puntatori;
	std::chrono::system_clock::time_point time_start, time_stop;
	//std::chrono::system_clock::duration time_diff; // solo duration utilizza una proporzione di default che corrisponde ai ticks
	std::chrono::milliseconds time_diff;
	time_t time_now; // data e ora in formato numerico
	struct tm time_struct; // data e ora in una struttura dati
	char time_str[26]; // data e ora in formato caratteri
	std::random_device rnd_device; // dispositivo per generare numeri casuali
	std::default_random_engine rnd_engine(rnd_device()); // motore che genera numeri casuali
	std::uniform_int_distribution<int> rnd_dim(1, 1000); // distribuzione di numeri casuali tra 1 e 1000
	std::uniform_int_distribution<long long> rnd_indice(0, 0); // indice casuale all'interno del vettore
	std::uniform_int_distribution<long long>::param_type parametri;
	std::vector<test> misurazioni;
	MyVector_Pool<struct_500, 10000> array_char;
	std::vector<struct_500*> puntatori_array_500;
	std::stack<char*> pila;

	misurazioni.push_back(test(" 1. Misurazione del tempo per allocare 10K oggetti di dimensioni tra 1 e 1000 byte usando new():"));
	misurazioni.push_back(test(" 2. Misurazione del tempo per deallocare i 10K oggetti usando delete():"));
	misurazioni.push_back(test(" 3. Misurazione del tempo per deallocare i 10K oggetti ma nell'ordine inverso:"));
	misurazioni.push_back(test(" 4. Misurazione del tempo per deallocare i 10K oggetti ma in ordine casuale:"));
	misurazioni.push_back(test(" 5. Misurazione del tempo necessario per allocare 10K oggetti di 500 byte nel Pool:"));
	misurazioni.push_back(test(" 6. Misurazione del tempo per deallocare i 10K oggetti dal Pool:"));
	misurazioni.push_back(test(" 7. Misurazione del tempo per deallocare i 10K oggetti in ordine inverso dal Pool:"));
	misurazioni.push_back(test(" 8. Misurazione del tempo per deallocare i 10K oggetti in ordine casuale dal Pool:"));
	misurazioni.push_back(test(" 9. Misurazione del tempo per inserire 10K oggetti di dimensioni [1000:0) byte nella pila:"));
	misurazioni.push_back(test("10. Misurazione del tempo per togliere i 10K oggetti dalla pila:"));

	//std::cout << "TEST: "; misurazione.stampa_nome(std::cout) << "\n";
	//std::cout << "Misure: "; misurazione.stampa_risultati(std::cout) << "\n";
	//std::cout << "Media: " << misurazione.media() << "\n\n\n";
	
	// 	std::cout << "1. Misurazione del tempo per allocare 10K oggetti di dimensioni tra 1 e 1000 byte usando new():\n\n";

	// misurazione più volte
	for (size_t misure = 1; misure <= 5; ++misure) {
		size_t num_test{ 0 };
		//std::cout << "Misurazione numero " << misure << ":\n";

		// *** new()
		// prendiamo il tempo iniziale
		time_start = std::chrono::system_clock::now();
		time_now = std::chrono::system_clock::to_time_t(time_start);
		localtime_s(&time_struct, &time_now);
		asctime_s(time_str, sizeof(time_str), &time_struct);
		std::cout << "Inizio del test " << (num_test + 1) << ": " << time_str << std::endl;
		// esecuzione del test
		for (size_t allocazioni = 0; allocazioni < 10000; ++allocazioni) {
			int dim = rnd_dim(rnd_engine);
			char* pchar = new char[dim];
			puntatori.push_back(pchar);
		}
		// prendiamo il tempo finale
		time_stop = std::chrono::system_clock::now();
		time_now = std::chrono::system_clock::to_time_t(time_stop);
		localtime_s(&time_struct, &time_now);
		asctime_s(time_str, &time_struct);
		std::cout << "Fine del test: " << time_str << std::endl;
		auto time_diff = std::chrono::duration_cast<std::chrono::milliseconds>((time_stop - time_start));
		//std::cout << "Durata del test (millisecondi): " << time_diff.count() << std::endl << std::endl;
		misurazioni[num_test].add(time_diff.count());

		// *** delete()
		// misura del tempo necessari per la deallocazione usando delete
		//std::cout << "2. Misurazione del tempo per deallocare i 10K oggetti usando delete():\n\n";
		++num_test;
		// prendiamo il tempo iniziale
		time_start = std::chrono::system_clock::now();
		time_now = std::chrono::system_clock::to_time_t(time_start);
		localtime_s(&time_struct, &time_now);
		asctime_s(time_str, sizeof(time_str), &time_struct);
		std::cout << "Inizio del test " << (num_test + 1) << ": " << time_str << std::endl;
		// esecuzione del test
		delete_puntatori(puntatori);
		// prendiamo il tempo finale
		time_stop = std::chrono::system_clock::now();
		time_now = std::chrono::system_clock::to_time_t(time_stop);
		localtime_s(&time_struct, &time_now);
		asctime_s(time_str, &time_struct);
		std::cout << "Fine del test: " << time_str << std::endl;
		time_diff = std::chrono::duration_cast<std::chrono::milliseconds>((time_stop - time_start));
		//std::cout << "Durata del test (millisecondi): " << time_diff.count() << std::endl << std::endl;
		misurazioni[num_test].add(time_diff.count());
		// togliamo da mezzo i puntatori senza una zona di memoria
		puntatori.clear();

		// *** delete() inverso
		++num_test;
		// Prepariamo un nuovo set di puntatori da cancellare in ordine inverso.
		for (size_t allocazioni = 0; allocazioni < 10000; ++allocazioni) {
			int dim = rnd_dim(rnd_engine);
			char* pchar = new char[dim];
			puntatori.push_back(pchar);
		}
		std::reverse(puntatori.begin(), puntatori.end());
		// ora li cancelliamo in ordine inverso rispetto alla loro creazione
		//std::cout << "Misurazione del tempo per deallocare i 10K oggetti ma nell'ordine inverso:\n\n";
		// prendiamo il tempo iniziale
		time_start = std::chrono::system_clock::now();
		time_now = std::chrono::system_clock::to_time_t(time_start);
		localtime_s(&time_struct, &time_now);
		asctime_s(time_str, sizeof(time_str), &time_struct);
		std::cout << "Inizio del test " << (num_test + 1) << ": " << time_str << std::endl;
		// esecuzione del test
		delete_puntatori(puntatori);
		// prendiamo il tempo finale
		time_stop = std::chrono::system_clock::now();
		time_now = std::chrono::system_clock::to_time_t(time_stop);
		localtime_s(&time_struct, &time_now);
		asctime_s(time_str, &time_struct);
		std::cout << "Fine del test: " << time_str << std::endl;
		time_diff = std::chrono::duration_cast<std::chrono::milliseconds>((time_stop - time_start));
		//std::cout << "Durata del test (millisecondi): " << time_diff.count() << std::endl << std::endl;
		misurazioni[num_test].add(time_diff.count());
		// togliamo da mezzo i puntatori senza una zona di memoria
		puntatori.clear();

		// *** delete() casuale
		++num_test;
		// Prepariamo un nuovo set di puntatori da cancellare in ordine casuale.
		for (size_t allocazioni = 0; allocazioni < 10000; ++allocazioni) {
			int dim = rnd_dim(rnd_engine);
			char* pchar = new char[dim];
			puntatori.push_back(pchar);
		}
		// preapariamo prima della misurazione un ordine di cancellazione casuale
		//std::uniform_int_distribution<long long> rnd_indice(0, (puntatori.size() - 1)); // indice casuale all'interno del vettore
		parametri._Init(0, (puntatori.size() - 1));
		rnd_indice.param(parametri);
		// per un 50K volte scambiano due numeri all'inetrno del vettore
		for (size_t volte = 1; volte <= 50000; ++volte) {
			// generiamo 2 indici casuali
			size_t indice1 = rnd_indice(rnd_engine);
			size_t indice2 = rnd_indice(rnd_engine);
			if (indice1 != indice2) {
				// scambio
				char* pchar_temp = puntatori[indice1];
				puntatori[indice1] = puntatori[indice2];
				puntatori[indice2] = pchar_temp;
			}
		}
		// ora li cancelliamo in ordine casuale
		//std::cout << "Misurazione del tempo per deallocare i 10K oggetti ma in ordine casuale:\n\n";
		// prendiamo il tempo iniziale
		time_start = std::chrono::system_clock::now();
		time_now = std::chrono::system_clock::to_time_t(time_start);
		localtime_s(&time_struct, &time_now);
		asctime_s(time_str, sizeof(time_str), &time_struct);
		std::cout << "Inizio del test " << (num_test + 1) << ": " << time_str << std::endl;
		// esecuzione del test
		delete_puntatori(puntatori);
		// prendiamo il tempo finale
		time_stop = std::chrono::system_clock::now();
		time_now = std::chrono::system_clock::to_time_t(time_stop);
		localtime_s(&time_struct, &time_now);
		asctime_s(time_str, &time_struct);
		std::cout << "Fine del test: " << time_str << std::endl;
		time_diff = std::chrono::duration_cast<std::chrono::milliseconds>((time_stop - time_start));
		//std::cout << "Durata del test (millisecondi): " << time_diff.count() << std::endl << std::endl;
		misurazioni[num_test].add(time_diff.count());
		// togliamo da mezzo i puntatori senza una zona di memoria
		puntatori.clear();

		// *** Pool get()
		// Facciamo lo stesso allocando 10000 oggetti di 500 byte nel pool.
		++num_test;
		//std::cout << "Misurazione del tempo necessario per allocare 10K oggetti di 500 byte nel Pool:\n\n";
		//MyVector_Pool<struct_500, 10000> array_char;
		//std::vector<struct_500*> puntatori_array_500;
		// prendiamo il tempo iniziale
		time_start = std::chrono::system_clock::now();
		time_now = std::chrono::system_clock::to_time_t(time_start);
		localtime_s(&time_struct, &time_now);
		asctime_s(time_str, sizeof(time_str), &time_struct);
		std::cout << "Inizio del test " << (num_test + 1) << ": " << time_str << std::endl;
		// esecuzione del test
		for (size_t allocazioni = 1; allocazioni <= 10000; ++allocazioni) {
			struct_500* p = array_char.get();
			if (p) puntatori_array_500.push_back(p);
			else throw; // non ci sono abbastanza allocazioni !?
		}
		// prendiamo il tempo finale
		time_stop = std::chrono::system_clock::now();
		time_now = std::chrono::system_clock::to_time_t(time_stop);
		localtime_s(&time_struct, &time_now);
		asctime_s(time_str, &time_struct);
		std::cout << "Fine del test: " << time_str << std::endl;
		time_diff = std::chrono::duration_cast<std::chrono::milliseconds>((time_stop - time_start));
		//std::cout << "Durata del test (millisecondi): " << time_diff.count() << std::endl << std::endl;
		misurazioni[num_test].add(time_diff.count());

		// *** Pool del()
		// Misuriamo il tempo nel rilasciare i dati del Pool.
		++num_test;
		//std::cout << "Misurazione del tempo per deallocare i 10K oggetti dal Pool:\n\n";
		// prendiamo il tempo iniziale
		time_start = std::chrono::system_clock::now();
		time_now = std::chrono::system_clock::to_time_t(time_start);
		localtime_s(&time_struct, &time_now);
		asctime_s(time_str, sizeof(time_str), &time_struct);
		std::cout << "Inizio del test " << (num_test + 1) << ": " << time_str << std::endl;
		// esecuzione del test
		delete_puntatori(puntatori_array_500, array_char);
		// prendiamo il tempo finale
		time_stop = std::chrono::system_clock::now();
		time_now = std::chrono::system_clock::to_time_t(time_stop);
		localtime_s(&time_struct, &time_now);
		asctime_s(time_str, &time_struct);
		std::cout << "Fine del test: " << time_str << std::endl;
		time_diff = std::chrono::duration_cast<std::chrono::milliseconds>((time_stop - time_start));
		//std::cout << "Durata del test (millisecondi): " << time_diff.count() << std::endl << std::endl;
		misurazioni[num_test].add(time_diff.count());
		// togliamo da mezzo i puntatori senza una zona di memoria
		puntatori_array_500.clear();

		// *** Pool del() inverso
		++num_test;
		// Prepariamo un nuovo set di puntatori da cancellare in ordine inverso.
		for (size_t allocazioni = 1; allocazioni <= 10000; ++allocazioni) {
			struct_500* p = array_char.get();
			if (p) puntatori_array_500.push_back(p);
			else throw; // non ci sono abbastanza allocazioni !?
		}
		// invertiamo l'ordine
		std::reverse(puntatori_array_500.begin(), puntatori_array_500.end());
		//std::cout << "Misurazione del tempo per deallocare in ordine inverso i 10K oggetti dal Pool:\n\n";
		// prendiamo il tempo iniziale
		time_start = std::chrono::system_clock::now();
		time_now = std::chrono::system_clock::to_time_t(time_start);
		localtime_s(&time_struct, &time_now);
		asctime_s(time_str, sizeof(time_str), &time_struct);
		std::cout << "Inizio del test " << (num_test + 1) << ": " << time_str << std::endl;
		// esecuzione del test
		delete_puntatori(puntatori_array_500, array_char);
		// prendiamo il tempo finale
		time_stop = std::chrono::system_clock::now();
		time_now = std::chrono::system_clock::to_time_t(time_stop);
		localtime_s(&time_struct, &time_now);
		asctime_s(time_str, &time_struct);
		std::cout << "Fine del test: " << time_str << std::endl;
		time_diff = std::chrono::duration_cast<std::chrono::milliseconds>((time_stop - time_start));
		//std::cout << "Durata del test (millisecondi): " << time_diff.count() << std::endl << std::endl;
		misurazioni[num_test].add(time_diff.count());
		// togliamo da mezzo i puntatori senza una zona di memoria
		puntatori_array_500.clear();

		// *** Pool del() casuale
		++num_test;
		// Prepariamo un nuovo set di puntatori da cancellare in ordine casuale.
		for (size_t allocazioni = 1; allocazioni <= 10000; ++allocazioni) {
			struct_500* p = array_char.get();
			if (p) puntatori_array_500.push_back(p);
			else throw; // non ci sono abbastanza allocazioni !?
		}
		// per un 50K volte scambiano due puntatori all'inetrno del vettore
		//std::uniform_int_distribution<long long>::param_type parametri(0, (puntatori_array_500.size() - 1));
		parametri._Init(0, (puntatori_array_500.size() - 1));
		rnd_indice.param(parametri);
		for (size_t volte = 1; volte <= 50000; ++volte) {
			// generiamo 2 indici casuali
			size_t indice1 = rnd_indice(rnd_engine);
			size_t indice2 = rnd_indice(rnd_engine);
			if (indice1 != indice2) {
				// scambio
				struct_500* p500_temp = puntatori_array_500[indice1];
				puntatori_array_500[indice1] = puntatori_array_500[indice2];
				puntatori_array_500[indice2] = p500_temp;
			}
		}
		//std::cout << "Misurazione del tempo per deallocare in ordine casuale i 10K oggetti dal Pool:\n\n";
		// prendiamo il tempo iniziale
		time_start = std::chrono::system_clock::now();
		time_now = std::chrono::system_clock::to_time_t(time_start);
		localtime_s(&time_struct, &time_now);
		asctime_s(time_str, sizeof(time_str), &time_struct);
		std::cout << "Inizio del test " << (num_test + 1) << ": " << time_str << std::endl;
		// esecuzione del test
		delete_puntatori(puntatori_array_500, array_char);
		// prendiamo il tempo finale
		time_stop = std::chrono::system_clock::now();
		time_now = std::chrono::system_clock::to_time_t(time_stop);
		localtime_s(&time_struct, &time_now);
		asctime_s(time_str, &time_struct);
		std::cout << "Fine del test: " << time_str << std::endl;
		time_diff = std::chrono::duration_cast<std::chrono::milliseconds>((time_stop - time_start));
		//std::cout << "Durata del test (millisecondi): " << time_diff.count() << std::endl << std::endl;
		misurazioni[num_test].add(time_diff.count());
		// togliamo da mezzo i puntatori senza una zona di memoria
		puntatori_array_500.clear();

		// *** stack
		// allocazione di 10000 oggetti di dimensione casuale [1000-0) byte in una pila
		++num_test;
		//std::stack<char*> pila;
		//std::cout << "Misurazione del tempo per inserire nella pila 10K oggetti di dimensioni [1000:0) byte:\n\n";
		// prendiamo il tempo iniziale
		time_start = std::chrono::system_clock::now();
		time_now = std::chrono::system_clock::to_time_t(time_start);
		localtime_s(&time_struct, &time_now);
		asctime_s(time_str, sizeof(time_str), &time_struct);
		std::cout << "Inizio del test " << (num_test + 1) << ": " << time_str << std::endl;
		// esecuzione del test
		for (size_t allocazioni = 1; allocazioni <= 10000; ++allocazioni) {
			int dim = rnd_dim(rnd_engine);
			//char* pchar = new char[dim];
			pila.emplace(new char[dim]);
		}
		// prendiamo il tempo finale
		time_stop = std::chrono::system_clock::now();
		time_now = std::chrono::system_clock::to_time_t(time_stop);
		localtime_s(&time_struct, &time_now);
		asctime_s(time_str, &time_struct);
		std::cout << "Fine del test: " << time_str << std::endl;
		time_diff = std::chrono::duration_cast<std::chrono::milliseconds>((time_stop - time_start));
		//std::cout << "Durata del test (millisecondi): " << time_diff.count() << std::endl << std::endl;
		misurazioni[num_test].add(time_diff.count());

		/*
		// Test size dello stack
		for (size_t count = 0; count < pila.size(); ++count) pila.pop();
		pila.emplace(new char[10] {'c', 'i', 'a', 'o', ' ', 'b', 'r', 'o', '.', '\0'});
		char* elemento = pila.top();
		std::cout << "Elemento '" << elemento << "' di dimensione " << sizeof(*elemento) << " byte\n";
		*/

		// *** stack pop()
		// deallocazione in modo inverso dalla pila, siccome lo stack è di tipo Last Input - First Output basta recuperarli con la propria funzione membro 
		++num_test;
		//std::cout << "Misurazione del tempo per togliere dalla pila 10K oggetti di dimensioni [1000:0) byte:\n\n";
		// prendiamo il tempo iniziale
		time_start = std::chrono::system_clock::now();
		time_now = std::chrono::system_clock::to_time_t(time_start);
		localtime_s(&time_struct, &time_now);
		asctime_s(time_str, sizeof(time_str), &time_struct);
		std::cout << "Inizio del test " << (num_test + 1) << ": " << time_str << std::endl;
		// esecuzione del test
		while (!pila.empty()) pila.pop();
		// prendiamo il tempo finale
		time_stop = std::chrono::system_clock::now();
		time_now = std::chrono::system_clock::to_time_t(time_stop);
		localtime_s(&time_struct, &time_now);
		asctime_s(time_str, &time_struct);
		std::cout << "Fine del test: " << time_str << std::endl;
		time_diff = std::chrono::duration_cast<std::chrono::milliseconds>((time_stop - time_start));
		//std::cout << "Durata del test (millisecondi): " << time_diff.count() << std::endl << std::endl;
		misurazioni[num_test].add(time_diff.count());
	}

	// Ora stampiamo i risultati:
	std::cout << "\n\n\nRisultati dei test : \n\n";

	for (test t : misurazioni) {
		t.stampa_nome(std::cout) << std::endl;
		std::cout << "Risultati: "; t.stampa_risultati(std::cout) << std::endl;
		std::cout << "Media: " << t.media() << "\n\n";
	}
	
	return 0;
}