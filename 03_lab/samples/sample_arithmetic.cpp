#include <iostream>
#include "stack.h"
#include "arithmetic.h"

using namespace std;

int main() {
	try {
		string s;
		cout << "Enter expression:";
		cin >> s;
		TArithmeticExpression example(s);
		example.SetValues();
		cout <<"Result:" <<example.Calculate() << endl;
	}
	catch (string exp) {
		cout << exp << endl;
	}
	return 0;
}