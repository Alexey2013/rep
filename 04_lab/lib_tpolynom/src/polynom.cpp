#include "polynom.h"

TPolynom::TPolynom() {
	monoms = nullptr;
	name = "";
}

TPolynom::TPolynom(const string& _name) {
	name = _name;
	RemoveSpaces(name);
	ToPostfix();
	monoms = new TList<TMonom>;
	ParseMonoms();
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

void TPolynom::ParseMonoms() {
	string str = name;
	while (!str.empty()) {
		int degree = 0;
		TMonom tmp;
		size_t j = str.find_first_of("+-", 1);
		string monom = str.substr(0, j);
		str.erase(0, j);
		size_t coeff_end = monom.find_first_of("xyz");
		string coeff_str = monom.substr(0, coeff_end);
		tmp.Set_coeff((coeff_str == "" || coeff_str == "+") ? 1 : (coeff_str == "-") ? -1 : std::stod(coeff_str));
		monom.erase(0, coeff_end);
		for (size_t i = 0; i < monom.size(); ++i) {
			if (isalpha(monom[i])) {
				int exp = 1;
				if (monom[i + 1] == '^') {
					size_t exp_start = i + 2;
					while (isdigit(monom[exp_start])) {
						exp_start++;
					}
					exp = stoi(monom.substr(i + 2, exp_start - i - 2));
					i = exp_start - 1;
				}
				switch (monom[i]) {
				case 'x':
					degree += exp * 100;
					break;
				case 'y':
					degree += exp * 10;
					break;
				case 'z':
					degree += exp * 1;
					break;
				default:
					throw "Input error: end of string";
					break;
				}
			}
		}
		tmp.Set_degree(degree);
		if (tmp.Get_degree() != 0 && tmp.Get_coeff() != 0) {
			monoms->insert_last(tmp);
		}
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

TPolynom TPolynom::dx() const {
	TPolynom result;
	for (auto it = monoms->GetCurrent(); it != nullptr; it = it->pNext) {
		TMonom monom = it->data;
		if (monom.Get_degree() == 0) continue;
		int new_degree = monom.Get_degree() - 100;
		double new_coeff = monom.Get_coeff() * (monom.Get_degree() / 100);
		if (new_degree != 0 && monom.Get_coeff() != 0) {
			TMonom new_monom(new_coeff, new_degree);
			result.monoms->insert_last(new_monom);
		}
	}
	return result;
}

TPolynom TPolynom::dy() const {
	TPolynom result;
	for (auto it = monoms->GetCurrent(); it != nullptr; it = it->pNext) {
		TMonom monom = it->data;
		if (monom.Get_degree() == 0) continue;
		int new_degree = monom.Get_degree() - 10;
		double new_coeff = monom.Get_coeff() * (monom.Get_degree() / 10);
		if (new_degree != 0 && monom.Get_coeff() != 0) {
			TMonom new_monom(new_coeff, new_degree);
			result.monoms->insert_last(new_monom);
		}
	}
	return result;
}

TPolynom TPolynom::dz() const {
	TPolynom result;
	for (auto it = monoms->GetCurrent(); it != nullptr; it = it->pNext) {
		TMonom monom = it->data;
		if (monom.Get_degree() == 0) continue;
		int new_degree = monom.Get_degree() - 1;
		double new_coeff = monom.Get_coeff() * (monom.Get_degree());
		if (new_degree != 0 && monom.Get_coeff() != 0) {
			TMonom new_monom(new_coeff, new_degree);
			result.monoms->insert_last(new_monom);
		}
	}
	return result;
}

void TPolynom::print()
{
	cout << "Monoms:" << endl;
	while (monoms->GetCurrent() != nullptr)
	{
		int deg=monoms->GetCurrent()->data.Get_degree();
		int x = deg/100;
		int y = (deg % 100)/10;
		int z = deg%10;
		cout << monoms->GetCurrent()->data.Get_coeff() << " "<< "x^" << x <<" "<< "y^" << y <<" "<< "z^" << z << endl;
		monoms->next();
	}
}

TPolynom TPolynom::operator *(const TPolynom& p) {
	TPolynom result;
	for (auto it = monoms->GetCurrent(); it != nullptr; it = it->pNext) {
	}

	return result;
}
