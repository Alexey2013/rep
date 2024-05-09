#include "ScanTable.h"
#include "polynom.h"
#include <gtest.h>

TEST(ScanTable,table_is_empty) {
    ScanTable<int, string> table(10);
    EXPECT_TRUE(table.IsEmpty());
}

TEST(ScanTable, can_create_copied_table) {
    ScanTable<int, string> table(10);
    int key = 1;
    string data = "Data1";
    table.Insert(key, new std::string(data));
    ScanTable<int, string> table2(table);
    EXPECT_EQ(table2.GetCurrent()->GetKey(), 1);
}

TEST(ScanTable, get_current_on_empty_table) {
    ScanTable<int, string> table(5);
    ASSERT_ANY_THROW(table.GetCurrent());
}

TEST(ScanTable, next_on_empty_table) {
    ScanTable<int, string> table(5);
    ASSERT_ANY_THROW(table.Next());
}

TEST(ScanTable, can_insert_record) {
    ScanTable<int, string> table(10);

    int key = 1;
    string data = "Data1";
    table.Insert(key, new std::string(data));
    EXPECT_EQ(table.GetCurrent()->GetKey(), 1);
}

TEST(ScanTable, throw_when_table_is_full_to_insert) {
    ScanTable<int, string> table(1);

    int key = 1;
    string data = "Data1";
    table.Insert(key, new std::string(data));
    ASSERT_ANY_THROW(table.Insert(2, new std::string(data)));
}

TEST(ScanTable, is_full_check) {
    ScanTable<int, string> table(1);

    int key = 1;
    string data = "Data1";
    table.Insert(key, new std::string(data));
    EXPECT_TRUE(table.IsFull());
}

TEST(ScanTable, can_get_next_element) {
    ScanTable<int, string> table(10);

    int key1 = 1;
    string data1 = "Data1";
    table.Insert(key1, new std::string(data1));

    int key2 = 2;
    string data2 = "Data2";
    table.Insert(key2, new std::string(data2));

    table.Next();
    EXPECT_EQ(table.GetCurrent()->GetKey(),2);
}

TEST(ScanTable,when_the_key_is_already_exists) {
    ScanTable<int, string> table(10);

    int key1 = 1;
    string data1 = "Data1";
    table.Insert(key1, new std::string(data1));

    string data2 = "Data2";
    ASSERT_ANY_THROW(table.Insert(key1, new std::string(data2)));
}

TEST(ScanTable, can_find_record) {
    ScanTable<int, string> table(10);

    int key1 = 1;
    string data1 = "Data1";
    table.Insert(key1, new std::string(data1));

    int key2 = 2;
    string data2 = "Data2";
    table.Insert(key2, new std::string(data2));

    table.Next();
    EXPECT_TRUE(table.GetCurrent()->GetData(),table.Find(1)->GetData());
}

TEST(ScanTable, can_remove_record) {
    ScanTable<int, string> table(2);
    int key1 = 1;
    string data1 = "Data1";
    table.Insert(key1, new std::string(data1));
    int key2 = 2;
    string data2 = "Data2";
    table.Insert(key2, new std::string(data1));

    table.Remove(1);
    EXPECT_EQ(table.Find(1),nullptr);
}

TEST(ScanTable, throw_when_table_is_empty_to_remove) {
    ScanTable<int, string> table(1);

    int key = 1;
    string data = "Data1";
    table.Insert(key, new std::string(data));
    table.Remove(1);
    ASSERT_ANY_THROW(table.Remove(1););
}
