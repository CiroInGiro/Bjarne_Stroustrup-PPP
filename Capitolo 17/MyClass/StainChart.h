#pragma once
// Questa classe usa dei punti di diametro differente a secondo del valore, quindi è possibile rappresentare dati che rappresentano 2 valori in funzione dell'asse x.

#include "../GUI/Graph.h"

namespace Graph_lib {
	class StainChart : public Shape
	{
	public:
		StainChart(Point posizione, int width, int height);
		void set_value(double x, double y, double z);
		void set_label_x(const std::string& label);
		void set_label_y(const std::string& label);
		void calcola();
		void draw_lines() const;
	private:
		Point* origine;
		int _width;
		int _height;
		Axis* asse_x;
		Axis* asse_y;
		std::string asse_x_label;
		std::string asse_y_label;
		vector<double> _x_value;
		vector<Text*> _x_label;
		vector<double> _y_value;
		vector<Text*> _y_label;
		vector<double> _z_value;
		vector<Text*> _z_label;
		double _min(const vector<double>& v) const;
		double _max(const vector<double>& v) const;
	};
}

