#ifndef _HEADER_H
#define _HEADER_H
#include <string>
using namespace std;

class Tvector {
private:
	double x, y, z;
public:
	Tvector();
	Tvector(double X, double Y, double Z);
	Tvector operator +(const Tvector& v);
	Tvector operator -(const Tvector& v);
	const Tvector& operator =(const Tvector& v) ;
	double operator *(const Tvector& v) const;
	double get_length() const;
	double cos(const Tvector& b) const;
	friend ostream& operator<<(ostream& out, const Tvector& v);
	friend istream& operator>>(istream& in, Tvector& v);
};

void menu();
void intro();
#endif
