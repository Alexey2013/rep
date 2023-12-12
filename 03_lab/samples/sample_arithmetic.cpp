#include <iostream>
#include "stack.h"
#include "arithmetic.h"

using namespace std;

int main() {
	try {
		string str;
		cout << "Enter expression:";
		cin >> str;
		TArithmeticExpression example(str);
		if (example.isCorrectInfixExpression()) {
			example.SetValues();
			cout << "Result:" << example.Calculate() << endl;
		}
	}
	catch (string exp) {
		cout << exp << endl;
	}
	return 0;
}