#ifndef _MONOM_H
#define _MONOM_H
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include "stack.h"
#include "list.h"
using namespace std;

class TMonom : public TData {
private:
	double coeff;
	int degree;
public:
	TMonom();
	TMonom(const TMonom& monom);
	TMonom(double _coeff, int _degree);
	TData* copy() const;
	bool operator <(const TData& data)const;
	bool operator <=(const TData& data)const;
	bool operator >(const TData& data)const;
	bool operator >=(const TData& data)const;
	bool operator ==(const TData& data)const;
	bool operator !=(const TData& data)const;
	friend ostream& operator<<(ostream& os, const TMonom& monom);
};

#endif 