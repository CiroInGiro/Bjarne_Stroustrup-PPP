#pragma once

#include <string>
#include <stdexcept>
#include <iostream>

class Roman_int
{
public:
	Roman_int(int r = 1);
	int as_int() const;
	int to_int(char roman); // restituisce 0 in caso di mancata conversione
	void to_int(int roman_int); // imposta direttamente _roman_int
	std::string to_roman() const;
private:
	int _roman_int;
};

std::ostream& operator<<(std::ostream& os, Roman_int& r);
std::istream& operator>>(std::istream& is, Roman_int& r);