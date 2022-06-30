#pragma once
#include <map>
#include <fstream>

// prende un file e restituisce un set di parole per le ricerche.
class pulitore
{
public:
	explicit pulitore(std::ifstream& ifs);
	std::map<std::string, int>* get_map();
private:
	std::ifstream* _ifs;
	std::map<std::string, int>* _parole = new std::map<std::string, int>;
};

