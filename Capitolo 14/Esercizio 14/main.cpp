/*
Capitolo 14 Esercizio 14
Aggiungi un operazione a Binary_tree che aggiunge un testo ad un nodo.
Potrebbe essere necessario modificare il design di Binary_tree per implementare questo in modo elegante.
Scegli un modo per identificare un nodo: ad esmpio potresti dare la stringa lrrlr che significa left, right, right, left e right
navigando l'albero verso il basso.
Il nodo principale ha sia un l che un r
*/

#include "../GUI/Simple_window.h"
#include "../MyClass/Binary_tree.h"

int main() {
	const string titolo{ "Capitolo 14 Esercizio 14" };
	Simple_window win(Point{ 0, 0 }, 1900, 600, titolo);
	win.color(Color::white);

	Binary_tree tr(Point{ 950, 50 }, 6, Conn_verso::Down, Color::green);
	tr.set_color(Color::dark_blue);
	tr.set_fill_color(Color::blue);

	win.attach(tr);
	win.wait_for_button();

	tr.add_text("o", "Root");
	tr.add_text("llrll", "Wagliò");
	tr.add_text("rrlr", "rotonda");
	win.wait_for_button();

}