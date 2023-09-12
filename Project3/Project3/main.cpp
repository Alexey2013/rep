#include  "header.h"
#include <iostream>
using namespace std;

int main() {
	int n, n_unique;
	cout << "Enter amount:";
	cin >> n;
	int* a = create_a(n);
	int* unique = create_unique(n, a, n_unique);
	print_a(n_unique, unique);
	delete[] a;
	delete[] unique;
	return 0;
}