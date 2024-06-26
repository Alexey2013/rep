#ifndef _THEADRINGLIST_H
#define _THEADRINGLIST_H
#include "list.h"

template <typename T>
class THeadRingList : public TList<T> {
private:
    TNode<T>* pHead;
public:
    THeadRingList();
    THeadRingList(const THeadRingList& ringL);
    virtual ~THeadRingList();
    void insert_first(const T& data);
    void remove(const T& data);
};

template <typename T>
THeadRingList<T>::THeadRingList() : TList<T>() {
    pHead = new TNode<T>();
    pStop = pHead;
}

template <typename T>
THeadRingList<T>::THeadRingList(const THeadRingList<T>& ringL) : TList<T>(ringL) {
    pHead = new TNode<T>(ringL.pHead->data, pFirst);
    if (!ringL.IsEmpty()) {
        pLast->pNext = pHead;
    }
    pStop = pHead;
}

template <typename T>
THeadRingList<T>::~THeadRingList() {
    delete pHead;
}

template <typename T>
void THeadRingList<T>::insert_first(const T& data) {
    TList<T>::insert_first(data);
    pHead->pNext = pFirst;
    pStop = pHead;
    pLast->pNext = pHead;
}

template <typename T>
void THeadRingList<T>::remove(const T& data) {
    TNode<T>* curr = pFirst;
    if (curr->data == data) {
        if (curr->pNext == pHead) {
            delete curr;
            pFirst = nullptr;
            pCurr = nullptr;
            pLast = nullptr;
            pHead->pNext = nullptr;
            return;
        }
        pFirst = pFirst->pNext;
        pHead->pNext = pFirst;
        delete curr;
        return;
    }
    TList<T>::remove(data);
}

#endif 