/* Capitolo 25 Esercizio 10
* Guardate l'esempio su bitfield dal §25.5.5.
* Scrivi un esempio che inizializzi un PPN, 
* quindi legga e stampi ogni valore di campo, 
* quindi modifichi ogni valore di campo (assegnandolo al campo) e stampi il risultato.
* Ripetete questo esercizio, ma memorizzate le informazioni PPN in un intero senza segno a 32 bit 
* e usate gli operatori di manipolazione dei bit (§25.5.4) per accedere ai bit nella parola. 
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
	/*
	* usare numeri negativi crea problemi perché anche utilizzando la maschera, appena si tocca il bit più significativo
	* tutti gli altri saranno invertiti e si sovrascrivono anche gli altri campi.
	*/
	// signed char status : 4; // non posso utilizzare numeri negativi su 4 bit perché saranno utilizzati tutti e anche nei cast a tipi con più bit BUG !!!
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
	//frame1.status = -1; // BUG
	frame1.status = 5;
	frame1.link = 'C';

	stampa_PPN(frame1);

	using std::cout; using std::endl;

	unsigned int bit_PPN{ 0 };
	//bit_PPN = frame1.link | frame1.status | frame1.reserved |frame1.led_yellow | frame1.led_red | frame1.led_green | frame1.Id;
	//bit_PPN = frame1.status;
	bit_PPN |= frame1.link;
	bit_PPN |= (frame1.status << 8);
	bit_PPN |= (frame1.led_red << 16);
	bit_PPN |= (frame1.led_green << 14);
	bit_PPN |= (frame1.led_yellow << 15);
	bit_PPN |= (frame1.Id << 16);

	cout << "bit_PPN: " << std::bitset<sizeof(unsigned int) * 8>(bit_PPN) << endl;
	//signed char sc{ 0 };
	//sc |= frame1.status;
	//cout << "bit_PPN: " << std::bitset<sizeof(signed char) * 8>(sc) << endl;

	unsigned int mask{ 0 };

	// estrazione di link (si trova sui bit meno significativi ed è 8 bit
	mask = 0xFF & bit_PPN;
	cout << "Zone (link): " << (char)mask << endl;

	// estrazione di status: sono 4 bit dopo gli 8 che compongono link
	mask = bit_PPN >> 8;
	mask &= 0xF;
	cout << "STATUS: " << mask << endl;

	// estrazione di led rosso: 1 bit dopo 16
	mask = bit_PPN >> 16;
	mask &= 0x1;
	cout << "LED Rosso: " << (bool)mask << endl;

	// estrazione di led yellow
	mask = bit_PPN >> 15;
	mask &= 1; // rappresentiamo sempre 1 ma in decimale
	cout << "LED yellow: " << (bool)mask << endl;

	// estrazione di led green
	mask = bit_PPN >> 14;
	mask &= 1;
	cout << "LED green: " << (bool)mask << endl;

	// estrazione di Id
	mask = bit_PPN >> 16;
	mask &= 0xFFFF; // 4 byte di lunghezza
	cout << "ID: " << mask << endl;

	return 0;
}