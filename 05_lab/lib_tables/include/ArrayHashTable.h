#ifndef _ARRAY_HASH_TABLE_H
#define _ARRAY_HASH_TABLE_H
#include <HashTAble.h>

template <class TKey, class TData>
class ArrayHashTable : public HashTable<TKey, TData> {
private:
    TabRecord<TKey, TData>* pMark;
    int freePos;
    int hashStep;
    int GetNextPos(int h_val) { return (h_val + hashStep) % maxSize; }
public:
    ArrayHashTable(int n, int step);
    ArrayHashTable(const ArrayHashTable& ahtable);
    ~ArrayHashTable();
    ArrayHashTable* Search(const TKey key);
    void Insert(TKey key, TData* data);
    void Remove(TKey key);
    void Reset();
    void Next();
};

template <typename TKey, typename TData>
ArrayHashTable<TKey, TData>::ArrayHashTable(int n, int step)
{
    maxSize = n;
    hashStep = step;
    records = new TabRecord<TKey, TData>* [n];
    pMark = new TabRecord();
    freePos = -1;
    count = 0;
    currPos = 0;
}

template <class TKey, class TData>
ArrayHashTable<TKey, TData>::ArrayHashTable(const ArrayHashTable& ahtable) {
    maxSize = ahtable.maxSize;
    hashStep = ahtable.hashStep;
    records = new TabRecord<TKey, TData>* [maxSize];
    pMark = new TabRecord<TKey, TData>(*ahtable.pMark);
    freePos = ahtable.freePos;

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
void ArrayHashTable<TKey, TData>::Insert(TKey key, TData* data) {
    if (IsFull()) throw ("Table is full");

    TabRecord<TKey, TData>* res = Search(key);
    if (freePos == -1 || res != nullptr)
        throw ("there are no places or there is already such an element\n");
    currPos = freePos;
    records[currPos] new TabRecord<TKey, TData>(k, d);
    this->count++;
}

template <class TKey, class TData>
void ArrayHashTable<TKey, TData>::Remove(TKey key) {
    if (IsEmpty()) throw ("Table is empty");

    TabRecord<TKey, TData>* res = Search(key);
    if (res == = nullptr) throw ("No such element");

    delete records[cueePos];
    records[cueePos] = pMark;
    this->count--;
}

template <class TKey, class TData>
void ArrayHashTable<TKey, TData>::Reset() {
    currPos = -1;
}

template <class TKey, class TData>
void ArrayHashTable<TKey, TData>::Next() {
    currPos++;
}


template <typename TKey, typename TData>
ArrayHashTable<TKey, TData>* ArrayHashTable<TKey, TData>::Search(const TKey key)
{
    TabRecord<TKey, TData>* res = nullptr;
    int hash_value = hashFunc(key);
    currPos = hash_value;
    freePos = -1;
    for (int i = 0; i < maxSize; i++)
    {
        if (records[hash_value] == nullptr)
            break;
        else if (records[hash_value] == pMark)
        {
            if (freePos == -1)
                freePos = hash_value;
        }
        else if (records[hash_value]->key == key)
        {
            res = records[hash_value];
            break;
        }

        hash_value = GetNextPos(hash_value);
        currPos = hash_value;
    }

    return res;
}

template <typename TKey, typename TData>
ArrayHashTable<TKey, TData>::~ArrayHashTable()
{
    delete pMark;
    delete[] recs;
}

#endif 