/*
Capitolo 19 Esercizio 12
Definisci una classe File_handle che prende una string come argomento (nome del file) nel costruttore,
apre il file nel costruttore e lo chiude nel distruttore.
*/

#include <iostream>
#include <fstream>

class File_handle : public std::fstream {
private:
	std::fstream file;
public:

	File_handle(const std::string& name) {
		file.open(name.c_str(), std::ios_base::app|std::ios_base::out);
		if (!file) throw;
	}
	~File_handle() {
		file.flush();
		file.close();
	}
	File_handle& operator<<(const std::string& in) {
		file << in;
		return *this;
	}
};

void save_str(const std::string& file, const std::string& stringa) {
	File_handle fh(file);
	fh << stringa;
}

int main(int argc, char** argv[]) {
	save_str("miofile.txt", "Buon Natale.");
	return 0;
}
