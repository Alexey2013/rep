#ifndef __TBITFIELD_H__
#define __TBITFIELD_H__
#include <iostream>
using namespace std;
typedef unsigned int elem_t;

class TBitField
{
private:
	int  BitLen;
	elem_t* pMem;
	int  MemLen; 
	int   GetMemIndex(const int n) const;
	elem_t GetMemMask(const int n) const; 
public:
	TBitField(int len);              
	TBitField(const TBitField& bf);   
	~TBitField();           
	int GetLength(void) const;  
	void SetBit(const int n);     
	void ClrBit(const int n);     
	int  GetBit(const int n) const;
	bool operator==(const TBitField& bf) const;
	void swap(TBitField& lhs, TBitField& rhs);
	bool test(const int n) const;
	bool operator!=(const TBitField& bf) const;
	TBitField& operator=(const TBitField& bf);
	TBitField  operator|(const TBitField& bf);
	TBitField  operator&(const TBitField& bf);
	TBitField  operator~(void);               
	friend istream& operator>>(istream& istr, TBitField& bf);   
	friend ostream& operator<<(ostream& ostr, const TBitField& bf); 
};

#endif
