#include "polynom.h"
#include <gtest.h>

TEST(TPolynom, create_empty_polinom)
{
	ASSERT_NO_THROW(TPolynom p());
}

TEST(TPolynom, create_polinom)
{
	ASSERT_NO_THROW(TPolynom p("x^2*y^2*z^2+xyz+x+y+z"));
}

TEST(TPolynom, can_create_copied_polinom)
{
	TPolynom p1("x^2*y^2*z^2+xyz+x+y+z");
	ASSERT_NO_THROW(TPolynom p2(p1));
}

TEST(TPolynom, can_create_polinom_with_empty_list) {
	THeadRingList<TMonom> list;
	ASSERT_NO_THROW(TPolynom p(&list));
}

TEST(TPolynom, can_create_polinom_with_list) {
	THeadRingList<TMonom> list;
	TMonom m1(1, 1);
	TMonom m2(0, 1);
	list.insert_sort(m1);
	list.insert_sort(m2);
	ASSERT_NO_THROW(TPolynom p(&list));
}

TEST(TPolynom, polinom_with_list_is_right) {
	THeadRingList<TMonom> list;
	TMonom m1(1, 100);
	TMonom m2(1, 10);
	TMonom m3(1, 1);
	TMonom m4(1, 1);
	TMonom m5(0, 1);
	list.insert_sort(m1);
	list.insert_sort(m2);
	list.insert_sort(m3);
	list.insert_sort(m4);
	list.insert_sort(m5);
	TPolynom p1(&list);
	TPolynom p2("x+y+2z");
	EXPECT_EQ(p1, p2);
}

TEST(TPolynom, equality_operator_is_correct)
{
	TPolynom p1("x^2*y^2*z^2+xyz+x+y+z");
	TPolynom p2("x^2*y^2*z^2+xyz+x+y+z");
	EXPECT_EQ(p1, p2);
}

TEST(TPolynom, copied_polinom_is_correct)
{
	TPolynom p1("x^2*y^2*z^2+xyz+x+y+z");
	TPolynom p2(p1);
	EXPECT_EQ(p1, p2);
}

TEST(TPolynom, to_string_is_correct)
{
	TPolynom p1("X ^ 3 + x ^ 2 + y + z + 1");
	string str = "1.00+z+y+x^2+x^3";
	EXPECT_EQ(p1.ToString(), str);
}

TEST(TPolynom, no_throw_when_polynom_will_be_empty) 
{
   ASSERT_NO_THROW(TPolynom p("x-x+y-y+z-z"));
}

TEST(TPolynom, similar_test1) {
	TPolynom p1("x+x-x+x+y+y+z+z+z");
	TPolynom p2("2x+2y+3z");
	EXPECT_EQ(p1, p2);
}

TEST(TPolynom, similar_test2) {
	TPolynom p1("y+x-x");
	TPolynom p2("y");
	EXPECT_EQ(p1, p2);
}

TEST(TPolynom, similar_test3) {
	TPolynom p1("x-x+y-y+z-z");
	TPolynom p2("0");
	EXPECT_EQ(p1, p2);
}

TEST(TPolynom, similar_test4) {
	TPolynom p1("x+x+y+x");
	TPolynom p2("3x+y");
	EXPECT_EQ(p1, p2);
}

TEST(TPolynom, similar_test5) {
	TPolynom p1("x+x+x^2+x");
	TPolynom p2("3x+x^2");
	EXPECT_EQ(p1, p2);
}

TEST(TPolynom, similar_test6) {
	TPolynom p1("x+y-x-y+z+1-z");
	TPolynom p2("1");
	EXPECT_EQ(p1, p2);
}

TEST(TPolynom, can_create_polynom_in_different_order)
{
	TPolynom p("x^2*y^2*z^2+xyz+x+y+z");
	TPolynom p_reordered("z+y+x+x^2*y^2*z^2+xyz");
	EXPECT_EQ(p, p_reordered);
}

TEST(TPolynom, can_create_polynom_with_negative_coefficient)
{
	ASSERT_NO_THROW(TPolynom p("-2x^2"));
}

TEST(TPolynom, calculate_is_correct1) 
{
	TPolynom pol("x+y+z");
	double res = pol(1,2,3);
	EXPECT_EQ(6, pol(1, 2, 3));
}

TEST(TPolynom, calculate_is_correct2)
{
	TPolynom pol("x^3+x^2+y+z+1");
	double res = pol(0.1, 0.2, 0.3);
	ASSERT_NEAR(1.511, res, 1);
}

TEST(TPolynom, calculate_is_correct3)
{
	TPolynom p("5");
	EXPECT_EQ(p(0, 0, 0), 5);
}

TEST(TPolynom, calculate_is_correct4)
{
	TPolynom pol("x^3+x^2+y+z+1");
	double res = pol(1, 2, 3);
	EXPECT_EQ(8, pol(1, 2, 3));
}

TEST(TPolynom, dx_is_correct) 
{
	TPolynom pol("x^3+x^2+y+z+1");
	TPolynom tmp("3x^2+2x");
	EXPECT_EQ(pol.dx(), tmp);
}

