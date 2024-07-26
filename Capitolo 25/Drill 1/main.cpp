/*
* Run this:
* int v=1; for(int i=0; i<sizeof(v)*8; ++i) {cout<<v<<' ';v<<1;}
*/

#include <iostream>

int main() {
	using std::cout;

	int v{ 1 };

	for (int i = 0; i < sizeof(v) * 8; ++i) {
		cout << v << ' ';
		v <<= 1;
	}

	return 0;
}