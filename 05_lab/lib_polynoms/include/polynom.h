#ifndef _POLYNOM_H
#define _POLYNOM_H
#include <string>
#include <algorithm>
#include "monom.h"
#include "THeadRingList.h"
using namespace std;

class TPolynom {
private:
	string name;
	THeadRingList<TMonom>* monoms;

	void parse_monoms(const string& _name);
	void convert_string(string& str) const;
	void similar();
public:
	TPolynom();
	TPolynom(const string& _name);
	TPolynom(const THeadRingList<TMonom>* l);
	TPolynom(const TPolynom& p);
	~TPolynom();
	TPolynom operator +(const TPolynom& p);
	TPolynom operator -(const TPolynom& p);
	TPolynom operator -() const;
	TPolynom operator *(const TPolynom& p);
	const TPolynom& operator =(const TPolynom& p);
	TPolynom dx() const;
	TPolynom dy() const;
	TPolynom dz() const;
	string ToString()const;
	bool operator ==(const TPolynom&p) const;
	bool operator !=(const TPolynom& p) const;
	friend ostream& operator<<(ostream& os, const TPolynom& p);
	friend istream& operator>>(istream& in, TPolynom& p);
};

#endif 