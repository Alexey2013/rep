#include "ArrayHashTable.h"
#include <gtest.h>

TEST(ArrayHashTable, can_create_table) {
    ArrayHashTable<int, string> hashTable(10,1);
    EXPECT_TRUE(hashTable.IsEmpty());
}

TEST(ArrayHashTable, can_insert_record) {
    ArrayHashTable<int, string> hashTable(10,1);

    int key = 1;
    string data = "Data1";
    hashTable.Insert(key, new std::string(data));
    EXPECT_EQ(hashTable.GetCurrent()->GetKey(), 1);
}

TEST(ArrayHashTable, can_create_copied_table) {
    ArrayHashTable<int, string> hashTable(10,1);
    int key = 1;
    string data = "Data1";
    hashTable.Insert(key, new std::string(data));
    ArrayHashTable<int, string> table2(hashTable);
    EXPECT_EQ(table2.GetCurrent()->GetKey(), 1);
}

TEST(ArrayHashTable, throw_when_table_is_full_to_insert) {
    ArrayHashTable<int, string> hashTable(1,0);

    int key = 1;
    string data = "Data1";
    hashTable.Insert(key, new std::string(data));
    ASSERT_ANY_THROW(hashTable.Insert(2, new std::string(data)));
}

TEST(ArrayHashTable, is_full_check) {
    ArrayHashTable<int, string> hashTable(1,0);

    int key = 1;
    string data = "Data1";
    hashTable.Insert(key, new std::string(data));
    EXPECT_TRUE(hashTable.IsFull());
}


TEST(ArrayHashTable, when_the_key_is_already_exists) {
    ArrayHashTable<int, string> hashTable(10, 1);

    int key1 = 1;
    string data1 = "Data1";
    hashTable.Insert(key1, new std::string(data1));

    string data2 = "Data2";
    ASSERT_ANY_THROW(hashTable.Insert(key1, new std::string(data2)));
}

TEST(ArrayHashTable, can_find_record) {
    ArrayHashTable<int, string> hashTable(10,1);

    int key1 = 1;
    string data1 = "Data1";
    hashTable.Insert(key1, new std::string(data1));

    int key2 = 2;
    string data2 = "Data2";
    hashTable.Insert(key2, new std::string(data2));

    EXPECT_TRUE(hashTable.GetCurrent()->GetData(), hashTable.Find(1)->GetData());
}

TEST(ArrayHashTable, can_remove_record) {
    ArrayHashTable<int, string> hashTable(10,1);
    int key1 = 1;
    string data1 = "Data1";
    hashTable.Insert(key1, new std::string(data1));
    int key2 = 2;
    string data2 = "Data2";
    hashTable.Insert(key2, new std::string(data1));

    hashTable.Remove(1);
    EXPECT_EQ(hashTable.Find(1), nullptr);
}

TEST(ArrayHashTable, throw_when_table_is_empty_to_remove) {
    ArrayHashTable<int, string> hashTable(1,0);

    int key = 1;
    string data = "Data1";
    hashTable.Insert(key, new std::string(data));
    hashTable.Remove(1);
    ASSERT_ANY_THROW(hashTable.Remove(1););
}

TEST(ArrayHashTableTest, insert_and_remove_test) {
    ArrayHashTable<int, std::string> hashTable(10,1);

    hashTable.Insert(1, new std::string("One"));
    hashTable.Insert(2, new std::string("Two"));
    hashTable.Insert(3, new std::string("Three"));

    hashTable.Remove(2);

    TabRecord<int, std::string>* record = hashTable.Find(2);
    EXPECT_EQ(record, nullptr);

    hashTable.Insert(4, new std::string("Four")); 

    record = hashTable.Find(4);
    ASSERT_NE(record, nullptr);
    EXPECT_EQ(*(record->GetData()), "Four");
}

TEST(ArrayHashTable, can_get_next_element) {
    ArrayHashTable<int, string> hashTable(10, 1);

    int key1 = 1;
    string data1 = "Data1";
    hashTable.Insert(key1, new std::string(data1));

    int key2 = 2;
    string data2 = "Data2";
    hashTable.Insert(key2, new std::string(data2));
    hashTable.Reset();
    hashTable.Next();
    EXPECT_TRUE(hashTable.GetCurrent()->GetKey(), 2);
}

