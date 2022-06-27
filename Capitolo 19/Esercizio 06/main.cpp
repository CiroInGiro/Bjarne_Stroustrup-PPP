/*
Capitolo 19 Esercizio 6
Ripeti il precedente esercizio ma con la classe Number<T> dove T può essere un valore numerico.
Prova ad aggiungere % a Number e vedi cosa succese utilizzando % con Number<double> e Number<int>.
*/

#include <iostream>

template<typename N>
//requires Numbers<N>()
class Number {
public:
	Number() {};
	Number(N i) { _i = i; }
	N get() const { return _i; }
	void set(const N& p) { _i = p; }
	void operator=(const Number<N>& p) { _i = p.get(); }
	Number<N> operator+(const Number<N>& p) const { 
		Number<N> retVal{ (_i + p.get()) };
		return retVal; 
	}
	void operator++() { ++_i; }
	Number<N> operator-(const Number<N>& p) const {
		Number<N> retVal{ (_i - p.get()) };
		return retVal;
	}
	void operator--() { --_i; }
	Number<N> operator*(const Number<N>& p) const {
		Number<N> retVal{ (_i * p.get()) };
		return retVal;
	}
	Number<N> operator/(const Number<N>& p) const {
		Number<N> retVal;
		if (p.get() == 0) retVal.set(0);
		else retVal.set((_i / p.get()));
		return retVal;
	}
	void operator+=(const Number<N>& p) { _i += p.get(); }
	void operator-=(const Number<N>& p) { _i -= p.get(); }
	void operator*=(const Number<N>& p) { _i *= p.get(); }
	void operator/=(const Number<N>& p) {
		if (p.get() == 0) _i = 0;
		else _i /= p.get();
	}
	operator bool() const {
		return _itest;
	}
	bool operator==(const Number<N>& r) const {
		return (_i == r.get());
	}
	bool operator<(const Number<N>& r) const {
		return (_i < r.get());
	}
	bool operator>(const Number<N>& r) const {
		return !(*this < r);
	}
	void good() { _itest = true; }
	void bad() { _itest = false; }
	Number<N> operator%(const Number<N>& d) const {
		Number<N> retVal{ (_i % d.get()) };
		return retVal;
	}
private:
	N _i;
	bool _itest{ false };
};

int main(int argc, char** argv) {
	Number<double> id{ 5.4 };
	Number<double> id2{ 2.0 };
	using std::cout;
	// con i double si ottiene un errore a livello di compilazione
	//cout << "Inizializzate due Int<double> a " << id.get() << " e " << id2.get() << "; il modulo tra il primo e il secondo vale: " << (id % id2).get() << "\n";
	Number<int> ii{ 5 };
	Number<int> ii2{ 2 };
	using std::cout;
	cout << "Inizializzate due Int<int> a " << ii.get() << " e " << ii2.get() << "; il modulo tra il primo e il secondo vale: " << (ii % ii2).get() << "\n";
	return 0;
}