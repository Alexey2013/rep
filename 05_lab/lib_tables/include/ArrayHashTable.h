#ifndef _ARRAY_HASH_TABLE_H
#define _ARRAY_HASH_TABLE_H
#include <HashTAble.h>

template <class TKey, class TData>
class ArrayHashTable : public HashTable<TKey, TData> {
private:
    TabRecord<TKey, TData>** records;
    TabRecord<TKey, TData>* pMark;
    int freePos;
    int hashStep;
    int GetNextPos(int h_val);
public:
    ArrayHashTable(int n, int step);
    ArrayHashTable(const ArrayHashTable& ahtable);
    ~ArrayHashTable();
    ArrayHashTable* Search(const TKey key);
    void Insert(TKey key, TData* data);
    void Remove(TKey key);
    void Reset();
    void Next();
    bool IsEnded() const;
};

template <class TKey, class TData>
ArrayHashTable<TKey, TData>::ArrayHashTable(const ArrayHashTable& ahtable) {
    maxSize = ahtable.maxSize;
    hashStep = ahtable.hashStep;
    records = new TabRecord<TKey, TData>* [maxSize];
    pMark = new TabRecord<TKey, TData>(*ahtable.pMark);
    freePos = ahtable.freePos;
    // Copy the records
    for (int i = 0; i < maxSize; ++i) {
        if (ahtable.records[i] == nullptr)
            records[i] = nullptr;
        else if (ahtable.records[i] == ahtable.pMark)
            records[i] = pMark;
        else
            records[i] = new TabRecord<TKey, TData>(*ahtable.records[i]);
    }
}

template <class TKey, class TData>
ArrayHashTable<TKey, TData>::~ArrayHashTable() {
    delete pMark;
    for (int i = 0; i < maxSize; ++i) {
        if (records[i] != nullptr && records[i] != pMark)
            delete records[i];
    }
    delete[] records;
}

template <class TKey, class TData>
void ArrayHashTable<TKey, TData>::Insert(TKey key, TData* data) {
    if (Search(key) != nullptr) {
        // Key already exists, update the data
        Search(key)->SetData(data);
        return;
    }
    int pos = hashFunc(key);
    while (records[pos] != nullptr && records[pos] != pMark)
        pos = GetNextPos(pos);
    if (records[pos] == nullptr || records[pos] == pMark) {
        if (records[pos] == nullptr)
            freePos = pos;
        records[pos] = new TabRecord<TKey, TData>(key, data);
    }
}

template <class TKey, class TData>
void ArrayHashTable<TKey, TData>::Remove(TKey key) {
    int pos = hashFunc(key);
    while (records[pos] != nullptr) {
        if (records[pos] != pMark && records[pos]->GetKey() == key) {
            delete records[pos];
            records[pos] = pMark;
            return;
        }
        pos = GetNextPos(pos);
    }
}

template <class TKey, class TData>
void ArrayHashTable<TKey, TData>::Reset() {
    currPos = -1;
}

template <class TKey, class TData>
void ArrayHashTable<TKey, TData>::Next() {
    currPos++;
}

template <class TKey, class TData>
bool ArrayHashTable<TKey, TData>::IsEnded() const {
    return currPos >= maxSize;
}

template <class TKey, class TData>
ArrayHashTable<TKey, TData>::ArrayHashTable(int n, int step) {
    maxSize = n;
    hashStep = step;
    records = new TabRecord<TKey, TData>* [n];
    pMark = new TabRecord<TKey, TData>();
    freePos = -1;
}

template <class TKey, class TData>
ArrayHashTable<TKey, TData>* ArrayHashTable<TKey, TData>::Search(const TKey key) {
    TabRecord<TKey, TData>* res = nullptr;
    currPos = hashFunc(key);
    freePos = -1;
    for (int i = 0; i < maxSize; i++) {
        if (records[currPos] == nullptr)
            break;
        else if (records[currPos] == pMark) {
            if (freePos == -1)
                freePos = currPos;
        }
        else if (records[currPos]->GetKey() == key) {
            res = records[currPos];
            break;
        }
        currPos = GetNextPos(currPos);
    }
    // Do something with res here
    return nullptr;
}
#endif 