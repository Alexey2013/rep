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
    bool IsEnded() const { return currPos >= count;}
    friend std::ostream& operator<<(std::ostream& out, const ScanTable<TKey, TData>& t)
    {
        ScanTable<TKey, TData> tmp(t);

        while (!tmp.IsEnded())
        {
            out << *tmp.GetCurrent();
            tmp.Next();
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

    for (int i = 0; i < count; i++)
    {
        recs[i] = new TabRecord<TKey, TData>(table.recs[i]->GetKey(), table.recs[i]->GetData());
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
    for (int i = 0; i < this->count; ++i) {
        if (recs[i]->GetKey() == key) {
            this->currPos = i;
            return recs[i];
        }
    }
    return nullptr;
}

template <typename TKey, typename TData>
void ScanTable<TKey, TData>::Insert(TKey key, TData* data) {
    if (this->IsFull()) {
        throw "Table is full";
    }
    if (Find(key) != nullptr) {
        throw("key is already exist");
    }

    recs[this->count++] = new TabRecord<TKey, TData>(key, data);
}

template <typename TKey, typename TData>
void ScanTable<TKey, TData>::Remove(TKey key) {
    if (this->IsEmpty()) {
        throw "Table is empty";
    }

    TabRecord<TKey, TData>* recordToRemove = Find(key);
    if (recordToRemove) {
        delete recordToRemove;
        for (int i = this->currPos; i < this->count - 1; ++i) {
            recs[i] = recs[i + 1];
        }
        --this->count;
    }
}

template <typename TKey, typename TData>
TabRecord<TKey, TData>* ScanTable<TKey, TData>::GetCurrent() const {
    return recs[this->currPos];
}

#endif 