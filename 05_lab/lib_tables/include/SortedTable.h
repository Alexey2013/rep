#ifndef _SORTED_TABLE_H
#define _SORTED_TABLE_H
#include <ScanTable.h>

template <typename TKey, typename TData>
class SortedTable : public ScanTable<TKey, TData> {
private:
    void QuickSort(TabRecord<TKey, TData>** rec_arr, int left, int right);
public:
    SortedTable(int maxSize);
    SortedTable(const ScanTable<TKey, TData>& table);

    TabRecord<TKey, TData>* Find(TKey key) override;
    void Insert(TKey key, TData* data) override;
    void Remove(TKey key) override;
};


template <typename TKey, typename TData>
SortedTable<TKey, TData>::SortedTable(int maxSize) : ScanTable<TKey, TData>(maxSize) {}

template <typename TKey, typename TData>
SortedTable<TKey, TData>::SortedTable(const ScanTable<TKey, TData>& table) : ScanTable<TKey, TData>(table) {
    if (!this->IsEmpty()) {
        QuickSort(this->recs, 0, this->count - 1);
    }
}

template <typename TKey, typename TData>
TabRecord<TKey, TData>* SortedTable<TKey, TData>::Find(TKey key) {
    int left = 0;
    int right = this->count - 1;

    while (left <= right) {
        int middle = (left + right) / 2;
        if (this->recs[middle]->GetKey() == key) {
            return this->recs[middle];
        }
        else if (this->recs[middle]->GetKey() > key) {
            right = middle - 1;
        }
        else {
            left = middle + 1;
        }
    }

    return nullptr;
}

template <typename TKey, typename TData>
void SortedTable<TKey, TData>::Insert(TKey key, TData* data) {
    if (this->IsEmpty()) {
        this->recs[0] = new TabRecord<TKey, TData>(key, data);
        this->count++;
        return;
    }

    if (this->IsFull()) {
        throw "Table is full";
    }

    TabRecord<TKey, TData>* recordToInsert = Find(key);
    if (recordToInsert != nullptr) {
        throw "Key already exists";
    }

    int pos = this->count - 1;
    while (pos >= 0 && this->recs[pos]->GetKey() > key) {
        this->recs[pos + 1] = this->recs[pos];
        pos--;
    }
    this->recs[pos + 1] = new TabRecord<TKey, TData>(key, data);
    this->count++;
}

template <typename TKey, typename TData>
void SortedTable<TKey, TData>::Remove(TKey key) {
    if (this->IsEmpty()) {
        throw "Table is empty";
    }

    TabRecord<TKey, TData>* recordToRemove = Find(key);
    if (recordToRemove == nullptr) {
        throw "No such element";
    }

    delete recordToRemove;
    int pos = 0;
    while (pos < this->count && this->recs[pos]->GetKey() != key) {
        pos++;
    }
    for (int i = pos; i < this->count - 1; i++) {
        this->recs[i] = this->recs[i + 1];
    }
    this->count--;
}

template <typename TKey, typename TData>
void SortedTable<TKey, TData>::QuickSort(TabRecord<TKey, TData>** rec_arr, int left, int right) {
    if (left >= right)  return;

    int i = left;
    int j = right;

    TabRecord<TKey, TData>* middle = rec_arr[(left + right) / 2];

    while (i <= j) {
        while (rec_arr[i]->GetKey() < middle->GetKey())
            i++;
        while (rec_arr[j]->GetKey() > middle->GetKey())
            j--;
        if (i <= j) {
            TabRecord<TKey, TData>* temp = rec_arr[i];
            rec_arr[i] = rec_arr[j];
            rec_arr[j] = temp;
            i++;
            j--;
        }
    }

    QuickSort(rec_arr, left, j);
    QuickSort(rec_arr, i, right);
}


#endif 