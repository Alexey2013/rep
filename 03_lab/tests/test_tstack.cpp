#include "tstack.h"

#include <gtest.h>

TEST(TStack, can_create_stack) {
	ASSERT_NO_THROW(TStack<int> s(3));
}

TEST(TStack, throws_when_create_stack_with_negative_size) {
	ASSERT_ANY_THROW(TStack<int> s(-3));
}

TEST(TStack, throws_when_create_stack_with_zero_size) {
	ASSERT_ANY_THROW(TStack<int> s(0));
}

TEST(TStack, IsEmptyTest) {
	TStack<int> s(3);
	EXPECT_EQ(true, s.IsEmpty());

	s.Push(1);
	EXPECT_EQ(false, s.IsEmpty());
}