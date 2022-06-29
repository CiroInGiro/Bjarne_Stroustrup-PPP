#pragma once

#include "../GUI/Graph.h"

namespace Graph_lib {
	struct StyleBar {
		Color border_color{ Color::black };
		Color fill_color{ Color::black };
		Text* label{ nullptr };
		Text* x_label{ nullptr };
	};

	class BarChart : public Shape
	{
	public:
		BarChart(Point posizione, int width, int height, int num_valori);
		void set_value(double valore, int indice);
		double value(int indice) const;
		void draw_lines() const;
		void set_label(const string& etichetta);
		void set_bar_label(const string& etichetta, int indice);
		void set_bar_x_label(const string& etichetta, int indice);
		void set_bar_color(Color colore, int indice);
		void set_bar_fill_color(Color colore, int indice);
	private:
		int _width{ 0 };
		int _height{ 0 };
		int _max_valori{ 0 };
		vector<double> _valori;
		double _max() const;
		Text* _etichetta{ nullptr };
		vector<StyleBar> _barre;
	};
}
