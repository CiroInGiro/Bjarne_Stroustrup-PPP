/*
Capitolo 20 Esercizio 1
Se non lo hai ancora fatto, prova tutti i Try This di questo capitolo.
*/

#include <iostream>
#include <vector>

// Jack mette i dati in un array e restituisce il numero di elementi in *count
double* get_from_jack(int* count) { return nullptr; }

// Jill riempe il vettore
std::vector<double>* get_from_jill() { return nullptr; }

void fct() {
	int jack_count{ 0 };
	double* jack_data = get_from_jack(&jack_count);
	std::vector<double>* jill_data = get_from_jill();
	// faccio qualcosa
	double h{ -1 };
	double* jack_high{ nullptr };
	double* jill_high{ nullptr };
	// elaboro i dati di Jack
	for (int i = 0; i < jack_count; ++i) {
		if (h < jack_data[i]) { h = jack_data[i]; jack_high = &jack_data[i]; }
	}
	// elaboro i dati di Jill
	h = -1;
	for (int i = 0; i < jill_data->size(); ++i) {
		if (h < (*jill_data)[i]) { h = (*jill_data)[i]; jill_high = &(*jill_data)[i]; }
	}
	std::cout << "Il valore più alto nei dati di Jack: " << *jack_high << ";" << std::endl;
	std::cout << "Il valore più alto nei dati di Jill: " << *jill_high << "." << std::endl;
	delete[] jack_data;
	delete jill_data;
}

/*
Try This
Se tu fossi in grado di cambiare il codice di Jill, come cambieresti la sua interfaccia per eliminare la bruttezza?
*/
// prendo come argomento un puntatore al vettore da riempire e lavoro su quello senza restituire niente o restituire il codice di stato.
void get_from_jill2(std::vector<double>* v); // interfaccia che chiama poi get_from_jill();

double* high(double* first, double* last) {
	double* highest{ nullptr };
	double h{ -1 };
	for (double* p = first; first != last; ++first) {
		if (h < *p) { h = *p; highest = p; }
	}
	return highest;
}

void fct2() {
	int jack_count{ 0 };
	double* jack_data = get_from_jack(&jack_count);
	std::vector<double>* jill_data = get_from_jill();
	// faccio qualcosa
	double* jack_high{ nullptr };
	double* jill_high{ nullptr };
	// elaboro i dati di Jack
	jack_high = high(jack_data, (jack_data + jack_count));
	// elaboro i dati di Jill
	std::vector<double>& rif_jill_data = *jill_data;
	jill_high = high(&rif_jill_data[0], (&rif_jill_data[0] + rif_jill_data.size()));
	std::cout << "Il valore più alto nei dati di Jack: " << *jack_high << ";" << std::endl;
	std::cout << "Il valore più alto nei dati di Jill: " << *jill_high << "." << std::endl;
	delete[] jack_data;
	delete jill_data;
}

/*
Try This
Abbiamo lasciato due potenziali e seri errori in questo piccolo programma.
Uno può provocare un crash e l'altro può dare risultati inattesi se high è usato in altri programmi dove può essere utile.
Le tecniche generali che descriviamo di seguito le renderanno ovvie e mostreranno come evitarle sistematicamente.
Per ora basta trovarle e suggerire i rimedi.
*/

// impostando il puntatore a 0 sapremo se high ha avuto esito positivo ed evitiamo dati inattesi per un puntatore indefinito.
// double* highest{ nullptr };

// Impostando h già al primo valore siamo sicuri di confrontare solo i valori nel range di dati da eaminare e non rischiare ad esempio di evitare il confronto per dati presentati tutti minori del valore -1
// double h{ *first };

/*
Try This
Scrivi una funzione void copy(int* f1, int* e1, int* f2) che copia gli elementi di un array di interi definito come [f1:e1] nell'altro [f2:(f2 + e1-f1)]
Usa solo le operazioni di iterator menzionate prima (non subscripting)
*/

void copy(int* f1, int* e1, int* f2) {
	int* ar2 = f2;
	for (int* p = f1; p != e1; ++p) {
		*ar2 = *p;
		++ar2;
	}
}

template<typename Iterator>
//requires Iterator<Iterator>();
Iterator high(Iterator start, Iterator end) {
	if (!start || !end) return nullptr;
	if (start > end) return nullptr;
	Iterator h = start;
	for (Iterator p = start; p != end; ++p) {
		if (*h < *p) h = p;
	}
	return h;
}

/*
Try This
Abbiamo lasciato Ancora  un serio problema al programma. Trovalo e riparalo, suggerisci un rimedio in generale per questo tipo di problemi.
*/
// ho aggiunto dei controlli sugli iteratori che tra l'altro devono essere puntatori e non qualsiasi tipo

