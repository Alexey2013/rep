#include "polynom.h"
#include <iostream>
using namespace std;

int main() {
	try {
		string example1;
		string example2;
		cout << "Enter polynom:";
		getline(cin, example1);
		TPolynom pol1(example1);
		cout << example1<<endl;
		cout << "Result(1, 2, 3):"<<pol1(1, 2, 3) << endl;
		pol1.print();
		cout << endl;
		pol1.dx();
		pol1.print();
	}
	catch (char* exp) {
		cout << exp << endl;
	}
	return 0;
}

