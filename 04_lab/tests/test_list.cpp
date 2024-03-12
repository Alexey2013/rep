#include "THeadRingList.h"
#include <gtest.h>

TEST(TList, can_create_new_list)
{
	ASSERT_NO_THROW(TList <int> list);
}

TEST(TList, can_create_copied_list)
{
	ASSERT_NO_THROW(TList<int>{new TNode<int>});
}

TEST(TList, list_is_empty_check)
{
	TList<int> list;
	ASSERT_TRUE(list.IsEmpty());
}

//TEST(TList, can_get_size)
//{
//	TList<int> list;
//	list.insert_last(2);
//	EXPECT_EQ(1, list.GetSize());
//}
//

TEST(TList, can_insert_last_in_the_list)
{
	TList<int> list;
	ASSERT_NO_THROW(list.insert_last(1));
}

//TEST(TList, can_remove_element)
//{
//	TList<int> list;
//	list.insert_last(1);
//	list.insert_last(2);
//	list.insert_last(3);
//	list.remove(3);
//	EXPECT_EQ(2, list.GetSize());
//}

TEST(TList, can_get_next_elemet)
{
	TList<int> list;
	list.insert_last(1);
	list.insert_last(2);
	list.next();
	EXPECT_EQ(2, list.GetCurrent()->data);
}

TEST(TList, can_clear_list)
{
	TList<int> list;
	list.insert_last(1);
	list.insert_last(2);
	list.clear();
	EXPECT_EQ(0, list.GetSize());
}

//TEST(TList, can_clear_list)
//{
//	TList<int> list;
//	EXPECT_EQ(0, list.GetSize());
//}
//



