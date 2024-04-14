#include "ScanTable.h"
#include <gtest.h>
const int maxSize = 5;

TEST(ScanTable, can_insert_record) {
    const int maxSize = 10; // ѕримерное значение размера таблицы
    ScanTable<int, std::string> table(maxSize);
    ASSERT_NO_THROW(table.Insert(1, new std::string("data")));
}

//// “ест дл€ проверки поиска записи в таблице
//TEST(ScanTable, can_find_record) {
//    ScanTable<int, std::string> table(maxSize);
//    std::string data = "data";
//    table.Insert(1, &data);
//    ASSERT_NE(table.Find(1), nullptr);
//}
//
//// “ест дл€ проверки удалени€ записи из таблицы
//TEST(ScanTable, can_remove_record) {
//    ScanTable<int, std::string> table(maxSize);
//    std::string data = "data";
//    table.Insert(1, &data);
//    ASSERT_NO_THROW(table.Remove(1));
//    ASSERT_EQ(table.Find(1), nullptr);
//}
//
//// “ест дл€ проверки исключени€ при попытке вставить запись в полную таблицу
//TEST(ScanTable, throw_exception_when_insert_into_full_table) {
//    const int maxSize = 1;
//    ScanTable<int, std::string> table(maxSize);
//    table.Insert(1, new std::string("data"));
//    ASSERT_THROW(table.Insert(2, new std::string("data")), std::exception);
//}
//
//// “ест дл€ проверки исключени€ при попытке удалить запись из пустой таблицы
//TEST(ScanTable, throw_exception_when_remove_from_empty_table) {
//    const int maxSize = 5;
//    ScanTable<int, std::string> table(maxSize);
//    ASSERT_THROW(table.Remove(1), std::exception);
//}
//
//// “ест дл€ проверки исключени€ при попытке удалить несуществующую запись из таблицы
//TEST(ScanTable, throw_exception_when_remove_nonexistent_record) {
//    const int maxSize = 5;
//    ScanTable<int, std::string> table(maxSize);
//    std::string data = "data";
//    table.Insert(1, &data);
//    ASSERT_THROW(table.Remove(2), std::exception);
//}