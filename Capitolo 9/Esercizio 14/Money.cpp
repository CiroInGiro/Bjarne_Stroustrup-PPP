#include "Money.h"

/* col parametro di default a 0.0 abbiamo già incluso questo costruttore
Money::Money() {
	_cent = 0;
}
*/

Money::Money(std::string valuta, double prezzo) {
	//if (_cent < 0) throw Error();
	_init_valuta();
	_cent = (long int)(prezzo * 100);
	_arrotondamento();
	_valuta = valuta;
	if (!(_valuta_exist())) throw Error{};
}

void Money::centesimi(long int cent) {
	_cent = cent;
	_arrotondamento();
}

long int Money::centesimi() const { return _cent; }

void Money::valuta(std::string valuta) {
	_valuta = valuta;
	if (!_valuta_exist()) throw Error{};
}

std::string Money::valuta() const { return _valuta; }

void Money::print() const {
	double cent = (double)(_cent / 100.0);
	//std::cout << "$ " << cent;
	std::cout << _valuta << " " << cent;
}

void Money::_arrotondamento() {
	long int dollar = (long int)(_cent / 100);
	long int cent = (long int)(_cent - (dollar * 100)); // moltiplico di nuovo per 100 per rimettere gli zeri al posto delle cifre occupate dai decimali e centesimi
	long int decine = (long int)(cent / 10);
	cent -= (decine * 10);
	if (cent >= 5) { _cent += (10 - cent); }
	else { _cent -= cent; }
}

void Money::_init_valuta() {
	Cambi cambio;
	cambio.da = "USD";
	cambio.a = "DDK";
	cambio.fattore = 5;
	_indici.push_back(cambio);
	cambio.da = "USD";
	cambio.a = "EUR";
	cambio.fattore = 0.5;
	_indici.push_back(cambio);
	cambio.da = "EUR";
	cambio.a = "DDK";
	cambio.fattore = 10;
	_indici.push_back(cambio);
}

bool Money::_valuta_exist() const {
	for (Cambi cambio : _indici) {
		if (cambio.da == _valuta || cambio.a == _valuta) return true;
	}
	return false;
}

void Money::converti(std::string valuta) {
	if (_valuta == valuta) return;

	std::string da_valuta = _valuta;
	_valuta = valuta;

	if (!_valuta_exist()) throw Error{};

	for (Cambi indice : _indici) {
		if (indice.da == da_valuta && indice.a == _valuta) {
			_cent *= indice.fattore;
			return;
		}
		else if (indice.a == da_valuta && indice.da == _valuta) {
			_cent *= (1 / indice.fattore);
			return;
		}
	}
	// tabella indice con valuta mancante!
	throw Error{};
}

std::ostream& operator<<(std::ostream& os, const Money& saldo) {
	os << saldo.valuta();
	os << " ";
	os << ((long int)(saldo.centesimi()) / 100.0);
	return os;
}

std::istream& operator>>(std::istream& is, Money& saldo) {
	char carattere;
	//while (is >> carattere && carattere == '$' || !(isdigit(carattere))) {} // Esercizio 14
	/*
	while (is >> carattere && isdigit(carattere) || carattere == '.') {

	}
	*/
	// provo prima con un double
	std::string valuta = "";
	while (is >> carattere && !isdigit(carattere)) {
		valuta += carattere;
	}
	std::cin.putback(carattere);
	saldo.valuta(valuta);
	double cent;
	is >> cent;
	saldo.centesimi((long int)(cent * 100));
	return is;
}

Money operator+(const Money& left, const Money& right) {
	Money retVal;
	// aggiungendo le valute consideriamo la valuta principale quella a sinistra, quindi controlliamo e convertiamo quella a destra dell'operatore, a meno ché non siano uguali
	if (left.valuta() == right.valuta()) {
		retVal.valuta(left.valuta());
		retVal.centesimi((left.centesimi() + right.centesimi()));
	}
	else {
		// i parametri sono costanti quindi covertiamo la valuta di destra in quella di sinistra direttamente in retVal
		retVal.valuta(right.valuta());
		retVal.centesimi(right.centesimi());
		retVal.converti(left.valuta());
		// sommo il valore a destra convertito con quello sinistro della stessa valuta.
		retVal.centesimi(retVal.centesimi() + left.centesimi());
	}

	return retVal;
}

Money operator-(const Money& left, const Money& right) {
	Money retVal;
	retVal.valuta(right.valuta());
	retVal.centesimi(-(right.centesimi()));
	retVal = left + retVal;
	return retVal;
}

Money operator*(const Money& left, const Money& right) {
	Money retVal;
	// impostiamo a priori la valuta di destra perché se saranno diverse è quella che ci servirà in entrambe le condizioni
	retVal.valuta(right.valuta());

	if (left.valuta() == right.valuta()) {
		// la normale operazione che si faceva nell'esercizio precedente
		retVal.centesimi((left.centesimi() * right.centesimi()));
	}
	else {
		// in caso di valute diverse mi creo un Money convertito e uso di nuovo l'operatore* che ora si trova i parametri con la stessa valuta.
		retVal.centesimi(right.centesimi());
		retVal.converti(left.valuta());
		retVal = left * retVal;
	}

	return retVal;
}

Money operator/(const Money& left, const Money& right) {
	Money retVal;
	retVal.valuta(right.valuta());

	if (left.valuta() == right.valuta()) {
		retVal.centesimi((left.centesimi() / right.centesimi()));
	}
	else {
		retVal.centesimi(right.centesimi());
		retVal.converti(left.valuta());
		retVal = left * retVal;
	}

	return retVal;
}
