#include "arithmetic.h"
#include <gtest.h>

TEST(TArithmeticExpression, can_create_exp)
{
    string str = "A+B";
    ASSERT_NO_THROW(TArithmeticExpression expression(str));
}
