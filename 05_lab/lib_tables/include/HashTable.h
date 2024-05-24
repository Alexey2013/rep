#ifndef _HASH_TABLE_H
#define _HASH_TABLE_H
#include <Table.h>

template <typename TKey, typename TData>
class HashTable : public Table<TKey, TData> {
protected:
    virtual size_t hashFunc(const TKey& key) const = 0;

public:
    HashTable(int n) : Table<TKey, TData>(n) {}
};


#endif 