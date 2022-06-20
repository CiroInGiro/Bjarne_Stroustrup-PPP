/*
Capitolo 12 Esercizio 13
Trova un modo per aggiungere il colore alle linee del precedente esercizio.
Crea alcune linee con un colore e altre con un altro colori o altri colori.
*/

// Adesso ho capito che nell'esercizio precedente si voleva creare dei punti e unirli con linee
// E' stato fatto aggiungendo i punti al poligono chiuso ma i punti non sono in successione

// Ver.2 proverò a creare un insieme di punti e a collegarli con le linee punto dopo punto

#include "../GUI/Simple_window.h"
#include "../GUI/Graph.h"
#include <cmath>
#include <random>

bool getParameter(double& a, double& b, double& m, double& n, int& N) {
	// m, n > 0
	// a, b != 0
	// N > 2
	using std::cin;
	using std::cout;
	using std::endl;
	double input{ 0.0 };

	cout << "Inserimento parametro a: ";
	cin >> a;
	while (a == 0) {
		if (a == 0) cout << endl << "'a' deve essere diverso da zero: ";
		cin >> a;
	}
	if (a == 0) return false;

	cout << "Inserimento parametro b: ";
	cin >> b;
	while (b == 0) {
		if (b == 0) cout << endl << "'b' deve essere diverso da zero: ";
		cin >> b;
	}
	if (b == 0) return false;

	cout << "Inserimento parametro m: ";
	cin >> m;
	while (m <= 0) {
		if (m <= 0) cout << endl << "'m' deve essere maggiore do zero: ";
		cin >> m;
	}
	if (m <= 0) return false;

	cout << "Inserimento parametro n: ";
	cin >> n;
	while (n <= 0) {
		if (n <= 0) cout << endl << "'n' deve essere maggiore di da zero: ";
		cin >> n;
	}
	if (n <= 0) return false;

	cout << "Inserimento parametro N (nuero di punti sull'elissi): ";
	cin >> N;
	while (N <= 2) {
		if (N <= 2) cout << endl << "'N' deve essere maggiore di 2: ";
		cin >> N;
	}
	if (N <= 2) return false;

	return true;
}

double sgn(const double& val) {
	if (val == 0) return 0.0;
	if (val < 0) return -1.0;
	if (val > 0) return 1.0;
}

int main() {
	// formula inversa
	// x(t) = (|cos t|^(2/m)) * a * sgn(cos t)
	// y(t) = (|sin t|^(2/n)) * b * sgn(sin t)
	// gli '|' mi sembra di ricordare che sono il modulo, cioè il risultato commuta sempre in positivo
	// sgn è la funzione segno che restituisce 3 valori:
	// 0 se il risultato è 0, -1 se è < 0 e +1 se è >0
	double a, b, m, n;
	int N;

	try {
		if (!getParameter(a, b, m, n, N)) throw std::exception{ "Parametri non validi." };
		Simple_window win{ Point{10, 10}, 800, 800, "Esercizio 12" };
//		Graph_lib::Window win{ Point{10, 10}, 800, 800, "Esercizio 12" };
		Point centro{ (win.x_max() / 2), (win.y_max() / 2) };
		win.color(Color::white);
		
		// creo prima i punti
		vector<Point*> punti;
		double angolo = 0;
		int x1 = (pow((abs(cos(angolo))), (2 / m))) * a * sgn(cos(angolo));
		int y1 = (pow((abs(sin(angolo))), (2 / n))) * b * sgn(sin(angolo));
		x1 += centro.x;
		y1 += centro.y;
		Color colore = Color::blue;

		for (int step = 1; step <= N; ++step) {
			angolo += (360.0 / (double)N);
			int x2 = (pow((abs(cos(angolo))), (2 / m))) * a * sgn(cos(angolo));
			int y2 = (pow((abs(sin(angolo))), (2 / n))) * b * sgn(sin(angolo));
			x2 += centro.x;
			y2 += centro.y;
			// Ho imparato il comando new per allocare nuovo spazio in memoria
			//Point* punto = new Point{ (int)x, (int)y };
			//punti.push_back(punto);
			Graph_lib::Line* linea = new Graph_lib::Line(Point{ x1, y1 }, Point{ x2, y2 });
			linea->set_color(colore);
			win.attach(*linea);
			x1 = x2;
			y1 = y2;
			colore = Color::Color(randint(0, 255));
		}

		/*

		win.show();

		// Adesso dovremmo ordinare l'arrey in modo che ogni punto sia consecutivo al punto più vicino sul piano

		// Disegniamo le linee
		for (unsigned int indice = 0; indice < (punti.size() - 1); ++indice) {
			Graph_lib::Line* linea = new Graph_lib::Line(*punti[indice], *punti[(indice + 1)]);
			win.attach(*linea);
			win.wait_for_button();

		}
		*/


		win.wait_for_button();
		// Bel risultato con 150, 400, 0.1, 1.6, 400 linee
	}
	catch (std::exception e) {
		std::cerr << "Errore " << e.what() << std::endl;
	}
	return 0;
}