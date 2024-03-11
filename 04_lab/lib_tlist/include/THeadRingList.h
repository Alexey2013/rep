#ifndef _THEADRINGLIST_H
#define _THEADRINGLIST_H
#include <iostream>
#include "list.h"
using namespace std;

template <typename T>
class THeadRingList : public TList<T> {
private:
	TNode<T>* pHead;
public:
	THeadRingList();
	THeadRingList(const TNode<T>* _pFirst);
	THeadRingList(const TList<T>& obj);
	THeadRingList(const THeadRingList<T>& obj);
	virtual ~THeadRingList();
};

template <typename T>
THeadRingList<T>::THeadRingList() : TList<T>()
{
	pHead = new TNode<T>;
	this->pStop = pHead;
	pHead->pNext = this->pFirst;
}

template <typename T>
THeadRingList<T>::THeadRingList(const TNode<T>* _pFirst) : TList<T>(_pFirst)
{
	pHead = new TNode<T>();
	this->pStop = pHead;
	pHead->pNext = this->pFirst;
}

template <typename T>
THeadRingList<T>::THeadRingList(const TList<T>& obj) : TList<T>(obj)
{
	pHead = new TNode<T>();
	this->pStop = pHead;
	pHead->pNext = this->pFirst;
}

template <typename T>
THeadRingList<T>::THeadRingList(const THeadRingList<T>& obj)
{
	if (obj.pFirst == nullptr)
		return;

	this->pFirst = new TNode<T>(obj.pFirst->data);
	TNode<T>* tmp = this->pFirst;
	TNode<T>* tmp2 = this->pFirst;

	while (tmp->pNext != rlist.pStop)
	{
		tmp2->pNext = new TNode<T>(tmp->data);
		tmp2 = tmp2->pNext;
		tmp = tmp->pNext;
	}
	this->pCurr = this->pFirst;
	pHead = new TNode<T>();
	this->pStop = pHead;
	pHead->pNext = this->pFirst;
}

template <typename T>
THeadRingList<T>::~THeadRingList()
{
	if (pHead)
		delete pHead;
}

#endif 