#include "stack.h"
#include "arithmetic.h"

TArithmeticExpression::TArithmeticExpression(const string& _infix)  { 
    string noSpacesInfix = infix; 
    RemoveSpaces(noSpacesInfix); 
    infix = noSpacesInfix; 
}

map<string, int> TArithmeticExpression::priority = {
	{"*", 3},
	{"/", 3},
	{"+", 2},
	{"-", 2},
	{"(", 1},
	{")", 1}
};

void TArithmeticExpression::RemoveSpaces(string& str) const {
    str.erase(remove(str.begin(), str.end(), ' '), str.end());
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
    RemoveSpaces(infix);
    string currentElement;
    for (int i = 0; i < infix.size(); i++) {
        char c = infix[i];
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

string TArithmeticExpression::ToPostfix() {
    Parse();
    TStack<string> st;
    for (string item : lexems) {
        if (item == "(") {
            st.Push(item);
        }
        else if (item == ")") {
            while (st.Top() != "(") {
                postfix += st.Top();
                postfixExpression.push_back(st.Top());
                st.Pop();
            }
            st.Pop();
        }
        else if (IsOperator(item[0])) {
            while (!st.IsEmpty() && priority[item] <= priority[st.Top()]) {
                postfix += st.Top();
                postfixExpression.push_back(st.Top());
                st.Pop();
            }
            st.Push(item);
        }
        else {
            double value = IsConst(item) ? stod(item) : 0.0;
            operands.insert({ item, value });
            postfixExpression.push_back(item);
            postfix += item;
        }
    }
    while (!st.IsEmpty()) {
        postfix += st.Top();
        postfixExpression.push_back(st.Top());
        st.Pop();
    }
    return postfix;
}

double TArithmeticExpression::Calculate(const map<string, double>& values) {
    TStack<double> st;
    for (const string& lexem : postfixExpression) {
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
            if (rightOperand == 0) { throw "Expression error: Division by zero"; }
            st.Push(leftOperand / rightOperand);
        }
        else {
            auto it = values.find(lexem);
            if (it != values.end()) {
                st.Push(it->second);
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
	int countParenthesis =0;
	for (char c : infix) {
		if (IsParenthesis(c)) {
			countParenthesis++;
		}
	}
	return (countParenthesis %2 == 0);
}