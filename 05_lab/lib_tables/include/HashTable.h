#ifndef _HASH_TABLE_H
#define _HASH_TABLE_H
#include <Table.h>

template <typename TKey, typename TData>
class HashTable : public Table<TKey, TData> {
protected:
    string hashFunc(const std::string& key) const {
        string hashValue = 0;
        for (char ch : key) {
            hashValue = hashValue * 31 + ch;
        }
        return hashValue;
    }

    int hashFunc(int key) const {return key % maxSize;}
public:
    HashTable(int n) : Table<TKey, TData>(n) {} 
};


#endif 