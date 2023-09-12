#include  "header.h"
#include <iostream>
#include <cmath>
#include <stdlib.h>

using namespace std;

float* create_a(int n) {
	float* a = new float[n];
	srand((unsigned int)time(0));
	for (int i = 0; i < n; i++)
	{
		a[i] = rand();
	}
	return a;
}

void print_a(int n, float* a) {
	cout << endl;
	for (int i = 0; i < n; i++) {
		cout << a[i] << endl;
	}

}

void change_a(int n, float* a) {
	for (int i = 0; i < n; i++) {
		if (a[i] > 10) {
			a[i] = sqrt(a[i]);

		}
	}


}