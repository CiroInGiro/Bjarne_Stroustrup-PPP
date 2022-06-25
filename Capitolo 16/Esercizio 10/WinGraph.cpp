#include "WinGraph.h"

WinGraph::WinGraph(Point pos, int width, int height, const std::string& titolo) : Window(pos, width, height, titolo),
min(Point(pos.x+50, pos.y+10), 100, 30, "x da: "),
max(Point(pos.x+200, pos.y+10), 100, 30, "x a: "),
risoluzione(Point(pos.x+350, pos.y+10), 100, 30, "Punti: "),
errore(Point(pos.x+50, pos.y+100),"Scegli la tua funzione: "),
//x(Axis::Orientation::x, Point{pos.x+10, (y_max()/2)+100}, x_max()-20, 25,"x"),
//y(Axis::Orientation::y, Point{x_max()/2, pos.y+(y_max()-10)}, (y_max()-170), 25, "y"),
bt_sin(Point{ pos.x + 50, pos.y + 50 }, 100, 30, "sin()", [](Address, Address pw) {reference_to<WinGraph>(pw).action_sin(); }),
bt_cos(Point{ pos.x + 170, pos.y + 50 }, 100, 30, "cos()", [](Address, Address pw) {reference_to<WinGraph>(pw).action_cos(); }),
func_graph(nullptr, -10, 10, Point(pos.x+10, (y_max()/2)+55))
{
	_pos = pos;
	attach(min);
	attach(max);
	attach(risoluzione);
	attach(errore);
	attach(bt_sin);
	attach(bt_cos);
	attach(func_graph);
}

void WinGraph::prepara() {
	// 1 in = 2.54 cm
	// facciamo in modo che sullo schermo si veda 1 tacca ogni centimetro
	// disegniamo gli assi sfruttando lo spazio rimanente in finestra
	// il punto _origine è calcolato come centro tra gli assi x e y corrispondente allo 0 di entrambi
	int dpcm = 72 / 2.54;
	_start = min.get_int();
	_end = max.get_int();
	_ris = risoluzione.get_int();
	// margini 2 cm
	int margin = 2 * dpcm;
	int graph_space_x = x_max() - 2 * margin;
	graph_space_x -= graph_space_x % dpcm;
	int non_x = graph_space_x / dpcm;
	_zoom_x = dpcm;
	int graph_space_y = y_max() - 112 - margin - margin;
	graph_space_y -= graph_space_y % dpcm;
	int non_y = graph_space_y / dpcm;
	_zoom_y = dpcm;
	if (x != nullptr) detach(*x);
	if (y != nullptr) detach(*y);
	int x_origin = margin + ((int)(non_x / 2) * dpcm);
	int y_origin = margin + 112 + ((int)(non_y / 2) * dpcm);
	_origine = Point{ x_origin, y_origin };
	x = new Axis(Axis::Orientation::x, Point{ x_origin - (graph_space_x / 2), y_origin }, graph_space_x, non_x, "X: 1 tacca = 1 cm.");
	attach(*x);
	y = new Axis(Axis::Orientation::y, Point{ x_origin, y_origin + (graph_space_y / 2) }, graph_space_y, non_y, "Y: 1 tacca = 1 cm.");
	attach(*y);
}

void WinGraph::action_sin() {
	try {
		prepara();
		func_graph.reset();
		func_graph.parametri(func_sin, _start, _end, _origine, _ris, _zoom_x, _zoom_y, 0);
		func_graph.start();
		func_graph.set_color(Color::green);
	}
	catch (exception e) {
		std::ostringstream oss;
		oss << "Errore: " << e.what() << ".";
		errore.set_label(oss.str());
	}
	redraw();
}

void WinGraph::action_cos() {
	try {
		prepara();
		func_graph.reset();
		func_graph.parametri(func_cos, _start, _end, _origine, _ris, _zoom_x, _zoom_y, 0);
		func_graph.start();
		func_graph.set_color(Color::green);
	}
	catch (exception e) {
		std::ostringstream oss;
		oss << "Errore: " << e.what() << ".";
		errore.set_label(oss.str());
	}
	redraw();
}

double WinGraph::func_sin(double x, int precision) { return sin(x); }

double WinGraph::func_cos(double x, int precision) { return cos(x); }
