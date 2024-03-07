#ifndef _MONOM_H
#define _MONOM_H
#include <iostream>
#include "list.h"
using namespace std;

 struct TMonom  {
public:
	double coeff;
	int degree;
	TMonom();
	TMonom(const TMonom& monom);
	TMonom(double _coeff, int _degree);
	TMonom& operator=(const TMonom& _monom);
	bool operator <(const TMonom& data)const;
	bool operator <=(const TMonom& data)const;
	bool operator >(const TMonom& data)const;
	bool operator >=(const TMonom& data)const;
	bool operator ==(const TMonom& data)const;
	bool operator !=(const TMonom& data)const;
};
#endif 