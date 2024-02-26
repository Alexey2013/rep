#include "polynom.h"
#include <iostream>

using namespace std;

int main() {
	try {
		string example1;
		string example2;
		cout << "Enter first polynom:";
		getline(cin, example1);
		TPolynom pol1(example1);
		//cout << "Enter second polynom:";
		//getline(cin, example2);
		//TPolynom pol2(example2);
		cout << example1<<endl;
		cout << "Result(1, 2, 3):"<<pol1(1, 2, 3) << endl;;
		//cout << "1+2" << pol1 + pol2<<endl;
		//cout << "1-2" << pol1-pol2 << endl;
		//cout << "1-2" << pol1*pol2 << endl;
		//cout << "dx(1)" << pol1.dx<< endl;*/
	}
	catch (char* exp) {
		cout << exp << endl;
	}
	return 0;
}