#include "WumpusGUI.h"

WumpusGUI::WumpusGUI(Point pos, int width, int height, const std::string& titolo) : Window(pos, width, height, titolo),
cmd(Point{ (pos.x + 70), (y_max() - 40) }, (width - 200), 30, "Comandi: "),
esito(Point{ (pos.x + 70), (y_max() - 150) }, (width - 200), 100, "Esito: "),
vai(Point{ (x_max() - 120), (y_max() - 40) }, 80, 30, "VAI", [](Address, Address pw) {reference_to<WumpusGUI>(pw).action(); })
{
	Window::color(Color::white);
	dim_room = 40;
	margin = 20;
	xc = width / 2;
	yc = (y_max() - 150) / 2;
	in_sense = false;
	hero = nullptr;
	stanza_attuale = nullptr;
	oss.str("");
	attach(cmd);
	attach(esito);
	attach(vai);
}

void WumpusGUI::action() {
	in_sense = true;
	iss.str(cmd.get_string());
}

istream& WumpusGUI::cin() {
	//std::stringstream retVal{ "" };
	//redraw();
	//while (!in_sense) { Fl::wait(); }
	//if (in_sense) retVal.str(cmd.get_string());
	//in_sense = false;
	//Fl::redraw();
	//return retVal;
	//iss.str(cmd.get_string());
	//iss.str("");
	return iss;
}

ostream& WumpusGUI::cout() {
	// oss.str("");
	return oss;
}

bool WumpusGUI::get_in_sense() const { return in_sense; }

void WumpusGUI::reset_in_sense() { in_sense = false; }

void WumpusGUI::refresh() { 
	esito.put(oss.str());
	oss.str("");
	redraw(); 
}

void WumpusGUI::set_hero(Room* h) { 
	// imposto la testa della lista. Solo la prima volta !!!
	if (!hero) inizializza(h);
	else {
		hero = h;
		stanza_attuale->toggle_hero();
		stanza_attuale = trova_hero(h);
		if (!stanza_attuale) throw;
		stanza_attuale->toggle_hero();
	}
	//redraw();
}

void WumpusGUI::inizializza(Room* h) {
	hero = h;
	Explorer e(hero, xc, yc, margin, dim_room);
	stanza_attuale = e.vai(&stanze);
	stanza_attuale->set_visitata(true);
	stanza_attuale->toggle_hero();
	for (RoomGUI* s : stanze) {
		attach(*(s->getgui()));
	}
}

RoomGUI* WumpusGUI::trova_hero(Room* h) {
	for (RoomGUI* stanza : stanze) {
		if (stanza->get_stanza() == h) return stanza;
	}
	return nullptr;
}

void WumpusGUI::set_wump(Room* w) {
	for (RoomGUI* r : stanze) {
		if (r->get_stanza() == w) r->set_wump(true);
		else r->set_wump(false);
		//r->getgui()->draw();
	}
	//redraw();
}

void WumpusGUI::mark_pit(Room* p) {
	for (RoomGUI* rg : stanze) {
		if (rg->get_stanza() == p) rg->toggle_markpit();
	}
}

void WumpusGUI::mark_bat(Room* b) {
	for (RoomGUI* rg : stanze) {
		if (rg->get_stanza() == b) rg->toggle_markbat();
	}
}

void WumpusGUI::mark_wump(Room* w) {
	for (RoomGUI* rg : stanze) {
		if (rg->get_stanza() == w) rg->toggle_markwump();
	}
}

void WumpusGUI::move_rooms(int dx, int dy) {
	for (RoomGUI *stanza : stanze) {
		stanza->getgui()->move(dx, dy);
	}
//	redraw();
}

void WumpusGUI::move_rear() {
	// sposta tutto a destra e piazza la stanza in rear al centro
	int dx, dy;
	dx = dim_room + margin;
	dy = 0;
	//stanza_attuale->getgui()->set_label("");
	//stanza_attuale->getgui()->set_width(dim_room);
	//stanza_attuale->getgui()->set_height(dim_room);
	stanza_attuale->toggle_hero();
	stanza_attuale = stanza_attuale->rear;
	stanza_attuale->toggle_hero();
	hero = hero->rear;
	//move_rooms(dx, dy);
}

void WumpusGUI::move_front() {
	// sposta tutto a sinistra e piazza la stanza in front al centro
	int dx, dy;
	dx = -dim_room - margin;
	dy = 0;
	//stanza_attuale->getgui()->set_label("");
	//stanza_attuale->getgui()->set_width(dim_room);
	//stanza_attuale->getgui()->set_height(dim_room);
	stanza_attuale->toggle_hero();
	stanza_attuale = stanza_attuale->front;
	stanza_attuale->toggle_hero();
	hero = hero->front;
//	move_rooms(dx, dy);
}

void WumpusGUI::move_left() {
	// sposta tutto in basso e piazza la stanza in left al centro
	int dx, dy;
	dy = dim_room + margin;
	dx = 0;
	//stanza_attuale->getgui()->set_label("");
	//stanza_attuale->getgui()->set_width(dim_room);
	//stanza_attuale->getgui()->set_height(dim_room);
	stanza_attuale->toggle_hero();
	stanza_attuale = stanza_attuale->left;
	stanza_attuale->toggle_hero();
	hero = hero->left;
//	move_rooms(dx, dy);
}

void WumpusGUI::move_right() {
	// sposta tutto in altro e piazza la stanza in right al centro
	int dx, dy;
	dy = -dim_room - margin;
	dx = 0;
	//stanza_attuale->getgui()->set_label("");
	//stanza_attuale->getgui()->set_width(dim_room);
	//stanza_attuale->getgui()->set_height(dim_room);
	stanza_attuale->toggle_hero();
	stanza_attuale = stanza_attuale->right;
	stanza_attuale->toggle_hero();
	hero = hero->right;
//	move_rooms(dx, dy);
}

void WumpusGUI::debug() {
	for (RoomGUI* s : stanze) {
		s->set_visitata(true);
	}
	redraw();
}