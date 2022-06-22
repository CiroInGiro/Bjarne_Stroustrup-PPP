/*
Capitolo 14 Esercizio 17
Le eccezioni definite nella libreria standard c++, come exception, runtime_error e out_of_range (cap. 5) sono organizzate in una gerarchia di classi.
(con un utile funzione virtuale what() che restituisce una stringa che spiega presumibilente cosa sia successo.)
Cerca informazioni sui sorgenti di queste classi e disegna un diagramma sulla gerarchia di classi di cui è formato.
*/

#include "../GUI/Graph.h"
#include "../GUI/Simple_window.h"
#include "../MyClass/TBox.h"
#include "../MyClass/Arrow.h"

int main() {
	Simple_window win(Point{ 0,0 }, 1233, 550, "Capitolo 14 Esercizio 17");
	win.color(Color::yellow);

	/*
	// exception
	TBox tb_exception(Point{ 400, 10 }, "class exception");
	tb_exception.set_color(Color::blue);
	win.attach(tb_exception);

	// logic_error:exception
	TBox tb_logic_error(Point{ 10, 100 }, "class logic_error");
	tb_logic_error.set_color(Color::blue);
	win.attach(tb_logic_error);

	//Arrow ar_logic_error(Point{ 400, 100 }, 50, 245);
	//ar_logic_error.set_color(Color::black);
	//win.attach(ar_logic_error);

	// invalid_argument:logic_error:exception
	TBox tb_invalid_argument(Point{10,150}, "class invalid_argument");
	tb_invalid_argument.set_color(Color::blue);
	win.attach(tb_invalid_argument);
	*/

	Image mappa(Point{ 0, 40 }, "std--exception.jpg", Graph_lib::Suffix::jpg);
	win.attach(mappa);

	win.wait_for_button();

}