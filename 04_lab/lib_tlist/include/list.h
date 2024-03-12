#ifndef _LIST_H
#define _LIST_H
#include "node.h"
#include <iostream>
using namespace std;

template <typename T>
class TList{
protected:
	TNode<T>* pFirst;
	TNode<T>* pPrev;
	TNode<T>* pCurr;
	TNode<T>* pStop;
	TNode<T>* pLast;
public:
	TList();
	TList( TNode<T>* _pFirst);
	TList(const TList<T>& list);
	~TList();
	TNode<T>* search(const T& data);
	void insert_first(const T& data);
	void insert_last(const T& data);
	void insert_after(const T& data, const T& beforedata);
	void insert_before(const T& data, const T& nextdata);
	void remove(const T& data);
	void clear();
	int GetSize() const;
	bool IsEmpty() const;
	bool IsFull() const;
	void print() const;
	bool Is_End();
	TNode<T>* GetCurrent() const;
	void next();  
	void reset(); 
};

template<typename T>
TList<T>::TList() {
	pFirst = nullptr;
	pLast = nullptr;
	pCurr = nullptr;
	pStop = nullptr;
}

template <typename T>
TList<T>::TList( TNode<T>* _pFirst)
{
	pFirst = _pFirst;
	pPrev = nullptr;
	pCurr = pFirst;
	pStop = nullptr;
	TNode<T>* tmp = pFirst;
	while (tmp->pNext != pStop)
		tmp = tmp->pNext;
	pLast = tmp;
}

template <typename T>
TList<T>::TList(const TList<T>& list)
{
	if (list.pFirst == nullptr) return;
	pFirst = new TNode<T>(list.pFirst->data, list.pFirst->pNext);
	TNode<T>* tmp = pFirst;
	TNode<T>* tmp2 = pFirst;
	tmp = tmp->pNext;
	while (tmp != list.pStop)
	{
		tmp2->pNext = new TNode<T>(tmp->data);
		tmp2 = tmp2->pNext;
		tmp = tmp->pNext;
	}
	pPrev = nullptr;
	pCurr = pFirst;
	pStop = tmp2->pNext;
	pLast = tmp2;
}

template<typename T>
void TList<T>::clear() {
	TNode<T>* tmp = pFirst;
	while (tmp != nullptr) {
		pFirst = pFirst->pNext;
		tmp->pNext = nullptr;
		delete tmp;
		tmp = pFirst;
	}
	pCurr = pStop;
	pLast = pStop;
}

template <typename T>
TList<T>::~TList()
{
	clear();
}

template<typename T>
TNode<T>* TList<T>::search(const T& data_) {
	TNode<T>* tmp = pFirst;
	while (tmp != nullptr && tmp->data == data_) {
		tmp = tmp->pNext;
	}
	if (tmp == nullptr && tmp->data != data_) {
		throw "Data not found!";
	}
	return tmp;
}

template <typename T>
void TList<T>::insert_first(const T& data)
{
	TNode<T>* pNode = new TNode<T>(data);
	if (pFirst != pStop)
		pNode->pNext = pFirst;
	pFirst = pNode;
	pLast = pNode;
	pCurr = pFirst;
}

template <typename T>
void TList<T>::insert_last(const T& data)
{
	if (pFirst == pStop)
	{
		insert_first(data);
		return;
	}
	TNode<T>* pNode = new TNode<T>(data);
	pLast->pNext = pNode;
	pLast = pNode;
}

template <typename T>
void TList<T>::insert_after(const T& data, const T& beforedata)
{
	TNode<T>* pPrev = Search(beforedata);
	if (pPrev != pStop)
	{
		if (pPrev->pNext == pStop)
		{
			InsertEnd(data);
			return;
		}
		TNode<T>* pNode = new TNode<T>(data);
		pNode->pNext = pPrev->pNext;
		pPrev->pNext = pNode;
	}
	else
	{
		string msg = "Element not found!";
		throw msg;
	}
}

template <typename T>
void TList<T>::insert_before(const T& data, const T& nextdata)
{
	if (pFirst != pStop && pFirst->data == nextdata)
		InsertFirst(data);
	else
	{
		TNode<T>* tmp = pFirst;
		pPrev = nullptr;
		while (tmp != pStop && tmp->data != nextdata)
		{
			pPrev = tmp;
			tmp = tmp->pNext;
		}
		if (tmp != pStop)
		{
			TNode<T>* pNode = new TNode<T>(data);
			pNode->pNext = tmp;
			pPrev->pNext = pNode;
		}
		else
		{
			string msg = "Element not found!";
			throw msg;
		}
	}
}

template<typename T>
void TList<T>::remove(const T& data_) {
	TNode<T>* tmp = pFirst;
	TNode<T>* pPrev = nullptr;
	while (tmp->data != data_ && tmp != pStop) {
		pPrev = tmp;
		tmp = tmp->pNext;
	}
	if (tmp->data != data_ && tmp == pStop) {
		throw "Data not found!";
	}
	if (pPrev == nullptr) {
		pFirst = pFirst->pNext;
		pCurr = pFirst;
		tmp->pNext = nullptr;
		delete tmp;
	}
	else { pPrev->pNext = tmp->pNext;  tmp->pNext = nullptr; delete tmp; }
}

template<typename T>
int TList<T>::GetSize()const {
	if (pFirst == nullptr) { return 0; }
	int count;
	TNode<T>* tmp = pFirst;
	while (tmp != pStop) {
		count++;
		tmp = tmp->pNext;
	}
	return count;
}

template<typename T>
bool TList<T>::IsEmpty()const {
	return (pFirst == nullptr);
}

template<typename T>
bool TList<T>::IsFull()const {
	TNode<T>* tmp = new TNode<T>();
	if (tmp == nullptr) {
		throw ("exp");
	}
}

template<typename T>
bool TList<T>::Is_End() {
	return (pCurr == nullptr || pCurr == pStop);
}

template<typename T>
TNode<T>* TList<T>::GetCurrent()const {
	return pCurr;
}

template<typename T>
void TList<T>::next() {
	pCurr = pCurr->pNext;
}

template<typename T>
void TList<T>::reset() {
	pCurr = pFirst;
}

template<typename T>
void TList<T>::print() const {
	TNode<T>* tmp = pFirst;
	while (tmp != nullptr) {
		cout << tmp->data << " ";
		tmp = tmp->pNext;
	}
	cout << endl;
}

#endif 