/*
Try This
Nello Standard Library il vettore non provvede alla funzione membro push_front(), perché secondo te.
Prova a implementare la funzione push_front()
*/
template<typename T, typename A = std::allocator<T>>
class mvector {
public:
	class iterator {
		T* iter;
	public:
		iterator(T* addr) : iter{addr} {}
		T* operator*() { return iter; }
	};
	using size_type = unsigned long;
	mvector() {};
	iterator push_front(T val) {
		// riserviamoci lo spazio di size() + 1 per aggiungere un elemento
		reserve(size() + 1);
		// copiamo tutti gli elementi attuali di un posto in avanti partendo dalla coda
		for (iterator i = (end() - 1); i != begin(); --i) {
			*i = *(i - 1);
		}
		// al posto attuale assegniamo il valore nuovo
		*(begin()) = val;
		// restituiamo l'iteratore del valore attuale
		return begin();
	}
	void reserve();
	size_type size() const;
	iterator begin();
	iterator end();
};



/*
Try This
Riscrivi advance(Iter& p, int n) in modo che indietreggi se si passa un valore negativo
*/
template<typename Iter>
void advance(Iter& p, int n) {
	if (n > 0) {
		while (n != 0) {
			--p;
			--n;
		}
	}
	if (n < 0) {
		while (n != 0) {
			++p;
			++n;
		}
	}
}

/*
Try This
Cosa significa questa lista di fiferenze nel codice reale?
Per ognuno di array di char, vector<char>, list<char> e string, 
definiscine uno con il valore "Hello", passalo in una funzione come argomento,
scrivi in output il numero di caratteri nella stringa passata, prova a confrontarla
con "Hello" nella funzione (per vedere se realmente hai passato "Hello"),
e confronta l'argomento con "Howdy" per vedere quale sarebbe prima in un dizionario.
Copia l'argomento in un'altra variabile dello stesso tipo.
*/

template <typename Iter>
// requires input_iterator<Iter>();
void fchar(Iter start, Iter end) {
	std::string s;
	int count{ 0 };
	while (start != end) {
		s += *start;
		++start;
		++count;
	}
	std::cout << "Mi hai passato " << s << std::endl;
	std::cout << "Il numero di caratteri sono: " << count << std::endl;
	std::string s2{ "Howdy" };
	s < s2 ? std::cout << s << " è minore di " << s2 << ".\n" : std::cout << s << " è maggiore di " << s2 << ".\n";
}

#include <list>
int main(int argc, char** argv) {
	char ac[6]{ 'H', 'e', 'l', 'l', 'o', '\0' }; // la lunghezza è 1 in più per il carattere terminatore
	std::vector<char> vc{ 'H', 'e', 'l', 'l', 'o' }; // al vettore non serve perché viene allocato lo spazio nella memoria estesa per ogni carattere in contiguo
	std::list<char> lc{ 'H', 'e', 'l', 'l', 'o' }; // la lista è simile al vettore ma non alloca in maniera contigua
	std::string sc{ "Hello" }; // la stringa è come al vettore ma semplifica la gestione dei caratteri come testo e non come singoli caratteri.
	std::cout << "\nAdesso chiamo la funzione con array di caratteri 'H','e','l','l','o','\\0':" << std::endl;
	fchar(&ac[0], &ac[0]+6);
	std::cout << "\nAdesso chiamo la funzione con vettore di caratteri 'H','e','l','l','o':" << std::endl;
	fchar(vc.begin(), vc.end());
	std::cout << "\nAdesso chiamo la funzione con la lista di caratteri 'H','e','l','l','o':" << std::endl;
	fchar(lc.begin(), lc.end());
	std::cout << "\nAdesso chiamo la funzione con la stringa \"Hello\":" << std::endl;
	fchar(sc.begin(), sc.end());
	// l'array che utilizza singoli caratteri ha bisogno anche di un carattere terminatore per far capire che la stringa è finita altrimenti se seguiamo il puntatore dal primo caratteri finiamo in memoria fuori dall'array
	// se passiamo un puntatore al primo elemento del vettore finiremo con leggere anche nello spazio non allocato o fuori dalla memoria assegnata dal vettore perché manca il terminatore e nonpossiamo controllare se il puntatore è valido
	// se usiamo la lista possiamo leggere solo il primo carattere valido perché la memoria non è contigua
	// la stringa invece è un vettore specifico per i caratteri e gestisce lei la fine delle stringe

/*
Try This
Esegui il precedente 'Try This' per un array di int e un list<int> ognuno coi valori {1, 2, 3, 4, 5 }
*/
	int ai[]{ 1, 2, 3, 4, 5 };
	std::list<int> li{ 1, 2, 3, 4, 5 };
	std::cout << "\nAdesso chiamo la funzione con un array di int da 1 a 5:" << std::endl;
	fchar(&ai[0], &ai[0]+5);
	std::cout << "\nAdesso chiamo la funzione con la lista di int da 1 a 5:" << std::endl;
	fchar(li.begin(), li.end());
	return 0;
}