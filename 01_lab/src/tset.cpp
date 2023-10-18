#include "tset.h"

TSet::TSet(int mp) :MaxPower(mp), BitField(mp) {}
TSet::TSet(const TSet& s) : BitField(s.BitField),MaxPower(s.GetMaxPower()) {}
TSet::TSet(const TBitField& bf) :MaxPower(bf.GetLength()), BitField(bf) {}
int TSet::GetMaxPower(void) const { return MaxPower;}
TSet::operator TBitField(){ return BitField;}

int TSet::IsMember(const int Elem) const 
{
    if (Elem >= MaxPower || Elem < 0)  throw ("Elemet is out of universe");
    return BitField.GetBit(Elem);
}

void TSet::InsElem(const int Elem) 
{
    if (Elem >= MaxPower || Elem < 0)  throw ("Elemet is out of universe");
    return BitField.SetBit(Elem);
}

void TSet::DelElem(const int Elem) 
{
    if (Elem >= MaxPower || Elem < 0)  throw ("Elemet is out of universe");
    return BitField.ClrBit(Elem);
}

const TSet& TSet::operator=(const TSet& s) 
{
    if (*this == s) return *this;
        MaxPower = s.MaxPower;
        BitField = s.BitField;
        return *this;
}

int TSet::operator==(const TSet& s) const 
{
    if (MaxPower != s.GetMaxPower())
    {  return 0;}
    return (BitField == s.BitField);
}

int TSet::operator!=(const TSet& s) const {
    return !(*this == s);
}

TSet TSet::operator+(const TSet& s) 
{
    TSet tmp(max(MaxPower, s.GetMaxPower()));
    tmp.BitField = BitField | s.BitField;
    return tmp;
}

TSet TSet::operator+(const int Elem) 
{
    if (Elem >= MaxPower || Elem < 0)  throw ("Elemet is out of universe");
    TSet tmp(*this);
    tmp.InsElem(Elem);
    return tmp;
}

TSet TSet::operator-(const int Elem) 
{
    if (Elem >= MaxPower || Elem < 0)  throw ("Elemet is out of universe");
    TSet tmp(*this);
    tmp.DelElem(Elem);
    return tmp;
}

TSet TSet::operator*(const TSet& s) 
{
    TSet tmp(max(MaxPower, s.GetMaxPower()));
    tmp.BitField = BitField & s.BitField;
    return tmp;
}

TSet TSet::operator~(void) 
{
    TSet tmp(MaxPower);
    tmp.BitField = ~BitField;
    return tmp;
}

 ostream& operator<<(ostream& ostr, const TSet& s)
 {
     const int x = s.MaxPower - 1;
     for (int i = 0; i <= x; ++i)
     {
         ostr << s.IsMember(i) << " ";
     }
     return ostr;
 }

 istream& operator>>(std::istream& istr, TSet& s) {
     int elemt;
     int n;
     cout << "Enter the number of positions you want to insert:";
     cin >> n;
     for (int i = 0; i < n; i++)
     {
    istr>>elemt;
    s.InsElem(elemt);
     }
     return istr;
}

