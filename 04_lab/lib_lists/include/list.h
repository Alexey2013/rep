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
	virtual void insert_before(const T& data, const T& nextdata);
	void insert_last(const T& data);
	void insert_after(const T& data, const T& beforedata);
	TNode<T>* search(const T& data);
	TNode<T>* GetCurrent() const;
	void clear();
	int GetSize() const;
	bool IsEmpty() const;
	bool IsFull() const;
	bool IsEnded()const;
	void next();
	void reset();
	void insert_sort(const T& data);
	void sort();
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
	if (tmp == pFirst){
		pFirst = pFirst->pNext;
		delete tmp;
		return;
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
	if (pCurr == pStop) throw("Lis is ended");
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
	TNode<T>* tmp = pFirst;
	while (tmp->pNext != pStop && tmp->pNext->data <= data) {
		tmp = tmp->pNext;
	}
	if (tmp->data == data) {
		tmp->data = tmp->data + data;
		return;
	}
	insert_after(data, tmp->data);
}

template <typename T>
void TList<T>::sort() {
	if (IsEmpty() || GetSize() == 1) {
		return;
	}
	TNode<T>* current = pFirst;
	do {
		bool swapped = false;
		TNode<T>* prev = nullptr;
		TNode<T>* next = current->pNext;
		while (next != nullptr && next != pStop) {
			if (current->data > next->data) {
				swap(current->data, next->data);
				swapped = true;
			}
			prev = current;
			current = next;
			next = next->pNext;
		}
		if (!swapped) {break;}
		current = pFirst;

	} while (true);

	pCurr = pFirst;
}
#endif 