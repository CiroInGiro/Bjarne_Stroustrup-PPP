#include "Lavagna.h"

unsigned int Lavagna::uid = 0;

int Lavagna::run() {
	print_guida();

	while (Fl::wait() && running) {
		std::cin >> *this;
	}

	return 0;
}

void Lavagna::chiamata(const std::string& comando, const std::string& parametri) {
	// interpretare la funzione in comando
	// a seconda della funzione interpretare i parametri da aggiungere a parametri_funzione
	std::istringstream iss{ parametri };
	char ch;
	bool esito{ false }; // se rimane true per un comando di creazione Graph_lib sarà aggiunto a Lavagna
	Graph_lib::Shape* p_disegno{ 0 };

	try {
		if (comando == "help") print_guida();
		else if (comando == "quit") running = false;
		else if (comando == "Color") {
			// cambio colore
			if (parametri == "black") colore = Color::black;

			if (parametri == "blue") colore = Color::blue;

			if (parametri == "cyan") colore = Color::cyan;

			if (parametri == "green") colore = Color::green;

			if (parametri == "yellow") colore = Color::yellow;

			if (parametri == "red") colore = Color::red;
		}
		else if (comando == "print") {
			// stampo le info sui disegni sulla lavagna
			print();
		}
		else if (comando == "Line") {
			esito = true;
			// interpretiamo int, int, int, int
			int x1{ 0 }, y1{ 0 }; // punto di partenza
			int x2{ 0 }, y2{ 0 }; // punto finale della riga

			iss >> x1;
			iss >> ch;
			if (ch != ',') return;
			iss >> y1;
			iss >> ch;
			if (ch != ',') return;
			iss >> x2;
			iss >> ch;
			if (ch != ',') return;
			iss >> y2;
			p_disegno = new Graph_lib::Line(Point(x1, y1), Point(x2, y2));
		}
		else if (comando == "Rectangle") {
			esito = true;
			// interpretiamo due int per il Point, altri due per width e height
			Point p1{ 0, 0 };
			int w{ 0 }, h{ 0 };

			iss >> p1.x;
			iss >> ch;
			if (ch != ',') return;
			iss >> p1.y;
			iss >> ch;
			if (ch != ',') return;
			iss >> w;
			iss >> ch;
			if (ch != ',') return;
			iss >> h;
			p_disegno = new Graph_lib::Rectangle(p1, w, h);
		}
		else if (comando == "Circle") {
			esito = true;
			// interpretiamo tre int per le coordinate del cento e il suo raggio
			Point centro{ 0, 0 };
			int raggio{ 0 };

			iss >> centro.x;
			iss >> ch;
			if (ch != ',') return;
			iss >> centro.y;
			iss >> ch;
			if (ch != ',') return;
			iss >> raggio;
			p_disegno = new Graph_lib::Circle(centro, raggio);
		}

		// parte non implementata
		if (comando == "Ellipse") {
			// interpretiamo un Point, int, int

		}

		if (comando == "Image") {
			// interpretiamo un Point, string, Suffix::Encoding dall'estensione file
		}

		if (comando == "TriangoloRettangolo") {
			// interpretiamo Point, double, double, int

		}

		// se non ci sono intoppi con new()
		if (esito) {
			p_disegno->set_color(colore);
			attach(*p_disegno);
			++uid;
			Disegno disegno{ comando, p_disegno, uid };
			disegni.push_back(disegno);
			std::cout << disegno << std::endl;
		}
	} // fine try{}
	catch (...) { esito = false; }
}

