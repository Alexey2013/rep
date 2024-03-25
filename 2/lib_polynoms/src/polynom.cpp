#include "polynom.h"

TPolynom::TPolynom() : monoms() {
	name = "";
}

TPolynom::TPolynom(const string& _name) {
	monoms = new THeadRingList<TMonom>;
	monoms->InsertLast(TMonom(-1, 0));
	name = _name;
	ParseMonoms();
}

TPolynom::TPolynom(const THeadRingList<TMonom>* l) {
	monoms = new THeadRingList<TMonom>(*l);
	name = "";
}

TPolynom::TPolynom(const TPolynom& p) : monoms(p.monoms), name(p.name) {}

TPolynom::~TPolynom() {
	if (monoms != nullptr) {
		delete monoms;
	}
}

void TPolynom::ParseMonoms() {
	string str = name;
	while (!str.empty()) {
		int degree = 0;
		size_t j = str.find_first_of("+-", 1);
		string monom = str.substr(0, j);
		str.erase(0, j);
		string coefficient = monom.substr(0, monom.find_first_of("xyz"));
		TMonom tmp;
		tmp.coeff = ((coefficient.empty() || coefficient == "+") ? 1 : (coefficient == "-") ? -1 : stod(coefficient));
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
					throw ("Invalid monom format");
					break;
				}
			}
		}
		tmp.degree = degree;
		if (tmp.coeff != 0) {
			monoms->InsertToSort(tmp);
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

const TPolynom& TPolynom::operator=(const TPolynom& p) {
	if (this != &p) {
		name = p.name;
		delete monoms;
		monoms = new THeadRingList<TMonom>(*(p.monoms));
	}
	return *this;
}

TPolynom TPolynom::operator+(const TPolynom& p) {
	TPolynom result(*this);
	p.monoms->reset();
	while (!p.monoms->IsEnded()) {
		TMonom curr = p.monoms->GetCurrent()->data;
		result.monoms->InsertToSort(curr);
		p.monoms->next();
	}
	return result;
}

TPolynom TPolynom::operator-(const TPolynom& p) {
	TPolynom neg_p = p;
	neg_p.monoms->reset();
	while (neg_p.monoms->IsEnded()) {
		neg_p.monoms->GetCurrent()->data.coeff *= -1;
		neg_p.monoms->next();
	}
	return (*this + neg_p);
}

TPolynom TPolynom::operator*(const TPolynom& p) {
	TPolynom result(*this);
	monoms->reset();
	while (!monoms->IsEnded()) {
		p.monoms->reset();
		while (!p.monoms->IsEnded()) {
			TMonom m1 = monoms->GetCurrent()->data;
			TMonom m2 = p.monoms->GetCurrent()->data;
			TMonom m3 = m1 * m2;
			result.monoms->InsertToSort(m3);
			p.monoms->next();
		}
		monoms->next();
	}
	return result;
}

TPolynom TPolynom::dx() const {
	TPolynom result; 
	monoms->reset();
	while (!monoms->IsEnded()) {
		TMonom m = monoms->GetCurrent()->data; 
		if (m.degree >= 100) {
			int new_degree = m.degree - 100; 
			double new_coeff = m.coeff * (m.degree / 100); 
			m.degree = new_degree;
			m.coeff = new_coeff; 
			result.monoms->InsertToSort(m);
		}
		monoms->next();
	}

	return result;
}

TPolynom TPolynom::dy() const {
	TPolynom result;
	monoms->reset();
	while (!monoms->IsEnded()) {
		TMonom m = monoms->GetCurrent()->data;
		int deg = monoms->GetCurrent()->data.degree;
		int y = (deg % 100) / 10;
		if (y >= 1) {
			int new_degree = m.degree - 10;
			double new_coeff = m.coeff * (m.degree / 10);
			m.degree = new_degree;
			m.coeff = new_coeff;
			result.monoms->InsertToSort(m);
		}
		monoms->next();
	}
	return result;
}

TPolynom TPolynom::dz() const {
	TPolynom result;
	monoms->reset();
	while (!monoms->IsEnded()) {
		TMonom m = monoms->GetCurrent()->data;
		int deg = monoms->GetCurrent()->data.degree;
		int z = deg % 10;
		if (z >= 1) {
			int new_degree = m.degree - 1;
			double new_coeff = m.coeff * m.degree;
			m.degree = new_degree;
			m.coeff = new_coeff;
			result.monoms->InsertToSort(m);
		}
		monoms->next();
	}

	return result;
}

bool TPolynom::operator==(const TPolynom& p) const {
	monoms->reset();
	p.monoms->reset();
	while (!monoms->IsEnded() && !p.monoms->IsEnded()) {
		if (monoms->GetCurrent()->data != p.monoms->GetCurrent()->data) {
			return false;
		}
		monoms->next();
		p.monoms->next();
	}
	return (monoms->IsEnded() && p.monoms->IsEnded());
}

bool TPolynom::operator!=(const TPolynom& p) const {
	return !(*this == p);
}

 ostream& operator<<(ostream& out, const TPolynom& p){
        while (!p.monoms->IsEnded()) {
			int deg = p.monoms->GetCurrent()->data.degree;
            int coeff = p.monoms->GetCurrent()->data.coeff;
            int x = deg / 100;
            int y = (deg % 100) / 10;
            int z = deg % 10;
            if (deg == 0) {cout << p.monoms->GetCurrent()->data.coeff << endl;}
                if (coeff < 0) { cout << "(" << p.monoms->GetCurrent()->data.coeff << ")"; }
                if (coeff != 1 && coeff >0) {cout << p.monoms->GetCurrent()->data.coeff;}
                if (x == 1) {cout << "x";}
                if (y == 1) {cout << "y"; }
                if (z == 1) {  cout << "z"; }
                if (x != 0 && x != 1) { cout << "x^" << x;}
                if (y != 0 && y!= 1) {cout << "y^" << y;}
                if (z != 0&&z!=1) {   cout << "z^" << z;}
           if(p.monoms->GetCurrent()->pNext != nullptr)   cout <<"+";
            p.monoms->next();
            }
            return out;
        }
