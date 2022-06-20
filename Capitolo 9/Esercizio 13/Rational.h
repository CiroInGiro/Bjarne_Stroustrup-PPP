#pragma once

#include <string>
#include <vector>

class Rational
{
public:
	Rational(); // di default viene impostato al valore 1
	Rational(int, int denominatore = 1); // creato con un numeratore e denominatore
	int numeratore() const;
	void numeratore(int);
	int denominatore() const;
	void denominatore(int);
	double frazione() const;
	void operator=(const Rational&);
	class Error {
	public:
		Error() {}
		Error(std::string message) :_message{ message } {}
	private:
		std::string _message;
	};

private:
	// i numeri razionali sono composti da numeratore e denominatore interi
	int _numeratore;
	int _denominatore;
};

// operatori
Rational operator+(const Rational&, const Rational&);
Rational operator-(const Rational&, const Rational&);
Rational operator*(const Rational&, const Rational&);
Rational operator/(const Rational&, const Rational&);
bool operator==(const Rational&, const Rational&);

// funzioni di semplificazione
int mcm(int, int); // calcola il minimo comune multiplo fra due numeri
std::vector<int> scomposizione(int); // scompone un numero nella sequenza di moltiplicazioni di numeri naturali più piccoli possibili
void vector_sort(std::vector<int>& vettore);
int eleva_potenza(int base, int esponente); // calcola la potenza di un numero.
Rational semplificazione(Rational&); // semplifica una frazione

// forse ci servirà una funzione per semplificare le frazioni.