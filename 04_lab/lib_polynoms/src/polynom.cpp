#include "polynom.h"

TPolynom::TPolynom() {
	monoms = nullptr;
	name = "";
}

TPolynom::TPolynom(const string _name) {
	name = _name;
	monoms = new TList<TMonom>;
	ParseMonoms();
	conversion();
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
		size_t j = str.find_first_of("+-", 1);
		string monom = str.substr(0, j);
		str.erase(0, j);
		string coefficent = monom.substr(0, monom.find_first_of("xyz"));
		TMonom tmp;
		tmp.Set_coeff((coefficent == "" || coefficent == "+") ? 1 : (coefficent == "-") ? -1 : stod(coefficent));
		monom.erase(0, monom.find_first_of("xyz"));
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
		if (tmp.Get_coeff() != 0) {
			monoms->insert_last(tmp);
		}
	}
}

void TPolynom::conversion() {
	TList<TMonom>* list = new TList<TMonom>();
	monoms->reset();
	while (monoms->GetCurrent() != nullptr) {
		TMonom m = monoms->GetCurrent()->data;
		bool has_same_degree = false;
		for (auto it = list->GetCurrent(); it != nullptr; it = it->pNext) {
			if (it->data.Get_degree() == m.Get_degree()) {
				it->data.Set_coeff(it->data.Get_coeff() + m.Get_coeff());
				has_same_degree = true;
				break;
			}
		}
		if (!has_same_degree) {
			list->insert_last(m);
		}
		monoms->next();
	}
	TList<TMonom>* res = new TList<TMonom>(*list);
	monoms = res;
}

double TPolynom::operator ()(double x,double y,double z) {
	TArithmeticExpression expression(name);
	vector<double> xyz ={x,y,z};
	expression.ToPostfix();
	expression.SetValues(xyz);
	return (expression.Calculate());
}

TPolynom& TPolynom::operator=(const TPolynom& p) {
	if (this != &p) {
		name = p.name;
		delete monoms;
		monoms = new TList<TMonom>(*(p.monoms));
	}
	return *this;
}

TPolynom TPolynom::operator+(const TPolynom& p) {
	TList<TMonom>* list = new TList<TMonom>();
	monoms->reset();
	p.monoms->reset();
	while (monoms->GetCurrent() != nullptr) {
		list->insert_last(monoms->GetCurrent()->data);
		monoms->next();
	}
	while (p.monoms->GetCurrent() != nullptr) {
		monoms->reset();
		TMonom m2 = p.monoms->GetCurrent()->data;
		bool found = false;
		while (monoms->GetCurrent() != nullptr) {
			TMonom m1 = monoms->GetCurrent()->data;
			if (m1.Get_degree() == m2.Get_degree()) {
				double coefficient = m1.Get_coeff() + m2.Get_coeff();
				if (coefficient == 0) {
					list->remove(monoms->GetCurrent()->data);
				}
				else {
					m2.Set_coeff(coefficient);
					list->insert_after(m2, monoms->GetCurrent()->data);
					list->remove(monoms->GetCurrent()->data);
				}
				found = true;
				break;
			}
			monoms->next();
		}
		if (!found) {
			list->insert_last(p.monoms->GetCurrent()->data);
		}
		p.monoms->next();
	}
	TList<TMonom>* res = new TList<TMonom>(*list);
	TPolynom result;
	result.monoms = res;
	return result;
}

TPolynom TPolynom::operator-(const TPolynom& p) {
	TList<TMonom>* list = new TList<TMonom>();
	monoms->reset();
	p.monoms->reset();
	while (monoms->GetCurrent() != nullptr) {
		list->insert_last(monoms->GetCurrent()->data);
		monoms->next();
	}
	while (p.monoms->GetCurrent() != nullptr) {
		monoms->reset();
		TMonom m2 = p.monoms->GetCurrent()->data;
		bool found = false;
		while (monoms->GetCurrent() != nullptr) {
			TMonom m1 = monoms->GetCurrent()->data;
			if (m1.Get_degree() == m2.Get_degree()) {
				double coefficient = m1.Get_coeff() - m2.Get_coeff();
				if (coefficient == 0) {
					list->remove(monoms->GetCurrent()->data);
				}
				else {
					m2.Set_coeff(coefficient);
					TMonom search = list->search(monoms->GetCurrent()->data)->data;
					list->insert_after(m2, search);
					list->remove(monoms->GetCurrent()->data);
				}
				found = true;
				break;
			}
			monoms->next();
		}
		if (!found) {
			p.monoms->GetCurrent()->data.Set_coeff(-p.monoms->GetCurrent()->data.Get_coeff());
			list->insert_last(p.monoms->GetCurrent()->data);
		}
		p.monoms->next();
	}
	TList<TMonom>* res = new TList<TMonom>(*list);
	TPolynom result;
	result.monoms = res;
	return result;
}


TPolynom TPolynom::operator*(const TPolynom& p){
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
		if (m.Get_degree() < 100) {
			monoms->next();
			continue;
		}
		int new_degree = m.Get_degree() - 100;
		double new_coeff = m.Get_coeff() * (m.Get_degree() / 100);
		TMonom new_m = m;
		new_m.Set_degree(new_degree);
		new_m.Set_coeff(new_coeff);
		list->insert_last(new_m);
		monoms->next();
	}
	if (list->GetSize() == 0) {
		delete list;
		throw("there are no monomials to derive from");
	}
	TList<TMonom>* res = new TList<TMonom>(*list);
	delete list;
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
	if (list->GetSize() == 0) {
		delete list;
		throw("there are no monomials to derive from");
	}
	TList<TMonom>* res = new TList<TMonom>(*list);
	TPolynom result;
	delete list;
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
	if (list->GetSize() == 0) {
		delete list;
		throw("there are no monomials to derive from");
	}
	TList<TMonom>* res = new TList<TMonom>(*list);
	TPolynom result;
	delete list;
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

 ostream& operator<<(ostream& out, const TPolynom& p){
        while (p.monoms->GetCurrent() != nullptr) {
			int deg = p.monoms->GetCurrent()->data.Get_degree();
            int coeff = p.monoms->GetCurrent()->data.Get_coeff();
            int x = deg / 100;
            int y = (deg % 100) / 10;
            int z = deg % 10;
            if (deg == 0) {cout << p.monoms->GetCurrent()->data.Get_coeff() << endl;}
            else {
                if (coeff < 0) { cout << "(" << p.monoms->GetCurrent()->data.Get_coeff() << ")"; }
                if (coeff != 1 && coeff >0) {cout << p.monoms->GetCurrent()->data.Get_coeff();}
                if (x == 1) {cout << "x";}
                if (y == 1) {cout << "y"; }
                if (z == 1) {  cout << "z"; }
                if (x != 0 && x != 1) { cout << "x^" << x;}
                if (y != 0 && y!= 1) {cout << "y^" << y;}
                if (z != 0&&z!=1) {   cout << "z^" << z;}
                if(p.monoms->GetCurrent()->pNext != nullptr)
                cout <<"+";
            }
            p.monoms->next();
            }
            return out;
        }