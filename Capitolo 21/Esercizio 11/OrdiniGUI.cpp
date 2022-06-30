#include "OrdiniGUI.h"

// --------------------------------------------------------------------------------------
// Riga di input nella maschera inserimento ordini
righe_ordine::righe_ordine(Point pos, int width, int height, int p1, int p2, int p3) : Widget(pos, width, height, "", 0) {
	
	if ((p1 + p2 + p3) > 100) p1 = p2 = p3 = 30;
	int p4 = 100 - p1 - p2 - p3;
	double wmargin{ 0.0 };
	if (p4 <= 0) wmargin = 0; else wmargin = width * (p4 / 100.0);
	wmargin /= 3;
	double wdesc = width * (p1 / 100.0);
	double wprezzo = width * (p2 / 100.0);
	double wqty = width * (p3 / 100.0);
	//double wmargin = (_width - wdesc - wprezzo - wqty) / 4;
	//int dx = wmargin;
	int dx = pos.x;
	int dy = pos.y;
	// posiziono il campo per la descrizone
	_prodotto = new Graph_lib::In_box(Point{ dx, dy }, wdesc, height, "");

	// posizione la quantita
	dx += (int)(wdesc + wmargin);
	_quantità = new Graph_lib::In_box(Point{ dx, dy }, wqty, height, "");

	// posiziono il campo per il prezzo unitario
	dx += (int)(wqty + wmargin);
	_prezzo = new Graph_lib::In_box(Point{ dx, dy }, wprezzo, height, "");
}

void righe_ordine::move(int dx, int dy) {
	_prodotto->move(dx, dy);
	_prezzo->move(dx, dy);
	_quantità->move(dx, dy);
}

void righe_ordine::attach(Graph_lib::Window& w) {
	_prodotto->attach(w);
	_quantità->attach(w);
	_prezzo->attach(w);
}

void righe_ordine::hide() {
	_prodotto->hide();
	_prezzo->hide();
	_quantità->hide();
}

void righe_ordine::show() {
	_prodotto->show();
	_prezzo->show();
	_quantità->show();
}

Purchase righe_ordine::get_riga() {
	Purchase retVal;
	retVal.prodotto = _prodotto->get_string();
	std::istringstream iss{ _prezzo->get_string() };
	iss >> retVal.unit_price;
	retVal.count = _quantità->get_int();
	return retVal;
}
// --------------------------------------------------------------------------------------

// Finestra con la testata ordine e le righe
// --------------------------------------------------------------------------------------
// costruttore
InserimentoOrdini::InserimentoOrdini(Point pos, int width, int height, const std::string titolo, Order& ordine) : Window(pos, width, height, titolo),
	_cliente(Point{ 0, 0}, (width * 80 / 100), 25, "Cliente: "),
	_indirizzo(Point{ 0, 0 }, (width * 80 / 100), 25, "Indirizzo: "),
	_data(Point{ 0, 0 }, 150, 25, "Data: "),
	_prev(Point{ 0, 0 }, 120, 25, "Prev", cb_prev),
	_next(Point{ 0, 0 }, 120, 25, "Next", cb_next),
	_salva(Point{ 0, 0 }, 120, 25, "Salva", cb_salva)
{
	// Prima di tutto colleghiamo il tutto alla finestra: altrimenti Fltk non potrà gestirli (muoverli e aggiornarli)
	attach(_cliente);
	attach(_indirizzo);
	attach(_data);
	attach(_prev);
	attach(_next);
	attach(_salva);

	// Impostiamo le variabili
	_ordine = &ordine;

	// Impostiamo la configurazione della finestra
	_margine = 5;
	_field_height = 25;
	x_min = 350;
	y_min = (6 * _field_height) + (7 * _margine);

	// impostiamo sulla dimensione minima della finestra o gestendo lo spazio in percentuale
	int x_deep = (x_min > x_max()) ? x_min : x_max();
	int y_deep = (y_min > y_max()) ? y_min : y_max();
	int dx = _margine + 100;
	int dy = _margine + _field_height;
	_cliente.move(dx, dy);

	dy += _margine + _indirizzo.height;
	_indirizzo.move(dx, dy);
	dy += _margine + _data.height;
	_data.move(dx, dy);

	// impostiamo un 2% per i margini, 12% per i campi numerici e il resto per la descrizione
	double wdesc = (x_deep - dx - _margine) * 0.70;
	double wprezzo = (x_deep - dx - _margine) * 0.12;
	double wqty = (x_deep - dx - _margine) * 0.12;
	double wmargin = (x_deep - dx - _margine) * 0.02;
	int riga_dx = dx;
	Graph_lib::Out_box* label;
	dy += _margine + _field_height;
	label = new Graph_lib::Out_box(Point{ riga_dx, dy }, wdesc, _field_height, "");
	attach(*label);
	label->put("DESCRIZIONE");
	riga_dx += wdesc + wmargin;
	label = new Graph_lib::Out_box(Point{ riga_dx, dy }, wqty, _field_height, "");
	attach(*label);
	label->put("QUANTITA");
	riga_dx += wqty + wmargin;
	label = new Graph_lib::Out_box(Point{ riga_dx, dy }, wprezzo, _field_height, "");
	attach(*label);
	label->put("PREZZO");
	dy += _field_height + _margine;
	r_start = 0;
	r_max = (y_deep - dy - _margine - _field_height - _margine) / (_margine + _field_height);
	if (r_max < 1) r_max = 1;
	int riga_x_deep = x_deep - dx - _margine;
	r_pos = Point{ dx, dy };
	for (int i = 0; i < r_max; ++i) {
		righe_ordine* r = new righe_ordine{ Point{ dx, dy }, riga_x_deep, _field_height, 70, 12, 12 };
		attach(*r);
		_righe.push_back(r);
		dy += _field_height + _margine;
	}

	// posizioniamo i tasti
	dx = _margine;
	dy += _field_height + _margine;
	_prev.move(dx, dy);
	dx += 120 + _margine;
	_next.move(dx, dy);
	dx = x_deep - _margine - 120;
	_salva.move(dx, dy);
	gira = true;
}
// --------------------------------------------------------------------------------------

