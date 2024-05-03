#include "polynom.h"
using namespace std;

int main() {
	try {
		TPolynom pol1;
		TPolynom pol2;

		cin>>pol1;
		cout << pol1;

		cin >> pol2;
		cout << pol2;

		cout << "p1+p2:" << pol1 + pol2;
		cout << "p1-p2:" << pol1 - pol2;
		cout << "p1*p2:" << pol1 * pol2;

		cout << "1:dx:" << pol1.dx();
		cout << "1:dy:" << pol1.dy();
		cout << "1:dz:" << pol1.dz();
	}
	catch (char* exp) {
		cout << exp << endl;
	}
	return 0;
}
