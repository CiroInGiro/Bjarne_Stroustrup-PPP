#pragma once

#include "../GUI/Graph.h"

namespace Graph_lib {
	struct StyleBar {
		Color border_color{ Color::black };
		Color fill_color{ Color::black };
		Text* label{ nullptr };
		Text* x_label{ nullptr };
	};

	class Bar2Chart : public Shape
	{
	public:
		enum Serie {
			y1 = 0,
			y2
		};
		Bar2Chart(Point posizione, int width, int height);
		void add_value(double valore, Graph_lib::Bar2Chart::Serie yy);
		double value(int indice, Graph_lib::Bar2Chart::Serie yy) const;
		void draw_lines() const;
		void set_label(const string& etichetta);
		void set_bar_label(const string& etichetta, int indice, Graph_lib::Bar2Chart::Serie yy);
		void set_bar_x_label(const string& etichetta, int indice, Graph_lib::Bar2Chart::Serie yy);
		void set_bar_color(Color colore, int indice, Graph_lib::Bar2Chart::Serie yy);
		void set_bar_fill_color(Color colore, int indice, Graph_lib::Bar2Chart::Serie yy);
	private:
		int _width{ 0 };
		int _height{ 0 };
		int _max_valori{ 0 };
		vector<double> _valori_y1;
		vector<double> _valori_y2;
		double _max() const;
		Text* _etichetta{ nullptr };
		vector<StyleBar> _barre_y1;
		vector<StyleBar> _barre_y2;
	};
}
