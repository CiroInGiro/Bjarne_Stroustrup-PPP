/*
Capitolo 17 Esercizio 6
Questo capitolo non spiega cosa succede quando eccedi con la memoria utilizzando new().
Questo è chiamata esaurimento della memoria.
Scopri cosa succede.
Hai 2 ovvie alternative: guardare la documentazione o scrivere un programma con un loop infinito che alloca memoria senza mai deallocare.
Prova entrambe. Approssimativamente quanta memoria riesci a gestire prima del fallimento?
*/

#include <iostream>
#include <sstream>

std::string human(const unsigned long n) {
	std::ostringstream oss;
	unsigned long unit{ n };
	unsigned long b{ 0 };
	std::string suffix{ "b" };
	if (unit / 1000 > 0) {
		suffix = "Kb";
		b = unit % 1000;
		unit /= 1000;
	}
	if (unit / 1000 > 0) {
		suffix = "Mb";
		b += (unit % 1000) * 1000;
		unit /= 1000;
	}
	if (unit / 1000 > 0) {
		suffix = "Gb";
		b += (unit % 1000) * 1000 * 1000;
		unit /= 1000;
	}
	oss << unit << " " << suffix;
	if (b > 0) oss << " e " << human(b);
	return oss.str();
}

int main(int argc, char** argv) {
	char* p1{ nullptr };
	char* p2{ nullptr };
	const unsigned int blocco{ 1000000 };
	unsigned int bytes{ blocco };
	unsigned long allocati{ 0 };
	try {
		while (p1 = new char[bytes], p2 = new char[bytes]) {
			allocati += bytes * 2;
			std::cout << "Allocati attualmente " << human((allocati)) << std::endl;
			bytes += blocco;
			//delete[] p1; // una nuova chiamata a new() senza deallocare impegneremo la nuova allocazione oltre a mantenere la vecchia memoria allocata
		}
	}
	catch (std::exception e) {
		std::cerr << "Errore: " << e.what() << std::endl;
		// Bad Allocation a 2GB
		// Il limite credo che sia l'indirizzamento a 32 bit, come per i file in windows a 32 bit, provo a compilare a 64 bit
		// a 64 bit alloco 4GB
	}
	std::cin.get();
	return 0;
}