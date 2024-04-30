#ifndef _SCAN_TABLE_H
#define _SCAN_TABLE_H
#include <table.h>

template <typename TKey, typename TData>
class ScanTable : public Table<TKey, TData> {
protected:
    TabRecord<TKey, TData>** recs;
public:
    ScanTable(int maxSize);
    ScanTable(const ScanTable<TKey, TData>& t);
    ~ScanTable();
    TabRecord<TKey, TData>* Find(TKey key) const;
    void Insert(TKey key, TData* data);
    void Remove(TKey key);
    virtual TabRecord<TKey, TData>* GetCurrent() const;
};

template <typename TKey, typename TData>
ScanTable<TKey, TData>::ScanTable(int maxSize) : Table<TKey, TData>(maxSize) {
    recs = new TabRecord<TKey, TData>* [maxSize];
}

template <typename TKey, typename TData>
ScanTable<TKey, TData>::ScanTable(const ScanTable& t) : Table<TKey, TData>(t.maxSize) {
    recs = new TabRecord<TKey, TData>* [maxSize];
    for (int i = 0; i < maxSize; ++i) {
        if (t.recs[i]) {
            recs[i] = new TabRecord<TKey, TData>(*t.recs[i]);
        }
        else {
            recs[i] = nullptr;
        }
    }
}

template <typename TKey, typename TData>
ScanTable<TKey, TData>::~ScanTable() {
    for (int i = 0; i < this->count; ++i) {
        delete recs[i];
    }
    delete[] recs;
}

template <typename TKey, typename TData>
TabRecord<TKey, TData>* ScanTable<TKey, TData>::Find(TKey key) const {
    for (int i = 0; i < this->count; i++) {
        if (recs[i]->GetKey() == key) {
            currPos = i;
            return recs[i];
        }
    }
    return nullptr;
}

template <typename TKey, typename TData>
void ScanTable<TKey, TData>::Insert(TKey key, TData* data) {
    if (IsFull()) throw ("Table is full");

    recs[++this->count] = new TabRecord<TKey, TData>(key, data);
}

template <typename TKey, typename TData>
void ScanTable<TKey, TData>::Remove(TKey key) {
    if (IsEmpty()) throw ("Table is empty");
    TabRecord<TKey, TData>* remove_record = Find(key);
    if (remove_record == nullptr) throw ("No such element");

    delete remove_record;
    recs[currPos] = recs[--this->count];
}

template <typename TKey, typename TData>
TabRecord<TKey, TData>* ScanTable<TKey, TData>::GetCurrent() const {
    return recs[currPos];
}

#endif 