#include "polynom.h"

TPolynom::TPolynom() {
	monoms = new THeadRingList<TMonom>();
	name = "";
}

TPolynom::TPolynom(const string& _name) {
	monoms = new THeadRingList<TMonom>();
	name = _name;
	conversion(name);
	ParseMonoms();
}

TPolynom::TPolynom(const THeadRingList<TMonom>* l) {
	monoms = new THeadRingList<TMonom>(*l);
	name = ToString();
}

TPolynom::TPolynom(const TPolynom& p) {
	name = p.name;
	monoms = new THeadRingList<TMonom>(*(p.monoms));
}

TPolynom::~TPolynom() {
	if (monoms != nullptr) {
		delete monoms;
	}
}

void TPolynom::conversion(string& str) const {
	str.erase(remove(str.begin(), str.end(), ' '), str.end());
	transform(str.begin(), str.end(), str.begin(), ::tolower);
}

void TPolynom::RemoveZero() {
	if (monoms == nullptr) return;
	bool flag = false;
	monoms->reset();
	while (!monoms->IsEnded()) {
		TNode<TMonom>* current = monoms->GetCurrent();
		if (current->data.coeff != 0) { 
			monoms->next();
			flag = true;
			continue; 
		}
		TNode<TMonom>* monomToRemove = current;
		monoms->next();
		monoms->remove(monomToRemove->data);
	}
	if (flag == false) {
		monoms->clear();
	}
}

string TPolynom::ToString() const {
	TPolynom p(*this);
	string str;
	char tmp[5];
	if (p.monoms->IsEmpty()) {
		return "0";
	}
	bool firstTerm = true;
	p.monoms->reset();
	while (!p.monoms->IsEnded()) {
		int deg = p.monoms->GetCurrent()->data.degree;
		double coeff = p.monoms->GetCurrent()->data.coeff;
		int x = deg / 100;
		int y = (deg % 100) / 10;
		int z = deg % 10;
		if (coeff != 0) {
			if (!firstTerm) {
				str += ((coeff > 0) ? "+" : "-");
			}
			else {
				if (coeff < 0) {
					str += "-";
				}
				firstTerm = false;
			}
			if (abs(coeff) != 1 || deg == 0) {
				sprintf(tmp, "%.2f", abs(coeff));
				str += string(tmp);
			}
			if (x != 0) str += "x" + ((x != 1) ? "^" + to_string(x) : "");
			if (y != 0) str += "y" + ((y != 1) ? "^" + to_string(y) : "");
			if (z != 0) str += "z" + ((z != 1) ? "^" + to_string(z) : "");
		}
		p.monoms->next();
	}
	p.name = str;
	return str;
}

void TPolynom::ParseMonoms() {
	string str = name;
	while (!str.empty()) {
		TMonom tmp;
		int degree = 0;
		size_t j = str.find_first_of("+-", 1);
		string monom = str.substr(0, j);
		str.erase(0, j);
		string coefficient = monom.substr(0, monom.find_first_of("xyz"));
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
		if ((tmp.coeff != 0)||(name == "0")) {
			monoms->insert_sort(tmp);
		}
	}
}

double TPolynom::operator()(double x,double y,double z) {
	TArithmeticExpression expression(name);
	vector<double> xyz ={x,y,z};
	expression.ToPostfix();
	expression.SetValues(xyz);
	return (expression.Calculate());
}

const TPolynom& TPolynom::operator=(const TPolynom& p)  {
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
		result.monoms->insert_sort(curr);
		p.monoms->next();
	}
	result.RemoveZero();
	result.ToString();
	return result;
}

TPolynom TPolynom::operator-(const TPolynom& p) {
	TPolynom result(*this);
	result = result+(-p);
	result.ToString();
	return result;
}

TPolynom TPolynom::operator-() const {
	TPolynom result(*this);
	result.monoms->reset();
	while (!result.monoms->IsEnded()) {
		result.monoms->GetCurrent()->data.coeff *= -1;
		result.monoms->next();
	}
	result.ToString();
	return result;
}

TPolynom TPolynom::operator*(const TPolynom& p) {
	TPolynom result;
	monoms->reset();
	while (!monoms->IsEnded()) {
		p.monoms->reset();
		while (!p.monoms->IsEnded()) {
			TMonom m1 = monoms->GetCurrent()->data;
			TMonom m2 = p.monoms->GetCurrent()->data;
			TMonom m3 = m1 * m2;
			if (m3.coeff != 0) {
				result.monoms->insert_sort(m3);
			}
			p.monoms->next();
		}
		monoms->next();
	}
	result.ToString();
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
			TMonom new_monom(new_coeff, new_degree);
			result.monoms->insert_sort(new_monom);
		}
		monoms->next();
	}
	result.ToString();
	return result;
}

TPolynom TPolynom::dy() const {
	TPolynom result;
	monoms->reset();
	while (!monoms->IsEnded()) {
		TMonom m = monoms->GetCurrent()->data;
		int deg = m.degree;
		int y = (deg % 100) / 10;
		if (y >= 1) {
			int new_degree = m.degree - 10;
			double new_coeff = m.coeff * y; 
			TMonom new_monom(new_coeff, new_degree);
			result.monoms->insert_sort(new_monom);
		}
		monoms->next();
	}
	result.ToString();
	return result;
}

TPolynom TPolynom::dz() const {
	TPolynom result;
	monoms->reset();
	while (!monoms->IsEnded()) {
		TMonom m = monoms->GetCurrent()->data;
		int deg = m.degree;
		int z = deg % 10;
		if (z >= 1) {
			int new_degree = m.degree - 1;
			double new_coeff = m.coeff * z;
			TMonom new_monom(new_coeff, new_degree);
			result.monoms->insert_sort(new_monom);
		}
		monoms->next();
	}
	result.ToString();
	return result;
}

bool TPolynom::operator==(const TPolynom& p) const {
	if (monoms->IsEmpty() && p.monoms->IsEmpty()) {
		return true;  
	}
	if (monoms->IsEmpty() || p.monoms->IsEmpty()) {
		return false;  
	}
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

ostream& operator<<(ostream& out, const TPolynom& p) {
	cout << p.ToString();
	return out;
}