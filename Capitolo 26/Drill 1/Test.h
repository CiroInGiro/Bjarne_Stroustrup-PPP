#pragma once
#include <string>
#include <vector>
#include <iostream>

// Creo la struttura come classe
// Test è la struttura che contiene il test da eseguire e legge da stream
class Test
{
public:
	std::string label;
	int val;
	std::vector<int> seq;
	bool res;
	// operatore di input
	friend std::istream& operator>>(std::istream& is, Test& t);
};
