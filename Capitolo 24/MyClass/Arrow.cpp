#include "Arrow.h"

Graph_lib::Arrow::Arrow(Point xy1, int lunghezza, int rotazione) {
	add(xy1);
	_l = lunghezza;
	_a = rotazione;
}

Graph_lib::Arrow::Arrow(Point start, Point end) {
	// le coordinate dei 2 punti sono le proiezioni del raggio sugli assi per un cerchio immaginario dove un punto è il suo centro e l'altro un punto sulla sua circonferenza
	// il rapporto delle proiezioni ci darà il coefficiente della formula per la retta: m
	// da m sappiamo che l'angolo della retta passante per il centro del cerchio e per il punto 2 avrà il seguente angolo:
	// 90° se m=1, quindi è una verticale
	// arcotangente(m) se m è diverso da 1
	// ho usato atan2 che tiene conto dei segni delle 2 proiezioni per determinare il quadrante, l'angolo è in radianti e lo zero è in alto non a destra

	add(start);
	// calcoliamo prima il raggio del cerchio immaginario con pitagora sulle proiezioni
	const double pi = 3.14159265; // pi greco
	double cateto1, cateto2, ipotenusa;
	double angolo;
	cateto1 = end.x - start.x;
	cateto2 = end.y - start.y;
	ipotenusa = sqrt((pow(cateto1, 2) + pow(cateto2, 2)));
	_l = (int)ipotenusa;
	angolo = atan2(cateto1, cateto2);
	angolo = (angolo * 180) / pi;
	angolo -= 90; // sfasato perché lo 0° sullo schermo si trova ad ore 3
	_a = (int)angolo;
}

void Graph_lib::Arrow::draw_lines() const {
	int x1, y1;
	double x2, y2;
	int dim{ 10 };
	int xo, yo;
	double p1x, p1y, p2x, p2y;
	double radianti; // le funzioni cos e sin vogliono l'angolo in radianti
	const double pi = 3.14159265; // pi greco
	
	if (color().visibility()) {
		fl_color(color().as_int());
		radianti = _a * pi / 180;
		x1 = point(0).x;
		y1 = point(0).y;
		x2 = x1 + _l;
		y2 = y1;
		// cerchiamo un punto sulla linea per avere la punta della freccia alta 5px
		xo = x2 - dim;
		yo = y2;
		// il vertice della punta coincide con la fine della linea, ricaviamo gli altri due spigoli
		p1x = xo;
		p1y = yo - dim;
		p2x = xo;
		p2y = yo + dim;
		// ruotiamo la freccia creata
		double newx, newy;
		// togliendo x1 e y1, l'origine della freccia spostiamo la freccia sullo zero degli assi cartesiano, per farla coincidere con l'origine di rotazione
		newx = (x2 - x1) * std::cos(radianti) - (y2 - y1) * std::sin(radianti);
		newy = (x2 - x1) * std::sin(radianti) + (y2 - y1) * std::cos(radianti);
		// riposizionamento dei punti dopo la rotazione, la punta della freccia
		x2 = newx + x1;
		y2 = -newy + y1;
		fl_line(x1, y1, (int)x2, (int)y2);
		newx = (p1x - x1) * std::cos(radianti) - (p1y - y1) * std::sin(radianti);
		newy = (p1x - x1) * std::sin(radianti) + (p1y - y1) * std::cos(radianti);
		p1x = newx + x1;
		p1y = -newy + y1;
		// una punta inferiore della freccia
		fl_line(x2, y2, (int)p1x, (int)p1y);
		newx = (p2x - x1) * std::cos(radianti) - (p2y - y1) * std::sin(radianti);
		newy = (p2x - x1) * std::sin(radianti) + (p2y - y1) * std::cos(radianti);
		p2x = newx + x1;
		p2y = -newy + y1;
		// l'altra punta inferiore della freccia
		fl_line(x2, y2, (int)p2x, (int)p2y);
		// unione delle due punte inferiori
		fl_line((int)p1x, (int)p1y, (int)p2x, (int)p2y);
	}
}