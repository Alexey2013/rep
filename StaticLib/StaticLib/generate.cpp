#include <iostream>

float* create_a(int n, float left, float right) {
	float* a = new float[n];
	srand((unsigned int)time(0));
	for (int i = 0; i < n; i++) {
		a[i] = (right - left) / RAND_MAX * rand() + left;
	}
	return a;
}