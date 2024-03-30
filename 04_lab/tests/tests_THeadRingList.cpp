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

TEST(THeadRingList, can_assign_list)
{
	THeadRingList<int> list1;
	list1.insert_last(1);
	list1.insert_last(2);
	THeadRingList<int> list2;
	list2.insert_last(3);
	list2 = list1;
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

TEST(THeadRingList, check_list_is_ring)
{
	THeadRingList<int> list;
	list.insert_last(1);
	list.insert_last(2);
	list.next(); list.next(); list.next();
	ASSERT_NO_THROW(list.GetCurrent()->data);
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
	list.Clear();
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
