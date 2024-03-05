#include "monom.h"

TMonom::TMonom() : coeff(0.0), degree(-1) {};

TMonom::TMonom(double _coeff,  int _degree){
	if (_degree < 0 || _degree > 999){
		throw ("Degree must be from 0 to 999");
	}
	coeff = _coeff;
	degree = _degree;
}

TData* TMonom::copy() const {
	return new TMonom(coeff, degree);
}

bool TMonom::operator<(const TData& data)const {
	const TMonom& monom = static_cast<const TMonom&>(data);
	return (degree < monom.degree);
}

bool TMonom::operator<=(const TData& data)const {
	const TMonom& monom = static_cast<const TMonom&>(data);
	return (degree <= monom.degree);
}

bool TMonom::operator>(const TData& data)const {
	const TMonom& monom = static_cast<const TMonom&>(data);
	return (degree > monom.degree);
}

bool TMonom::operator>=(const TData& data)const {
	const TMonom& monom = static_cast<const TMonom&>(data);
	return (degree >= monom.degree);
}

bool TMonom::operator==(const TData& data)const {
	const TMonom& monom = static_cast<const TMonom&>(data);
	return  (degree == monom.degree && coeff == monom.coeff);
}

bool TMonom::operator!=(const TData& data)const {
	const TMonom& monom = static_cast<const TMonom&>(data);
	return !(degree == monom.degree || coeff == monom.coeff);
}