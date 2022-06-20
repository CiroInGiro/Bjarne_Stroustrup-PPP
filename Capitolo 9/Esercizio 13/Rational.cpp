#include "Rational.h"
//#include <vector>

Rational::Rational() :_numeratore{ 1 }, _denominatore{ 1 } {} // evitiamo di inizializzare una frazione che dia subito un division by zero.

Rational::Rational(int numeratore, int denominatore) : _numeratore{ numeratore }, _denominatore{ denominatore } {
	if (numeratore == 0) throw Error("Rational: numeratore a zero");
	if (denominatore == 0) throw Error("Rational: denominatore a zero");
}

int Rational::numeratore() const { return _numeratore; }

void Rational::numeratore(int numeratore) {
	if (numeratore == 0) throw Error("Rational: numeratore a zero");
	_numeratore = numeratore;
}

int Rational::denominatore() const { return _denominatore; }

void Rational::denominatore(int denominatore) {
	if (denominatore == 0) throw Error("Rational: denominatore a zero");
	_denominatore = denominatore;
}

double Rational::frazione() const { 
	double retVal = (double)_numeratore / (double)_denominatore;
	return retVal;
}

void Rational::operator=(const Rational& right) {
	_numeratore = right.numeratore();
	_denominatore = right.denominatore();
}

// Operatori
Rational operator+(const Rational& left, const Rational& right) {
	Rational retVal;

	retVal.numeratore((left.numeratore() + right.numeratore()));
	if (left.denominatore() == right.denominatore()) retVal.denominatore(left.denominatore());
	else {
		retVal.denominatore(mcm(left.denominatore(), right.denominatore()));
	}

	return retVal;
}

Rational operator-(const Rational& left, const Rational& right) {
	Rational retVal;

	retVal.numeratore((left.numeratore() - right.numeratore()));
	if (left.denominatore() == right.denominatore()) retVal.denominatore(left.denominatore());
	else {
		retVal.denominatore(mcm(left.denominatore(), right.denominatore()));
	}

	return retVal;
}

Rational operator*(const Rational& left, const Rational& right) {
	Rational retVal;

	retVal.numeratore((left.numeratore() * right.numeratore()));
	retVal.denominatore((left.denominatore() * right.denominatore()));
	retVal = semplificazione(retVal);

	return retVal;
}

Rational operator/(const Rational& left, const Rational& right) {
	Rational retVal;

	retVal.numeratore(right.denominatore()); // invertiamo numeratore e denominatore di una delle due frazioni
	retVal.denominatore(right.numeratore());
	retVal = left * retVal;

	return retVal;
}

bool operator==(const Rational& left, const Rational& right) {
	// credo che la cosa più semplice è convertire i valori in double e confrontari
	return (left.frazione() == right.frazione());
}

// Funzioni di Comodo
int mcm(int denominatore1, int denominatore2) {
	std::vector<int> divisori1 = scomposizione(denominatore1); // numeri della scomposizione sul denominatore interno
	std::vector<int> divisori2 = scomposizione(denominatore2); // numeri della scomposizione sul denominatore passato come parametro

	/*
	int dividendo = denominatore1; // denominatore da scomporre
	int divisore = 2; // divisore da trovare

	while (dividendo != divisore) {
		if ((dividendo % divisore) == 0) {
			dividendo /= divisore;
			divisori1.push_back(divisore);
		}
		else if ((dividendo % divisore) > 0) {
			++divisore;
		}
		else {
			divisore = 2;
		} // il dividendo è troppo piccolo per il divisore
	}

	dividendo = denominatore2; // denominatore da scomporre
	divisore = 2; // divisore da trovare

	while (dividendo != divisore) {
		if ((dividendo % divisore) == 0) {
			dividendo /= divisore;
			divisori2.push_back(divisore);
		}
		else if ((dividendo % divisore) > 0) {
			++divisore;
		}
		else {
			divisore = 2;
		} // il dividendo è troppo piccolo per il divisore
	}
	*/
	// abbiamo i due vettori dei denominatori che contengono le loro scomposizioni in divisori, ora bisogna contarci le ripetizione che corrisponde al loro esponente se presi una sola volta per bumero.
	// per semplicità ci conviene ordinarci i vettori
	vector_sort(divisori1);
	vector_sort(divisori2);

	int mcm = { 0 }, exp1{ 0 }, exp2{ 0 }; // il minimo comune multiplo e la conta degli esponenti da confrontare
	int base{ 0 };
	if (divisori1.size() > 0) {
		base = divisori1[0];
		exp1 = 1;
	}

	for (unsigned int pos1 = 1; pos1 < divisori1.size(); ++pos1) {
		if (base == divisori1[pos1]) {
			++exp1;
		}
		else {
			for (int divisore : divisori2) {
				if (divisore == base) ++exp2;
			}
			exp1 < exp2 ? mcm += eleva_potenza(base, exp2) : mcm += eleva_potenza(base, exp1);
			base = divisori1[pos1];
			exp1 = 1;
			exp2 = 1;
		}
	}

	return mcm;
}

std::vector<int> scomposizione(int numero) {
	std::vector<int> retVal;
	int dividendo = numero; // denominatore da scomporre
	int divisore = 2; // divisore da trovare

	while (dividendo != divisore) {
		if ((dividendo % divisore) == 0) {
			dividendo /= divisore;
			retVal.push_back(divisore);
		}
		else if ((dividendo % divisore) > 0) {
			++divisore;
		}
		else {
			divisore = 2;
		} // il dividendo è troppo piccolo per il divisore
	}
	retVal.push_back(divisore); // l'ultimo numero della scomposizione che equivale a se stesso
	return retVal;
}

void vector_sort(std::vector<int>& vettore) {
	if (vettore.size() <= 1) return; // troppo pochi elementi
	for (unsigned int indice = 0; indice < (vettore.size() - 1); ++indice) {
		for (unsigned int pos = 1; pos < vettore.size(); ++pos) {
			if (vettore[indice] > vettore[pos]) {
				int temp = vettore[indice];
				vettore[indice] = vettore[pos];
				vettore[pos] = temp;
			}
		}
	}
}

int eleva_potenza(int base, int esponente) {
	int retVal{ base };
	if (base == 0) return 0;
	if (esponente == 1) return 1;
	for (int ciclo = 0; ciclo < esponente; ++ciclo) {
		retVal *= base;
	}
}

Rational semplificazione(Rational& frazione) {
	Rational retVal;
	std::vector<int> numeratori = scomposizione(frazione.numeratore());
	std::vector<int> denominatori = scomposizione(frazione.denominatore());

	for (unsigned int pos_num = 0; pos_num < numeratori.size(); ++pos_num) {
		for (unsigned int pos_den = 0; pos_den < denominatori.size(); ++pos_den) {
			if (numeratori[pos_num] == denominatori[pos_den]) {
				numeratori[pos_num] = 1; // vengono impostati ad 1 invece di togliere i valori dall'array sfalsando gli indici dello stesso
				denominatori[pos_den] = 1; // la moltiplicazione per 1 da sempre se stesso.
				break; // appena incontriamo uno uguale lo togliamo e ci fermiamo
			}
		}
	}

	for (int numeratore : numeratori) {
		retVal.numeratore((retVal.numeratore() * numeratore));
	}

	for (int denominatore : denominatori) {
		retVal.denominatore((retVal.denominatore() * denominatore));
	}

	return retVal;
}
