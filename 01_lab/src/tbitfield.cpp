#include "tbitfield.h"
const int bitsInElem = 32;
const int shiftSize = 5;

TBitField::TBitField(int len)
{
    if (len > 0) {
        BitLen = len;
        MemLen = ((len + bitsInElem - 1) >> shiftSize);
        pMem = new TELEM[MemLen];
        memset(pMem, 0, MemLen * sizeof(TELEM));
    }
    else if (len == 0)
    {
        BitLen = 0;
        MemLen = 0;
        pMem = nullptr;
    }
    else {
        throw ("Bitfield size less than 0");
    }
}

TBitField::TBitField(const TBitField& bf)
{
    BitLen = bf.BitLen;
    MemLen = bf.MemLen;
    if (MemLen) {
        pMem = new TELEM[MemLen];
        memcpy(pMem, bf.pMem, MemLen * sizeof(TELEM));
    }
    else {
        pMem = nullptr;
    }
}

TBitField::~TBitField()
{
    delete[] pMem;
}

int TBitField::GetMemIndex(const int n) const 
{
    return n >> shiftSize;
}

TELEM TBitField::GetMemMask(const int n) const 
{
    return 1 << (n & (bitsInElem - 1));
}

int TBitField::GetLength(void) const 
{
    return BitLen;
}

void TBitField::SetBit(const int n) 
{
    if (n >= BitLen || n < 0) 
        throw("bit position is out of range");
    pMem[GetMemIndex(n)] |= GetMemMask(n);
}

void TBitField::ClrBit(const int n) 
{
    if (n >= BitLen || n < 0)
        throw("bit position is out of range");
    pMem[GetMemIndex(n)] &= ~GetMemMask(n);
}

int TBitField::GetBit(const int n) const {
    if (n >= BitLen || n < 0)
        throw("bit position is out of range");
    return (pMem[GetMemIndex(n)] & GetMemMask(n)) ? 1 : 0;
}

const  TBitField & TBitField::operator=(const TBitField & bf)
{
    if (*this == bf) return *this;
    if (BitLen != bf.BitLen)
    {
        delete[] pMem;
        BitLen = bf.BitLen;
        MemLen = bf.MemLen;
        pMem = new TELEM[MemLen];
    }
    for (int i = 0; i < MemLen; ++i)
    {
        pMem[i] = bf.pMem[i];
    }
    return *this;
}

 int TBitField::operator==(const TBitField& bf) const
 {
     if (BitLen != bf.BitLen) return 0;
     for (int i = 0; i < MemLen; i++) {
         if (pMem[i] != bf.pMem[i]) {
             return 0;

         }
     }
     return 1;
 }

int TBitField::operator!=(const TBitField& bf) const 
{
    return !((*this) == bf);
}

TBitField TBitField::operator|(const TBitField& bf) 
{
    int len = max(BitLen, bf.BitLen);
    TBitField tmp(len);
    for (int i = 0; i < tmp.MemLen; i++)
        tmp.pMem[i] = pMem[i] | bf.pMem[i];
    return tmp;
}

TBitField TBitField::operator&(const TBitField& bf) 
{
    int len = max(BitLen, bf.BitLen); 
    TBitField tmp(len);
    for (int i = 0; i < tmp.MemLen; i++) {
        tmp.pMem[i] = pMem[i] & bf.pMem[i];
    }
    return tmp;
}

TBitField TBitField::operator~(void)
{
    TBitField tmp(BitLen);
    for (int i = 0; i < BitLen; i++)
        if (GetBit(i)==0)
            tmp.SetBit(i);
    return tmp;
}

 istream& operator>>(std::istream& in, TBitField& bf) {
    string answer;
    in >> answer;
    if (answer.length() > bf.BitLen)  throw "out of range";
    for (int i = 0; i < bf.BitLen; i++) {
        if (answer[bf.BitLen - 1 - i] == '1') {
            bf.SetBit(i);
        }
    }
    return in;
}

ostream& operator<<(ostream& ostr, const TBitField& bf) 
{
    for (int i = 0; i < bf.GetLength(); ++i)
    {
        ostr << bf.GetBit(i) << " ";
    }
    return ostr;
}
