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

TPolynom& TPolynom::operator =(const TPolynom& p) {
	if (this != &p) {
		name = p.name;
		delete monoms;
		monoms = new TList<TMonom>(*(p.monoms));
	}
	return *this;
}

TPolynom TPolynom::operator+(const TPolynom& p){
	TList<TMonom>* list = new TList<TMonom>();
	monoms->reset();
	p.monoms->reset();
	while (monoms->GetCurrent() != nullptr){
		list->insert_last(monoms->GetCurrent()->data);
		monoms->next();
	}
	while (p.monoms->GetCurrent() != nullptr){
		monoms->reset();
		int tmp = 1;
		TMonom m2 = p.monoms->GetCurrent()->data;
		while (monoms->GetCurrent() != nullptr){
			TMonom m1 = monoms->GetCurrent()->data;
			if (m1.Get_degree() == m2.Get_degree()) {
				double coefficient = m1.Get_coeff() + m2.Get_coeff();
				if (coefficient == 0) {
					tmp = 3;
				}
				else{
					m2.Set_coeff(coefficient);
					tmp = 2;
				}
				break;
			}
			monoms->next();
		}
		switch (tmp){
		case 1:{list->insert_last(p.monoms->GetCurrent()->data);break;}
		case 2:{
			TMonom search = list->search(monoms->GetCurrent()->data)->data;
			list->insert_after(m2, search);
			list->remove(monoms->GetCurrent()->data);
			break;
		}
		case 3: {list->remove(monoms->GetCurrent()->data);break;}
		}
		p.monoms->next();
	}
	TList<TMonom>* res = new TList<TMonom>(*list);
	TPolynom result;
	result.monoms = res;
	return result;
}

TPolynom TPolynom::operator-(const TPolynom& p)
{
	TList<TMonom>* list = new TList<TMonom>();
	monoms->reset();
	p.monoms->reset();
	while (monoms->GetCurrent() != nullptr){
		list->insert_last(monoms->GetCurrent()->data);
		monoms->next();
	}
	while (p.monoms->GetCurrent() != nullptr)
	{
		monoms->reset();
		int tmp = 1;
		TMonom m2 = p.monoms->GetCurrent()->data;
		while (monoms->GetCurrent() != nullptr)
		{
			TMonom m1 = monoms->GetCurrent()->data;
			if (m1.Get_degree() == m2.Get_degree()) {
				double coefficient = m1.Get_coeff()-m2.Get_coeff();
				if (coefficient == 0)
					tmp = 3;
				else
				{
					m2.Set_coeff(coefficient);
					tmp = 2;
				}
				break;
			}
			monoms->next();
		}
		switch (tmp) {
		case 1: { list->insert_last(p.monoms->GetCurrent()->data); break; }
		case 2: {
			TMonom search = list->search(monoms->GetCurrent()->data)->data;
			list->insert_after(m2, search);
			list->remove(monoms->GetCurrent()->data);
			break;
		}
		case 3: { list->remove(monoms->GetCurrent()->data); break; }
		}
		p.monoms->next();
	}
	TList<TMonom>* res = new TList<TMonom>(*list);
	TPolynom result;
	result.monoms = res;
	return result;
}

TPolynom TPolynom::operator*(const TPolynom& p)
{
	TList<TMonom>* list = new TList<TMonom>();
	monoms->reset();
	p.monoms->reset();
	while (monoms->GetCurrent() != nullptr){
		p.monoms->reset();
		while (p.monoms->GetCurrent() != nullptr)
		{
			TMonom m1 = monoms->GetCurrent()->data;
			TMonom m2 = p.monoms->GetCurrent()->data;
			TMonom m3 = m1 * m2;
			list->insert_last(m3);
			p.monoms->next();
		}
		monoms->next();
	}
	TList<TMonom>* res = new TList<TMonom>(*list);
	TPolynom result;
	result.monoms = res;
	return result;
}

TPolynom TPolynom::dx() const {
	TList<TMonom>* list = new TList<TMonom>();
	monoms->reset();
	while (monoms->GetCurrent() != nullptr) {
		TMonom m = monoms->GetCurrent()->data;
		if (m.Get_degree() < 100) { monoms->next(); continue; }
		int new_degree = m.Get_degree() - 100;
		double new_coeff = m.Get_coeff() * (m.Get_degree() / 100);
		m.Set_degree(new_degree);
		m.Set_coeff(new_coeff);
		list->insert_last(m);
		monoms->next();
	}
	TList<TMonom>* res = new TList<TMonom>(*list);
	TPolynom result;
	result.monoms = res;
	return result;
}

TPolynom TPolynom::dy() const {
	TList<TMonom>* list = new TList<TMonom>();
	monoms->reset();
	while (monoms->GetCurrent() != nullptr) {
		TMonom m = monoms->GetCurrent()->data;
		int deg = monoms->GetCurrent()->data.Get_degree();
		int y = (deg % 100) / 10;
		if (y < 1) { monoms->next(); continue; }
		int new_degree = m.Get_degree() - 10;
		double new_coeff = m.Get_coeff() * (m.Get_degree() / 10);
		m.Set_degree(new_degree);
		m.Set_coeff(new_coeff);
		list->insert_last(m);
		monoms->next();
	}
	TList<TMonom>* res = new TList<TMonom>(*list);
	TPolynom result;
	result.monoms = res;
	return result;
}

TPolynom TPolynom::dz() const {
	TList<TMonom>* list = new TList<TMonom>();
	monoms->reset();
	while (monoms->GetCurrent() != nullptr) {
		TMonom m = monoms->GetCurrent()->data;
		int deg = monoms->GetCurrent()->data.Get_degree();
		int z = deg % 10;
		if (z < 1) { monoms->next(); continue; }
		int new_degree = m.Get_degree() - 1;
		double new_coeff = m.Get_coeff() * (m.Get_degree());
		m.Set_degree(new_degree);
		m.Set_coeff(new_coeff);
		list->insert_last(m);
		monoms->next();
	}
	TList<TMonom>* res = new TList<TMonom>(*list);
	TPolynom result;
	result.monoms = res;
	return result;
}

bool TPolynom::operator==(const TPolynom& p) const {
	if (monoms->GetSize() != p.monoms->GetSize()) {
		return false;
	}
	monoms->reset();
	p.monoms->reset();
	while (monoms->GetCurrent() != nullptr && p.monoms->GetCurrent() != nullptr) {
		if (monoms->GetCurrent()->data != p.monoms->GetCurrent()->data) {
			return false;
		}
		monoms->next();
		p.monoms->next();
	}
	return true;
}

bool TPolynom::operator!=(const TPolynom& p) const {
	return !(*this == p);
}
