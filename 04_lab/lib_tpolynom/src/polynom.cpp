#include "polynom.h"

TPolynom::TPolynom() {
	monoms = new TList<TMonom>;
}

TPolynom::TPolynom(const string& _name) {
	name = _name;
	RemoveSpaces(name);
	ToPostfix();
	monoms = new TList<TMonom>;
}

TPolynom::TPolynom(const TList<TMonom>* m) {
	monoms = new TList<TMonom>(*m);
	name = "";
}

TPolynom::TPolynom(const TPolynom& p) {
	name = p.name;
	monoms = new TList<TMonom>(*(p.monoms));
}

TPolynom::~TPolynom() {
	delete monoms;
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

TPolynom::TPolynom(const string& polinomStr)
{
	istringstream iss(polinomStr);
	string token;
	while (getline(iss, token, '+'))
	{
		if (token.empty()) continue;

		double coefficient = 1.0;
		int xDegree = 0;
		int yDegree = 0;
		int zDegree = 0;
		size_t pos = 0;
		if (token[pos] == '-' || token[pos] == '+')
		{
			++pos;
		}
		coefficient = stod(token.substr(pos));
		while (pos < token.length())
		{
			if (token[pos] == 'x')
			{
				xDegree = (pos + 1 < token.length() && token[pos + 1] == '^') ? stoi(token.substr(pos + 2)) : 1;
			}
			else if (token[pos] == 'y')
			{
				yDegree = (pos + 1 < token.length() && token[pos + 1] == '^') ? stoi(token.substr(pos + 2)) : 1;
			}
			else if (token[pos] == 'z')
			{
				zDegree = (pos + 1 < token.length() && token[pos + 1] == '^') ? stoi(token.substr(pos + 2)) : 1;
			}
			++pos;
		}

		unsigned int combinedDegree = xDegree * 100 + yDegree * 10 + zDegree;
		addMonom(monom(coefficient, combinedDegree));
	}

	simplify();
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
	SetValues({ x,y,z });
	return Calculate(operands);
}

TPolynom& TPolynom::operator =(const TPolynom& p) {
	if (this != &p) {
		name = p.name;
		delete monoms;
		monoms = new TList<TMonom>(*(p.monoms));
	}
	return *this;
}
