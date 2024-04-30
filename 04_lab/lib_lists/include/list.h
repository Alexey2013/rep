#ifndef _LIST_H
#define _LIST_H
#include "node.h"

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
	virtual ~TList();
	virtual void insert_first(const T& data);
	virtual void remove(const T& data);
    void insert_before(const T& data, const T& nextdata);
	void insert_last(const T& data);
	void insert_after(const T& data, const T& beforedata);
	TNode<T>* search(const T& data) const;
	TNode<T>* GetCurrent() const;
	void clear();
	int GetSize() const;
	bool IsEmpty() const;
	bool IsFull() const;
	bool IsEnded()const;
	void next();
	void reset();
	void insert_sort(const T& data);
	const TList<T>& operator=(const TList<T>& other);
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
	while (curr != pStop) {
		TNode<T>* next = curr->pNext;
		delete curr;
		curr = next;
	}
	pCurr = nullptr;
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
TNode<T>* TList<T>::search(const T& data) const {
	TNode<T>* curr = pFirst;
	while (curr != pStop && curr->data != data) {
		curr = curr->pNext;
	}
	if (curr == pStop) {
		throw ("Element not found!");
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
	TNode<T>* pWhere = search(where);
	if (pWhere == pFirst) {
		insert_first(who);
		return;
	}
	TNode<T>* pPrev = pFirst;
	while (pPrev->pNext != pWhere) {
		pPrev = pPrev->pNext;
	}
	TNode<T>* new_node = new TNode<T>(who, pWhere);
	pPrev->pNext = new_node;
}

template <typename T>
void TList<T>::insert_after(const T& who, const T& where) {
	TNode<T>* pWhere = search(where);
	if (pWhere == pLast) {
		insert_last(who);
		return;
	}
	TNode<T>* new_node = new TNode<T>(who, pWhere->pNext);
	pWhere->pNext = new_node;
}

template <typename T>
void TList<T>::remove(const T& data_) {
	if (pFirst == nullptr) throw "List is empty!";
	TNode<T>* tmp = pFirst;
	TNode<T>* pPrev = nullptr;
	while (tmp != pStop && tmp->data != data_)
	{
		pPrev = tmp;
		tmp = tmp->pNext;
	}
	if (tmp == pFirst) {
		pFirst = pFirst->pNext;
		delete tmp;
		return;
	}
	if (tmp == pStop)throw "Data not found!";
	pPrev->pNext = tmp->pNext;
	delete tmp;
}

template <typename T>
void TList<T>::reset() {
	pCurr = pFirst;
}

template <typename T>
void TList<T>::next() {
	if (pCurr == pStop) throw("List is ended");
	pCurr = pCurr->pNext;
}

template<typename T>
int TList<T>::GetSize() const {
	if (pFirst == nullptr)  return 0;
	int size = 0;
	TNode<T>* tmp = pFirst;
	while (tmp != pStop) {
		size++;
		tmp = tmp->pNext;
	}
	return size;
}

template<typename T>
TNode<T>* TList<T>::GetCurrent()const {
	return pCurr;
}

template <typename T>
void TList<T>::insert_sort(const T& data) {
	if (IsEmpty() || data < pFirst->data) {
		insert_first(data);
		return;
	}

	TNode<T>* prev = pFirst;
	TNode<T>* current = pFirst->pNext;

	while (current != pStop && current->data <= data) {
		prev = current;
		current = current->pNext;
	}

	if (current == pStop) {insert_last(data); }
	else {
		TNode<T>* newNode = new TNode<T>(data);
		prev->pNext = newNode;
		newNode->pNext = current;
	}
}

template <typename T>
const TList<T>& TList<T>::operator=(const TList<T>& other)
{
	if (this == &other){return *this;}
	clear();
	TNode<T>* otherCurr = other.pFirst;
	while (otherCurr != nullptr)
	{
		insert_last(otherCurr->data);
		otherCurr = otherCurr->pNext;
	}
	return *this;
}

#endif 