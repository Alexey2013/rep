#ifndef __TSET_H__
#define __TSET_H__
#include "Bitfield.h"

class TSet {
private:
    int MaxPower;      
    TBitField BitField; 
public:
    TSet(int mp);
    TSet(const TSet& s);     
    TSet(const TBitField& bf);
    operator TBitField();    
    int GetMaxPower(void) const;    
    void InsElem(const int Elem);   
    void DelElem(const int Elem);    
    int IsMember(const int Elem) const;
    bool operator== (const TSet& s) const; 
    bool operator!= (const TSet& s) const; 
    TSet& operator=(const TSet& s);  
    TSet operator+ (const int Elem); 
    TSet operator- (const int Elem); 
    TSet operator+ (const TSet& s); 
    TSet operator* (const TSet& s); 
    TSet operator~ (void); 
    void swap(TSet& lhs, TSet& rhs);
    friend istream& operator>>(istream& istr, TSet& bf);
    friend ostream& operator<<(ostream& ostr, const TSet& bf);
};
#endif

