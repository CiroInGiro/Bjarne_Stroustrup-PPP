#pragma once

#ifndef ORDINI_H
#define ORDINI_H

#include <fstream>
#include <iostream>
#include <vector>
#include <string>
//#include <list>
//#include <algorithm> // per merge e sort
//#include <iterator>

struct Logger {
	std::ofstream ofile;
	std::string last_message;
public:
	Logger() : last_message{ "Errore generico" } {
		logga(last_message);
	}
	Logger(const std::string& s) {
		logga(s);
	}
	Logger(const Logger& old) {
		last_message = old.last_message;
	}
	void logga(const std::string testo) {
		ofile.open("log.txt", std::ios_base::app);
		if (!ofile) ofile.open("log.txt");
		ofile << testo << std::endl;
		ofile.close();
	}
	std::string what() { return last_message; }
};

struct Data {
	int day;
	int month;
	int year;
	Data() : day{ 0 }, month{ 0 }, year{ 0 } {}
	friend std::ofstream& operator<<(std::ofstream& ofs, Data& d);
	friend std::ifstream& operator>>(std::ifstream& ifs, Data& d);
	friend std::ostream& operator<<(std::ostream& os, Data& d);
	friend std::istream& operator>>(std::istream& is, Data& d);
	void operator=(const Data& d) {
		day = d.day;
		month = d.month;
		year = d.year;
	}
	operator bool() { return !(day == 0 || month == 0 || year == 0); }
};

struct Purchase {
	std::string prodotto;
	double unit_price;
	int count;
public:
	Purchase() : prodotto{ "" }, unit_price{ 0 }, count{ 0 } {}
	friend std::ofstream& operator<<(std::ofstream& ofs, Purchase& p);
	friend std::ifstream& operator>>(std::ifstream& ifs, Purchase& p);
	friend std::ostream& operator<<(std::ostream& os, Purchase& p);
	friend std::istream& operator>>(std::istream& is, Purchase& p);
	void operator=(Purchase& b) {
		prodotto = b.prodotto;
		unit_price = b.unit_price;
		count = b.count;
	}
	operator bool() { return (prodotto != "" && unit_price > 0); }
};

struct Order {
	std::string cliente;
	std::string address;
	Data data_ordine;
	std::vector<Purchase> acquisti;
public:
	Order() : cliente{ "" }, address{ "" }, data_ordine{} {}
	friend std::ofstream& operator<<(std::ofstream& ofs, Order& o);
	friend std::ifstream& operator>>(std::ifstream& ifs, Order& o);
	friend std::ostream& operator<<(std::ostream& os, Order& o);
	friend std::istream& operator>>(std::istream& is, Order& o);
	operator bool() { return (cliente != "" && address != "" && data_ordine && acquisti.size() > 0); }
	void operator=(const Order& o) {
		cliente = o.cliente;
		address = o.address;
		data_ordine = o.data_ordine;
		acquisti = o.acquisti; // copia del vettore
	}
};

#endif // !ORDINI_H