/* Capitolo 25 Esercizio 11
* Ripeti il precedente esercizio ma lascia i bits in un bitset<32>
*/

#include <iostream>
#include <bitset>

// inventiamo una struttura dati
struct PPN {
	unsigned short Id : 16;
	bool led_red : 1;
	bool led_yellow : 1;
	bool led_green : 1;
	bool reserved : 1;
	unsigned short status : 4;
	unsigned char link : 8;
}; // struttura di 32 bit: 16 | 1 | 1 | 1 | 1 | 4 | 8

void stampa_PPN(PPN data) {
	using std::cout;
	using std::endl;
	cout << "ID: " << data.Id << ";\n";
	if (data.led_red) cout << "LED rosso acceso;\n"; else cout << "LED rosso spento;\n";
	if (data.led_yellow) cout << "LED giallo acceso;\n"; else cout << "LED giallo spento;\n";
	if (data.led_green) cout << "LED verde acceso;\n"; else cout << "LED verde spento;\n";
	cout << "Codice di stato: " << data.status << ";\n";
	cout << "Zone: " << data.link << "." << endl << endl;
}

int main() {
	PPN frame1;
	frame1.Id = 1500;
	frame1.led_green = 1;
	frame1.led_red = 0;
	frame1.led_yellow = 0;
	frame1.reserved = 0;
	frame1.status = 5;
	frame1.link = 'C';

	stampa_PPN(frame1);

	using std::cout; using std::endl;
	using std::bitset;

	//unsigned int bit_PPN{ 0 };
	bitset<32> bit_PPN;

	bit_PPN |= frame1.link;
	bit_PPN |= (frame1.status << 8);
	bit_PPN |= (frame1.led_red << 16);
	bit_PPN |= (frame1.led_green << 14);
	bit_PPN |= (frame1.led_yellow << 15);
	bit_PPN |= (frame1.Id << 16);

	//cout << "bit_PPN: " << std::bitset<sizeof(unsigned int) * 8>(bit_PPN) << endl;
	cout << "bit_PPN: " << bit_PPN << endl;

	// estrazione di link (si trova sui bit meno significativi ed è 8 bit
	//unsigned int mask{ 0 };
	bitset<32> mask;
	mask = 0xFF;
	mask &= bit_PPN;
	cout << "Zone (link): " << (char)(mask.to_ulong()) << endl;
	
	// estrazione di status: sono 4 bit dopo gli 8 che compongono link
	mask = bit_PPN >> 8;
	mask &= 0xF;
	cout << "STATUS: " << mask.to_ulong() << endl;
	
	// estrazione di led rosso: 1 bit dopo 16
	mask = bit_PPN >> 16;
	mask &= 0x1;
	cout << "LED Rosso: " << (bool)mask.to_ulong() << endl;

	// estrazione di led yellow
	mask = bit_PPN >> 15;
	mask &= 1; // rappresentiamo sempre 1 ma in decimale
	cout << "LED yellow: " << (bool)mask.to_ulong() << endl;

	// estrazione di led green
	mask = bit_PPN >> 14;
	mask &= 1;
	cout << "LED green: " << (bool)mask.to_ulong() << endl;

	// estrazione di Id
	mask = bit_PPN >> 16;
	mask &= 0xFFFF; // 4 byte di lunghezza
	cout << "ID: " << mask.to_ulong() << endl;
	
	return 0;
}