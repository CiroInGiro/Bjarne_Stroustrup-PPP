#include "Roman_int.h"

Roman_int::Roman_int(int r) : _roman_int{ r } {};

int Roman_int::as_int() const { return _roman_int; }

std::string Roman_int::to_roman() const{
	if (_roman_int == 1) return "I";
	if (_roman_int == 5) return "V";
	if (_roman_int == 50) return "L";
	if (_roman_int == 100) return "C";
	if (_roman_int == 500) return "D";
	if (_roman_int == 1000) return "M";
	return " ";
}

int Roman_int::to_int(char roman) {
	if (roman == 'I') _roman_int = 1;
	else if (roman == 'V') _roman_int = 5;
	else if (roman == 'X') _roman_int = 10;
	else if (roman == 'L') _roman_int = 50;
	else if (roman == 'C') _roman_int = 100;
	else if (roman == 'D') _roman_int = 500;
	else if (roman == 'M') _roman_int = 1000;
	else return 0;
	return _roman_int;
}

void Roman_int::to_int(int roman_int) { _roman_int = roman_int; }

std::ostream& operator<<(std::ostream& os, Roman_int& r) {
	//os << r.to_roman();
	int _numero = r.as_int();
	std::string roman{ "" };
	while (_numero != 0) {
		if (_numero < 0) throw std::runtime_error{ "conversione in numeri romani minore di 0" };
		if (_numero >= r.to_int('M')) {
			roman += "M";
			_numero -= r.to_int('M');
		}
		else if (_numero >= r.to_int('D')) {
			roman += "D";
			_numero -= r.to_int('D');
		}
		else if (_numero >= r.to_int('C')) {
			int diff = r.to_int('D') - r.to_int('C');
			if (_numero >= diff) {
				roman += "CD";
				_numero -= diff;
			}
			else {
				roman += "C";
				_numero -= r.to_int('C');
			}
		}
		else if (_numero >= r.to_int('L')) {
			roman += "L";
			_numero -= r.to_int('L');
		}
		else if (_numero >= r.to_int('X')) {
			int diff = r.to_int('L') - r.to_int('X');
			if (_numero >= diff) {
				roman += "XL";
				_numero -= diff;
			}
			else {
				roman += "X";
				_numero -= r.to_int('X');
			}
		}
		else if (_numero >= r.to_int('V')) {
			roman += "V";
			_numero -= r.to_int('V');
		}
		else if (_numero >= r.to_int('I')) {
			int diff = r.to_int('V') - r.to_int('I');
			if (_numero >= diff) {
				roman += "IV";
				_numero -= diff;
			}
			else {
				roman += "I";
				_numero -= r.to_int('I');
			}
		}
	}
	os << roman;
	return os;
}

// I numeri romani si leggono da sinistra verso destra, leggo un simbolo x volta
// I X C M possono ripetersi massimo 3 volte consecutive
// V L D non possono essere ripetuti consecutivamente
// Un simbolo tra due simboli di valore maggiore viene sottratto dal successivo altrimenti si sommano
// I X C sono gli unici che possono essere sottratti e 1 sola volta
// Il simbolo sottratto non deve essere inferiore ad 1/10 del simbolo al quale viene sottratto 


std::istream& operator>>(std::istream& is, Roman_int& r) {
	std::string roman{ "" };
	//is >> roman;
	char ch[1]{ ' ' };

	while (ch[0] != '0') {
		is.read(ch, 1);
		switch (ch[0]) {
		case 'I':
		case 'V':
		case 'X':
		case 'L':
		case 'C':
		case 'D':
		case 'M':
			roman += ch[0];
			break;
		default:
			is.unget();
			ch[0] = '0';
			break;
		}
	}
	int roman_int{ 0 };
	int attuale = 0;
	int precedente, successivo;
	char s1, s2, s3;
	int ripetizioni{ 0 };

	while (attuale < roman.size()) {
	//for (char croman : roman) {
		precedente = attuale - 1;
		successivo = attuale + 1;
		if (precedente >= 0) s1 = roman[precedente]; else s1 = ' ';
		s2 = roman[attuale];
		if (successivo < roman.size()) s3 = roman[successivo]; else s3 = ' ';
		// abbiamo la situazione da 1 a 3 simboli vicini
		// per un simbolo solo
		if (s1 == ' ' && s3 == ' ') roman_int += r.to_int(s2);
		// per due simboli soli
		if (s1 == ' ' && s3 != ' ') {
			if ((r.to_int(s2) < r.to_int(s3)) && (s2 == 'I' || s2 == 'X' || s2 == 'C')) {
				if (r.to_int(s2) < (r.to_int(s3) / 10)) throw std::runtime_error{ "Simbolo da sottrarre troppo piccolo" };
				roman_int -= r.to_int(s2);
			}
			else roman_int += r.to_int(s2);
		}
		// ci spostiamo avanti e abbiamo solo s1 e s2
		if (s1 != ' ' && s3 == ' ') {
			// s1 è già stato valutato nel ciclo precedente
			//if (r.to_int(s1) < r.to_int(s2)) roman_int += (r.to_int(s2) - r.to_int(s1));
			roman_int += r.to_int(s2);
		}
		// abbiamo 3 simboli o più
		if (s1 != ' ' && s2 != ' ' && s3 != ' ') {
			if (r.to_int(s2) < r.to_int(s1) && r.to_int(s2) < r.to_int(s3)) {
				if (s2 != 'I' && s2 != 'X' && s2 != 'C') throw std::runtime_error{ "Simbolo non sottraibile." };
				if (r.to_int(s2) < (r.to_int(s3) / 10)) throw std::runtime_error( "Simbolo da sottrarre troppo piccolo" );
				roman_int -= r.to_int(s2);
			}
			else {
				if (r.to_int(s2) < r.to_int(s3)) throw std::runtime_error{ "Simboli mal formati, mettimi i simboli in ordine decrescenti." };
				roman_int += r.to_int(s2);
			}
		}
		// controllo ripetizioni
		if (s2 == s1) ++ripetizioni; else ripetizioni = 0;
		if (ripetizioni) {
			if ((s2 == 'I' || s2 == 'X' || s2 == 'C' || s2 == 'M') && ripetizioni > 2) throw std::runtime_error{ "Troppe ripetizioni dei simboli I, X, C, M." };
			if ((s2 == 'V' || s2 == 'L' || s2 == 'D') && ripetizioni > 0) throw std::runtime_error{ "I simboli V, L e D non possono ripetersi." };
		}
		//int next_roman_int = r.to_int(croman);
		//if (next_roman_int == 0) break;
		//roman_int += next_roman_int;
		++attuale;
	}

	r.to_int(roman_int);

	return is;
}