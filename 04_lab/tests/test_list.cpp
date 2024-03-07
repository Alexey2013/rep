#include "list.h"
#include <gtest.h>

TEST(TList, can_create_new_list)
{
	ASSERT_NO_THROW(TList<int> list);
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

