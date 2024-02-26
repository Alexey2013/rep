#ifndef _POLYNOM_H
#define _POLYNOM_H
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include "monom.h"
#include "stack.h"
#include "list.h"
using namespace std;

class  TPolynom {
private:
	string name;
	THeadRingList* monoms;

	vector<string>  postfix;
	vector<string> lexems;
	static map<string, int> priority;
	map<string, double> operands;
	void Parse();
	bool IsConst(const string& st) const;
	bool IsOperator(char c) const;
	bool IsParenthesis(char c) const;
	bool IsDigitOrLetter(char c) const;
	double Calculate(const map<string, double>& values);
	void RemoveSpaces(string& str) const;
public:
	TPolynom();
	TPolynom(const string& _name);
	TPolynom(const THeadRingList* m);
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
	string ToPostfix();
	void SetValues(const vector<double>& values);
	friend ostream& operator<<(ostream& os, const TPolynom& polynom);
};

#endif 