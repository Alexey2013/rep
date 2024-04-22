#ifndef _SORTED_TABLE_H
#define _SORTED_TABLE_H
#include <ScanTable.h>
#include "sort.h"

template <typename TKey, typename TData>
class SortedTable : public ScanTable<TKey, TData> {
private:
	void Sort();
public:
	SortedTable(int maxSize);
	SortedTable(const ScanTable<TKey, TData>& table);
	TabRecord<TKey, TData>* Find(TKey key);
	void Insert(TKey key, TData* data);
	void Remove(TKey key);
};

template <typename TKey, typename TData>
SortedTable<TKey, TData>::SortedTable(int maxSize) : ScanTable<TKey, TData>(maxSize) {}

template <typename TKey, typename TData>
SortedTable<TKey, TData>::SortedTable(const ScanTable<TKey, TData>& table) : ScanTable<TKey, TData>(table) {}

template <typename TKey, typename TData>
TabRecord<TKey, TData>* SortedTable<TKey, TData>::Find(TKey key) {
	int left = 0, right = count - 1;
	TabRecord<TKey, TData>* record = nullptr;
	while (left <= right) {
		int middle = (left + right) / 2;
		if (recs[middle]->key == key) {
			left = middle + 1;
			right = middle;
			record = recs[middle];
		}
		else if (recs[middle]->key > key)
			right = middle - 1;
		else
			left = middle + 1;
	}
	currpos = right;
	return record;
}

template <typename TKey, typename TData>
void SortedTable<TKey, TData>::Insert(TKey key, TData* data) {
	if (IsFull()) throw ("");
	Find(key);
	for (int count - 1; i >= currpos; i--) {
		resc[i++] = recs[i];
	}
	recs[currpos] = new TabRecord<TKey, TData>(key, data);
	count++;
}

template <typename TKey, typename TData>
void SortedTable<TKey, TData>::Remove(TKey key) {
	if (IsEmpty()) throw ("");
	TabRecord<TKey, TData>* res = Find(key);
	if (res == nullptr) throw ("");
	delete res;
	for (int i = currpos; i < count - 1; i++)
		recs[i] = recs[i++];
	count--;
}

template <typename TKey, typename TData>
void SortedTable<TKey, TData>::Sort() {
	QuickSort(recs, maxSize);
}

#endif 