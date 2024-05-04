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
    void Next();
    TabRecord<TKey, TData>* GetCurrent() const;
    friend std::ostream& operator<<(std::ostream& out, const ArrayHashTable<TKey, TData>& t)
    {
        for (int i = 0; i < t.maxSize; ++i)
        {
            if (t.recs[i] != nullptr)
            {
                out << *(t.recs[i]); 
            }
        }
        return out;
    }
};

template <typename TKey, typename TData>
ArrayHashTable<TKey, TData>::ArrayHashTable(int n, int step) : HashTable<TKey, TData>(n) {
    maxSize = n;
    hashStep = step;
    recs = new TabRecord<TKey, TData>* [n];

    for (int i = 0; i < n; ++i) {
        recs[i] = nullptr; 
    }

    pMark = new TabRecord<TKey, TData>();
    freePos = -1;
    count = 0;
    currPos =0;
}

template <typename TKey, typename TData>
ArrayHashTable<TKey, TData>::ArrayHashTable(const ArrayHashTable& ahtable)
    : HashTable<TKey, TData>(ahtable.maxSize) {

    maxSize = ahtable.maxSize;
    hashStep = ahtable.hashStep;
    currPos = ahtable.currPos;
    recs = new TabRecord<TKey, TData>* [maxSize];
    pMark = new TabRecord<TKey, TData>();
    freePos = ahtable.freePos;

    for (int i = 0; i < maxSize; ++i) {
        if (ahtable.recs[i] == nullptr) {
            recs[i] = nullptr;
        }
        else if (ahtable.recs[i] == ahtable.pMark) {
            recs[i] = pMark;
        }
        else {
            recs[i] = new TabRecord<TKey, TData>(*ahtable.recs[i]); 
        }
    }
}

template <typename TKey, typename TData>
void ArrayHashTable<TKey, TData>::Insert(TKey key, TData* data) {
    if (IsFull()) throw ("Table is full");

    TabRecord<TKey, TData>* res = Find(key);
    if (freePos == -1 || res != nullptr)
        throw ("there are no places or there is already such an element");
    currPos = freePos;
    recs[currPos] =new TabRecord<TKey, TData>(key, data);
    count++;
}

template <typename TKey, typename TData>
void ArrayHashTable<TKey, TData>::Remove(TKey key) {
    if (IsEmpty()) throw ("Table is empty");

    TabRecord<TKey, TData>* res = Find(key);
    if (res ==  nullptr) throw ("No such element");

    delete recs[currPos];
    recs[currPos] = pMark;
    count--;
}

template <typename TKey, typename TData>
TabRecord<TKey, TData>* ArrayHashTable<TKey, TData>::Find(const TKey key) {
    int hash_value = hashFunc(key);
    currPos = hash_value; 
    freePos = -1; 

    TabRecord<TKey, TData>* res = nullptr; 

    for (int i = 0; i < maxSize; i++) {
        if (recs[currPos] == nullptr) {
            if (freePos == -1) {
                freePos = currPos; 
            }
            break; 
        }
        else if (recs[currPos] == pMark) {
            if (freePos == -1) {
                freePos = currPos; 
            }
        }
        else if (recs[currPos]->GetKey() == key) {
            res = recs[currPos]; 
            break;
        }
        else
        currPos = GetNextPos(currPos);
    }

    return res; 
}

template <typename TKey, typename TData>
ArrayHashTable<TKey, TData>::~ArrayHashTable()
{
    delete pMark;
    delete[] recs;
}

template <typename TKey, typename TData>
TabRecord<TKey, TData>* ArrayHashTable<TKey, TData>::GetCurrent() const {
    if (currPos == -1 || currPos >= maxSize || recs[currPos] == nullptr) {
        return nullptr; 
    }

    return recs[currPos];
}

template <typename TKey, typename TData>
void ArrayHashTable<TKey, TData>::Next() {
    if (currPos >= 0 && currPos < maxSize) {
        currPos = GetNextPos(currPos); 
    }
}

#endif 