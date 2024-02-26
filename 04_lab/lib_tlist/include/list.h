#ifndef _LIST_H
#define _LIST_H
#include <iostream>
#include <string>
#include <map>
#include <vector>
using namespace std;

class TData {
public:
	virtual TData* copy() const = 0;
	virtual bool operator <(const TData& data)const = 0;
	virtual bool operator <=(const TData& data)const = 0;
	virtual bool operator >(const TData& data)const = 0;
	virtual bool operator >=(const TData& data)const = 0;
	virtual bool operator ==(const TData& data)const = 0;
	virtual bool operator !=(const TData& data)const = 0;
};

struct TNode
{
	TData* data;
	TNode* pNext = nullptr;
};

class TList {
protected:
	TNode* pFirst;
	TNode* pStop;
	TNode* pCurr;
	TNode* pLast;
public:
	//TList();
//	TList(const TNode* _pFirst);
//	TList(const TList& obj);
//	virtual ~TList();
//	TNode* Search(const TData& data);
//	void InsertFirst(const TData& data);
//	void InsertLast(const TData& data);
//	void InsertBefore(const TData& data, const TData& before);
//	void InsertAfter(const TData& data, const TData& after);
//	void InsertBefore(const TData& data);
//	void InsertAfter(const TData& data);
//	void Remove(const TData& data);
//	void Clear();
//	size_t GetSize() const;
//	bool IsFull() const;
//	bool IsEmpty() const;
//	void Reset();
//	TNode* GetCurrent() const;
//	void Next();
//	bool IsEnded() const;
//};
//
//TList::TList() {
//	pFirst = nullptr;
//	pStop = nullptr;
//	pCurr = nullptr;
//	pLast = nullptr;
//}
//
//TList::TList(const TNode* _pFirst) {
//}
//
//TList::TList(const TList& obj) {
//	pStop = obj.pStop;
//	pFirst = obj.pFirst;
//	pCurr = obj.pCurr;
//	pLast = obj.pLast;
};

//TList::~TList() {
//	Clear();
//}
//
//TNode* TList::Search(const TData& data) {
//	TNode* pNode = pFirst;
//
//	while (pNode != pStop) {
//		if (*(pNode->data) == data) {
//			return pNode;
//		}
//		pNode = pNode->pNext;
//	}
//	return nullptr;
//}
//
//void TList::InsertFirst(const TData& data) {
//	TNode* pNode = new TNode;
//	pNode->data = data.copy();
//
//	if (pFirst == pStop) {
//		pNode->pNext = pStop;
//		pLast = pNode;
//	}
//	else {
//		pNode->pNext = pFirst;
//	}
//
//	pFirst = pNode;
//}
//
//void TList::InsertLast(const TData& data) {
//	if (pLast == pStop) {
//		InsertFirst(data);
//	}
//	else {
//		TNode* pNode = new TNode;
//		pNode->data = data.copy();
//		pNode->pNext = pStop;
//
//		pLast->pNext = pNode;
//		pLast = pNode;
//	}
//}
//
//void TList::InsertBefore(const TData& data, const TData& before) {
//	if (pFirst == pStop || *(pFirst->data) == before) {
//		InsertFirst(data);
//	}
//	else {
//		TNode* pNode = new TNode;
//		pNode->data = data.copy();
//
//		TNode* prevNode = pFirst;
//		TNode* currNode = pFirst->pNext;
//
//		while (currNode != pStop) {
//			if (*(currNode->data) == before) {
//				pNode->pNext = currNode;
//				prevNode->pNext = pNode;
//				return;
//			}
//			prevNode = currNode;
//			currNode = currNode->pNext;
//		}
//	}
//}
//
//void TList::InsertAfter(const TData& data, const TData& after) {
//	TNode* pNode = new TNode;
//	pNode->data = data.copy();
//
//	TNode* currNode = pFirst;
//
//	while (currNode != pStop) {
//		if (*(currNode->data) == after) {
//			pNode->pNext = currNode->pNext;
//			currNode->pNext = pNode;
//			if (currNode == pLast) {
//				pLast = pNode;
//			}
//			return;
//		}
//		currNode = currNode->pNext;
//	}
//
//	delete pNode;
//}
//
//
//void TList::InsertBefore(const TData& data) {
//	InsertBefore(data, *(pCurr->data));
//}
//
//void TList::InsertAfter(const TData& data) {
//	if (pCurr != pStop) {
//		InsertAfter(data, *(pCurr->data));
//	}
//	else {
//		InsertLast(data);
//	}
//}
//
//void TList::Remove(const TData& data) {
//	if (pFirst == pStop) {
//		return;
//	}
//
//	if (*(pFirst->data) == data) {
//		TNode* pTemp = pFirst;
//		pFirst = pFirst->pNext;
//
//		if (pFirst == pStop) {
//			pLast = pStop;
//		}
//		delete pTemp;
//		return;
//	}
//	TNode* prevNode = pFirst;
//	TNode* currNode = pFirst->pNext;
//	while (currNode != pStop) {
//		if (*(currNode->data) == data) {
//			prevNode->pNext = currNode->pNext;
//
//			if (currNode == pLast) {
//				pLast = prevNode;
//			}
//
//			delete currNode;
//			return;
//		}
//		prevNode = currNode;
//		currNode = currNode->pNext;
//	}
//}
//
//void TList::Clear() {
//	while (pFirst != pStop) {
//		TNode* tmp = pFirst;
//		pFirst = tmp->pNext;
//		delete tmp;
//	}
//	pCurr = pStop;
//	pLast = pStop;
//}
//
//size_t TList::GetSize() const {
//	size_t size = 0;
//	TNode* tmp = pFirst;
//	while (tmp != pStop) {
//		tmp = tmp->pNext;
//		size++;
//	}
//	return size;
//}
//
//bool TList::IsFull() const {
//	try {
//		TNode* tmp = new TNode;
//		delete tmp;
//		return false;
//	}
//	catch (...) {return true;}
//}
//
//bool TList::IsEmpty() const {
//	return (pFirst == pStop);
//}
//
//void TList::Reset() {
//	pCurr = pFirst;
//}
//
//TNode* TList::GetCurrent() const {
//	return pCurr;
//}
//
//void TList::Next() {
//	if (!IsEnded())
//	pCurr = pCurr->pNext;
//	else
//	Reset();
//}
//
//bool TList::IsEnded() const {
//	return (pCurr == pStop);
//}
//
class THeadRingList : public TList {
private:
	TNode* pHead;
public:

};

#endif 