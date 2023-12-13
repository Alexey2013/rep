#include "stack.h"
#include "arithmetic.h"

TArithmeticExpression::TArithmeticExpression(const string& infx) :infix(infx) {
	priority = { {"(",1},{")",1},{"+",2},{"-",2}, {"*",3},{"/",3} };
	//ToPostfix(); 
}

bool TArithmeticExpression::IsConst(const string& s) const {
	for (char c:s) {
		if (!isdigit(c) && c != '.') {
			return false;
		}
	}
	return true;
}

bool TArithmeticExpression::IsOperator(char c) const {
	return (c == '+' || c == '-' || c == '*' || c == '/');
}

bool TArithmeticExpression::IsParenthesis(char c) const {
	return (c == '(' || c == ')');
}

bool TArithmeticExpression::IsDigitOrLetter(char c) const{
	return (isdigit(c) || c == '.' || isalpha(c));
}

void TArithmeticExpression::SetValues(){
	double value;
	for (auto& op : operands){
		if (!IsConst(op.first)){
			cout << "Enter value of " << op.first << ":";
			cin >> value;
			operands[op.first] = value;
		}
	}
}

void TArithmeticExpression::Parse()
{
	string currentElement;
	for (int i = 0; i < infix.size(); i++) {
		char c = infix[i];
		if (IsOperator(c) || IsParenthesis(c) || c==' ') {
			if (!currentElement.empty()) {
				lexems.push_back(currentElement);
				currentElement = "";
			}
			lexems.push_back(string(1, c));
		}
		else if (IsDigitOrLetter(c)) {
			currentElement += c;
		}
	}
	if (!currentElement.empty()) {
		lexems.push_back(currentElement);
	}
}

string TArithmeticExpression::ToPostfix() {
	Parse();
	TStack<string> st;
	string stackItem;
		for (string item : lexems) {
			if (item == "(") {
				st.Push(item);
			}
			else if (item == ")") {
				while (st.Top() != "(") {
					postfix.push_back(st.Top());
					st.Pop();
				}
				st.Pop();
			}
			else if (item == "+" || item == "-" || item == "*" || item == "/") {
				while (!st.IsEmpty() && priority[item] <= priority[st.Top()]) {
					postfix.push_back(st.Top());
					st.Pop();
				}
				st.Push(item);
			}
			else {
				double value = IsConst(item) ? stod(item) : 0.0;
				operands.insert({ item, value });
				postfix.push_back(item);
			}
		}
	while (!st.IsEmpty()) {
		postfix.push_back(st.Top());
		st.Pop();
	}
}

double TArithmeticExpression::Calculate(const map<string, double>& values) {
	TStack<double> st;
	for (string lexem : postfix) {
		if (lexem == "+") {
			double rightOperand = st.Top(); st.Pop();
			double leftOperand = st.Top(); st.Pop();
			st.Push(leftOperand + rightOperand);
		}
		else if (lexem == "-") {
			double rightOperand = st.Top(); st.Pop();
			double leftOperand = st.Top(); st.Pop();
			st.Push(leftOperand - rightOperand);
		}
		else if (lexem == "*") {
			double rightOperand = st.Top(); st.Pop();
			double leftOperand = st.Top(); st.Pop();
			st.Push(leftOperand * rightOperand);
		}
		else if (lexem == "/") {
			double rightOperand = st.Top(); st.Pop();
			double leftOperand = st.Top(); st.Pop();
			if (rightOperand == 0) {throw "exp";}
			st.Push(leftOperand / rightOperand);
		}
		else {
			auto _lexem = values.find(lexem);
			if (_lexem != values.end()) {
				st.Push(_lexem->second);
			}
		}
	}
	return st.Top();
}

double TArithmeticExpression::Calculate() {
	return Calculate(operands);
}

bool TArithmeticExpression::isCorrectInfixExpression()
{
	int openParentheses = 0;
	int closeParentheses = 0;

	for (char c : infix) {
		if (c == '(') {
		openParentheses++;
		}
		else if (c == ')') {
		closeParentheses++;
		}
	}
	return openParentheses == closeParentheses;
}