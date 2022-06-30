#pragma once
#include <set>
#include <fstream>

// prende un file e restituisce un set di parole per le ricerche.
class pulitore
{
public:
	explicit pulitore(std::ifstream& ifs);
	std::set<std::string>* get_set();
private:
	std::ifstream* _ifs;
	std::set<std::string>* _parole;
};

