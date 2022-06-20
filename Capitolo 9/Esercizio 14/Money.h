#pragma once

#include <iostream>
#include <string>
#include <vector>

// struttura dati di un fattore di conversione:
// quando vogliamo convertire dalla valuta "da" alla valuta "a" moltiplicamio il valore per "fattore"
// mentre quando siamo noi la valuta "a" e vogliamo convertire in "da" allora dividiamo per "fattore" o moltiplichiamo per 1/fattore.
struct Cambi {
	std::string da;
	std::string a;
	long double fattore;
};

class Money {
public:
	//Money();
	Money(std::string valuta = "USD", double prezzo = 0.0);
	void centesimi(long int); // imposta i centesimi
	long int centesimi() const; // legge _cent
	void valuta(std::string); // imposta la valuta senza conversioni
	std::string valuta() const; // restituisce la valuta corrente
	void print() const;
	std::istream& calcola(std::istream& input); // legge lo streram per eseguire calcoli finanziari e il risultato lo memorizza
	void converti(std::string); // coverte in altra valuta il valore corrente
	class Error {};
private:
	long int _cent;
	void _arrotondamento(); // arrotondo _cont al decimo di centesimo, ad es. .56 cent diventono .60
	std::string _valuta;
	std::vector<Cambi> _indici; // indici della borsa
	void _init_valuta(); // inizializza la tabelle delle valute, poi ci vorrà una interfaccia per gli aggiornamenti.
	bool _valuta_exist() const; // controlla che la valuta esista nella tabbella
};

std::ostream& operator<<(std::ostream&, const Money&);
std::istream& operator>>(std::istream&, Money&);
Money operator+(const Money&, const Money&);
Money operator-(const Money&, const Money&);
Money operator*(const Money&, const Money&);
Money operator/(const Money&, const Money&);
