#include "polynom.h"
#include <gtest.h>
const string str="x+y+z";

TEST(TPolynom, create_polinom)
{
	ASSERT_NO_THROW(TPolynom p(str));
}

TEST(TPolynom, create_copied_polinom)
{
	TPolynom p1(str);
	ASSERT_NO_THROW(TPolynom p2(p1));
}

TEST(TPolynom, simple_calculate_is_correct) {
	TPolynom pol(str);
	double res = pol(1,2,3);
	EXPECT_EQ(6, pol(1, 2, 3));
}

TEST(TPolynom, dx_is_correct) {
	TPolynom pol("x^3+x^2+y+z+1");
	TPolynom tmp("3x^2+2x^1");
	EXPECT_EQ(pol.dx(), tmp);
}

TEST(TPolynom, dy_is_correct) {
	TPolynom pol("y^3+y^2+x+z+1");
	TPolynom tmp("3y^2+2y^1");
	EXPECT_EQ(pol.dy() , tmp);
}

TEST(TPolynom, dz_is_correct) {
	TPolynom pol("z^3+z^2+y+x+1");
	TPolynom tmp("3z^2+2z^1");
	EXPECT_EQ(pol.dz(), tmp);
}