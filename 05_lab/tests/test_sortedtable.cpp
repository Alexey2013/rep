#include "SortedTable.h"
#include <gtest.h>

TEST(SortedTable, table_is_empty) {
    SortedTable<int, string> table(10);
    EXPECT_TRUE(table.IsEmpty());
}

TEST(SortedTable, can_insert_record) {
    SortedTable<int, string> table(10);

    int key = 1;
    string data = "Data1";
    table.Insert(key, new std::string(data));
    EXPECT_EQ(table.GetCurrent()->GetKey(), 1);
}

TEST(SortedTable, throw_when_table_is_full_to_insert) {
    SortedTable<int, string> table(1);

    int key = 1;
    string data = "Data1";
    table.Insert(key, new std::string(data));
    ASSERT_ANY_THROW(table.Insert(2, new std::string(data)));
}

TEST(SortedTable, is_full_check) {
    SortedTable<int, string> table(1);

    int key = 1;
    string data = "Data1";
    table.Insert(key, new std::string(data));
    EXPECT_TRUE(table.IsFull());
}

TEST(SortedTable, can_get_next_element) {
    SortedTable<int, string> table(10);

    int key1 = 1;
    string data1 = "Data1";
    table.Insert(key1, new std::string(data1));

    int key2 = 2;
    string data2 = "Data2";
    table.Insert(key2, new std::string(data2));

    table.Next();
    EXPECT_TRUE(table.GetCurrent()->GetKey(), 2);
}

TEST(SortedTable, can_find_record) {
    SortedTable<int, string> table(10);

    int key1 = 1;
    string data1 = "Data1";
    table.Insert(key1, new std::string(data1));

    int key2 = 2;
    string data2 = "Data2";
    table.Insert(key2, new std::string(data2));

    table.Next();
    EXPECT_TRUE(table.GetCurrent()->GetData(), table.Find(1)->GetData());
}

TEST(SortedTable, can_remove_record) {
    SortedTable<int, string> table(2);
    int key1 = 1;
    string data1 = "Data1";
    table.Insert(key1, new std::string(data1));

    table.Remove(1);
    EXPECT_TRUE(table.IsEmpty());
}

TEST(SortedTable, throw_when_table_is_empty_to_remove) {
    SortedTable<int, string> table(1);

    int key = 1;
    string data = "Data1";
    table.Insert(key, new std::string(data));
    table.Remove(1);
    ASSERT_ANY_THROW(table.Remove(1););
}


TEST(SortedTable, when_the_key_is_already_exists) {
    SortedTable<int, string> table(10);

    int key1 = 1;
    string data1 = "Data1";
    table.Insert(key1, new std::string(data1));

    string data2 = "Data2";
    ASSERT_ANY_THROW(table.Insert(key1, new std::string(data2)));
}


TEST(SortedTable, insert_is_sorting) {
    SortedTable<int, std::string> table(5);

    std::string data = "Data";

    table.Insert(5, new std::string(data));
    table.Insert(2, new std::string(data));
    table.Insert(3, new std::string(data));
    table.Insert(4, new std::string(data));
    table.Insert(1, new std::string(data));

    EXPECT_EQ(1, table.GetCurrent()->GetKey());
    table.Next();
    EXPECT_EQ(2, table.GetCurrent()->GetKey());
    table.Next();
    EXPECT_EQ(3, table.GetCurrent()->GetKey());
    table.Next();
    EXPECT_EQ(4, table.GetCurrent()->GetKey());
    table.Next();
    EXPECT_EQ(5, table.GetCurrent()->GetKey());
}

TEST(SortedTable, sort_is_right) {
    ScanTable<int,  std::string> table1(5);

    std::string data = "Data";

    table1.Insert(5, new std::string(data));
    table1.Insert(2, new std::string(data));
    table1.Insert(4, new std::string(data));
    table1.Insert(3, new std::string(data));
    table1.Insert(1, new std::string(data));

    SortedTable<int, std::string> table2(table1);

    EXPECT_EQ(1, table2.GetCurrent()->GetKey());
    table2.Next();
    EXPECT_EQ(2, table2.GetCurrent()->GetKey());
    table2.Next();
    EXPECT_EQ(3, table2.GetCurrent()->GetKey());
    table2.Next();
    EXPECT_EQ(4, table2.GetCurrent()->GetKey());
    table2.Next();
    EXPECT_EQ(5, table2.GetCurrent()->GetKey());
}

