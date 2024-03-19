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
	TNode<T>* GetCurrent() const;
	void next();  
	void reset(); 
	void print() const; // <<
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
	pCurr = pFirst;
	pStop = nullptr;
	TNode<T>* tmp = pFirst;
	while (tmp->pNext != pStop)
		tmp = tmp->pNext;
	pLast = tmp;
}

template <typename T>
TList<T>::TList(const TList<T>& list){
	if (list.pFirst == nullptr) return ;
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
	pCurr = pFirst;
	pStop = tmp2->pNext;
	pLast = tmp2;
}

template<typename T>
void TList<T>::clear() {
	while (pFirst != nullptr) {
		TNode<T>* tmp = pFirst;
		pFirst = pFirst->pNext;
		delete tmp;
	}
		pCurr = pStop;
		pLast = pStop;
}

template <typename T>
TList<T>::~TList(){
	clear();
}

template<typename T>
TNode<T>* TList<T>::search(const T& data_) {
	TNode<T>* tmp = pFirst;
	while (tmp != nullptr && tmp->data != data_) {
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
	if (pFirst != pStop && pFirst->data == nextdata) { insert_first(data); }
	else{
		TNode<T>* tmp = pFirst;
		pPrev = nullptr;
		while (tmp != pStop && tmp->data != nextdata){
			pPrev = tmp;
			tmp = tmp->pNext;
		}
		if (tmp == pStop) throw("Data not found!");
		TNode<T>* pNode = new TNode<T>(data, tmp);
		pPrev->pNext = pNode;
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
	if (tmp == nullptr) {
		throw ("exp");
	}
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