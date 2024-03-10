#ifndef _LIST_H
#define _LIST_H
#include "node.h"
#include <iostream>
using namespace std;

template<typename T> class TList {
private:
	TNode<T>* pFirst;
	TNode<T>* pLast;
	TNode<T>* pCurr;
	TNode<T>* pStop;
public:
	TList();
	TList(TNode<T>* pFirst_);
	TList(const TList<T>& obj);
	~TList();
	TNode<T>* search(const T& data_);
	void insert_first(const T& data_);
	void insert_last(const T& data_);
	void insert_before(const T& data_, const T& next_data_);
	void insert_after(const T& data_, const T& next_data_);
	void remove(const T& data_);
	void clear();
	int GetSize()const;
	bool IsEmpty()const;
	bool IsFull()const;
	void reset();
	TNode<T>* GetCurrent()const;
	void next();
	bool Is_End();
	friend ostream& operator<<(ostream& out, const TList& l){
		for (const T& element : l.v) {
			out << element << " " << endl;
		}
		out <<endl;
		return out;
	}
};

template<typename T>
TList<T>::TList() {
	pFirst = nullptr;
	pLast = nullptr;
	pCurr = nullptr;
	pStop = nullptr;
}

template<typename T>
TList<T>::TList(TNode<T>* pFirst_) {
	pFirst = pFirst_;
	pStop = nullptr;
	TNode<T>* tmp = pFirst;
	while (tmp->pNext != pStop) {
		tmp = tmp->pNext;
	}
	pLast = tmp;
	pCurr = pFirst;
}

template<typename T>
TList<T>::TList(const TList<T>& list) {
	if (list.pFirst == nullptr) {
		pFirst = nullptr;
		pLast = nullptr;
		pCurr = nullptr;
		return;
	}
	pFirst = new TNode<T>(list.pFirst->data);
	TNode<T>* tmp1 = list.pFirst->pNext;
	TNode<T>* tmp2 = pFirst;
	while (tmp1 != nullptr) {
		tmp2->pNext = new TNode<T>(tmp1->data);
		tmp2 = tmp2->pNext;
		tmp1 = tmp1->pNext;
	}
	pLast = tmp2;
	pCurr = nullptr;
}

template<typename T>
TList<T>::~TList() {
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

template<typename T>
void TList<T>::insert_first(const T& data_) {
	TNode<T>* tmp = new TNode<T>(data_);
	if (pFirst == pStop) {
		pFirst = tmp;
		pLast = pFirst;
		pCurr = pFirst;
	}
	tmp->pNext = pFirst;
	pFirst = tmp;
	pCurr = pFirst;
}

template<typename T>
void TList<T>::insert_last(const T& data_) {
	if (pFirst == nullptr) {
		insert_first(data_);
	}
	TNode<T>* tmp = pFirst;
	while (tmp->pNext != pStop) {
		tmp = tmp->pNext;
	}
	tmp->pNext = new TNode<T>(data_);
	pLast = tmp->pNext;
}

template<typename T>
void TList<T>::insert_before(const T& data_, const T& next_data_) {
	if (pFirst == nullptr) {
		insert_first(data_);
	}
	TNode<T>* tmp = pFirst;
	TNode<T>* pPrev = nullptr;
	while (tmp->data != next_data_ && tmp != pStop) {
		pPrev = tmp;
		tmp = tmp->pNext;
	}
	if (tmp->data != next_data_ && tmp == pStop) {
		throw "Data not found!";
	}
	TNode<T>* node = new Node<T>(data_);
	node->pNext = tmp;
	if (pPrev == nullptr) {
		pFirst = node;
	}
	else pPrev->pNext = node;
}

template<typename T>
void TList<T>::insert_after(const T& data_, const T& next_data_) {
	if (pFirst == nullptr) {
		insert_first(data_);
	}
	TNode<T>* tmp = pFirst;
	while (tmp->data != next_data_ && tmp != pStop) {
		tmp = tmp->pNext;
	}
	if (tmp->data != next_data_ && tmp == pStop) {
		throw "exp!";
	}
	TNode<T>* node = new Node<T>(data_);
	node->pNext = tmp->pNext;
	tmp->pNext = node;
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
	TNode<T>* tmp = new Node<T>();
	if (tmp == nullptr) {
		throw ("exp");
	}
}

template<typename T>
void TList<T>::reset() {
	pCurr = pFirst;
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
bool TList<T>::Is_End() {
	return (pCurr == nullptr || pCurr == pStop);
}

#endif 