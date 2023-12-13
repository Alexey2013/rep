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
	vector<string> postfix; // !!! string
	vector<string> lexems;
	map<string, int> priority; // static
	map<string, double> operands;

	void Parse();
	bool IsConst(const string& st) const;
	bool IsOperator(char c) const;
	bool IsParenthesis(char c) const;
	bool IsDigitOrLetter(char c) const;
	double Calculate(const map<string, double>& values);

	bool isCorrectInfixExpression();
public:
	TArithmeticExpression(const string& infx);
	string ToPostfix();
	void SetValues();
	double Calculate();	
};

#endif 