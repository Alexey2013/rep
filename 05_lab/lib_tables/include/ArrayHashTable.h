#ifndef _ARRAY_HASH_TABLE_H
#define _ARRAY_HASH_TABLE_H
#include <HashTable.h>

template <typename TKey, typename TData>
class ArrayHashTable : public HashTable<TKey, TData> {
private:
    TabRecord<TKey, TData>** recs;
    TabRecord<TKey, TData>* pMark;

    int freePos;
    int hashStep;
    void GetNextPos(int pos);
    virtual size_t hashFunc(const TKey& key) const override;
public:
    ArrayHashTable(int n, int step);
    ArrayHashTable(const ArrayHashTable& ahtable);
    ~ArrayHashTable();

    TabRecord <TKey, TData>* Find(const TKey key);
    void Insert(TKey key, TData* data);
    void Remove(TKey key);
    void Next();
    void Reset();
    TabRecord<TKey, TData>* GetCurrent() const;
    friend ostream& operator<<(ostream& out, const ArrayHashTable<TKey, TData>& t) {
        if (t.IsEmpty()) {
            out << "Table is empty";
            return out;
        }
        for (int i = 0; i < t.maxSize; i++) {
                if (t.recs[i] != nullptr) out << *(t.recs[i]);   
        }
        return out;
    };
};

template <typename TKey, typename TData>
ArrayHashTable<TKey, TData>::ArrayHashTable(int n, int step) : HashTable<TKey, TData>(n) {
    maxSize = n;
    hashStep = step;
    recs = new TabRecord<TKey, TData>* [n];
    pMark = new TabRecord<TKey, TData>();

    for (int i = 0; i < n; ++i) {
        recs[i] = nullptr; 
    }

    freePos = -1;
    count = 0;
    currPos =0;
}

template <typename TKey, typename TData>
ArrayHashTable<TKey, TData>::ArrayHashTable(const ArrayHashTable& ahtable) : HashTable<TKey, TData>(ahtable.maxSize) {
    maxSize = ahtable.maxSize;
    hashStep = ahtable.hashStep;
    currPos = ahtable.currPos;
    recs = new TabRecord<TKey, TData>* [maxSize];
    pMark = new TabRecord<TKey, TData>();

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
        throw ("No space available or duplicate key found");

    currPos = freePos;
    recs[currPos] = new TabRecord<TKey, TData>(key, data);
    count++;
}

template <typename TKey, typename TData>
void ArrayHashTable<TKey, TData>::Remove(TKey key) {
    if (IsEmpty()) throw ("Table is empty");

    TabRecord<TKey, TData>* res = Find(key);
    if (res ==  nullptr) throw ("No such element");

    delete res;
    recs[currPos] = pMark;
    freePos = -1;
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
        else if (recs[currPos] == pMark && freePos == -1){
            freePos = currPos;
        }
        else if (recs[currPos]->GetKey() == key) {
            res = recs[currPos];
            break;  
        }

        currPos = (currPos + hashStep) % maxSize;
    }

    return res;
}

template <typename TKey, typename TData>
ArrayHashTable<TKey, TData>::~ArrayHashTable()
{
    for (int i = 0; i < maxSize; ++i) {
        if (recs[i] != nullptr) {
            delete recs[i];
        }
    }
    delete[] recs;
    delete pMark;
}

template <typename TKey, typename TData>
TabRecord<TKey, TData>* ArrayHashTable<TKey, TData>::GetCurrent() const {
    if (currPos == -1 || currPos >= maxSize || recs[currPos] == nullptr) {
        return nullptr; 
    }

    return recs[currPos];
}

template <typename TKey, typename TData>
void ArrayHashTable<TKey, TData>::GetNextPos(int pos) {
    return (pos + hashStep) % maxSize;
}

template <typename TKey, typename TData>
void ArrayHashTable<TKey, TData>::Reset() {
    currPos = 0;
    while (!IsEnded() && (recs[currPos] == nullptr || recs[currPos] == pMark))
    {
        currPos++;
    }
}

template <typename TKey, typename TData>
void ArrayHashTable<TKey, TData>::Next()  {
    if (IsEnded())  throw ("table is ended");
    currPos++;
    while (!IsEnded() && (recs[currPos] == nullptr || recs[currPos] == pMark))
    {
        currPos++;
    }
}

template<class TKey, class TData>
size_t ArrayHashTable<TKey, TData>::hashFunc(const TKey& key) const
{
    return std::hash<TKey>{}(key) % maxSize;
}

template <typename string, typename TPolynom>
class PolynomialHashTable : public ArrayHashTable<string, TPolynom> {
    size_t hashFunc(const string& key) const { 
        uint64_t hashValue = 0;
        for (char ch : key) {
            hashValue +=ch;
        }
        return (hashValue % maxSize);
    }

public:
    PolynomialHashTable(int n, int step) : ArrayHashTable<string, TPolynom>(n, step) {}
};


#endif 