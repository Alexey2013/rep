#ifndef _LIST_H
#define _LIST_H
#include "node.h"
#include <iostream>
using namespace std;

template <typename T>
class TList{
protected:
	TNode<T>* pFirst;
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
	bool IsEnded()const;
	TNode<T>* GetCurrent() const;
	void next();  
	void reset(); 
	void sort();
};

template<typename T>
TList<T>::TList() {
	pFirst = nullptr;
	pLast = nullptr;
	pCurr = nullptr;
	pStop = nullptr;
}

template <typename T>
TList<T>::TList( TNode<T>* _pFirst){
	pFirst = _pFirst;
	TNode<T>* tmp = _pFirst;
	while (tmp->pNext != nullptr)
		tmp = tmp->pNext;
	pLast = tmp;
	pCurr = pFirst;
	pStop = nullptr;
}

template <typename T>
TList<T>::TList(const TList<T>& list){
	if (list.IsEmpty()){
		pFirst = nullptr;
		pLast = nullptr;
		pCurr = nullptr;
		pStop = nullptr;
	}
	pFirst = new TNode<T>(list.pFirst->data);
	TNode<T>* tmp = pFirst;
	TNode<T>* tmp2 = list.pFirst->pNext;
	while (tmp2 != list.pStop){
		tmp->pNext = new TNode<T>(tmp2->data);
		tmp = tmp->pNext;
		tmp2 = tmp2->pNext;
	}
	pLast = tmp;
	pCurr = pFirst;
	pStop = nullptr;
}

template<typename T>
void TList<T>::clear() {
	if (pFirst == nullptr) return;
	TNode<T>* curr = pFirst;
	TNode<T>* next = pFirst->pNext;
	while (next != pStop) {
		delete curr;
		curr = next;
		next = curr->pNext;
	}
	delete curr;
	pCurr = pStop;
	pFirst = nullptr;
	pLast = nullptr;
}

template <typename T>
TList<T>::~TList(){
	clear();
}

template<typename T>
TNode<T>* TList<T>::search(const T& _data) {
	TNode<T>* tmp = pFirst;
	while (tmp != nullptr && tmp->data != _data) {
		tmp = tmp->pNext;
	}
	if (tmp == nullptr ) {
		throw "Data not found!";
	}
	return tmp;
}

template <typename T>
void TList<T>::insert_first(const T& data){
	pFirst = new TNode<T>(data, pFirst == pStop ? pStop : pFirst);
	if (pLast == pStop)
		pLast = pFirst;
	pCurr = pFirst;
}

template <typename T>
void TList<T>::insert_last(const T& data){
	if (pFirst == pStop){
		insert_first(data);
		return;
	}
		pLast->pNext = new TNode<T>(data);
		pLast = pLast->pNext;
	}


template <typename T>
void TList<T>::insert_after(const T& data, const T& beforedata){
	TNode<T>* pPrev = search(beforedata);
	if (pPrev == pStop) throw("Data not found!"); 
	if (pPrev->pNext == pStop) insert_last(data);
	else{
		TNode<T>* pNode = new TNode<T>(data, pPrev->pNext);
		pPrev->pNext = pNode;
		}
	}

template <typename T>
void TList<T>::insert_before(const T& data, const T& nextdata) {
	TNode<T>* pPrev = nullptr;

	if (pFirst != pStop && pFirst->data == nextdata) {
		insert_first(data);
	}
	else {
		TNode<T>* tmp = pFirst;
		while (tmp != pStop && tmp->data != nextdata) {
			pPrev = tmp;
			tmp = tmp->pNext;
		}
		if (tmp == pStop) {
			throw std::runtime_error("Data not found!");
		}
		TNode<T>* pNode = new TNode<T>(data, tmp);
		if (pPrev != nullptr) {
			pPrev->pNext = pNode;
		}
		else {
			pFirst = pNode;
		}
	}
}

template<typename T>
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
	if (tmp == nullptr)
		return true;
	delete tmp;
	return false;
}

template<typename T>
bool TList<T>::IsEnded()const {
	return pCurr == pStop;
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


#endif 