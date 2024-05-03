#include "polynom.h"

TPolynom::TPolynom() {
	monoms = new THeadRingList<TMonom>();
	name = "";
}

TPolynom::TPolynom(const string& _name) {
	monoms = new THeadRingList<TMonom>();
	parse_monoms(_name);
}

TPolynom::TPolynom(const THeadRingList<TMonom>* list) {
	monoms = new THeadRingList<TMonom>();
	TNode<TMonom>* current = list->GetCurrent();
	int n= list->GetSize();
	for (int i = 0; i < n; i++) {
		TMonom curr = current->data;
		if (curr.coeff != 0) {
			monoms->insert_sort(curr);
		}
		current = current->pNext;
	}
	similar();
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

void TPolynom::convert_string(string& str) const {
	str.erase(remove(str.begin(), str.end(), ' '), str.end());
	transform(str.begin(), str.end(), str.begin(), ::tolower);
}

string TPolynom::ToString() const {
	string str;
	TPolynom p(*this);
	if (p.monoms->IsEmpty()) {return "";}
	bool firstTerm = true;
	p.monoms->reset();
	if (p.monoms->GetCurrent()->data.coeff == 0&&p.monoms->GetCurrent()->data.degree == 0) {
		return "0";
	}
	while (!p.monoms->IsEnded()) {
		int deg = p.monoms->GetCurrent()->data.degree;
		double coeff = p.monoms->GetCurrent()->data.coeff;
		int x = deg / 100;
		int y = (deg % 100) / 10;
		int z = deg % 10;
			if (!firstTerm) {
				str += ((coeff > 0) ? "+" : "-");
			}
			else {
				if (coeff < 0) str += '-';
				firstTerm = false;
			}
			if (abs(coeff) != 1 || deg == 0) {
				char tmp[10];
				sprintf(tmp, "%.2f", abs(coeff));
				str += string(tmp);
			}
			string mul_symbol = ((abs(coeff) == 1) ? "" : "*");
			if (x != 0) {
				str += (mul_symbol + "x") + ((x != 1) ? "^" + std::to_string(x) : "");
			}
			if (y != 0) {
				mul_symbol = (x == 0) ? mul_symbol : "*";
				str += (mul_symbol + "y") + ((y != 1) ? "^" + std::to_string(y) : "");
			}
			if (z != 0) {
				mul_symbol = (x == 0 && y == 0) ? mul_symbol : "*";
				str += (mul_symbol + "z") + ((z != 1) ? "^" + std::to_string(z) : "");
			}
		p.monoms->next();
	}
	return str;
}


void TPolynom::similar() {
	monoms->reset();
	while (!monoms->IsEnded() && !monoms->IsEmpty()) {
		TNode<TMonom>* current = monoms->GetCurrent();
		TNode<TMonom>* next = monoms->GetCurrent()->pNext;

		if (current->data == next->data) {
			next->data.coeff += current->data.coeff;
			if (next->data.coeff == 0) 
			{
				monoms->next();
				monoms->remove(current->data);
				monoms->next();
				monoms->remove(next->data);
			}
			else {
				monoms->next();
				monoms->remove(current->data);
			}
		}
		else {
			monoms->next();
		}
	}
	if (monoms->IsEmpty()) { monoms->insert_first(TMonom(0, 0)); }
}

void TPolynom::parse_monoms(const string& _name) {
	string str = _name;
	convert_string(str);
	if (_name == "0") { 
		monoms->insert_first(TMonom(0, 0)); 
		return; 
	}
	while (!str.empty()) {
		TMonom tmp;
		int degree = 0;
		size_t j = str.find_first_of("+-", 1);
		string monom = str.substr(0, j);
		str.erase(0, j);
		string coefficient = monom.substr(0, monom.find_first_of("xyz"));
		tmp.coeff = ((coefficient.empty() || coefficient == "+") ? 1 : 
			(coefficient == "-") ? -1 : stod(coefficient));
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
			monoms->insert_sort(tmp);
		}
	}
	similar();
	name = ToString();
}

const TPolynom& TPolynom::operator=(const TPolynom& p)  {
	if (this != &p) {
		name = p.name;
		delete monoms;
		monoms = new THeadRingList<TMonom>(*(p.monoms));
	}
	return (*this);
}

