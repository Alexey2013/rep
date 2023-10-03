#include "Bitfield.h"
#include <iostream>
using namespace std;

void TBitField::swap(TBitField& lhs, TBitField& rhs) {
	std::swap(lhs.BitLen, rhs.BitLen);
	std::swap(lhs.MemLen, rhs.MemLen);
	std::swap(lhs.pMem, rhs.pMem);
}

TBitField::TBitField(int len)
{
	MemLen = (len + BitLen - 1);
	pMem = new elem_t[MemLen];
	memset(pMem, 0, MemLen * sizeof(elem_t));
}

TBitField::TBitField(const TBitField& bf) 
{
	BitLen = bf.BitLen;
	MemLen = bf.MemLen;
	pMem = new elem_t[MemLen];
	std::copy(pMem, bf.pMem, MemLen * sizeof(elem_t));
}

TBitField::~TBitField()
{
	delete[]pMem;
}

int TBitField::GetMemIndex(const int n) const 
{
	return n/ BitLen;
}

elem_t TBitField::GetMemMask(const int n) const
{
	return 1 << (n & (BitLen - 1));
}

int TBitField::GetLength(void) const 
{
	return sizeof(TBitField);
}

void TBitField::SetBit(const int n) 
{
	if (n >= BitLen)
		throw("bit position is out of range");
	pMem[GetMemIndex(n)] |= GetMemMask(n);
}

void TBitField::ClrBit(const int n) 
{
	if (n >= BitLen)
		throw("bit position is out of range");
	pMem[GetMemIndex(n)] &= ~GetMemMask(n);
}

bool TBitField::test(const int n) const {
	if (n >= BitLen)
		throw("bit position is out of range");
	return pMem[GetMemIndex(n)] &= GetMemMask(n);
}

int TBitField::GetBit(const int n) const 
{
	return pMem[n];
}

TBitField& TBitField::operator=(const TBitField& bf) 
{
	if (this == &bf)
		return *this;
	TBitField tmp(bf);
	swap(*this, tmp);
	return *this;
}

bool TBitField::operator==(const TBitField& bf) const 
{
	if (BitLen != bf.BitLen) return false;
	for (int i = 0; i < MemLen; i++) {
		if (pMem[i] != bf.pMem[i]) {
			return false;
		
		}
	}
	return true;
}

bool TBitField::operator!=(const TBitField& bf) const 
{
	if (BitLen == bf.BitLen) return false;
	for (int i = 0; i < MemLen; i++) {
		if (pMem[i] == bf.pMem[i]) {
			return false;
		}
	}
	return true;
}

TBitField TBitField::operator|(const TBitField& bf) 
{
	int i, len = BitLen;
	if (bf.BitLen > len)
		len = bf.BitLen;
	TBitField temp(len);
	for (i = 0; i < MemLen; i++)
		temp.pMem[i] = pMem[i];
	for (i = 0; i < bf.MemLen; i++)
		temp.pMem[i] |= bf.pMem[i];
	return temp;
}

TBitField TBitField::operator&(const TBitField& bf)
{
	int i, len = BitLen;
	if (bf.BitLen > len)
		len = bf.BitLen;
	TBitField temp(len);
	for (i = 0; i < MemLen; i++)
		temp.pMem[i] = pMem[i];
	for (i = 0; i < bf.MemLen; i++)
		temp.pMem[i] &= bf.pMem[i];
	return temp;
}

TBitField TBitField::operator~(void) 
{
	TBitField temp(BitLen);
	for (int i = 0; i < MemLen; i++) {
		temp.pMem[i] = ~pMem[i];
	}
	return temp;
}

istream& operator>>(istream& istr, TBitField& bf) 
{
	int len = bf.GetLength();
	for (int i = 0; i < len; i++) {
		cin >> bf.pMem[i];
	}
}

ostream& operator<<(ostream& ostr, const TBitField& bf) 
{
	int len = bf.GetLength();
	for (int i = 0; i < len; i++){
		cout<<bf.GetBit(i);
	}
	return ostr;
}