TEST(TPolynom, dx_is_correct2)
{
	TPolynom pol("1 + 2x ^ 2 + x ^ 2*y");
	TPolynom tmp("4x+2yx");
	EXPECT_EQ(pol.dx(), tmp);
}

TEST(TPolynom, dy_is_correct) 
{
	TPolynom pol("y^3+y^2+x+z+1");
	TPolynom tmp("3y^2+2y");
	EXPECT_EQ(pol.dy() , tmp);
}

TEST(TPolynom, dy_is_correct2)
{
	TPolynom pol("1 + 2x ^ 2 + x ^ 2*y");
	TPolynom tmp("x^2");
	EXPECT_EQ(pol.dy(), tmp);
}

TEST(TPolynom, dz_is_correct) 
{
	TPolynom pol("z^3+z^2+y+x+1");
	TPolynom tmp("3z^2+2z");
	EXPECT_EQ(pol.dz(), tmp);
}

TEST(TPolynom, dz_is_correct2)
{
	TPolynom pol("z + 2z ^ 2 + z ^ 2*z");
	TPolynom tmp("1.00+4.00z+3.00z^2");
	EXPECT_EQ(pol.dz(), tmp);
}

TEST(TPolynom,no_throw_when_no_monomials_to_derive)
{
	TPolynom pol("z^3+z^2+y+1");
	ASSERT_NO_THROW(pol.dx());
}

TEST(TPolynom, zero_when_there_are_no_derivative_arguments)
{
	TPolynom pol1("z^3+z^2+y+1");
	TPolynom pol2("0");
	EXPECT_EQ(pol1.dx(), pol2);
}

TEST(TPolynom,sum_is_correct) 
{
	TPolynom pol1("x^3+y^2+x+1");
	TPolynom pol2("x^3+y+z+1");
	TPolynom pol3("2+z+y+x+y^2+2x^3");
	EXPECT_EQ(pol1+pol2, pol3);
}

TEST(TPolynom, remove_zeroes_is_correct)
{
	TPolynom pol1("x^3+y^2+y+x+1");
	TPolynom pol2("-x^3-y^2+y-x-1");
	TPolynom pol3("2y");
	EXPECT_EQ(pol1 + pol2, pol3);
}

TEST(TPolynom, sum_with_zero_is_correct)
{
	TPolynom pol1("x^3+y^2+y+x+1");
	TPolynom pol2("0");
	EXPECT_EQ(pol1+pol2, pol1);
}

TEST(TPolynom, sum_with_inverse_polynomial)
{
	TPolynom pol1("x^3+y^2+y+x+1");
	TPolynom pol2("-x^3-y^2-y-x-1");
	TPolynom pol3("0");
	EXPECT_EQ(pol1 + pol2, pol3);
}

TEST(TPolynom, diff_is_correct) 
{
	TPolynom pol1("2x^3+y^2+y+x");
	TPolynom pol2("x^3-2y^2+z");
	TPolynom pol3("x^3+3y^2+y^1+x-z");
	EXPECT_EQ(pol1-pol2, pol3);
}

TEST(TPolynom, diff_is_with_negative_coefficients)
{
	TPolynom p1("-3x^2-2y+5");
	TPolynom p2("-x^2-4y-3");
	TPolynom p3("2x^2+2y+8");
	EXPECT_EQ(p1 - p2, p3);
}

TEST(TPolynom, negation_operator_is_correct)
{
	TPolynom p1("-3x^2-2y+5");
	TPolynom p2("0");
	EXPECT_EQ(p1+(-p1), p2);
}

TEST(TPolynom, mult_is_correct1) 
{
	TPolynom pol1("x^2+y");
	TPolynom pol2("x^3+x");
	TPolynom pol3("x^5+x^3+x^3*y+x*y");
	EXPECT_EQ(pol1*pol2, pol3);
}

TEST(TPolynom, mult_is_correct2)
{
	TPolynom p1("x^2+y");
	TPolynom p2("x^1/2");
	TPolynom p_mult("x^3/2+yx^1/2");
	EXPECT_EQ(p1 * p2, p_mult);
}

TEST(TPolynom, mult_is_correct3)
{
	TPolynom p1("x^2+y");
	TPolynom p2("1");
	EXPECT_EQ(p1 * p2, p1);
}

TEST(TPolynom, mult_is_correct4)
{
	TPolynom p1("1");
	TPolynom p2("1");
	TPolynom p_mult("1");
	EXPECT_EQ(p1 * p2, p_mult);
}

TEST(TPolynom, mult_with_0_results_in_0)
{
	TPolynom p1("x+1");
	TPolynom p2("0");
	EXPECT_EQ(p1 * p2,p2);
}

TEST(TPolynom, conversion_mult_test1)
{
	TPolynom pol1("x^2*x");
	TPolynom pol2("x^3");
	EXPECT_EQ(pol1, pol2);
}

TEST(TPolynom, conversion_mult_test2)
{
	TPolynom pol1("-x");
	TPolynom pol2("-x");
	TPolynom pol3("x^2");
	EXPECT_EQ(pol1 * pol2,pol3);
}
