#include  "\StaticLib\StaticLib\generate.h"
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
	float* a = create_a(n, l, r);
}