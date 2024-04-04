#include "THeadRingList.h"
#include <gtest.h>

TEST(THeadRingList, can_create_THeadRingList) {
	THeadRingList<int> list;
}

TEST(THeadRingList, can_reset_list)
{
	THeadRingList<int> list;
	list.insert_last(1);
	list.insert_last(2);
	list.reset();
	EXPECT_EQ(1, list.GetCurrent()->data);
}

TEST(THeadRingList, can_copy_list)
{
	THeadRingList<int> list1;
	list1.insert_last(1);
	list1.insert_last(2);
	THeadRingList<int> list2(list1);
	list1.reset();
	EXPECT_EQ(list1.GetCurrent()->data, list2.GetCurrent()->data);
}

TEST(THeadRingList, can_insert_element) {
	THeadRingList<int> list;
	list.insert_last(1);
	EXPECT_EQ(1, list.GetCurrent()->data);
}

TEST(THeadRingList, can_get_next_elemet)
{
	THeadRingList<int> list;
	list.insert_last(1);
	list.next();
	list.insert_last(2);
	EXPECT_EQ(2, list.GetCurrent()->data);
}

TEST(THeadRingList, check_hr_list_cannot_do_Next_method_at_Head)
{
	THeadRingList<int> hr_list;
	hr_list.insert_last(1);
	hr_list.insert_last(2);
	hr_list.next();
	ASSERT_ANY_THROW(hr_list.next());
}

TEST(THeadRingList, can_insert_element_at_beginning)
{
	THeadRingList<int> list;
	list.insert_last(1);
	list.insert_first(2);
	EXPECT_EQ(2, list.GetCurrent()->data);
}

TEST(THeadRingList, can_insert_element_in_middle)
{
	THeadRingList<int> list;
	list.insert_last(1);
	list.next();
	list.insert_last(3);
	list.insert_after(2, list.GetCurrent()->data);
	EXPECT_EQ(2, list.GetCurrent()->data);
}

TEST(THeadRingList, can_remove_first_element)
{
	THeadRingList<int> list;
	list.insert_last(1);
	list.insert_last(2);
	list.remove(1);
	list.reset();
	EXPECT_EQ(2, list.GetCurrent()->data);
}

TEST(THeadRingList, can_remove_last_element)
{
	THeadRingList<int> list;
	list.insert_last(1);
	list.insert_last(2);
	list.remove(2);
	list.reset();
	EXPECT_EQ(1, list.GetCurrent()->data);
}

TEST(THeadRingList, can_clear_list)
{
	THeadRingList<int> list;
	list.insert_last(1);
	list.insert_last(2);
	list.insert_last(3);
	list.clear();
	EXPECT_TRUE(list.IsEmpty());
}

TEST(THeadRingList, can_insert_element_before_current)
{
	THeadRingList<int> list;
	list.insert_last(1);
	list.insert_last(3);
	list.insert_before(2, list.GetCurrent()->data);
	list.reset();
	list.next();
	EXPECT_EQ(2, list.GetCurrent()->data);
}

TEST(THeadRingList, can_insert_element_after_current)
{
	THeadRingList<int> list;
	list.insert_last(1);
	list.next();
	list.insert_last(3);
	list.insert_after(2, list.GetCurrent()->data);
	EXPECT_EQ(2, list.GetCurrent()->data);
}

TEST(THeadRingList, can_check_if_list_is_empty)
{
	THeadRingList<int> list;
	EXPECT_TRUE(list.IsEmpty());
	list.insert_last(1);
	EXPECT_FALSE(list.IsEmpty());
}

TEST(THeadRingList, can_find_element_by_value)
{
	THeadRingList<int> list;
	list.insert_last(1);
	list.insert_last(2);
	list.insert_last(3);
	EXPECT_EQ(2, list.search(2)->data);
}

TEST(THeadRingList, get_size_is_right) {
	THeadRingList<int> list;
	list.insert_last(5);
	list.insert_last(3);
	list.insert_last(7);
	list.insert_last(1);
	EXPECT_EQ(4, list.GetSize());
}

TEST(THeadRingList, sort_is_right) {
	THeadRingList<int> list;
	list.insert_last(5);
	list.insert_last(3);
	list.insert_last(7);
	list.insert_last(1);
	list.sort();
	EXPECT_EQ(0, list.GetCurrent()->data);
	list.next();
	EXPECT_EQ(1, list.GetCurrent()->data);
	list.next();
	EXPECT_EQ(3, list.GetCurrent()->data);
	list.next();
	EXPECT_EQ(5, list.GetCurrent()->data);
	list.next();
	EXPECT_EQ(7, list.GetCurrent()->data);
}

TEST(THeadRingList, can_sort_empty_list)
{
	THeadRingList<int> list;
	EXPECT_NO_THROW(list.sort());
}
