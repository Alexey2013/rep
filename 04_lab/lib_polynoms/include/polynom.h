#ifndef _POLYNOM_H
#define _POLYNOM_H
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include "monom.h"
#include "stack.h"
#include "arithmetic.h"
#include "THeadRingList.h"
using namespace std;

class TPolynom {
private:
	string name;
	TList<TMonom>* monoms;
	void ParseMonoms();
public:
	TPolynom();
	TPolynom(const string& _name);
	TPolynom(const TList<TMonom>* m);
	TPolynom(const TPolynom& p);
	~TPolynom();
	TPolynom operator +(const TPolynom& p);
	TPolynom operator -(const TPolynom& p);
	TPolynom operator *(const TPolynom& p);
	TPolynom& operator =(const TPolynom& p);
	double operator ()(double x, double y, double z);
	TPolynom dx() const;
	TPolynom dy() const;
	TPolynom dz() const;
	bool operator==(const TPolynom&p) const;
	bool operator!=(const TPolynom& p) const;
	friend ostream& operator<<(ostream& out, const TPolynom& p)
	{
		cout << endl;
		while (p.monoms->GetCurrent() != nullptr)
		{
			int deg = p.monoms->GetCurrent()->data.Get_degree();
			int x = deg / 100;
			int y = (deg % 100) / 10;
			int z = deg % 10;
			cout << p.monoms->GetCurrent()->data.Get_coeff() << "*" << "x^" << x << "*" << "y^" << y << "*" << "z^" << z << endl;
			p.monoms->next();
		}
		return out;
}
};

#endif 