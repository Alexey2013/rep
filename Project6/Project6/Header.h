#ifndef _HEADER_H
#define _HEADER_H
#include <iostream>
#include <string>
using namespace std;

template <typename T>
class Tvector {
private:
	int size;
	T* coord;
public:
	Tvector(int n = 3);
	Tvector(const Tvector <T>& v);
	~Tvector ();
	Tvector<T> operator +(const Tvector <T >& v);
	Tvector<T> operator -(const Tvector <T >& v);
	T operator *(const Tvector <T >& v) const;
	const Tvector <T>& operator  =(const Tvector <T>& v);
	bool operator ==(const Tvector <T>& v) const;
	bool operator !=(const Tvector <T>& v) const;
	friend ostream& operator <<(ostream& out, const Tvector<T>& v) {
		out << endl;
		for (int i = 0; i <v.size; i++) {
			out << v.coord[i] << endl;;
		}
		return out;
	}
	friend istream& operator >>(istream& in, Tvector <T>& v) {
		for (int i = 0; i < v.size; i++) {
			in>> v.coord[i];
		}
		return in;
	}
	double len() const;
};


#endif