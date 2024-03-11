#ifndef _MONOM_H
#define _MONOM_H
#include <iostream>
#include "list.h"
using namespace std;

 class TMonom  {
private:
	double coeff;
	int degree;
 public:
	TMonom();
	TMonom(const TMonom& monom);
	TMonom(double _coeff, int _degree);
	TMonom& operator=(const TMonom& _monom);
	double Get_coeff(void)const { return coeff; }
	int Get_degree(void)const { return degree; }
	void Set_coeff(int _coeff) { coeff = _coeff; }
	void Set_degree(int _coeff) { degree = _coeff; }
	bool operator <(const TMonom& data)const;
	bool operator <=(const TMonom& data)const;
	bool operator >(const TMonom& data)const;
	bool operator >=(const TMonom& data)const;
	bool operator ==(const TMonom& data)const;
	bool operator !=(const TMonom& data)const;
	TMonom operator*(const TMonom& monom)const;
	friend ostream& operator<<(ostream& os, const TMonom& m) {
		os << m.coeff << " " << m.degree;
		return os;
	}
};
#endif 