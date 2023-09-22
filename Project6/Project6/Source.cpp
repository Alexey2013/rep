#define _CRT_SECURE_NO_WARNINGS
#include  "header.h"
#include  "header1.h"
#include <iostream>
#include <stdlib.h>
#include <math.h>
using namespace std;

template <typename T>
Tvector <T>::Tvector(int n) {
	coord = new T[n];
	size = n;
}

template <typename T>
Tvector <T>::Tvector(const Tvector <T>& v) {
	size = v.size;
	coord = new T[size];
	for (int i = 0; i < size; i++) {
		coord[i] = v.coord[i];
	}
}

template <typename T>
Tvector <T>::~Tvector (){
	delete []coord;
	}

template <typename T>
Tvector <T>Tvector<T>:: operator +(const Tvector <T >& v) {
	if (size != v.size) {
		throw("Vector sizes are not equal");
	}
		Tvector <T> tmp(*this);
		for (int j = 0; j < size; j++) {
			tmp.coord[j] += v.coord[j];
		}
		return tmp;
	}

template <typename T>
Tvector <T>Tvector<T>:: operator -(const Tvector <T >& v) {
	if (size != v.size) {
		throw("Vector sizes are not equal");
	}
	Tvector <T> tmp(*this);
	for (int j = 0; j < size; j++) {
		tmp.coord[j] -= v.coord[j];
	}
	return tmp;
}

template <typename T>
T Tvector<T>::operator *(const Tvector <T >& v) const {
	if (size!= v.size) {
		throw("Vector sizes are not equal");
	}
	Tvector <T> tmp(*this);
	T sum=0;
	for (int j = 0; j < size; j++) {
		sum+=tmp.coord[j] * v.coord[j];
	}
	return sum;
}

template <typename T>
const Tvector <T>& Tvector <T> ::operator =(const Tvector <T >& v) {
	Tvector <T> tmp(*this);
	if (tmp == &v) {
		return tmp;
	}
	for (int j = 0; j < size; j++) {
		tmp.coord[j] = v.coord[j];
	}
	return tmp;
}

template <typename T>
bool Tvector <T>:: operator ==(const Tvector <T >& v) const {
	if (size != v.size) {
		return false;
	}
	Tvector <T> tmp(*this);
	for (int i = 0; i < size; i++) {
		if (coord[i] != v.coord[i]);
			return false;
	}
	return true;
}

template <typename T>
bool Tvector <T>:: operator !=(const Tvector <T >& v) const {
	if (size == v.size) {
		return false;
	}
	Tvector <T> tmp(*this);
	for (int i = 0; i < size; i++) {
		if (coord[i] == v.coord[i]);
			return false;
	}
	return true;
}

template <typename T>
double Tvector<T>::len() const {
	double lenght = 0;
	for (int j = 0; j < size; j++) {
		lenght += coord[j] * coord[j];
	}
	return sqrt(lenght);
}

void intro() {
	cout << "MENU:" << endl;
	cout << "1. Get vector addition." << endl;
	cout << "2. Get the vector difference." << endl;
	cout << "3. Get the scalar product of vectors." << endl;
	cout << "4. Get the length of the vector." << endl;
	cout << "5. Exit the program." << endl;
	cout << "Your answer:";
}

void  menu() {
	Tvector <int> v1;
	Tvector <int> v2;
	int answer;
	do {
		intro();
		cin >> answer;
		if (answer != 5) {
			cout << "First vector:" << endl;
			cin >> v1;
			cout << "Second vector:" << endl;
			cin >> v2;
			switch (answer) {
			case 1: {cout << "Addition: " << v1+v2; break; }
			case 2: {cout << "Difference:" << v1-v2; break; }
			case 3: {cout << "Scalar product:" << v1*v2 << endl; break; }
			case 4: {cout << "Length of the first vector:" << v1.len() << endl
				<< "Length of the second vector:" << v2.len() << endl;
				break; }
			}
		}
	} while (answer != 5);
}
