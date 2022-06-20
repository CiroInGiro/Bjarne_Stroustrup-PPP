/*
Capitolo 12 Esercizio 10
Disegna il grafico che vedi nel paragrafo 12.8
*/

#include "../GUI/Simple_window.h"
#include "../GUI/Graph.h"

struct Layer_out {
	int mw{ 0 }; // margine sinistro
	int mh{ 0 }; // margine alto
	int z{ 0 }; // 0-100% zoom di incremento
};

Point getPoint(const Layer_out& layout, const int& x, const int& y) {
	return Point{ (layout.mw + x), (layout.mh + y) };
}

int getSize(const Layer_out& layout, const int& size) {
	if (layout.z <= 0) return size; // min zoom
	if (layout.z > 100) return (size * 2); // max zoom
	return (size + ((size / 100) * layout.z));
}

int main() {
	using namespace Graph_lib;
	
	// Finestra
	Simple_window win{ Point{10,10}, 800, 800, "Esercizio 10" };
	win.color(Color::white);

	// Preparo il layout
	Layer_out layout; // default: senza margini e senza zoom
	
	// Fltk
	Graph_lib::Rectangle fltk_f1{ getPoint(layout, 300, 10), getSize(layout, 120), getSize(layout, 40) };
	fltk_f1.set_color(Color::black);
	fltk_f1.set_fill_color(Color::yellow);
	Graph_lib::Rectangle fltk_f2{ getPoint(layout, 305, 15), getSize(layout, 120), getSize(layout, 40) };
	fltk_f2.set_color(Color::black);
	fltk_f2.set_fill_color(Color::yellow);
	Graph_lib::Rectangle fltk_rect{ getPoint(layout, 310, 20), getSize(layout, 120), getSize(layout, 40) };
	fltk_rect.set_color(Color::black);
	fltk_rect.set_fill_color(Color::yellow);
	Graph_lib::Text fltk_text(getPoint(layout, 320, 45), "FLTK Headers");
	fltk_text.set_font(Font::times);
	fltk_text.set_font_size(getSize(layout, 14));
	fltk_text.set_color(Color::black);

	win.attach(fltk_f1);
	win.attach(fltk_f2);
	win.attach(fltk_rect);
	win.attach(fltk_text);

	// Fltk Code
	Graph_lib::Rectangle fltkcode_f1{ getPoint(layout, 480, 50), getSize(layout, 120), getSize(layout, 40) };
	fltkcode_f1.set_color(Color::black);
	fltkcode_f1.set_fill_color(Color::yellow);
	Graph_lib::Rectangle fltkcode_f2{ getPoint(layout, 485, 55), getSize(layout, 120), getSize(layout, 40) };
	fltkcode_f2.set_color(Color::black);
	fltkcode_f2.set_fill_color(Color::yellow);
	Graph_lib::Rectangle fltkcode_rect{ getPoint(layout, 490, 60), getSize(layout, 120), getSize(layout, 40) };
	fltkcode_rect.set_color(Color::black);
	fltkcode_rect.set_fill_color(Color::yellow);
	Graph_lib::Text fltkcode_text(getPoint(layout, 495, 80), "FLTK Code");
	fltkcode_text.set_font(Font::times);
	fltkcode_text.set_font_size(getSize(layout, 14));
	fltkcode_text.set_color(Color::black);

	win.attach(fltkcode_f1);
	win.attach(fltkcode_f2);
	win.attach(fltkcode_rect);
	win.attach(fltkcode_text);

	// Arrow Fltk
	Graph_lib::Line arrow_fltk(getPoint(layout, 480, 70), getPoint(layout, 430, 40));
	arrow_fltk.set_color(Color::black);
	arrow_fltk.set_style(Line_style(Line_style::solid, 1));
	//Graph_lib::Image punta_fltk(getPoint(layout, 430, 40), "punta freccia.gif", Suffix::gif); // non si possono ruotare, ci vogliono troppo immaginette
	Graph_lib::Circle punta_fltk(getPoint(layout, 430, 40), getSize(layout, 3));
	punta_fltk.set_color(Color::black);
	punta_fltk.set_fill_color(Color::black);

	win.attach(arrow_fltk);
	win.attach(punta_fltk);
	

	// Struct Point
	Graph_lib::Text point_title(getPoint(layout, 55, 85), "Point.h:");
	point_title.set_font(Font::times_bold);
	point_title.set_font_size(getSize(layout, 14));
	point_title.set_color(Color::black);
	Graph_lib::Rectangle point_rect{ getPoint(layout, 50, 90), getSize(layout, 120), getSize(layout, 40) };
	point_rect.set_color(Color::black);
	point_rect.set_fill_color(Color::yellow);
	Graph_lib::Text point_text(getPoint(layout, 60, 120), "Struct Point {...};");
	point_text.set_font(Font::times_bold);
	point_text.set_font_size(getSize(layout, 14));
	point_text.set_color(Color::black);
	
	win.attach(point_title);
	win.attach(point_rect);
	win.attach(point_text);

	// Window.h
	Graph_lib::Text window_title(getPoint(layout, 305, 155), "Window.h:");
	window_title.set_font(Font::times_bold);
	window_title.set_font_size(getSize(layout, 14));
	window_title.set_color(Color::black);
	Graph_lib::Rectangle window_rect(getPoint(layout, 300, 160), 140, 80);
	window_rect.set_color(Color::black);
	window_rect.set_fill_color(Color::yellow);
	Graph_lib::Text window_r1(getPoint(layout, 305, 180), "// Window Interface:");
	window_r1.set_font(Font::times);
	window_r1.set_font_size(getSize(layout, 14));
	window_r1.set_color(Color::black);
	Graph_lib::Text window_r2(getPoint(layout, 305, 200), "Class Window {...};");
	window_r2.set_font(Font::times_bold);
	window_r2.set_font_size(getSize(layout, 14));
	window_r2.set_color(Color::black);
	Graph_lib::Text window_r3(getPoint(layout, 305, 220), "...");
	window_r3.set_font(Font::times);
	window_r3.set_font_size(getSize(layout, 14));
	window_r3.set_color(Color::black);

	win.attach(window_title);
	win.attach(window_rect);
	win.attach(window_r1);
	win.attach(window_r2);
	win.attach(window_r3);

	// Arrow Window.h
	// to fltk
	Graph_lib::Line arrow1_window(getPoint(layout, 380, 160), getPoint(layout, 380, 60));
	arrow1_window.set_color(Color::black);
	arrow1_window.set_style(Line_style(Line_style::solid, 1));
	Graph_lib::Circle punta1_window(getPoint(layout, 380, 60), getSize(layout, 3));
	punta1_window.set_color(Color::black);
	punta1_window.set_fill_color(Color::black);
	// to point
	Graph_lib::Line arrow2_window(getPoint(layout, 310, 160), getPoint(layout, 130, 130));
	arrow2_window.set_color(Color::black);
	arrow2_window.set_style(Line_style(Line_style::solid, 1));
	Graph_lib::Circle punta2_window(getPoint(layout, 130, 130), getSize(layout, 3));
	punta2_window.set_color(Color::black);
	punta2_window.set_fill_color(Color::black);

	win.attach(arrow1_window);
	win.attach(punta1_window);
	win.attach(arrow2_window);
	win.attach(punta2_window);


	// Gui.h
	Graph_lib::Text gui_title(getPoint(layout, 405, 285), "GUI.h:");
	gui_title.set_font(Font::times_bold);
	gui_title.set_font_size(getSize(layout, 14));
	gui_title.set_color(Color::black);
	Graph_lib::Rectangle gui_rect(getPoint(layout, 400, 290), 140, 80);
	gui_rect.set_color(Color::black);
	gui_rect.set_fill_color(Color::yellow);
	Graph_lib::Text gui_r1(getPoint(layout, 405, 310), "// GUI Interface:");
	gui_r1.set_font(Font::times);
	gui_r1.set_font_size(getSize(layout, 14));
	gui_r1.set_color(Color::black);
	Graph_lib::Text gui_r2(getPoint(layout, 405, 330), "struct In_Box {...};");
	gui_r2.set_font(Font::times_bold);
	gui_r2.set_font_size(getSize(layout, 14));
	gui_r2.set_color(Color::black);
	Graph_lib::Text gui_r3(getPoint(layout, 405, 350), "...");
	gui_r3.set_font(Font::times);
	gui_r3.set_font_size(getSize(layout, 14));
	gui_r3.set_color(Color::black);

	win.attach(gui_title);
	win.attach(gui_rect);
	win.attach(gui_r1);
	win.attach(gui_r2);
	win.attach(gui_r3);

	// Arrow GUI.h
	// to fltk
	Graph_lib::Line arrow1_gui(getPoint(layout, 510, 290), getPoint(layout, 380, 60));
	arrow1_gui.set_color(Color::black);
	arrow1_gui.set_style(Line_style(Line_style::solid, 1));
	Graph_lib::Circle punta1_gui(getPoint(layout, 380, 60), getSize(layout, 3));
	punta1_gui.set_color(Color::black);
	punta1_gui.set_fill_color(Color::black);
	// to window
	Graph_lib::Line arrow2_gui(getPoint(layout, 510, 290), getPoint(layout, 380, 240));
	arrow2_gui.set_color(Color::black);
	arrow2_gui.set_style(Line_style(Line_style::solid, 1));
	Graph_lib::Circle punta2_gui(getPoint(layout, 380, 240), getSize(layout, 3));
	punta2_gui.set_color(Color::black);
	punta2_gui.set_fill_color(Color::black);

	win.attach(arrow1_gui);
	win.attach(punta1_gui);
	win.attach(arrow2_gui);
	win.attach(punta2_gui);

	// GUI.cpp
	Graph_lib::Text guicpp_title(getPoint(layout, 505, 435), "GUI.cpp:");
	guicpp_title.set_font(Font::times_bold);
	guicpp_title.set_font_size(getSize(layout, 14));
	guicpp_title.set_color(Color::black);
	Graph_lib::Rectangle guicpp_rect{ getPoint(layout, 500, 440), getSize(layout, 120), getSize(layout, 40) };
	guicpp_rect.set_color(Color::black);
	guicpp_rect.set_fill_color(Color::yellow);
	Graph_lib::Text guicpp_text(getPoint(layout, 505, 460), "GUI Code");
	guicpp_text.set_font(Font::times_bold);
	guicpp_text.set_font_size(getSize(layout, 14));
	guicpp_text.set_color(Color::black);

	win.attach(guicpp_title);
	win.attach(guicpp_rect);
	win.attach(guicpp_text);

	// Arrow gui.cpp
	Graph_lib::Line arrow_guicpp(getPoint(layout, 610, 440), getPoint(layout, 500, 370));
	arrow_guicpp.set_color(Color::black);
	arrow_guicpp.set_style(Line_style(Line_style::solid, 1));
	Graph_lib::Circle punta_guicpp(getPoint(layout, 500, 370), getSize(layout, 3));
	punta_guicpp.set_color(Color::black);
	punta_guicpp.set_fill_color(Color::black);

	win.attach(arrow_guicpp);
	win.attach(punta_guicpp);

	// Graph.h
	Graph_lib::Text graph_title(getPoint(layout, 55, 200), "Graph.h:");
	graph_title.set_font(Font::times_bold);
	graph_title.set_font_size(getSize(layout, 14));
	graph_title.set_color(Color::black);
	Graph_lib::Rectangle graph_rect(getPoint(layout, 50, 205), 120, 80);
	graph_rect.set_color(Color::black);
	graph_rect.set_fill_color(Color::yellow);
	Graph_lib::Text graph_r1(getPoint(layout, 55, 225), "// Graph Interface:");
	graph_r1.set_font(Font::times);
	graph_r1.set_font_size(getSize(layout, 14));
	graph_r1.set_color(Color::black);
	Graph_lib::Text graph_r2(getPoint(layout, 55, 245), "Class Shape {...};");
	graph_r2.set_font(Font::times_bold);
	graph_r2.set_font_size(getSize(layout, 14));
	graph_r2.set_color(Color::black);
	Graph_lib::Text graph_r3(getPoint(layout, 55, 260), "...");
	graph_r3.set_font(Font::times);
	graph_r3.set_font_size(getSize(layout, 14));
	graph_r3.set_color(Color::black);

	win.attach(graph_title);
	win.attach(graph_rect);
	win.attach(graph_r1);
	win.attach(graph_r2);
	win.attach(graph_r3);

	// Arrow Graph.h
	// to fltk
	Graph_lib::Line arrow1_graph(getPoint(layout, 110, 205), getPoint(layout, 380, 60));
	arrow1_graph.set_color(Color::black);
	arrow1_graph.set_style(Line_style(Line_style::solid, 1));
	Graph_lib::Circle punta1_graph(getPoint(layout, 380, 60), getSize(layout, 3));
	punta1_graph.set_color(Color::black);
	punta1_graph.set_fill_color(Color::black);
	// to point
	Graph_lib::Line arrow2_graph(getPoint(layout, 110, 205), getPoint(layout, 130, 130));
	arrow2_graph.set_color(Color::black);
	arrow2_graph.set_style(Line_style(Line_style::solid, 1));
	Graph_lib::Circle punta2_graph(getPoint(layout, 130, 130), getSize(layout, 3));
	punta2_graph.set_color(Color::black);
	punta2_graph.set_fill_color(Color::black);

	win.attach(arrow1_graph);
	win.attach(punta1_graph);
	win.attach(arrow2_graph);
	win.attach(punta2_graph);

	// Graph.cpp
	Graph_lib::Text graphcpp_title(getPoint(layout, 10, 400), "Graph.cpp:");
	graphcpp_title.set_font(Font::times_bold);
	graphcpp_title.set_font_size(getSize(layout, 14));
	graphcpp_title.set_color(Color::black);
	Graph_lib::Rectangle graphcpp_rect(getPoint(layout, 5, 405), 120, 40);
	graphcpp_rect.set_color(Color::black);
	graphcpp_rect.set_fill_color(Color::yellow);
	Graph_lib::Text graphcpp_r1(getPoint(layout, 10, 425), "Graph Code");
	graphcpp_r1.set_font(Font::times_bold);
	graphcpp_r1.set_font_size(getSize(layout, 14));
	graphcpp_r1.set_color(Color::black);

	win.attach(graphcpp_title);
	win.attach(graphcpp_rect);
	win.attach(graphcpp_r1);

	// Arrow Graph.cpp
	Graph_lib::Line arrow_graphcpp(getPoint(layout, 115, 405), getPoint(layout, 115, 285));
	arrow_graphcpp.set_color(Color::black);
	arrow_graphcpp.set_style(Line_style(Line_style::solid, 1));
	Graph_lib::Circle punta_graphcpp(getPoint(layout, 115, 285), getSize(layout, 3));
	punta_graphcpp.set_color(Color::black);
	punta_graphcpp.set_fill_color(Color::black);

	win.attach(arrow_graphcpp);
	win.attach(punta_graphcpp);

	// chapter12.cpp
	Graph_lib::Text cp12_title(getPoint(layout, 75, 545), "Chapter12.cpp:");
	cp12_title.set_font(Font::times_bold);
	cp12_title.set_font_size(getSize(layout, 14));
	cp12_title.set_color(Color::black);
	Graph_lib::Rectangle cp12_rect(getPoint(layout, 70, 550), 200, 80);
	cp12_rect.set_color(Color::black);
	cp12_rect.set_fill_color(Color::yellow);
	Graph_lib::Text cp12_r1(getPoint(layout, 75, 570), "#include \"Graph.h\"");
	cp12_r1.set_font(Font::times_bold);
	cp12_r1.set_font_size(getSize(layout, 14));
	cp12_r1.set_color(Color::black);
	Graph_lib::Text cp12_r2(getPoint(layout, 75, 590), "#include \"Simple_window.h\"");
	cp12_r2.set_font(Font::times_bold);
	cp12_r2.set_font_size(getSize(layout, 14));
	cp12_r2.set_color(Color::black);
	Graph_lib::Text cp12_r3(getPoint(layout, 75, 610), "int main() {...}");
	cp12_r3.set_font(Font::times_bold);
	cp12_r3.set_font_size(getSize(layout, 14));
	cp12_r3.set_color(Color::black);

	win.attach(cp12_title);
	win.attach(cp12_rect);
	win.attach(cp12_r1);
	win.attach(cp12_r2);
	win.attach(cp12_r3);

	// Arrow chapter12.cpp
	// to Simple_window.h
	Graph_lib::Line arrow1_cp12(getPoint(layout, 210, 550), getPoint(layout, 330, 500));
	arrow1_cp12.set_color(Color::black);
	arrow1_cp12.set_style(Line_style(Line_style::solid, 1));
	Graph_lib::Circle punta1_cp12(getPoint(layout, 330, 500), getSize(layout, 3));
	punta1_cp12.set_color(Color::black);
	punta1_cp12.set_fill_color(Color::black);
	// to Graph.h
	Graph_lib::Line arrow2_cp12(getPoint(layout, 210, 550), getPoint(layout, 110, 285));
	arrow2_cp12.set_color(Color::black);
	arrow2_cp12.set_style(Line_style(Line_style::solid, 1));
	Graph_lib::Circle punta2_cp12(getPoint(layout, 110, 285), getSize(layout, 3));
	punta2_cp12.set_color(Color::black);
	punta2_cp12.set_fill_color(Color::black);

	win.attach(arrow1_cp12);
	win.attach(punta1_cp12);
	win.attach(arrow2_cp12);
	win.attach(punta2_cp12);

	// Window.cpp
	Graph_lib::Text wincpp_title(getPoint(layout, 185, 335), "Window.cpp:");
	wincpp_title.set_font(Font::times_bold);
	wincpp_title.set_font_size(getSize(layout, 14));
	wincpp_title.set_color(Color::black);
	Graph_lib::Rectangle wincpp_rect{ getPoint(layout, 180, 340), getSize(layout, 120), getSize(layout, 40) };
	wincpp_rect.set_color(Color::black);
	wincpp_rect.set_fill_color(Color::yellow);
	Graph_lib::Text wincpp_text(getPoint(layout, 185, 360), "Window Code");
	wincpp_text.set_font(Font::times_bold);
	wincpp_text.set_font_size(getSize(layout, 14));
	wincpp_text.set_color(Color::black);

	win.attach(wincpp_title);
	win.attach(wincpp_rect);
	win.attach(wincpp_text);

	// Arrow window.cpp
	Graph_lib::Line arrow_windowcpp(getPoint(layout, 290, 340), getPoint(layout, 380, 240));
	arrow_windowcpp.set_color(Color::black);
	arrow_windowcpp.set_style(Line_style(Line_style::solid, 1));
	Graph_lib::Circle punta_windowcpp(getPoint(layout, 380, 240), getSize(layout, 3));
	punta_windowcpp.set_color(Color::black);
	punta_windowcpp.set_fill_color(Color::black);

	win.attach(arrow_windowcpp);
	win.attach(punta_windowcpp);

	// Simple_window.h
	Graph_lib::Text simple_window_title(getPoint(layout, 245, 415), "Simple_window.h:");
	simple_window_title.set_font(Font::times_bold);
	simple_window_title.set_font_size(getSize(layout, 14));
	simple_window_title.set_color(Color::black);
	Graph_lib::Rectangle simple_window_rect(getPoint(layout, 240, 420), getSize(layout, 180), getSize(layout, 80));
	simple_window_rect.set_color(Color::black);
	simple_window_rect.set_fill_color(Color::yellow);
	Graph_lib::Text simple_window_r1(getPoint(layout, 245, 440), "// Window Interface:");
	simple_window_r1.set_font(Font::times);
	simple_window_r1.set_font_size(getSize(layout, 14));
	simple_window_r1.set_color(Color::black);
	Graph_lib::Text simple_window_r2(getPoint(layout, 245, 460), "Class Simple_window {...};");
	simple_window_r2.set_font(Font::times_bold);
	simple_window_r2.set_font_size(getSize(layout, 14));
	simple_window_r2.set_color(Color::black);
	Graph_lib::Text simple_window_r3(getPoint(layout, 245, 480), "...");
	simple_window_r3.set_font(Font::times);
	simple_window_r3.set_font_size(getSize(layout, 14));
	simple_window_r3.set_color(Color::black);

	win.attach(simple_window_title);
	win.attach(simple_window_rect);
	win.attach(simple_window_r1);
	win.attach(simple_window_r2);
	win.attach(simple_window_r3);

	// Arrow Simple_window.h
	// to window.h
	Graph_lib::Line arrow1_sw(getPoint(layout, 380, 420), getPoint(layout, 380, 240));
	arrow1_sw.set_color(Color::black);
	arrow1_sw.set_style(Line_style(Line_style::solid, 1));
	Graph_lib::Circle punta1_sw(getPoint(layout, 380, 240), getSize(layout, 3));
	punta1_sw.set_color(Color::black);
	punta1_sw.set_fill_color(Color::black);
	// to gui.h
	Graph_lib::Line arrow2_sw(getPoint(layout, 380, 420), getPoint(layout, 500, 370));
	arrow2_sw.set_color(Color::black);
	arrow2_sw.set_style(Line_style(Line_style::solid, 1));
	Graph_lib::Circle punta2_sw(getPoint(layout, 500, 370), getSize(layout, 3));
	punta2_sw.set_color(Color::black);
	punta2_sw.set_fill_color(Color::black);

	win.attach(arrow1_sw);
	win.attach(punta1_sw);
	win.attach(arrow2_sw);
	win.attach(punta2_sw);

	win.wait_for_button();
	return 0;
}