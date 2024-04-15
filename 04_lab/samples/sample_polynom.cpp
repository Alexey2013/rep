#include "polynom.h"
#include <iostream>
using namespace std;

int main() {
	try {
		string example1;
		string example2;
		cout << "Enter polynom 1:";
		getline(cin, example1);
		TPolynom pol1(example1);
		cout << pol1 << endl;
		cout << "Enter polynom 2:";
		getline(cin, example2);
		TPolynom pol2(example2);
		cout << pol2 << endl;

		cout << "p1+p2:" << pol1 + pol2 << endl;
		cout << "p1-p2:" << pol1-pol2 << endl;
		cout << "p1*p2:" << pol1 * pol2 << endl;

		cout << "1:dx:" << pol1.dx() << endl;
		cout << "1:dy:" << pol1.dy() << endl;
		cout << "1:dz:" << pol1.dz() << endl;
		cout << "p1(0.1, 0.2, 0.3):" << pol1(0.1, 0.2, 0.3) << endl;
	}
	catch (char* exp) {
		cout << exp << endl;
	}
	return 0;
}
