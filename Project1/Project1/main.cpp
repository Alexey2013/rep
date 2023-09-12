#include  "header.h"
#include <iostream>
using namespace std;

int main() {
	int n;
	cout << "Enter amount:";
	cin >> n;
	float* a = create_a(n);
	print_a(n, a);
	change_a(n, a);
	print_a(n, a);
	delete[]a;
	return 0;
}