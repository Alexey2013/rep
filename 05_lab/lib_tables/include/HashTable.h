#ifndef _HASH_TABLE_H
#define _HASH_TABLE_H
#include <Table.h>

template <typename TKey, typename TData>
class HashTable : public Table<TKey, TData> {
protected:
    size_t hashFunc(const std::string& key) const {
        size_t hashValue;
        for (char ch : key) {
            hashValue = hashValue * 31 + static_cast<size_t>(ch); 
        }
        return hashValue;
    }

    size_t hashFunc(int key) const {
        return static_cast<size_t>(key) % maxSize;
    }

public:
    HashTable(int n) : Table<TKey, TData>(n) {}
};


#endif 