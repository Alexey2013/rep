#include "polynom.h"
#include <iostream>
using namespace std;

int main() {
	try {
		TPolynom pol3;
		string example1;
		string example2;
		cout << "Enter polynom 1:";
		getline(cin, example1);
		TPolynom pol1(example1);
		//cout << pol1;
		//cout << pol1.dx();
		//cout << pol1.dy();
		//cout << pol1.dz();
			cout << "Enter polynom 2:";
		getline(cin, example2);
		TPolynom pol2(example2);
		//pol3 = pol1 + pol2;
		//cout<<pol3;
		pol3 = pol1- pol2; 
		//cout << pol3;
	/*	pol3 = pol1*pol2;*/
		cout << pol3;
		cout << pol1(0.1, 0.2, 0.3);
	}
	catch (char* exp) {
		cout << exp << endl;
	}
	return 0;
}

