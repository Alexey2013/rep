#include "polynom.h"
#include <iostream>
using namespace std;

int main() {
	try {
		string example1;
		cout << "Enter polynom:";
		getline(cin, example1);
		TPolynom pol1(example1);
		cout << example1<<endl;
		cout << "Result(1, 2, 3):"<<pol1(1, 2, 3) << endl;
		pol1.ParseMonoms();
		pol1.printMonoms();
	}
	catch (char* exp) {
		cout << exp << endl;
	}
	return 0;
}

