#ifndef _TABLE_H
#define _TABLE_H
#include "TabRecord.h"

template <typename TKey, typename TData>
class Table {
private:
    int count;
    int maxSize;
    int currPos;
public:
    Table(int maxSize);
    virtual TabRecord<TKey, TData>* Find(TKey key) = 0;
    virtual void Insert(TKey key, TData* data) = 0;
    virtual void Remove(TKey key) = 0;
    bool IsFull() const;
    bool IsEmpty() const;
    virtual void Reset();
    virtual void Next();
    virtual bool IsEnded() const;
    virtual TKey GetKey() = 0;
    virtual TData* GetData() = 0;
};

template <typename TKey, typename TData>
Table<TKey, TData>::Table(int maxSize) : count(0), maxSize(maxSize), currPos(0) {}

template <typename TKey, typename TData>
bool Table<TKey, TData>::IsFull() const {
    return (count == maxSize);
}

template <typename TKey, typename TData>
bool Table<TKey, TData>::IsEmpty() const {
    return (count == 0);
}

template <typename TKey, typename TData>
void Table<TKey, TData>::Reset() {
    currPos = 0;
}

template <typename TKey, typename TData>
void Table<TKey, TData>::Next() {
    currPos++;
    if (IsEnded()) Reset();
}

template <typename TKey, typename TData>
bool Table<TKey, TData>::IsEnded() const {
    return (currPos >= count);
}

#endif 