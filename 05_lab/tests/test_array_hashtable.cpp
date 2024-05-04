#include "ArrayHashTable.h"
#include <gtest.h>

TEST(ArrayHashTable, can_create_table) {
    ArrayHashTable<int, string> table(10,1);
    EXPECT_TRUE(table.IsEmpty());
}

TEST(ArrayHashTable, can_insert_record) {
    ArrayHashTable<int, string> table(10,1);

    int key = 1;
    string data = "Data1";
    table.Insert(key, new std::string(data));
    EXPECT_EQ(table.GetCurrent()->GetKey(), 1);
}

TEST(ArrayHashTable, can_create_copied_table) {
    ArrayHashTable<int, string> table(10,1);
    int key = 1;
    string data = "Data1";
    table.Insert(key, new std::string(data));
    ArrayHashTable<int, string> table2(table);
    EXPECT_EQ(table2.GetCurrent()->GetKey(), 1);
}

TEST(ArrayHashTable, throw_when_table_is_full_to_insert) {
    ArrayHashTable<int, string> table(1,0);

    int key = 1;
    string data = "Data1";
    table.Insert(key, new std::string(data));
    ASSERT_ANY_THROW(table.Insert(2, new std::string(data)));
}

TEST(ArrayHashTable, is_full_check) {
    ArrayHashTable<int, string> table(1,0);

    int key = 1;
    string data = "Data1";
    table.Insert(key, new std::string(data));
    EXPECT_TRUE(table.IsFull());
}

TEST(ArrayHashTable, can_get_next_element) {
    ArrayHashTable<int, string> table(10,0);

    int key1 = 1;
    string data1 = "Data1";
    table.Insert(key1, new std::string(data1));

    int key2 = 2;
    string data2 = "Data2";
    table.Insert(key2, new std::string(data2));
    table.Next();
    EXPECT_TRUE(table.GetCurrent()->GetKey(), 2);
}

TEST(ArrayHashTable, when_the_key_is_already_exists) {
    ArrayHashTable<int, string> table(10, 0);

    int key1 = 1;
    string data1 = "Data1";
    table.Insert(key1, new std::string(data1));

    string data2 = "Data2";
    ASSERT_ANY_THROW(table.Insert(key1, new std::string(data2)));
}

TEST(ArrayHashTable, can_find_record) {
    ArrayHashTable<int, string> table(10,0);

    int key1 = 1;
    string data1 = "Data1";
    table.Insert(key1, new std::string(data1));

    int key2 = 2;
    string data2 = "Data2";
    table.Insert(key2, new std::string(data2));

    table.Next();
    EXPECT_TRUE(table.GetCurrent()->GetData(), table.Find(1)->GetData());
}

TEST(ArrayHashTable, can_remove_record) {
    ArrayHashTable<int, string> table(10,0);
    int key1 = 1;
    string data1 = "Data1";
    table.Insert(key1, new std::string(data1));
    int key2 = 2;
    string data2 = "Data2";
    table.Insert(key2, new std::string(data1));

    table.Remove(1);
    EXPECT_EQ(table.Find(1), nullptr);
}

TEST(ArrayHashTable, throw_when_table_is_empty_to_remove) {
    ArrayHashTable<int, string> table(1,0);

    int key = 1;
    string data = "Data1";
    table.Insert(key, new std::string(data));
    table.Remove(1);
    ASSERT_ANY_THROW(table.Remove(1););
}

TEST(ArrayHashTableTest, insert_and_remove_test) {
    ArrayHashTable<int, std::string> hashTable(10, 0);

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

//TEST(ArrayHashTableTest, iteration_test) {
//    ArrayHashTable<int, std::string> hashTable(10,0);
//
//    hashTable.Insert(1, new std::string("One"));
//    hashTable.Insert(2, new std::string("Two"));
//    hashTable.Insert(3, new std::string("Three"));
//
//    hashTable.Reset();
//
//    EXPECT_EQ(hashTable.GetCurrent()->GetKey(), 1);
//
//    hashTable.Next();
//    EXPECT_EQ(hashTable.GetCurrent()->GetKey(), 2);
//
//    hashTable.Next();
//    EXPECT_EQ(hashTable.GetCurrent()->GetKey(), 3);
//
//}