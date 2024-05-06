#ifndef _SCAN_TABLE_H
#define _SCAN_TABLE_H
#include <table.h>

template <typename TKey, typename TData>
class ScanTable : public Table<TKey, TData> {
protected:
    TabRecord<TKey, TData>** recs;

public:
    ScanTable(int _maxSize);
    ScanTable(const ScanTable<TKey, TData>& table);
    virtual ~ScanTable();

    virtual TabRecord<TKey, TData>* Find(TKey key) override;
    virtual void Insert(TKey key, TData* data) override;
    virtual void Remove(TKey key) override;
    TabRecord<TKey, TData>* GetCurrent() const override;
    bool IsEnded() const;
    friend std::ostream& operator<<(std::ostream& out, const ScanTable<TKey, TData>& t) {
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
ScanTable<TKey, TData>::ScanTable(int _maxSize) : Table<TKey, TData>(maxSize) {
    if (_maxSize <= 0) {
        throw "table size must be greater than 0";
    }
    currPos = 0;
    maxSize = _maxSize;
    recs = new TabRecord<TKey, TData>* [_maxSize]; 
    for (int i = 0; i < _maxSize; ++i) {
        recs[i] = nullptr; 
    }
}

template <typename TKey, typename TData>
ScanTable<TKey, TData>::ScanTable(const ScanTable<TKey, TData>& table) : Table<TKey, TData>(table.maxSize) {
    if (table.IsEmpty())
    {
        recs = nullptr;
        return;
    }
    count = table.count;
    currPos = 0;
    recs = new TabRecord<TKey, TData>* [maxSize];

    for (int i = 0; i < maxSize; ++i)
    {
        if (table.recs[i])
        {
            recs[i] = new TabRecord<TKey, TData>(*table.recs[i]);
        }
    }
}

template <typename TKey, typename TData>
ScanTable<TKey, TData>::~ScanTable() {
    if (recs != nullptr) {
        for (int i = 0; i < count; i++)
            if (recs[i] != nullptr) delete recs[i];
        delete recs;
    }
}

template <typename TKey, typename TData>
TabRecord<TKey, TData>* ScanTable<TKey, TData>::Find(TKey key) {
    for (int i = 0; i < count; ++i) {
        if (recs[i]->GetKey() == key) {
            currPos = i;
            return recs[i];
        }
    }
    return nullptr;
}

template <typename TKey, typename TData>
void ScanTable<TKey, TData>::Insert(TKey key, TData* data) {
    if (IsFull()) {
        throw "Table is full";
    }
    if (Find(key) != nullptr) {
        throw("key is already exist");
    }

    recs[count++] = new TabRecord<TKey, TData>(key, data);
}

template <typename TKey, typename TData>
void ScanTable<TKey, TData>::Remove(TKey key) {
    if (IsEmpty()) {
        throw "Table is empty";
    }

    TabRecord<TKey, TData>* recordToRemove = Find(key);

    if (recordToRemove == nullptr) {
        throw"No record";
    }
    delete recordToRemove;
    for (int i = currPos; i < count - 1; ++i) {
        recs[i] = recs[i + 1];
    }
    --count;
}

template <typename TKey, typename TData>
TabRecord<TKey, TData>* ScanTable<TKey, TData>::GetCurrent() const {
    if (currPos >= 0 && currPos < count) {
        return recs[currPos];
    }
    throw("Out of range");
}

template <typename TKey, typename TData>
bool ScanTable<TKey, TData>::IsEnded() const {
    return currPos >= count;
}

#endif 