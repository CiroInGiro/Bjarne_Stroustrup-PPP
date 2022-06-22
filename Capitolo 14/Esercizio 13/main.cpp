/*
Capitolo 14 Esercizio 13
Modifica Binary_tree per prendere un parametro (o parametri)
che permettono di scegliere come connettere i nodi, ad esempio una freccia con le punte verso il basso o una freccia rossa con le punte verso l'alto.
Nota come questo esercizio e l'ultimo usano due strade per creare una gerarchia di classi molto flessibili e utili.
*/

#include "../GUI/Simple_window.h"
#include "../MyClass/Binary_tree.h"

int main() {
	Simple_window win(Point{ 0, 0 }, 1200, 1000, "Capitolo 14 Esercizio 13");
	win.color(Color::white);

	Binary_tree tr(Point{ 600, 50 }, 4, Conn_verso::Down, Color::dark_blue);
	tr.set_color(Color::dark_blue);
	tr.set_fill_color(Color::blue);

	win.attach(tr);

	win.wait_for_button();
}