#include "polynom.h"
#include <gtest.h>
const string str="x+y";

TEST(TPolynom, create_polinom)
{
	ASSERT_NO_THROW(TPolynom p(str));
}

TEST(TPolynom, create_copied_polinom)
{
	TPolynom p1(str);
	ASSERT_NO_THROW(TPolynom p2(p1));
}
