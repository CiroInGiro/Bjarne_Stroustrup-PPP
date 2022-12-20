/* Capitolo 23 Esercizio 12
* Scrivi un programma, basato sul programma che trova linee contenenti date (esercizio 6), che trova tutte le date e le riformatta nel sistema internazionale yyyy-mm-dd.
* Il programma dovrebbe prendere un file di input e produrre un file di output che è identico eccetto per il formato delle date.
*/

#include <iostream>
#include <fstream>
#include <regex>

std::string data_conv(const std::string& y, const std::string& m, const std::string& d) {
	std::string retVal;
	std::string mounth;
	// controllo mesi letterali
	if (m == "Jan") mounth = "01";
	else if (m == "Feb") mounth = "02";
	else if (m == "Mar") mounth = "03";
	else if (m == "Apr") mounth = "04";
	else if (m == "May") mounth = "05";
	else if (m == "Jun") mounth = "06";
	else if (m == "Jul") mounth = "07";
	else if (m == "Aug") mounth = "08";
	else if (m == "Sep") mounth = "09";
	else if (m == "Oct") mounth = "10";
	else if (m == "Nov") mounth = "11";
	else if (m == "Dec") mounth = "12";
	else mounth = m;
	retVal = y + "-" + mounth + "-" + d;
	return retVal;
}

int main(int argc, char** argv) {
	std::ifstream ifs{ "INBOX" };
	std::ofstream ofs{ "INBOX2.txt" };
	std::regex data_it_breve, data_us_estesa;

	if (!ifs) {
		std::cerr << "\n\n\nErrore nell'aprire il file di input.\n\n\n";
		exit(1);
	}

	if (!ofs) {
		std::cerr << "\n\n\nErrore nel creare il file di output.\n\n\n";
		exit(1);
	}

	try {
		data_it_breve = R"( (\d{1,2})/(\d{1,2})/(\d{2}|\d{4}) )";
		//  Sun Jul  3 21:56:12 2022
		data_us_estesa = R"(( \w{3} )(\w{3}) {1,2}(\d{1,2})( \d{2}:\d{2}:\d{2} )(\d{4}))";

		for (std::string line; getline(ifs, line);) {
			while (line.size() > 0) {
				std::smatch match;
				if (std::regex_search(line, match, data_it_breve)) {
					ofs << match.prefix();
					// converti data 
					ofs << "### " << data_conv(match[3], match[2], match[1]) << " ###";
					line = match.suffix();
				}
				else if (std::regex_search(line, match, data_us_estesa)) {
					ofs << match.prefix();
					// converti data
					ofs << match[1] << "### " << data_conv(match[5], match[2], match[3]) << " ###" << match[4];
					line = match.suffix();
				}
				else {
					ofs << line << "\n";
					line = "";
				}
			}
		}
		ofs.close();
		ifs.close();
	}
	catch (std::regex_error e) {
		std::cerr << "Regex Error: " << e.what() << std::endl;
		exit(2);
	}

	return 0;
}