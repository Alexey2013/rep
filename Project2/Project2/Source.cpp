#include  "header.h"
#include <iostream>
#include <cmath>
#include <stdlib.h>

using namespace std;

float* create_a(int n,float left,float right) {
	float* a = new float[n];
	srand((unsigned int)time(0));
	for (int i = 0; i < n; i++) { 
		a[i] = (right - left) / RAND_MAX * rand() + left;
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
	int s1 = -1,s2 = -1;
	int i = 0; int j = n - 1;
	while ((i < n)&&(j > -1)) {
		if ((a[i] < 0)&&(s1 == -1)) { s1 = i; }
		if ((a[j] > 0)&&(s2 == -1)) { s2 = j; }
		i++;
		j--;
	}
		if (s1 == -1) throw "no negative numbers";
		if (s2 == -1) throw "no positive numbers";
	float tmp = a[s1];
	a[s1] = a[s2];
	a[s2] = tmp;


}