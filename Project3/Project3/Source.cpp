#include  "header.h"
#include <iostream>
#include <cmath>
#include <stdlib.h>
using namespace std;

int* create_a(int n) {
	int* a = new int[n];
	for (int i = 0; i < n; i++)
	{
		cin >> a[i];
	}
	return a;
}

void print_a(int n, int* a) {
	cout  << endl;
	for (int i = 0; i < n; i++) {
		cout << a[i] << endl;
	}
}

int count_unique(int n, int* a) {
	int count = 0;
	for (int i = 0; i < n; i++) {
		bool flag = false;
		for (int j = 0; j < i; j++) {
			if (a[i] == a[j]) {
				flag = true;
				break;
			}
		}
		if (!flag) { count++; }
	}
	return count;
}

int* create_unique(int n, int* a, int &n_unique) {
	n_unique =count_unique(n, a);
	int* uniqueArray = new int[n_unique];
	int k = 0;
	for (int i = 0; i < n; i++) {
		bool flag = false;
		for (int j = 0; j < i; j++) {
			if (a[i] == a[j]) {
				flag = true;
				break;
			}
		}
		if (!flag) {
			uniqueArray[k] = a[i];
			k++;
		}
	}
	return uniqueArray;
}