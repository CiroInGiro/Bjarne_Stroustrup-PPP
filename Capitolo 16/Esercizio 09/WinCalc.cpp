#include "WinCalc.h"

void WinCalc::calcola() {
	std::istringstream iss;
	std::ostringstream oss;
	std::ostringstream err;
	iss.str(tastiera.get_string());
	oss.str("");
	err.str("");
	err << "Errori: ";
	Calc calcolatrice(iss, oss, err);
	calcolatrice.calcola();
	//double risultato = calcolatrice.get_result();
	display.put(oss.str());
	log.set_label(err.str());
	redraw();
}