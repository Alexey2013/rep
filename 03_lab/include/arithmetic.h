#ifndef _ARITHMETIC_H
#define _ARITHMETIC_H
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include "stack.h"
using namespace std;

class TArithmeticExpression {
private:
	string infix;
	vector<string> postfix;
	vector<string> lexems;
	map<string, int> priority;
	map<string, double> operands;

	void Parse();
	void ToPostfix();
	bool IsConst(const string& st) const;
	double Calculate(const map<string, double>& values);

public:
	TArithmeticExpression(string infx);
	void SetValues();
	double Calculate();
};

#endif 