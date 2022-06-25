/*
Capitolo 16 Esercizio 3
Poni una immagine sopra un bottone.
Quando si preme il pulsante entrambi vengono mossi.
Usa il generatore di numeri casuali di std_lib_facilities.h per una nuova posizione.
*/

#include "../GUI/std_lib_facilities.h"
#include "../GUI/GUI.h"

class Particolar_button : public Graph_lib::Window{
public:
	Particolar_button(Point pos, int width, int height, const std::string& label) : Window(pos, width, height, label),
		bottone(Point{ (x_max() / 2) - 35, (y_max() / 2) - 35 }, 70, 70, "CatchMe", [](Graph_lib::Address, Graph_lib::Address pw) {Graph_lib::reference_to<Particolar_button>(pw).scappa(); }),
		bottone_im(Point{ (x_max() / 2) - 35, (y_max() / 2) - 35 }, "bt_img.jpg", Graph_lib::Suffix::jpg)
	{
		_pos = pos;
		attach(bottone);
		attach(bottone_im);
	}
private:
	Point _pos;
	Graph_lib::Button bottone;
	Graph_lib::Image bottone_im;
	void scappa() {
		int min = _pos.x + 20;
		int max = x_max() - 90;
		int newx = randint(min, max);
		min = _pos.y + 20;
		max = y_max() - 90;
		int newy = randint(min, max);
		newx -= bottone.loc.x;
		newy -= bottone.loc.y;
		bottone.move(newx, newy);
		bottone_im.move(newx, newy);
		redraw();
	}
};

int main() {
	try {
		Particolar_button magic(Point{ 0,0 }, 500, 500, "Capitolo 16 Esercizio 3");
		magic.color(Graph_lib::Color::white);
		return Graph_lib::gui_main();
	}
	catch (...) {
		std::cerr << std::endl << "Sei nei guai..." << std::endl;
	}
}