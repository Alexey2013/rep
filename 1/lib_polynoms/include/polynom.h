#ifndef _POLYNOM_H
#define _POLYNOM_H
#include <string>
#include <algorithm>
#include "monom.h"
#include "arithmetic.h"
#include "THeadRingList.h"
using namespace std;

class TPolynom {
private:
	string name;
	THeadRingList<TMonom>* monoms;

	void ParseMonoms();
	void conversion(string& str) const;
public:
	TPolynom();
	TPolynom(const string& _name);
	TPolynom(const THeadRingList<TMonom>* m);
	TPolynom(const TPolynom& p);
	~TPolynom();
	TPolynom operator +(const TPolynom& p);
	TPolynom operator -(const TPolynom& p);
	TPolynom operator-() const;
	TPolynom operator *(const TPolynom& p);
	const TPolynom& operator =(const TPolynom& p);
	double operator ()(double x, double y, double z);
	TPolynom dx() const;
	TPolynom dy() const;
	TPolynom dz() const;
	string ToString()const;
	bool operator==(const TPolynom&p) const;
	bool operator!=(const TPolynom& p) const;
	friend ostream& operator<<(ostream& out, const TPolynom& p);
};

#endif 