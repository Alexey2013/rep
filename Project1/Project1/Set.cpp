#include "Set.h"

TSet::TSet(int mp) :MaxPower(mp), BitField(mp){}
TSet::TSet(const TSet& s) : BitField(-1){}
TSet::TSet(const TBitField& bf) :MaxPower(bf.GetLength()), BitField(bf) {}
int TSet::GetMaxPower(void) const { return MaxPower; }

void TSet::swap(TSet& lhs, TSet& rhs) {
	std::swap(lhs.MaxPower, rhs.MaxPower);
	std::swap(lhs.BitField, rhs.BitField);
}

TSet::operator TBitField()
{
	TBitField tmp(BitField);
	return tmp;
}

int TSet::IsMember(const int Elem) const 
{
	return BitField.GetBit(Elem);
}

void TSet::InsElem(const int Elem) 
{
	if (Elem > MaxPower)
		throw ("Elemet is out of universe");
		BitField.SetBit(Elem);
}

void TSet::DelElem(const int Elem) 
{
	if (Elem > MaxPower)
		throw ("Elemet is out of universe");
	BitField.ClrBit(Elem);
}

TSet& TSet::operator=(const TSet& s)
{
	if (this == &s) return *this;
	TSet tmp(s);
	swap(*this, tmp);
	return *this;
}

bool TSet::operator==(const TSet& s) const 
{return BitField == s.BitField;}

bool TSet::operator!=(const TSet& s) const 
{return!(*this == s);}

TSet TSet::operator+(const TSet& s)
{
	TSet temp(BitField | s.BitField);
	return temp;
}

TSet TSet::operator+(const int Elem)
{
	TSet tmp(BitField);
	tmp.InsElem(Elem);
	return tmp;
}

TSet TSet::operator-(const int Elem) 
{
	TSet tmp(BitField);
	tmp.DelElem(Elem);
	return tmp;
}

TSet TSet::operator*(const TSet& s)
{
	TSet temp(BitField & s.BitField);
	return temp;
}

TSet TSet::operator~(void) 
{
	TSet temp(~BitField);
	return temp;
}

istream& operator>>(istream& istr, TSet& s) 
{
}

ostream& operator<<(ostream& ostr, const TSet& s) 
{
}