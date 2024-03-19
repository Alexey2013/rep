#ifndef _THEADRINGLIST_H
#define _THEADRINGLIST_H
#include <iostream>
#include "list.h"
using namespace std;

template <typename T>
class THeadRingList : public TList<T> {
private:
	TNode<T>* pHead;
public:
	THeadRingList();
	THeadRingList(const TNode<T>* _pFirst);
	THeadRingList(const TList<T>& obj);
	THeadRingList(const THeadRingList<T>& obj);
	virtual ~THeadRingList();
};

#endif 