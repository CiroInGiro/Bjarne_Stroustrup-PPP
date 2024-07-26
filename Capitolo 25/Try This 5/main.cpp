/*
* La chiave è bs; qual'era il testo?
*/

// usiamo la funzione di decryptazione dal testo.

#include <iostream>
#include <fstream>
#include <iomanip>

void encipher(const unsigned long* const v, unsigned long* const w, const unsigned long* const k) {
	// vettore v == testo da decifrare
	// vettore w == testo decifrato
	// vettore k == chiave

	// funziona prevedendo una dimensione di long pari a 4 byte
	static_assert(sizeof(long) == 4, "size of long wrong for TEA"); // TEA is Tiny Encrypt Algorithm

	unsigned long y = v[0]; // y contiene la prima parte del testo cifrato 1 long su 2
	unsigned long z = v[1]; // z contiene la seconda parte del testo cifrato 2° long

	unsigned long sum = 0;
	const unsigned long delta = 0x9E3779B9;

	for (unsigned long n = 32; n-- > 0;) {
		y += (z << 4 ^ z >> 5) + z ^ sum + k[sum & 3];
		sum += delta;
		z += (y << 4 ^ y >> 5) + y ^ sum + k[sum >> 11 & 3];
	}
	w[0] = y;
	w[1] = z;
}

void decipher(const unsigned long* const v, unsigned long* const w, const unsigned long* const k) {
	// vettore v == testo da decifrare
	// vettore w == testo decifrato
	// vettore k == chiave
	
	// funziona prevedendo una dimensione di long pari a 4 byte
	static_assert(sizeof(long) == 4, "size of long wrong for TEA"); // TEA is Tiny Encrypt Algorithm

	unsigned long y = v[0]; // y contiene la prima parte del testo cifrato 1 long su 2
	unsigned long z = v[1]; // z contiene la seconda parte del testo cifrato 2° long

	unsigned long sum = 0xC6EF3720;
	const unsigned long delta = 0x9E3779B9;
	
	// sum = delta<<5, in general sum = delta * n
	for (unsigned long n = 32; n-- > 0;) {
		z -= (y << 4 ^ y >> 5) + y ^ sum + k[sum >> 11 & 3];
		sum -= delta;
		y -= (z << 4 ^ z >> 5) + z ^ sum + k[sum & 3];
	}
	w[0] = y;
	w[1] = z;
}

void test() {
	std::string testo = "5b8fb57c";

	char c = 'a';
	unsigned long ul = char('a');

	std::cout << "c: " << c << "; ul: " << ul << std::endl;

	std::cout << "hex ul: " << std::hex << ul;
}

unsigned long hextolong(const char c) {
	unsigned long retVal{ 0 };
	switch (c) {
	case '1':
		retVal = 1;
		break;
	case '2':
		retVal = 2;
		break;
	case '3':
		retVal = 3;
		break;
	case '4':
		retVal = 4;
		break;
	case '5':
		retVal = 5;
		break;
	case '6':
		retVal = 6;
		break;
	case '7':
		retVal = 7;
		break;
	case '8':
		retVal = 8;
		break;
	case '9':
		retVal = 9;
		break;
	case 'a':
		retVal = 10;
		break;
	case 'b':
		retVal = 11;
		break;
	case 'c':
		retVal = 12;
		break;
	case 'd':
		retVal = 13;
		break;
	case 'e':
		retVal = 14;
		break;
	case 'f':
		retVal = 15;
		break;
	default:
		retVal = 0;
		break;
	}
	return retVal;
}

unsigned long hextolong(const char* const c, size_t l) {
	unsigned long retVal{ 0 };
	size_t peso = l;
	for (size_t n = 0; n < l; ++n) retVal += std::pow(16, --peso) * hextolong(c[n]);
	return retVal;
}

int main() {
	const int nchar = 2 * sizeof(long); // 64 bit
	const int kchar = 2 * nchar; // 128 bit

	//std::string op;
	std::string key;
	std::string infile;
	std::string outfile;
	
	//std::cout << "Dammi il nome del file da leggere, del file in cui scrivere e la chiave:\n";
	//std::cin >> infile >> outfile >> key;
	infile = "testo cifrato.txt";
	outfile = "testo chiaro.txt";
	key = "bs";

	while (key.size() < kchar) key += '0'; // pad key: riempe la lunghezza della chiave quando più corta di 128 bit

	std::ifstream inf(infile);
	std::ofstream outf(outfile);
	if (!inf || !outf) {
		std::cout << "Errore file." << std::endl;
		return 1;
	}

	const unsigned long* k = reinterpret_cast<const unsigned long*>(key.data());
	char outbuf[nchar + 1]; // dal libro
	outbuf[nchar] = 0; // dal libro
	unsigned long* outptr = reinterpret_cast<unsigned long*>(outbuf); // dal libro
	char inbuf[nchar+1];
	inbuf[nchar] = 0;
	//unsigned long* inptr = reinterpret_cast<unsigned long*>(inbuf);
	unsigned long inptr[2]; // dal libro
	//int count = 0;
	//inf.setf(std::ios_base::hex, std::ios_base::basefield); // dal libro

	/*
	* per decifrare dovremmo leggere dal file 2 long e leggere outptr come sequenze di caratteri.
	*/

	// ciclo per decifrare il file
	inf >> inbuf;
	inptr[0] = hextolong(inbuf, nchar);
	inf >> inbuf;
	inptr[1] = hextolong(inbuf, nchar);
	//while (inf >> inptr[0] >> inptr[1]) { // dal libro
	while (!inf.eof()) {
		decipher(inptr, outptr, k);
		outf << outbuf; // dal libro

	//		if (++count == nchar) {
				//enchipher(inptr, outptr, k);
		inf >> inbuf;
		inptr[0] = hextolong(inbuf, nchar);
		inf >> inbuf;
		inptr[1] = hextolong(inbuf, nchar);
		// pad with leading zeros;
		//outf << std::setw(8) << std::setfill('0') << outptr[0] << ' ' << std::setw(8) << std::setfill('0') << outptr[1] << ' ';
		//count = 0;
//	}
	}

	/*
	if (count) {
		// pad
		while (count != nchar) inbuf[count++] = '0';
		//encipher(inptr, outptr, k);
		//outf << outptr[0] << ' ' << outptr[1] << ' ';
	}
	*/
	outf.close();
	inf.close();
	inbuf[0] = '\0';
	return 0;
}