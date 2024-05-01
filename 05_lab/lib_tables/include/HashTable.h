#ifndef _HASH_TABLE_H
#define _HASH_TABLE_H
#include <Table.h>

template <class TKey, class TData>
class HashTable : public Table<TKey, TData> {
protected:
    virtual int hashFunc(const TKey key) = 0;
public:
    HashTable(int n) : Table(n) {}
};

#endif 