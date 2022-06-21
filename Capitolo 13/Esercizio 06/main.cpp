/*
Capitolo 13 Esercizio 6
Scrivi un programma che disegna uno schema di classe come nel paragrafo 12.6
Ti sarà più semplice se definisce una classe Box che è un rettangolo e una etichetta.
*/

#include "../GUI/Simple_window.h"
#include "../GUI/Graph.h"
#include "TBox.h"

int main() {
	Simple_window win(Point{ 0, 0 }, 800, 800, "Esercizio 6");
	win.color(Color::white);

	TBox tbox(Point{ 200,200 }, "Etichetta di prova");
	tbox.set_color(Color::blue);
	tbox.set_fill_color(Color::yellow);
	win.attach(tbox);

	win.wait_for_button();

	tbox.set_label("Capitolo 13 Esercizio 6, etichetta di prova.");
	win.wait_for_button();

	tbox.add_line("Hello World!");
	win.wait_for_button();

	tbox.add_line("funziona???");
	tbox.add_line("Provo ad aggiungere almeno 4 righe");
	tbox.add_line("questa è l'ultima, dopo provo a spostare il TBox");
	win.wait_for_button();

	tbox.move(30, 100);
	win.wait_for_button();

	return 0;
}