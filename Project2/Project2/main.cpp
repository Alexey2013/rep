#include  "header.h"
#include <iostream>
using namespace std;

int main() {
	int n;
	float l, r;
	cout << "Enter amount:";
	cin >> n;
	cout << "Enter left: ";
	cin >> l;
	cout << "Enter right: ";
	cin >> r;
	float* a = create_a(n,l,r);
	print_a(n, a);
	try {
		change_a(n, a);
		print_a(n, a);
	}
	catch (const char* ex) {
		cout << ex;
	}
	delete[]a;
	return 0;
}