void Lavagna::print() const {
	Point punto;

	std::cout << "Lavagna (width x height): " << x_max() << " x " << y_max() << std::endl;
	std::cout << "Colore attuale: ";

	switch (colore.as_int()) {
	case Color::black:
		std::cout << "black\n";
		break;
	case Color::blue:
		std::cout << "blue\n";
		break;
	case Color::cyan:
		std::cout << "cyan\n";
		break;

	case Color::green:
		std::cout << "green\n";
		break;
	case Color::red:
		std::cout << "red\n";
		break;
	case Color::yellow:
		std::cout << "yellow\n";
		break;
	}

	for (Disegno disegno : disegni) {
		std::cout << disegno.name << " OID: " << disegno.id	<< " { ";
		
		if (disegno.name == "Line") {
			for (int index = 0; index < disegno.pshape->number_of_points(); ++index) {
				punto = disegno.pshape->point(index);
				std::cout << punto.x << ", " << punto.y;
				if (index < disegno.pshape->number_of_points()) std::cout << ", ";
			}
		}
		else if (disegno.name == "Rectangle") {
			punto = disegno.pshape->point(0);
			std::cout << punto.x << ", " << punto.y << ", "
				<< ((Graph_lib::Rectangle*)disegno.pshape)->width() << ", "
				<< ((Graph_lib::Rectangle*)disegno.pshape)->height();
		}
		else if (disegno.name == "Circle") {
			punto = disegno.pshape->point(0);
			std::cout << punto.x << ", " << punto.y << ", "
				<< ((Graph_lib::Circle*)disegno.pshape)->radius();
		}

		std::cout << " }\n";
	}

	std::cout << std::endl;
}

void Lavagna::print_guida() const {
	std::cout << "Guida dei comandi per utilizzare la lavagna:\n\n"
		<< "help{} ristampa questa guida;\n"
		<< "quit{} termina l'esecuzione della lavagna."
		<< "print{} stampa il disegno: informazioni sulla lavagna e per ogni comando dato il suo id e le coordinate,\n"
		<< "con l'id si possono usare comandi (non implementati qui) tipo move{id, newx, newy} o del{id}\n"
		<< "Color{colore} cambia il colore con cui disegnare tra black, blue, cyan, green, red, yellow\n"
		<< "Line{x1,y1,x2,y2} disegna una linea dalle coordinate x1,y1 alle coordinate x2,y2\n"
		<< "Rectangle{x,y,width,height} disegna un rettangolo che ha l'angolo superiore sinistro in x,y ed è largo width e alto height\n"
		<< "Circle{x,y,raggio} disegna un cercio che ha il centro in x,y e raggio di raggio\n"

		<< std::endl << std::endl;
}

std::istream& operator>>(std::istream& is, Lavagna& lavagna) {
	char ch{ '\0' };
	std::string comando, parametri;

	// leggo comando
	while (is >> ch && ch != '{') comando += ch;

	// leggo la stritnga di parametri
	while (is >> ch && ch != '}') parametri += ch;

	// passo il tutto al cosruttore di chiamata a funzione
	lavagna.chiamata(comando, parametri);

	// chiediamo a fltk di ridisegnare Lavagna con i suoi nuovi widget
	lavagna.redraw();

	// restituisco lo stream
	return is;
}

std::ostream& operator<<(std::ostream& os, Lavagna& lavagna) {
	
	for (Lavagna::Disegno disegno : lavagna.disegni)
		os << disegno << std::endl;

	return os;
}

std::ostream& operator<<(std::ostream& os, Lavagna::Disegno& disegno) {
	Point punto;

	os << "Color{";

	switch (disegno.pshape->color().as_int()) {
	case Color::black:
		os << "black";
		break;
	case Color::blue:
		os << "blue";
		break;
	case Color::cyan:
		os << "cyan";
		break;

	case Color::green:
		os << "green";
		break;
	case Color::red:
		os << "red";
		break;
	case Color::yellow:
		os << "yellow";
		break;
	default:
		os << " ";
	}

	os << "} ";
	os << disegno.name << "{";

	if (disegno.name == "Line") {
		punto = disegno.pshape->point(0);
		os << punto << ",";
		punto = disegno.pshape->point(1);
		os << punto;
	}
	else if (disegno.name == "Rectangle") {
		punto = disegno.pshape->point(0);
		os << punto << ","
			<< ((Graph_lib::Rectangle*)disegno.pshape)->width() << ","
			<< ((Graph_lib::Rectangle*)disegno.pshape)->height();
	}
	else if (disegno.name == "Circle") {
		punto = disegno.pshape->point(0);
		os << punto << ","
			<< ((Graph_lib::Circle*)disegno.pshape)->radius();
	}

	os << "}";

	return os;
}