// --------------------------------------------------------------------------------------
// call back prev 
void InserimentoOrdini::cb_prev(Graph_lib::Address own, Graph_lib::Address pw) {
	Graph_lib::reference_to<InserimentoOrdini>(pw).prev();
}
// --------------------------------------------------------------------------------------

// --------------------------------------------------------------------------------------
// call back next
void InserimentoOrdini::cb_next(Graph_lib::Address own, Graph_lib::Address pw) {
	Graph_lib::reference_to<InserimentoOrdini>(pw).next();
}
// --------------------------------------------------------------------------------------

// --------------------------------------------------------------------------------------
// call back salva
void InserimentoOrdini::cb_salva(Graph_lib::Address own, Graph_lib::Address pw) {
	Graph_lib::reference_to<InserimentoOrdini>(pw).salva();
}
// --------------------------------------------------------------------------------------

// --------------------------------------------------------------------------------------
// funzione prev
void InserimentoOrdini::prev() {
	// se possiamo visualizzare la pagine precedente
	if (r_start - r_max >= 0) {
		// nascondiamo le righe attuali
		unsigned int limit = ((r_start + r_max) < _righe.size()) ? (r_start + r_max) : _righe.size();
		for (unsigned int i = r_start; i < limit; ++i) {
			_righe[i]->hide(); // mi serve hide e show
		}
		r_start -= r_max;
		limit = ((r_start + r_max) < _righe.size()) ? (r_start + r_max) : _righe.size();
		for (unsigned int i = r_start; i < limit; ++i) _righe[i]->show();
	}
}
// --------------------------------------------------------------------------------------

// --------------------------------------------------------------------------------------
// funzione next
void InserimentoOrdini::next() {
	// controlliamo se le righe sono già state create
	// dobbiamo prima aggiornare r_start
	r_start += r_max;
	if ((r_start + r_max) > _righe.size()) {
		// creiamo le righe mancanti
		int posx = r_pos.x;
		int posy = r_pos.y;
		int x_deep = (x_min > x_max()) ? x_min : x_max();
		int riga_x_deep = x_deep - posx - _margine;
		for (unsigned int i = _righe.size(); i < (r_start + r_max); ++i) {
			righe_ordine* r = new righe_ordine(Point{ posx, posy }, riga_x_deep, _field_height, 70, 12, 12);
			attach(*r);
			_righe.push_back(r);
			posy += _field_height + _margine;
		}
	}
	// nascondiamo le righe attuali
	for (unsigned int i = (r_start - r_max); i < r_start; ++i) _righe[i]->hide();

	// visualizziamo le prossime
	//r_start += r_max;
	for (unsigned int i = r_start; i < (r_start + r_max); ++i) _righe[i]->show();
}
// --------------------------------------------------------------------------------------

// --------------------------------------------------------------------------------------
// funzione salva, se abbiamo un puntatore valido lo aggiorniamo
void InserimentoOrdini::salva() {
	if (_ordine) {
		_ordine->cliente = _cliente.get_string();
		_ordine->address = _indirizzo.get_string();
		std::istringstream data_stream{ _data.get_string() };
		data_stream >> _ordine->data_ordine;
		for (righe_ordine* r : _righe) {
			Purchase p{ r->get_riga() };
			if (p) _ordine->acquisti.push_back(p);
		}
	}
	if (*_ordine) gira = false;
}
// --------------------------------------------------------------------------------------

// --------------------------------------------------------------------------------------
// funzione loop per la grafica che intercetta gli eventi
void InserimentoOrdini::go() {
	while (gira) Fl::wait(1000);
}
// --------------------------------------------------------------------------------------
