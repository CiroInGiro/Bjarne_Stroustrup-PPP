/*
Capitolo 19 esercizio 7
Prova la tua soluzione con l'esercizio 2 con alcuni Numbers.
*/

#include <iostream>
#include <vector>

template<typename N>
//requires Numbers<N>()
class Number {
public:
	Number() {};
	Number(N i) { _i = i; }
	Number(const Number& num) { _i = num.get(); }
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

template<typename T, typename U>
std::vector<T> f(std::vector<T>& vt, std::vector<U>& vu) {
	std::vector<T> retVal;
	int max = ((vt.size() > vu.size()) ? vu.size() : vt.size());
	for (int i = 0; i < max; ++i) {
		retVal.push_back((vt[i] + vu[i]));
	}
	if (vt.size() > vu.size()) {
		for (int i = vu.size(); i < vt.size(); ++i) retVal.push_back(vt[i]);
	}
	else if (vt.size() < vu.size()) {
		for (int i = vt.size(); i < vu.size(); ++i) retVal.push_back(vu[i]);
	}
	return retVal;
}

template<typename N>
// requires Number<T>()
std::istream& operator>>(std::istream& is, Number<N>& I) {
	N lettura{ 0 };
	if (is >> lettura) {
		I.good();
		I.set(lettura);
	}
	else I.bad();
	return is;
}

template<typename N>
// requires Number<N>()
std::ostream& operator<<(std::ostream& os, const Number<N>& I) {
	os << I.get();
	return os;
}

int main(int argc, char** argv) {
	std::vector<Number<double>> vnd{ {2.3}, {2.2}, {5.8} };
	std::vector<Number<double>> vni{ {32.0}, {80.7}, {32.5}, {21.9}, {1.3} };
	std::vector<Number<double>> vnsum = f(vnd, vni); // mi ritrovo in errore perché cerco di memorizzare un Number<int> nel vettore contenente i Number<double>
	using std::cout;
	cout << "Vettore 1:\n";
	for (Number<double> val : vnd) std::cout << "Valore del vettore: " << val << ";\n";
	cout << "\n\nVettore 2:\n";
	for (Number<double> val : vni) std::cout << "Valore del vettore: " << val << ";\n";
	cout << "\n\nVettore somma:\n";
	for (Number<double> val : vnsum) std::cout << "Valore del vettore: " << val << ";\n";
	return 0;
}