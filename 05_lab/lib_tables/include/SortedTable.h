#ifndef _SORTED_TABLE_H
#define _SORTED_TABLE_H
#include <ScanTable.h>

template <typename TKey, typename TData>
class SortedTable : public ScanTable<TKey, TData> {
private:
    void QuickSort(TabRecord<TKey, TData>** arr, int left, int right);
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
    if (!IsEmpty()) {
        QuickSort(recs, 0, count - 1);
    }
}

template <typename TKey, typename TData>
TabRecord<TKey, TData>* SortedTable<TKey, TData>::Find(TKey key) {
    int left = 0;
    int right = count - 1;

    while (left <= right) {
        int middle = (left + right) / 2;
        if (recs[middle]->GetKey() == key) {
            return recs[middle];
        }
        else if (recs[middle]->GetKey()> key) {
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
    if (IsEmpty()) {
        recs[0] = new TabRecord<TKey, TData>(key, data);
        count++;
        return;
    }

    if (IsFull()) {
        throw "Table is full";
    }

    TabRecord<TKey, TData>* recordToInsert = Find(key);
    if (recordToInsert != nullptr) {
        throw "Key already exists";
    }

    int pos = count - 1;
    while (pos >= 0 && recs[pos]->GetKey() > key) {
        recs[pos + 1] = recs[pos];
        pos--;
    }
    recs[pos + 1] = new TabRecord<TKey, TData>(key, data);
    count++;
}

template <typename TKey, typename TData>
void SortedTable<TKey, TData>::Remove(TKey key) {
    if (IsEmpty()) {
        throw "Table is empty";
    }
    TabRecord<TKey, TData>* recordToRemove = Find(key);

    if (recordToRemove == nullptr) {
        throw "No such element";
    }
    delete recordToRemove;
    int pos = 0;
    while (pos < count && recs[pos]->GetKey() != key) {
        pos++;
    }
    for (int i = pos; i < count - 1; i++) {
        recs[i] = recs[i + 1];
    }
    count--;
}

template <typename TKey, typename TData>
void SortedTable<TKey, TData>::QuickSort(TabRecord<TKey, TData>** arr, int left, int right) {
    if (left >= right)  return;

    int i = left;
    int j = right;

    TabRecord<TKey, TData>* middle = arr[(left + right) / 2];

    while (i <= j) {
        while (arr[i]->GetKey() < middle->GetKey())
            i++;
        while (arr[j]->GetKey() > middle->GetKey())
            j--;
        if (i <= j) {
            TabRecord<TKey, TData>* temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
            i++;
            j--;
        }
    }

    QuickSort(arr, left, j);
    QuickSort(arr, i, right);
}


#endif 