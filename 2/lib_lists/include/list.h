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
	//TNode<T>* search(const int degree);
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
	TNode<T>* GetpLast() const;
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
TList<T>::TList(TNode<T>* _pFirst) {
	pFirst = _pFirst;
	TNode<T>* tmp = _pFirst;
	while (tmp->pNext != nullptr) {
		tmp = tmp->pNext;
	}
	pLast = tmp;
	pCurr = pFirst;
	pStop = nullptr;
}

template <typename T>
TList<T>::TList(const TList<T>& list) {
	if (list.IsEmpty()) {
		pFirst = nullptr;
		pLast = nullptr;
		pCurr = nullptr;
		pStop = nullptr;
	}
	pFirst = new TNode<T>(list.pFirst->data);
	TNode<T>* tmp = pFirst;
	TNode<T>* tmp2 = list.pFirst->pNext;
	while (tmp2 != list.pStop) {
		tmp->pNext = new TNode<T>(tmp2->data);
		tmp = tmp->pNext;
		tmp2 = tmp2->pNext;	
	}
	pLast = tmp;
	pCurr = pFirst;
	pStop = nullptr;
}


template <typename T>
void TList<T>::clear() {
	if (pFirst == nullptr)
		return;
	TNode<T>* curr = pFirst;
	TNode<T>* next = pFirst->pNext;
	//while (next != nullptr) {
	//	delete curr;
	//	curr = next;
	//		next = curr->pNext;
	//}
	//delete curr;
	pCurr = pStop;
	pFirst = nullptr;
	pLast = nullptr;
}

template <typename T>
TList<T>::~TList() {
	clear();
}

template<typename T>
TNode<T>* TList<T>::search(const T& _data) {
	TNode<T>* curr = pFirst;
	while (curr != pStop && curr->data != _data) {
		curr = curr->pNext;
	}
	return curr;
}

//template<typename T>
//TNode<T>* TList<T>::search(const int degree) {
//	TNode<T>* tmp = pFirst;
//	while (tmp != nullptr && tmp->data.degree != degree) {
//		tmp = tmp->pNext;
//	}
//	if (tmp == nullptr) {
//		throw "Data not found!";
//	}
//	return tmp;
//}

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
void TList<T>::insert_after(const T& data, const T& beforedata) {
	TNode<T>* pWhere = search(beforedata);
	if (pWhere == nullptr) {
		throw ("no elements");
	}
	if (pWhere == pLast) {
		insert_last(data);
		return;
	}
	TNode<T>* new_node = new TNode<T>(data, pWhere->pNext);
	pWhere->pNext = new_node;
}

template <typename T>
void TList<T>::insert_before(const T& data, const T& nextdata) {
	TNode<T>* prev = nullptr;
	TNode<T>* curr = pFirst;
	while (curr != pStop && curr->data != nextdata) {
		prev = curr;
		curr = curr->pNext;
	}
	if (curr == pStop) {
		throw ("no elements");
	}
	if (prev == nullptr) {
		insert_first(data);
		return;
	}
	TNode<T>* new_node = new TNode<T>(data, curr);
	prev->pNext = new_node;
}

template<typename T>
void TList<T>::remove(const T& data_) {
	TNode<T>* prev = nullptr;
	TNode<T>* curr = pFirst;
	while (curr != pStop && curr->data != data_)
	{
		prev = curr;
		curr = curr->pNext;
	}
	if (curr == pStop)
		throw ("NoSuchElement");
	if (curr == pFirst && curr->pNext == pStop)
	{
		clear();
		return;
	}
	if (curr == pFirst)
	{
		pFirst = pFirst->pNext;
		delete curr;
		return;
	}
	if (curr == pLast)
	{
		prev->pNext = pStop;
		delete curr;
		return;
	}
	prev->pNext = curr->pNext;
	delete curr;
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
bool TList<T>::IsEmpty()const {
	return (pFirst == nullptr);
}

template<typename T>
bool TList<T>::IsFull()const {
	TNode<T>* tmp = new TNode<T>();
	if (tmp == nullptr) return true;
	delete tmp;
	return false;
}

template<typename T>
bool TList<T>::IsEnded()const {
	return (pCurr == pStop);
}

template<typename T>
TNode<T>* TList<T>::GetCurrent()const {
	return pCurr;
}

template<typename T>
TNode<T>* TList<T>::GetpLast()const {
	return pLast;
}

template<typename T>
void TList<T>::next() {
	if (pCurr == pLast) return;
	pCurr = pCurr->pNext;
}

template<typename T>
void TList<T>::reset() {
	pCurr = pFirst;
}

#endif 