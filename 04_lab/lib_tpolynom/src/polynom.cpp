#include "polynom.h"

TPolynom::TPolynom() {
	monoms = nullptr;
}

TPolynom::TPolynom(const string& _name) {
	name = _name;
	RemoveSpaces(name);
	ToPostfix();
	monoms = nullptr;
}

TPolynom::TPolynom(const THeadRingList* m) {
	monoms = new THeadRingList(*m);
	name = "";
}

TPolynom::TPolynom(const TPolynom& p) {
	name = p.name;
	monoms = new THeadRingList(*(p.monoms));
}

TPolynom::~TPolynom() {
	delete monoms;
}

TPolynom& TPolynom::operator =(const TPolynom& p) {
	if (this == &p) {
		return *this;
	}
	delete monoms;
	name = p.name;
	*monoms = *(p.monoms);
	return *this;
}

map<string, int> TPolynom::priority = {
	{"^", 4},
	{"*", 3},
	{"/", 3},
	{"+", 2},
	{"-", 2},
	{"(", 1},
	{")", 1}
};

void TPolynom::RemoveSpaces(string& str) const {
	str.erase(remove(str.begin(), str.end(), ' '), str.end());
}

bool TPolynom::IsConst(const string& s) const {
	for (char c : s) {
		if (!isdigit(c) && c != '.') {
			return false;
		}
	}
	return true;
}

bool TPolynom::IsOperator(char c) const {
	return (c == '+' || c == '-' || c == '*' || c == '/' || c == '^');
}

bool TPolynom::IsParenthesis(char c) const {
	return (c == '(' || c == ')');
}

bool TPolynom::IsDigitOrLetter(char c) const {
	return (isdigit(c) || c == '.' || isalpha(c));
}

//
//void TPolynom::ParseMonoms() {
//	string currentMonom;
//	for (char c : name) {
//		if (c=='+'|| c=='-') {
//			if (!currentMonom.empty()) {
//				monoms.pushback(currentMonom);
//				currentMonom = "";
//			}
//
//		}
//		else {
//			currentMonom += c;
//		}
//	}
//	if (!currentMonom.empty()) {
//		monoms.push_back(currentMonom);
//	}
//}


void TPolynom::ParseMult() {

}

void TPolynom::Parse()
{
	string currentElement;
	for (char c : name) {
		if (IsOperator(c) || IsParenthesis(c) || c == ' ') {
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

string TPolynom::ToPostfix() {
	Parse();
	TStack<string> st;
	string postfixExpression;
	for (string item : lexems) {
		if (item == "(") {
			st.Push(item);
		}
		else if (item == ")") {
			while (st.Top() != "(") {
				postfixExpression += st.Top();
				postfix.push_back(st.Top());
				st.Pop();
			}
			st.Pop();
		}
		else if (IsOperator(item[0])) {
			while (!st.IsEmpty() && priority[item] <= priority[st.Top()]) {
				postfixExpression += st.Top();
				postfix.push_back(st.Top());
				st.Pop();
			}
			st.Push(item);
		}
		else {
			double value = IsConst(item) ? stod(item) : 0.0;
			operands.insert({ item, value });
			postfix.push_back(item);
			postfixExpression += item;
		}
	}
	while (!st.IsEmpty()) {
		postfixExpression += st.Top();
		postfix.push_back(st.Top());
		st.Pop();
	}
	return postfixExpression;
}

double TPolynom::Calculate(const map<string, double>& values)
{
	for (auto& val : values) {
		try {
			operands.at(val.first) = val.second;
		}
		catch (out_of_range& e) {}
	}
	TStack<double> st;
	double leftOperand, rightOperand;
	for (string lexem : postfix) {
		if (lexem == "^") {
			rightOperand = st.Top(); st.Pop();
			leftOperand = st.Top(); st.Pop();
			st.Push(pow(leftOperand, rightOperand));
		}
		else if (lexem == "+") {
			rightOperand = st.Top(); st.Pop();
			leftOperand = st.Top(); st.Pop();
			st.Push(leftOperand + rightOperand);
		}
		else if (lexem == "-") {
			rightOperand = st.Top(); st.Pop();
			leftOperand = st.Top(); st.Pop();
			st.Push(leftOperand - rightOperand);
		}
		else if (lexem == "*") {
			rightOperand = st.Top(); st.Pop();
			leftOperand = st.Top(); st.Pop();
			st.Push(leftOperand * rightOperand);
		}
		else if (lexem == "/") {
			rightOperand = st.Top(); st.Pop();
			leftOperand = st.Top(); st.Pop();
			if (rightOperand == 0) { throw"Error"; }
			st.Push(leftOperand / rightOperand);
		}
		else {
			st.Push(operands[lexem]);
		}
	}
	return st.Top();
}

void TPolynom::SetValues(const vector<double>& values) {
	int i = 0;
	for (auto& op : operands)
	{
		if (!IsConst(op.first)) {
			operands[op.first] = values[i++];
		}
	}
}

double TPolynom::operator ()(double x, double y, double z) {
	vector<double> xyz = {x,y,z};
	SetValues(xyz);
	return Calculate(operands);
}

ostream& operator<<(ostream& os, const TPolynom& polynom) {
	os << polynom.name;
	return os;
}