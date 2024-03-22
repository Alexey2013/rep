#include "polynom.h"

TPolynom::TPolynom() : monoms(nullptr), name("") {}

TPolynom::TPolynom(const string& _name) :  name(_name) {
	monoms = new THeadRingList<TMonom>;
	ParseMonoms();
}

TPolynom::TPolynom(const THeadRingList<TMonom>* m) :  name("") {
	if (m != nullptr) {monoms = new THeadRingList<TMonom>(*m);}
	else {throw ("Input THeadRingList pointer is null");}
}

TPolynom::TPolynom(const TPolynom& p) : monoms(nullptr), name(p.name) {
	monoms = new THeadRingList<TMonom>(*(p.monoms));
}

TPolynom::~TPolynom() {
	delete monoms;
}

void TPolynom::ParseMonoms() {
	THeadRingList<TMonom>* list = new THeadRingList<TMonom>();
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
		tmp.degree=degree;
		if (tmp.degree != 0) {
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

//TPolynom TPolynom::operator+(const TPolynom& p) {
//	TPolynom result;
//	THeadRingList<TMonom>* list = new THeadRingList<TMonom>(*monoms);
//	p.monoms->reset();
//	while (p.monoms->GetCurrent() != p.monoms->GetpLast()) {
//		TMonom m2 = p.monoms->GetCurrent()->data;
//		bool found = false;
//		list->reset();
//		while (list->GetCurrent() != list->GetpLast()) {
//			TMonom m1 = list->GetCurrent()->data;
//			if (m1.degree == m2.degree) {
//				double coefficient = m1.coeff + m2.coeff;
//				if (coefficient == 0) {
//					list->remove(list->GetCurrent()->data);
//				}
//				else {
//					m2.coeff = coefficient;
//					list->insert_after(m2, list->GetCurrent()->data);
//					list->remove(list->GetCurrent()->data);
//				}
//				found = true;
//				break;
//			}
//			list->next();
//		}
//		if (!found) {
//			list->insert_last(m2);
//		}
//		p.monoms->next();
//	}
//	THeadRingList<TMonom>* res = new THeadRingList<TMonom>(*list);
//	result.monoms = res;
//	return result;
//}
//
//TPolynom TPolynom::operator-(const TPolynom& p) {
//	TPolynom neg_p = p;
//	neg_p.monoms->reset();
//	while (monoms->GetCurrent() != monoms->GetpLast()) {
//		neg_p.monoms->GetCurrent()->data.coeff *= -1;
//		neg_p.monoms->next();
//	}
//	return *this + neg_p;
//}
//
//TPolynom TPolynom::operator*(const TPolynom& p){
//	THeadRingList<TMonom>* list = new THeadRingList<TMonom>();
//	monoms->reset();
//	p.monoms->reset();
//	while (monoms->GetCurrent() != monoms->GetpLast()) {
//		p.monoms->reset();
//		while (p.monoms->GetCurrent() != p.monoms->GetpLast())
//		{
//			TMonom m1 = monoms->GetCurrent()->data;
//			TMonom m2 = p.monoms->GetCurrent()->data;
//			TMonom m3 = m1 * m2;
//			list->insert_last(m3);
//			p.monoms->next();
//		}
//		monoms->next();
//	}
//	THeadRingList<TMonom>* res = new THeadRingList<TMonom>(*list);
//	TPolynom result;
//	result.monoms = res;
//	return result;
//}
//
//TPolynom TPolynom::dx() const {
//	TPolynom result;
//	THeadRingList<TMonom>* list = new THeadRingList<TMonom>();
//	monoms->reset();
//	while (monoms->GetCurrent() != monoms->GetpLast()) {
//		TMonom m = monoms->GetCurrent()->data;
//		if (m.degree < 100) {
//			monoms->next();
//			continue;
//		}
//		int new_degree = m.degree - 100;
//		double new_coeff = m.coeff * (m.degree / 100);
//		TMonom new_m = m;
//		new_m.degree = new_degree;
//		new_m.coeff = new_coeff;
//		list->insert_last(new_m);
//		monoms->next();
//	}
//	if (list->GetSize() == 0) {
//		delete list;
//		return result;
//	}
//	THeadRingList<TMonom>* res = new THeadRingList<TMonom>(*list);
//	delete list;
//	result.monoms = res;
//	return result;
//}
//
//TPolynom TPolynom::dy() const {
//	TPolynom result;
//	THeadRingList<TMonom>* list = new THeadRingList<TMonom>();
//	monoms->reset();
//	while (monoms->GetCurrent() != monoms->GetpLast()) {
//		TMonom m = monoms->GetCurrent()->data;
//		int deg = monoms->GetCurrent()->data.degree;
//		int y = (deg % 100) / 10;
//		if (y < 1) { monoms->next(); continue; }
//		int new_degree = m.degree - 10;
//		double new_coeff = m.coeff * (m.degree / 10);
//		m.degree=new_degree;
//		m.coeff=new_coeff;
//		list->insert_last(m);
//		monoms->next();
//	}
//	if (list->GetSize() == 0) {
//		delete list;
//		return result;
//	}
//	THeadRingList<TMonom>* res = new THeadRingList<TMonom>(*list);
//	delete list;
//	result.monoms = res;
//	return result;
//}
//
//TPolynom TPolynom::dz() const {
//	TPolynom result;
//	THeadRingList<TMonom>* list = new THeadRingList<TMonom>();
//	monoms->reset();
//	while (monoms->GetCurrent() != monoms->GetpLast()) {
//		TMonom m = monoms->GetCurrent()->data;
//		int deg = monoms->GetCurrent()->data.degree;
//		int z = deg % 10;
//		if (z < 1) { monoms->next(); continue; }
//		int new_degree = m.degree - 1;
//		double new_coeff = m.coeff * m.degree;
//		m.degree=new_degree;
//		m.coeff=new_coeff;
//		list->insert_last(m);
//		monoms->next();
//	}
//	if (list->GetSize() == 0) {
//		delete list;
//		return result;
//	}
//	THeadRingList<TMonom>* res = new THeadRingList<TMonom>(*list);
//	delete list;
//	result.monoms = res;
//	return result;
//}
//
//bool TPolynom::operator==(const TPolynom& p) const {
//	if (monoms->GetSize() != p.monoms->GetSize()) {
//		return false;
//	}
//	monoms->reset();
//	p.monoms->reset();
//	while (monoms->GetCurrent() != nullptr && p.monoms->GetCurrent() != nullptr) {
//		if (monoms->GetCurrent()->data != p.monoms->GetCurrent()->data) {
//			return false;
//		}
//		monoms->next();
//		p.monoms->next();
//	}
//	return true;
//}
//
//bool TPolynom::operator!=(const TPolynom& p) const {
//	return !(*this == p);
//}

 ostream& operator<<(ostream& out, const TPolynom& p){
        while (p.monoms->GetCurrent() != p.monoms->GetpLast()) {
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

 //void TPolynom::sort_monoms() {
	// THeadRingList<TMonom>* sortedMonoms = new THeadRingList<TMonom>();
	// monoms->reset(); 
	// while (monoms->GetCurrent() != nullptr) {
	//	 TMonom m = monoms->GetCurrent()->data;
	//	 if (m.coeff != 0) {
	//		 sortedMonoms->reset();
	//		 while (sortedMonoms->GetCurrent() != nullptr && sortedMonoms->GetCurrent()->data.degree > m.degree) {
	//			 sortedMonoms->next();
	//		 }
	//		 sortedMonoms->insert_before(m, sortedMonoms->GetCurrent()->data);
	//	 }
	//	 monoms->next();
	// }
	// monoms = sortedMonoms;
 //}