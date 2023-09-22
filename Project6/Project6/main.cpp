#include  "header.h"
#include  "header1.h"
#include <iostream>
using namespace std;

int main() {
	try {
		menu();
	}
	catch (const char* ex) {
		cout << ex;
	}
	return 0;
}
