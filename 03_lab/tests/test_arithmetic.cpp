#include "arithmetic.h"
#include <gtest.h>

TEST(TArithmeticExpression, can_create_exp)
{
    string str = "A+B";
    ASSERT_NO_THROW(TArithmeticExpression expression(str));
}

TEST(TArithmeticExpression, expression_can_consist_of_a_letter_variable)
{
    string str = "A+B*C";
    map<string, double> values = { {"A",1},{"B",2},{"C",3} };
    TArithmeticExpression expression(str);
    EXPECT_EQ(7, expression.Calculate(values));
}

TEST(TArithmeticExpression, throw_then_last_symbol_is_operator)
{
    string str = "A+B*";
    map<string, double> values = { {"A",1},{"B",2}};
    TArithmeticExpression expression(str);
    ASSERT_ANY_THROW(expression.Calculate(values));
}

TEST(TArithmeticExpression, throw_then_first_symbol_is_minus)
{
    string str = "-A";
    map<string, double> values = { {"A",1} };
    TArithmeticExpression expression(str);
    ASSERT_ANY_THROW(expression.Calculate(values));
}

TEST(TArithmeticExpression, expression_can_consist_of_const)
{
    string str = "1+2*1.5";
    TArithmeticExpression expression(str);
    EXPECT_EQ(4, expression.Calculate());
}

TEST(TArithmeticExpression, expression_can_consist_of_a_multi_letter_variable)
{
    string str = "A1+A4/A2";
    map<string, double> values = { {"A1",1},{"A4",4},{"A2",2} };
    TArithmeticExpression expression(str);
    EXPECT_EQ(3, expression.Calculate(values));
}

TEST(TArithmeticExpression, can_not_divide_by_zero)
{
    string str = "1/X";
    map<string, double> values = { {"X",0} };
    TArithmeticExpression expression(str);
    ASSERT_ANY_THROW(expression.Calculate(values));
}

TEST(TArithmeticExpression, checking_infix_form_is_correct)
{
    string str = "(A+B)";
    TArithmeticExpression expression(str);
    EXPECT_EQ(1, expression.isCorrectInfixExpression());
}

TEST(TArithmeticExpression, checking_infix_form_is_not_correct)
{
    string str = "(A+B";
    TArithmeticExpression expression(str);
    EXPECT_EQ(0, expression.isCorrectInfixExpression());
}
