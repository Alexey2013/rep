#ifndef  __MATRIX_H__
#define __MATRIX_H__
#include <iostream>
#include "vector.h"
using namespace std;

template <typename ValueType>
class TMatrix : public TVector<TVector<ValueType>>
{
public:
	TMatrix(int size);
	TMatrix(const TMatrix& mt);
	TMatrix(const TVector<TVector<ValueType> >& mt);
	int operator==(const TMatrix& mt) const;
	int operator!=(const TMatrix& mt) const;
	const TMatrix& operator= (const TMatrix& mt);
	TMatrix  operator+(const TMatrix& mt);
	TMatrix  operator-(const TMatrix& mt);
	TMatrix operator*(const TMatrix& mt);
	friend istream& operator>>(istream& in, TMatrix& mt)
	{
		cout << "Enter elements of matrix vectors" << endl;
		for (int i = 0; i < mt.size; i++)
				in >> mt.pVector[i];
		return in;
	}
	friend ostream& operator<<(std::ostream& ostr, const TMatrix<ValueType>& m)
	{
		for (int i = 0; i < m.size; i++)
		{
			for (int j = 0; j < m.pVector[i].GetStartIndex(); j++) {
				ostr << "0" << " ";
				}
				ostr << m.pVector[i];
		}
		return ostr;

	}
};

template <typename ValueType>
TMatrix<ValueType>::TMatrix(int size) : TVector<TVector<ValueType>>(size) {
	for (int i = 0; i < size; ++i) {
		pVector[i] = TVector<ValueType>(size-i,i);
	}
}

template <typename ValueType>
TMatrix<ValueType>::TMatrix(const TMatrix& mt) : TVector<TVector<ValueType>>(mt) { }

template <typename ValueType>
TMatrix<ValueType>::TMatrix(const TVector<TVector<ValueType>>& mt) :TVector<TVector<ValueType> >(mt) {}

template <typename ValueType>
int TMatrix<ValueType>::operator==(const TMatrix<ValueType>& mt) const
{
	return TVector<TVector<ValueType> >::operator==(mt);
}

template <typename ValueType>
int TMatrix<ValueType>::operator!=(const TMatrix<ValueType>& mt) const
{
	return TVector<TVector<ValueType> >::operator!=(mt);
}

template <typename ValueType>
const TMatrix<ValueType>& TMatrix<ValueType>::operator=(const TMatrix<ValueType>& mt)
{
	return TVector<TVector<ValueType> >::operator=(mt);
}

template <typename ValueType>
TMatrix<ValueType> TMatrix<ValueType>::operator+(const TMatrix<ValueType>& mt)
{
	return TVector<TVector<ValueType> >::operator+(mt);
}

template <typename ValueType>
TMatrix<ValueType> TMatrix<ValueType>::operator-(const TMatrix<ValueType>& mt)
{
	return TVector<TVector<ValueType> >::operator-(mt);
}

template <typename ValueType>
TMatrix<ValueType> TMatrix<ValueType>::operator*(const TMatrix& m) {
	if (size != m.size)
		throw "Can't multiply matrix with different dimensions!";
	int size = this->GetSize();
	TMatrix<ValueType> result(size);

	for (int k = 0; k < size; k++) {
		for (int j = k; j < size; j++) {
			ValueType sum = 0;
			for (int r = k; r <= j; r++) {
				sum += this->pVector[k][r - k] * m.pVector[r][j - r];
			}
			result.pVector[k][j - k] = sum;
		}
	}
	return result;
}

#endif
