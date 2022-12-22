#include "StainChart.h"

Graph_lib::StainChart::StainChart(Point posizione, int width, int height) {
	origine = new Point{ posizione.x, posizione.y };
	_width = width;
	_height = height;
}

void Graph_lib::StainChart::set_label_x(const std::string& label) {
	asse_x_label = label;
}

void Graph_lib::StainChart::set_label_y(const std::string& label) {
	asse_y_label = label;
}

void Graph_lib::StainChart::set_value(double x, double y, double z) {
	_x_value.push_back(x);
	_y_value.push_back(y);
	_z_value.push_back(z);
	std::ostringstream oss;
	oss << x;
	Text* etichetta = new Text(*origine, oss.str());
	etichetta->set_color(color());
	_x_label.push_back(etichetta);
	oss.str("");
	oss << y;
	etichetta = new Text(Point{ 0,0 }, oss.str());
	etichetta->set_color(color());
	_y_label.push_back(etichetta);
	oss.str("");
	oss << z;
	etichetta = new Text(Point{ 0,0 }, oss.str());
	etichetta->set_color(color());
	_z_label.push_back(etichetta);
}

double Graph_lib::StainChart::_min(const vector<double>& v) const {
	double retVal{ v[0] };
	for (double elemento : v) {
		if (elemento < retVal) retVal = elemento;
	}
	return retVal;
}

double Graph_lib::StainChart::_max(const vector<double>& v) const {
	double retVal{ v[0] };
	for (double elemento : v) {
		if (elemento > retVal) retVal = elemento;
	}
	return retVal;
}

void Graph_lib::StainChart::calcola() {
	double min_x = _min(_x_value);
	double max_x = _max(_x_value);
	int tacche_x = _x_value.size();
	double scale_x = _width / max_x;
	double min_y = _min(_y_value);
	double max_y = _max(_y_value);
	int tacche_y = _y_value.size();
	double scale_y = _height / (max_y - min_y);
	Point px{ origine->x, origine->y };
	asse_x = new Axis(Axis::Orientation::x, px, _width, tacche_x, asse_x_label);
	if (color().visibility()) asse_x->set_color(color());
	Point py{ origine->x, (origine->y + (_height / 2)) };
	asse_y = new Axis(Axis::Orientation::y, py, _height, tacche_y, asse_y_label);
	if (color().visibility()) asse_y->set_color(color());
	int x{ 0 }, y{ 0 };
	if ((_x_value.size() != _y_value.size()) || (_y_value.size() != _z_value.size())) throw std::exception("Valori del grafico mal costruiti");
	for (int indice = 0; indice < _x_value.size(); ++indice) {
		x = origine->x + (int)(_x_value[indice] * scale_x);
		y = origine->y - (int)(_y_value[indice] * scale_y);
		add(Point{ x,y });
		_x_label[indice]->move(x, (origine->y + 15));
		_y_label[indice]->move((origine->x - 50), y);
	}
}

void Graph_lib::StainChart::draw_lines() const {
	asse_x->draw();
	asse_y->draw();
	fl_color(color().as_int());
	int x, y;
	double min_z = _min(_z_value);
	double max_z = _max(_z_value);
	double scale_z = 50 / (abs(max_z) > abs(min_z) ? abs(max_z) : abs(min_z)); // disegnamo punti che vanno da 5px a 50px di diametro
	int d = (int)(_z_value[0] * scale_z) + 10;
	d = abs(d);
	x = point(0).x - (int)(d / 2);
	y = point(0).y - (int)(d / 2);
	fl_pie(x, y, d, d, 0, 360);
	_x_label[0]->draw();
	_y_label[0]->draw();
	_z_label[0]->move(point(0).x + 5, point(0).y + d);
	_z_label[0]->draw();
	for (int indice = 1; indice < number_of_points(); ++indice) {
		int d = (int)(_z_value[indice] * scale_z) + 10;
		d = abs(d);
		x = point(indice).x - (int)(d / 2);
		y = point(indice).y - (int)(d / 2);
		fl_pie(x, y, d, d, 0, 360);
		fl_line(point((indice - 1)).x, point((indice - 1)).y, point(indice).x, point(indice).y);
		_x_label[indice]->draw();
		_y_label[indice]->draw();
		_z_label[indice]->move(point(indice).x + 5, point(indice).y + d);
		_z_label[indice]->draw();
	}
}