TPolynom TPolynom::operator+(const TPolynom& p){
	TPolynom result;
	monoms->reset();
	p.monoms->reset();
	if (name == "0.00" || p.name == "0.00") { return (name == "0.00") ? p : (*this); }
	while (!monoms->IsEnded() && !p.monoms->IsEnded()){
		TMonom m1 = monoms->GetCurrent()->data;
		TMonom m2 = p.monoms->GetCurrent()->data;
		if (m1 == m2){
			TMonom m3 = m1 + m2;
			if (m3.coeff != 0) {result.monoms->insert_last(m3);}
			monoms->next();
			p.monoms->next();
		}
		else if (m2<m1){
			result.monoms->insert_last(m2);
			p.monoms->next();
		}
		else{
			result.monoms->insert_last(m1);
			monoms->next();
		}
	}
	while (!monoms->IsEnded()) {
		TMonom m1 = monoms->GetCurrent()->data;
		result.monoms->insert_last(m1);
		monoms->next();
	}
	while (!p.monoms->IsEnded()) {
		TMonom m2 = p.monoms->GetCurrent()->data;
		result.monoms->insert_last(m2);
		p.monoms->next();
	}
	if (result.monoms->IsEmpty()) { result.monoms->insert_first(TMonom(0, 0)); }
	result.name = result.ToString();
	return result;
}

TPolynom TPolynom::operator-(const TPolynom& p) {
	TPolynom result(*this);
	result = result+(-p);
	result.name = result.ToString();	
	return result;
}

TPolynom TPolynom::operator-() const {
	TPolynom result(*this);
	result.monoms->reset();
	while (!result.monoms->IsEnded()) {
		result.monoms->GetCurrent()->data.coeff *= -1;
		result.monoms->next();
	}
	result.name = result.ToString();	
	return result;
}

TPolynom TPolynom::operator*(const TPolynom& p) {
	TPolynom result;
	monoms->reset();
	bool not_null =false;
	while (!monoms->IsEnded()) {
		p.monoms->reset();
		while (!p.monoms->IsEnded()) {
			TMonom m1 = monoms->GetCurrent()->data;
			TMonom m2 = p.monoms->GetCurrent()->data;
			TMonom m3 = m1 * m2;
			if (m3.coeff != 0) {
				result.monoms->insert_sort(m3);
				not_null = true;
			}
			p.monoms->next();
		}
		monoms->next();
	}
	if (!not_null) {result.monoms->insert_first(TMonom(0, 0));}
	result.similar();
	result.name = result.ToString();
	return result;
}

TPolynom TPolynom::dx() const {
	TPolynom result;
	bool not_null = false;
	monoms->reset();
	while (!monoms->IsEnded()) {
		TMonom m = monoms->GetCurrent()->data;
		if (m.degree >= 100) {
			int new_degree = m.degree - 100;
			double new_coeff = m.coeff * (m.degree / 100);
			TMonom new_monom(new_coeff, new_degree);
			result.monoms->insert_last(new_monom); 
			not_null = true;
		}
		monoms->next();
	}
	if (!not_null) {result.monoms->insert_first(TMonom(0, 0));}
	result.name = result.ToString();
	return result;
}

TPolynom TPolynom::dy() const {
	TPolynom result;
	bool not_null = false;
	monoms->reset();
	while (!monoms->IsEnded()) {
		TMonom m = monoms->GetCurrent()->data;
		int deg = m.degree;
		int y = (deg % 100) / 10;
		if (y >= 1) {
			int new_degree = m.degree - 10;
			double new_coeff = m.coeff * y; 
			TMonom new_monom(new_coeff, new_degree);
			result.monoms->insert_last(new_monom);
			not_null = true;
		}
		monoms->next();
	}
	if (!not_null) {result.monoms->insert_first(TMonom(0, 0));}
	result.name = result.ToString();
	return result;
}

TPolynom TPolynom::dz() const {
	TPolynom result;
	monoms->reset();
	bool not_null = false;
	while (!monoms->IsEnded()) {
		TMonom m = monoms->GetCurrent()->data;
		int deg = m.degree;
		int z = deg % 10;
		if (z >= 1) {
			int new_degree = m.degree - 1;
			double new_coeff = m.coeff * z;
			TMonom new_monom(new_coeff, new_degree);
			result.monoms->insert_last(new_monom);
			not_null = true;
		}
		monoms->next();
	}
	if (!not_null) {result.monoms->insert_first(TMonom(0, 0));}
	result.name=result.ToString();
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

ostream& operator<<(ostream& out, const TPolynom& p) {
	out << p.ToString() << endl;
	return out;
}

istream& operator>>(istream& in, TPolynom& p) {
	string input;
	cout << "Enter polynom:";
	getline(in, input);  
	p = TPolynom(input);  
	return in;
}

