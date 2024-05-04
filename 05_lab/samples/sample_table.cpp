#include "intro.h"

int main() {
	try {
		Tables example;
		example.menu();
	}
	catch (char* exp) {
		cout << exp << endl;
	}
	return 0;
}
