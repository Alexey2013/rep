#include  "header.h"
#include  "header1.h"
#include <iostream>
using namespace std;

int main() {
	try {
		string path = get_path();
		group group(path);
	}
	catch (const char* ex) {
		cout << ex;
	}
	return 0;
}
