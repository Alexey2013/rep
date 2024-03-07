#include "polynom.h"
#include <gtest.h>
const string str;

TEST(TPolynom, create_polinom)
{
	ASSERT_NO_THROW(TPolynom p1(str));
}

TEST(TPolynom, build_polinom)
{
	ASSERT_NO_THROW(TPolynom p1("4x^2y"));
}

TEST(TPolynom, create_polinom_after_existing)
{
	TPolynom p1("x^5z");
	ASSERT_NO_THROW(TPolynom p2(p1));
}