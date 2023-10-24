#ifndef  __VECTOR_H__
#define __VECTOR_H__
#include <iostream>
using namespace std;

template <typename ValueType>
class TVector
{
protected:
	int size;
	ValueType* pVector;
	int startIndex;
public:
	TVector(int s = 5, int si = 0);
	TVector(const TVector& v);
	~TVector();
	int GetSize() const;
	int GetStartIndex() const;
	ValueType& operator[](const int i);
	int operator==(const TVector& v) const;
	int operator!=(const TVector& v) const;
	const TVector& operator=(const TVector& v);

	TVector  operator+(const ValueType& val);
	TVector  operator-(const ValueType& val);
	TVector  operator*(const ValueType& val);

	TVector  operator+(const TVector& v);
	TVector  operator-(const TVector& v);
	double  operator*(const TVector& v);
	friend istream& operator>>(istream& in, TVector& v)
	{
		for (int i = 0; i < v.size; ++i) {
			in >> v.pVector[i];
		}
		return in;
	}
	friend ostream& operator<<(ostream& out, const TVector& v)
	{
		for (int i = 0; i < v.size; ++i) {
			out << v.pVector[i] << " ";
		}
		out <<endl;
		return out;
	}
};

template <typename ValueType>
int TVector<ValueType>::GetSize() const {
	return size;
}

template <typename ValueType>
int TVector<ValueType>::GetStartIndex()  const {
	return startIndex;
}

template <typename ValueType>
TVector<ValueType>::TVector(int size, int startIndex) : size(size), startIndex(startIndex) {
	pVector = new ValueType[size];
}

template <typename ValueType>
TVector<ValueType>::TVector(const TVector& v) : size(v.size), startIndex(v.startIndex) {
	pVector = new ValueType[size];
	for (int i = 0; i < size; ++i) {
		pVector[i] = v.pVector[i];
	}
}

template <typename ValueType>
TVector<ValueType>::~TVector()
{
	delete[] pVector;
}

template <typename ValueType>
ValueType& TVector<ValueType>::operator[](const int index) {
	if (index < 0 || index >= size)
		throw ("Index is out of range");
		return pVector[index];
}

template <typename ValueType>
int TVector<ValueType>::operator==(const TVector& v) const
{
	if (this != &v)
	{
		if ((size == v.size) && (startIndex == v.startIndex))
		{
			for (int i = 0; i < size; i++)
				if (pVector[i] != v.pVector[i])
					return 0;
			return 1;
		}
		else
			return 0;
	}
	return 1;
}

template <typename ValueType>
int TVector<ValueType>::operator!=(const TVector& v) const
{
	return !(*this == v);
}

template <typename ValueType>
const TVector<ValueType>& TVector<ValueType>::operator=(const TVector& v)
{
	if (this == &v) return *this;
	delete[] pVector;
	size = v.size;
	startIndex = v.startIndex;
	pVector = new ValueType[size];
	for (int i = 0; i < size; ++i) {
		pVector[i] = v.pVector[i];
	}
	return *this;
}

template <typename ValueType>
TVector<ValueType> TVector<ValueType>::operator+(const ValueType& val)
{
	TVector<ValueType> tmp(*this);
	for (int i = 0; i < size; i++) {
		tmp.pVector[i] += val;
	}
	return tmp;
}

template <typename ValueType>
TVector<ValueType> TVector<ValueType>::operator-(const ValueType& val)
{
	TVector<ValueType> tmp(*this);
	for (int i = 0; i < size; i++)
		tmp.pVector[i] -= val;
	return tmp;
}

template <typename ValueType>
TVector<ValueType> TVector<ValueType>::operator*(const ValueType& val)
{
	TVector<ValueType> tmp(*this);
	for (int i = 0; i < size; i++)
		tmp.pVector[i] *= val;
	return tmp;
}

template <typename ValueType>
TVector<ValueType> TVector<ValueType>::operator+(const TVector<ValueType>& v)
{
	if ((size != v.size) || (startIndex != v.startIndex))
		throw	("Vectors must have the same size");
	TVector tmp(size, startIndex);
	for (int i = 0; i < size; i++)
		tmp.pVector[i] = pVector[i] + v.pVector[i];
	return tmp;
}

template <typename ValueType>
TVector<ValueType> TVector<ValueType>::operator-(const TVector<ValueType>& v)
{
	if ((size != v.size) || (startIndex != v.startIndex))
		throw	("Vectors must have the same size");
	TVector tmp(size, startIndex);
	for (int i = 0; i < size; i++)
		tmp.pVector[i] = pVector[i] - v.pVector[i];
	return tmp;
}

template <typename ValueType>
double TVector<ValueType>::operator*(const TVector<ValueType>& v)
{
	if ((size != v.size) || (startIndex != v.startIndex))
		throw	("Vectors must have the same size");
	ValueType tmp = 0;
	for (int i = 0; i < size; i++)
		tmp += pVector[i] * v.pVector[i];
	return tmp;
}

#endif