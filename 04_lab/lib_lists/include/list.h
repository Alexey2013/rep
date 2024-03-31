#ifndef _LIST_H
#define _LIST_H
#include "node.h"
#include <iostream>
using namespace std;

template <typename T>
class TList {
protected:
	TNode<T>* pFirst;
	TNode<T>* pCurr;
	TNode<T>* pStop;
	TNode<T>* pLast;
public:
	TList();
	TList(TNode<T>* _pFirst);
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
	bool IsEnded()const;
	TNode<T>* GetCurrent() const;
	void next();
	void reset();
};

template <typename T>
TList<T>::TList() {
	pFirst = nullptr;
	pLast = nullptr;
	pCurr = nullptr;
	pStop = nullptr;
}

template <typename T>
TList<T>::TList(const TList& l) {
	if (l.IsEmpty())
	{
		pFirst = nullptr;
		pLast = nullptr;
		pCurr = nullptr;
		pStop = nullptr;
		return;
	}

	pFirst = new TNode<T>(l.pFirst->data);
	TNode<T>* tmp = pFirst;
	TNode<T>* ltmp = l.pFirst->pNext;
	while (ltmp != l.pStop)
	{
		tmp->pNext = new TNode<T>(ltmp->data);
		tmp = tmp->pNext;
		ltmp = ltmp->pNext;
	}
	pLast = tmp;
	pCurr = pFirst;
	pStop = nullptr;
}

template <typename T>
TList<T>::TList(TNode<T>* pNode) {
	pFirst = pNode;
	TNode<T>* tmp = pNode;
	while (tmp->pNext != nullptr)
		tmp = tmp->pNext;
	pLast = tmp;
	pCurr = pFirst;
	pStop = nullptr;
}

template <typename T>
void TList<T>::clear() {
	if (pFirst == nullptr) return;
	TNode<T>* curr = pFirst;
	TNode<T>* next = pFirst->pNext;
	while (next != nullptr) { 
		delete curr;
		curr = next;
		next = curr->pNext;
	}
	delete curr;
	pFirst = nullptr;
	pLast = nullptr;
}

template <typename T>
TList<T>::~TList() {
	clear();
}

template <typename T>
bool TList<T>::IsFull() const {
	TNode<T>* tmp = new TNode<T>();
	if (tmp == nullptr)
		return true;
	delete tmp;
	return false;
}

template <typename T>
bool TList<T>::IsEmpty() const {
	return (pFirst == nullptr);
}

template <typename T>
bool TList<T>::IsEnded()const {
	return pCurr == pStop;
}

template <typename T>
TNode<T>* TList<T>::search(const T& data) {
	TNode<T>* curr = pFirst;
	while (curr != pStop && curr->data != data) {
		curr = curr->pNext;
	}
	return curr;
}

template <typename T>
void TList<T>::insert_first(const T& data) {
	TNode<T>* new_first = new TNode<T>(data, pFirst);
	pFirst = new_first;
	if (pLast == nullptr) {
		pLast = pFirst;
	}
	pCurr = pFirst;
}

template <typename T>
void TList<T>::insert_last(const T& data) {
	if (IsEmpty()) {
		insert_first(data);
		return;
	}
	TNode<T>* new_last = new TNode<T>(data, pStop);
	pLast->pNext = new_last;
	pLast = new_last;
	pCurr = new_last;
}

template <typename T>
void TList<T>::insert_before(const T& who, const T& where) {
	TNode<T>* pPrev = nullptr;

	if (pFirst != pStop && pFirst->data == where) {
		insert_first(who);
	}
	else {
		TNode<T>* tmp = pFirst;
		while (tmp != pStop && tmp->data != where) {
			pPrev = tmp;
			tmp = tmp->pNext;
		}
		if (tmp == pStop) {
			throw ("Data not found!");
		}
		TNode<T>* pNode = new TNode<T>(who, tmp);
		if (pPrev != nullptr) {
			pPrev->pNext = pNode;
		}
		else {
			pFirst = pNode;
		}
	}
}

template <typename T>
void TList<T>::insert_after(const T& who, const T& where) {
	TNode<T>* pWhere = search(where);
	if (pWhere == nullptr) {
		throw ("no elements");
	}
	if (pWhere == pLast) {
		insert_last(who);
		return;
	}
	TNode<T>* new_node = new TNode<T>(who, pWhere->pNext);
	pWhere->pNext = new_node;
}

template <typename T>
void TList<T>::remove(const T& data_){
	if (pFirst == nullptr) throw "List is empty!";
	TNode<T>* tmp = pFirst;
	TNode<T>* pPrev = nullptr;
	while (tmp != pStop && tmp->data != data_)
	{
		pPrev = tmp;
		tmp = tmp->pNext;
	}
	if (tmp == pStop)throw "Data not found!";
	if (pPrev == nullptr) pFirst = pFirst->pNext;
	else { pPrev->pNext = tmp->pNext; }
	delete tmp;
}

template <typename T>
void TList<T>::reset() {
	pCurr = pFirst;
}

template <typename T>
void TList<T>::next() {
	if (pCurr == pStop) return;
	pCurr = pCurr->pNext;
}

template<typename T>
int TList<T>::GetSize() const {
	if (pFirst == nullptr)  return 0;
	int size = 0;
	TNode<T>* tmp = pFirst;
	while (tmp != nullptr) {
		size++;
		tmp = tmp->pNext;
	}
	return size;
}

template<typename T>
TNode<T>* TList<T>::GetCurrent()const {
	return pCurr;
}

#endif 