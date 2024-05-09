#ifndef _HASH_TABLE_H
#define _HASH_TABLE_H
#include <Table.h>

template <typename TKey, typename TData>
class HashTable : public Table<TKey, TData> {
protected:

    size_t hashFunc(const string& key) const {
        uint64_t hashValue = 0;
        for (char ch : key) {
            hashValue +=ch;
        }
        return (hashValue % maxSize);
    }

    size_t hashFunc(int key) const {
        return key % maxSize;
    }
    
public:
    HashTable(int n) : Table<TKey, TData>(n) {}
};


#endif 