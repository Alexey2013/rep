#ifndef _THEADRINGLIST_H
#define _THEADRINGLIST_H
#include <iostream>
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
    void InsertLast(const T& data);
    void InsertToSort(const T& data);
    void InsertBefore(const T& data, const T& nextdata);
};

template <typename T>
THeadRingList<T>::THeadRingList() : TList<T>(), pHead(nullptr) {}

template <typename T>
THeadRingList<T>::THeadRingList(const THeadRingList<T>& ringL) : TList<T>(ringL), pHead(nullptr) {
    if (!ringL.IsEmpty()) {
        pHead = new TNode<T>(ringL.pHead->data);
        TNode<T>* srcCurr = ringL.pHead->pNext;
        TNode<T>* destPrev = pHead;
        while (srcCurr != ringL.pHead) {
            TNode<T>* newNode = new TNode<T>(srcCurr->data);
            destPrev->pNext = newNode;
            destPrev = newNode;
            srcCurr = srcCurr->pNext;
        }
        destPrev->pNext = pHead;
    }
}

template <typename T>
THeadRingList<T>::~THeadRingList() {
    delete pHead;
}

template <typename T>
void THeadRingList<T>::InsertFirst(const T& data) {
    TNode<T>* newNode = new TNode<T>(data);
    if (IsEmpty()) {
        pHead = newNode;
        pHead->pNext = pHead;
    }
    else {
        newNode->pNext = pHead->pNext;
    }
    pHead->pNext = newNode;
    pFirst = newNode;
}

template <typename T>
void THeadRingList<T>::InsertLast(const T& data) {
    if (IsEmpty()) {
        InsertFirst(data);
        return;
    }
    TNode<T>* newNode = new TNode<T>(data);
    newNode->pNext = pHead->pNext;
    pHead->pNext = newNode;
    pHead = newNode;
}

template <typename T>
void THeadRingList<T>::InsertBefore(const T& data, const T& nextdata) {
    TNode<T>* newNode = new TNode<T>(data);
    TNode<T>* curr = pHead->pNext;
    while (curr != pHead && curr->data != nextdata) {
        curr = curr->pNext;
    }
    if (curr != pHead) {
        newNode->pNext = curr->pNext;
        curr->pNext = newNode;
    }
    else {
        delete newNode;
    }
}

template <typename T>
void THeadRingList<T>::InsertToSort(const T& data) {
    if (IsEmpty() || data < pHead->pNext->data) {
        InsertFirst(data);
        return;
    }
    TNode<T>* curr = pHead->pNext;
    while (curr->pNext != pHead && data < curr->pNext->data) {
        curr = curr->pNext;
    }
    if (curr->pNext->data == data) {
        curr->pNext->data= curr->pNext->data+ data;
    }
    else {
        InsertBefore(data, curr->data);
    }
}

#endif 