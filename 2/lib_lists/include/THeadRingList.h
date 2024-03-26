#ifndef _THEADRINGLIST_H
#define _THEADRINGLIST_H
#include <iostream>
#include <algorithm> 
#include "list.h"
using namespace std;

template <typename T>
class THeadRingList : public TList<T> {
public:
    TNode<T>* pHead;

    THeadRingList();
    THeadRingList(const THeadRingList& ringL);
    ~THeadRingList();
    void InsertFirst(const T& data);
    void insert_sort(const T& data);
};

template <typename T>
THeadRingList<T>::THeadRingList() : TList<T>(), pHead(nullptr) {}

template <typename T>
THeadRingList<T>::THeadRingList<T>(const THeadRingList& ringL) : TList(ringL) {
    pHead = new TNode<T>(ringL.pHead->data);
    if (ringL.IsEmpty()) {
        pHead->pNext = pHead;
    }
    else {
        pHead->pNext = pFirst;
    }
    pLast->pNext = pHead;
    pStop = pHead;
}

template <typename T>
THeadRingList<T>::~THeadRingList() {
    delete pHead;
}

template <typename T>
void THeadRingList<T>::InsertFirst(const T& data) {
    if (pHead == nullptr) {
        TNode<T>* new_head = new TNode<T>(data);
        pHead = new_head;
        pHead->pNext = pHead;
        pStop = pHead;
        return;
    }
    insert_first(data);
    pHead->pNext = pFirst;
    pStop = pHead;
    pLast->pNext = pHead;
}

template <typename T>
void THeadRingList<T>::insert_sort(const T& data) {
    if (IsEmpty() || pFirst->data < data) {
        InsertFirst(data);
        return;
    }
    TNode<T>* tmp = pFirst;
    while (tmp->pNext != pStop && tmp->pNext->data < data) {
        tmp = tmp->pNext;
    }
    if (tmp->pNext->data == data) {
        tmp->pNext->data = tmp->pNext->data + data;
    }
    else {
        insert_before(data, tmp->pNext->data);
    }
}

#endif 