/*
Capitolo 14 Esercizio 3
Definisci una classe astratta e prova a dichiarare un oggetto di questo tipo per vedere cosa succede.
*/

// Le classi astratte possono essere solo derivate perché hanno il costruttore di default nell'area protetta.

class Astratto {
protected:
	Astratto() {}
public:
	void chisono() {
		
	}
private:
	bool presente{ true };
};

class Astratto2 :Astratto {
public:
	Astratto2() {}
};

int main() {
	//Astratto maletiemp; // errore
	Astratto2 maletiemp;
}