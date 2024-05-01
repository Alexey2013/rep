#ifndef _SCAN_TABLE_H
#define _SCAN_TABLE_H
#include <table.h>

template <typename TKey, typename TData>
class ScanTable : public Table<TKey, TData> {
protected:
    TabRecord<TKey, TData>** recs;

public:
    ScanTable(int maxSize);  
    ~ScanTable() override;  
    TabRecord<TKey, TData>* Find(TKey key) override;          
    void Insert(TKey key, TData* data) override;               
    void Remove(TKey key) override;                            
    TabRecord<TKey, TData>* GetCurrent() const override;
};

template <typename TKey, typename TData>
ScanTable<TKey, TData>::ScanTable(int maxSize) : Table<TKey, TData>(maxSize) {
    recs = new TabRecord<TKey, TData>* [maxSize];
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