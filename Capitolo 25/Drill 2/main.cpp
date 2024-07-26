/*
* Run that again with v declared to be an unsigned int.
*/

#include <iostream>

int main() {
	using std::cout;

	unsigned int v{ 1 };

	for (int i = 0; i < sizeof(v) * 8; ++i) {
		cout << v << ' ';
		v <<= 1;
	}

	return 0;
}