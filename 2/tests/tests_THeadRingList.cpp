#include "THeadRingList.h"
#include <gtest.h>

TEST(THeadRingList, can_create_THeadRingList) {
	THeadRingList<int> list;
}

TEST(THeadRingList, can_insert_element) {
	THeadRingList<int> list;
	list.insert_last(1);
	EXPECT_EQ(1, list.GetCurrent()->data);
}

//TEST(THeadRingList, can_get_next_elemet)
//{
//	THeadRingList<int> list;
//	list.insert_last(1);
//	list.insert_last(2);
//	list.next();
//	EXPECT_EQ(2, list.GetCurrent()->data);
//}

//TEST(THeadRingList, can_remove_element)
//{
//	THeadRingList<int> list;
//	list.insert_last(1);
//	list.insert_last(2);
//	list.insert_last(3);
//	list.remove(3);
//	EXPECT_EQ(2, list.GetSize());
//}

//TEST(THeadRingList, check_list_is_ring)
//{
//	THeadRingList<int> list;
//	list.insert_last(1);
//	list.insert_last(2);
//	list.next(); list.next(); list.next();
//	ASSERT_NO_THROW(list.GetCurrent()->data);
//}

//TEST(THeadRingList, can_insert_element_at_beginning)
//{
//	THeadRingList<int> list;
//	list.insert_last(1);
//	list.insert_first(2);
//	EXPECT_EQ(2, list.GetCurrent()->data);
//}
//
//TEST(THeadRingList, can_insert_element_in_middle)
//{
//	THeadRingList<int> list;
//	list.insert_last(1);
//	list.insert_last(3);
//	list.insert_after(2, list.GetCurrent()->data);
//	list.next();
//	EXPECT_EQ(2, list.GetCurrent()->data);
//}
//
//TEST(THeadRingList, can_remove_first_element)
//{
//	THeadRingList<int> list;
//	list.insert_last(1);
//	list.insert_last(2);
//	list.remove(1);
//	list.reset();
//	EXPECT_EQ(2, list.GetCurrent()->data);
//}
//
//TEST(THeadRingList, can_remove_last_element)
//{
//	THeadRingList<int> list;
//	list.insert_last(1);
//	list.insert_last(2);
//	list.remove(2);
//	list.reset();
//	EXPECT_EQ(1, list.GetCurrent()->data);
//}
//
//TEST(THeadRingList, can_get_size)
//{
//	THeadRingList<int> list;
//	list.insert_last(1);
//	list.insert_last(2);
//	list.insert_last(3);
//	EXPECT_EQ(3, list.GetSize());
//}
//
//TEST(THeadRingList, can_clear_list)
//{
//	THeadRingList<int> list;
//	list.insert_last(1);
//	list.insert_last(2);
//	list.insert_last(3);
//	list.clear();
//	EXPECT_EQ(0, list.GetSize());
//	EXPECT_EQ(nullptr, list.GetCurrent());
//}
//
//TEST(THeadRingList, can_insert_element_before_current)
//{
//	THeadRingList<int> list;
//	list.insert_last(1);
//	list.insert_last(3);
//	list.next();
//	list.insert_before(2, list.GetCurrent()->data);
//	list.reset(); list.next();
//	EXPECT_EQ(2, list.GetCurrent()->data);
//}
//
//TEST(THeadRingList, can_insert_element_after_current)
//{
//	THeadRingList<int> list;
//	list.insert_last(1);
//	list.insert_last(3);
//	list.insert_after(2, list.GetCurrent()->data);
//	list.next();
//	EXPECT_EQ(2, list.GetCurrent()->data);
//}
//
//TEST(THeadRingList, can_insert_to_sort)
//{
//	THeadRingList<int> list;
//	list.InsertFirst(5);
//	list.insert_sort(1);
//	list.insert_sort(2);
//	EXPECT_EQ(5, list.pHead->data);
//	EXPECT_EQ(2, list.pHead->pNext->data);
//	EXPECT_EQ(1, list.pHead->pNext->pNext->data);
//}
//
//TEST(THeadRingList, get_next_element_in_ring)
//{
//	THeadRingList<int> list;
//	list.InsertFirst(1);
//	list.insert_last(2);
//	EXPECT_EQ(1, list.pHead->pNext->pNext->data);
//}