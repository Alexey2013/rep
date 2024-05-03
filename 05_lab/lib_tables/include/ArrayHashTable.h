#ifndef _ARRAY_HASH_TABLE_H
#define _ARRAY_HASH_TABLE_H
#include <HashTAble.h>

template <typename TKey, typename TData>
class ArrayHashTable : public HashTable<TKey, TData> {
private:
    TabRecord<TKey, TData>* pMark;
    TabRecord<TKey, TData>** recs;
    int freePos;
    int hashStep;
    int GetNextPos(int pos) { return (pos + hashStep) % maxSize; }
public:
    ArrayHashTable(int n, int step);
    ArrayHashTable(const ArrayHashTable& ahtable);
    ~ArrayHashTable();
    TabRecord <TKey, TData>* Find(const TKey key);
    void Insert(TKey key, TData* data);
    void Remove(TKey key);
    void Reset();
    void Next();
    TabRecord<TKey, TData>* GetCurrent() const;
    virtual int hashFunc(const TKey key) override {
        return static_cast<int>(key) % this->maxSize;
    }
};

//template <typename TKey, typename TData>
//ArrayHashTable<TKey, TData>::ArrayHashTable(int n, int step) : HashTable<TKey,TData>(n)
//{
//    maxSize = n;
//    hashStep = step;
//    recs = new TabRecord<TKey, TData>* [n];
//    pMark = new TabRecord<TKey, TData>(0,"");
//    freePos = -1;
//    count = 0;
//    currPos = 0;
//}
//
//template <typename TKey, typename TData>
//ArrayHashTable<TKey, TData>::ArrayHashTable(const ArrayHashTable& ahtable) {
//    maxSize = ahtable.maxSize;
//    hashStep = ahtable.hashStep;
//    recs = new TabRecord<TKey, TData>* [maxSize];
//    pMark = new TabRecord<TKey, TData>(*ahtable.pMark);
//    freePos = ahtable.freePos;
//
//    for (int i = 0; i < maxSize; ++i) {
//        if (ahtable.recs[i] == nullptr)
//            recs[i] = nullptr;
//        else if (ahtable.recs[i] == ahtable.pMark)
//            recs[i] = pMark;
//        else
//            recs[i] = new TabRecord<TKey, TData>(*ahtable.recs[i]);
//    }
//}
//
//template <typename TKey, typename TData>
//void ArrayHashTable<TKey, TData>::Insert(TKey key, TData* data) {
//    if (IsFull()) throw ("Table is full");
//
//    TabRecord<TKey, TData>* res = Find(key);
//    if (freePos == -1 || res != nullptr)
//        throw ("there are no places or there is already such an element\n");
//    currPos = freePos;
//    recs[currPos] =new TabRecord<TKey, TData>(key, data);
//    this->count++;
//}
//
//template <typename TKey, typename TData>
//void ArrayHashTable<TKey, TData>::Remove(TKey key) {
//    if (IsEmpty()) throw ("Table is empty");
//
//    TabRecord<TKey, TData>* res = Find(key);
//    if (res ==  nullptr) throw ("No such element");
//
//    delete recs[currPos];
//    recs[currPos] = pMark;
//    this->count--;
//}
//
//template <typename TKey, typename TData>
//void ArrayHashTable<TKey, TData>::Reset() {
//    currPos = 0;
//}
//
//template <typename TKey, typename TData>
//void ArrayHashTable<TKey, TData>::Next() {
//    currPos++;
//}
//
//template <typename TKey, typename TData>
//TabRecord<TKey, TData>* ArrayHashTable<TKey, TData>::Find(const TKey key) {
//    TabRecord<TKey, TData>* res = nullptr;
//    int hash_value = this->hashFunc(key); 
//    this->currPos = hash_value;
//    this->freePos = -1;
//
//    for (int i = 0; i < this->maxSize; i++) {
//        if (this->recs[hash_value] == nullptr) {
//            break; 
//        }
//        else if (this->recs[hash_value] == this->pMark) {
//            if (this->freePos == -1) {
//                this->freePos = hash_value; 
//            }
//        }
//        else if (this->recs[hash_value]->GetKey() == key) {
//            res = this->recs[hash_value];
//            break;
//        }
//
//        hash_value = this->GetNextPos(hash_value); 
//        this->currPos = hash_value;
//    }
//
//    return res;
//}
//
//template <typename TKey, typename TData>
//ArrayHashTable<TKey, TData>::~ArrayHashTable()
//{
//    for (int i = 0; i < maxSize; i++)
//    {
//        if (recs[i] != nullptr && recs[i] != pMark)
//            delete recs[i];
//    }
//    delete pMark;
//    delete[] recs;
//}
//
//template <typename TKey, typename TData>
//TabRecord<TKey, TData>* ArrayHashTable<TKey, TData>::GetCurrent() const {
//    if (this->currPos == -1 || this->currPos >= this->maxSize || this->recs[this->currPos] == nullptr) {
//        return nullptr; 
//    }
//
//    return this->recs[this->currPos];
//}


#endif 