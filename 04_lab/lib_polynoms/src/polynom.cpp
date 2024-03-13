#include "polynom.h"

TPolynom::TPolynom() {
	monoms = nullptr;
	name = "";
}

TPolynom::TPolynom(const string& _name) {
	name = _name;
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
					throw ("exp");
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

double TPolynom::operator ()(double x,double y,double z) {
	TArithmeticExpression expression(name);
	vector<double> xyz ={x,y,z};
	expression.ToPostfix();
	expression.SetValues(xyz);
	return (expression.Calculate());
}

TPolynom TPolynom::dx() const {
	TPolynom result;
	for (auto it = monoms->GetCurrent(); it != nullptr; it = it->pNext) {
		TMonom monom = it->data;
		if (monom.Get_degree()<100) continue;
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
		if (monom.Get_degree() <10) continue;
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
		if (monom.Get_degree()<100) continue;
		int new_degree = monom.Get_degree() - 1;
		double new_coeff = monom.Get_coeff() * (monom.Get_degree());
		if (monom.Get_coeff() != 0) {
			TMonom new_monom(new_coeff, new_degree);
			result.monoms->insert_last(new_monom);
		}
	}
	return result;
}

void TPolynom::print()
{
	cout << endl;
	while (monoms->GetCurrent() != nullptr)
	{
		int deg=monoms->GetCurrent()->data.Get_degree();
		int x = deg/100;
		int y = (deg % 100)/10;
		int z = deg%10;
		cout << monoms->GetCurrent()->data.Get_coeff() << "*"<< "x^" << x << "*" << "y^" << y << "*" << "z^" << z << endl;
		monoms->next();
	}
}

TPolynom& TPolynom::operator =(const TPolynom& p) {
	if (this != &p) {
		name = p.name;
		delete monoms;
		monoms = new TList<TMonom>(*(p.monoms));
	}
	return *this;
}
