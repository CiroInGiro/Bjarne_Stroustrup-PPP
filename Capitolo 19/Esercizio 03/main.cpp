/*
Capitolo 19 Esercizio 3
Scrivi un modello di classe Pair che può memorizzare una coppia di valori di ogni tipo.
Usa questa per implementare una semplice tabella di simboli tipo quella utilizzata in calculator (paragrafo 7.8).
*/

#include <vector>
#include <iostream>

template <typename T, typename U>
class variable {
public:
	variable() {}
	void set(const T& n, const U& v) {
		name = n;
		val = v;
	}
	T get_name() const { return name; }
	U get_val() const { return val; }
private:
	T name;
	U val;
};

int main(int argc, char** argv) {
	std::vector<variable<std::string, double>> vars;
	variable<std::string, double> singolo;
	singolo.set("Lato sinistro", 12.8);
	vars.push_back(singolo);
	singolo.set("Lato destro", 12.8);
	vars.push_back(singolo);
	singolo.set("Lato superiore", 10.5);
	vars.push_back(singolo);
	singolo.set("Lato inferiore", 10.5);
	vars.push_back(singolo);
	for (variable<std::string, double> v : vars) {
		std::cout << "Variabile " << v.get_name() << " nel vettore vale " << v.get_val() << ";\n";
	}

	return 0;
}