#include "matrix.h"
#include <gtest.h>

TEST(TMatrix, can_create_matrix_with_positive_length)
{
	ASSERT_NO_THROW(TMatrix<int> m(5));
}

TEST(TMatrix, throws_when_create_matrix_with_negative_length)
{
	ASSERT_ANY_THROW(TMatrix<int> m(-5));
}

TEST(TMatrix, can_create_copied_matrix)
{
	TMatrix<int> m(5);

	ASSERT_NO_THROW(TMatrix<int> m1(m));
}


TEST(TMatrix, copied_matrix_is_equal_to_source_one)
{
	TMatrix<int> m(10);
	TMatrix<int> m1(m);
    EXPECT_EQ(m, m1);
}

TEST(TMatrix, can_get_size)
{
	TMatrix<int> m1(4);

    EXPECT_EQ(4, m1.GetSize());
}

TEST(TMatrix, can_set_and_get_element)
{
	TMatrix<int> m(3);
    m[0][0] = 4;

    EXPECT_EQ(4, m[0][0]);
}

TEST(TMatrix, throws_when_set_element_with_negative_index)
{
	TMatrix<int> m(3);
    ASSERT_ANY_THROW(m[-1][0]= 1);
}

TEST(TMatrix, can_assign_matrix_to_itself)
{
    TMatrix<int>m(4);
    ASSERT_NO_THROW(m = m);
}

TEST(TMatrix, can_assign_matrix_of_equal_size)
{
    TMatrix<int>m1(5);
    TMatrix<int>m2(5);
    EXPECT_EQ(m1.GetSize(), m2.GetSize());
}

TEST(TMatrix, assign_operator_change_matrix_size)
{
    TMatrix<int> m1(4);
    TMatrix<int> m2(5);
    ASSERT_NO_THROW(m1 = m2);
}

TEST(TMatrix, can_assign_matrix_of_different_size)
{

    TMatrix<int> m1(4);
    TMatrix<int> m2(5);
    ASSERT_NO_THROW(m1= m2);
}

TEST(TMatrix, compare_equal_matrix_return_true)
{
    TMatrix<int> m1(4);
    TMatrix<int> m2(4);
    ASSERT_NO_THROW(m1 == m2);
}

TEST(TMatrix, compare_matrix_with_itself_return_true)
{
    TMatrix<int> m1(4);
    EXPECT_EQ(m1 == m1, 1);
}


TEST(TMatrix, matrix_with_different_size_are_not_equal)
{
    TMatrix<int> m1(4);
    TMatrix<int> m2(5);
    ASSERT_TRUE(m1 != m2);
}

TEST(TMatrix, checking_the_corresponding_matrix)
{
	TMatrix<int> m1(5);
	TMatrix<int> m2(5);

	for (int i = 0; i < 5; i++)
		for (int j = 0; j < 5 - i; j++)
		{
			m1[i][j] = i;
			m2[i][j] = i + 1;
		}

	ASSERT_TRUE(m1 != m2);
}

TEST(TMatrix, can_add_matrices_with_equal_size)
{
	TMatrix<int> m1(3), m2(3), m3(3);
	m1[0][0] = 1;
	m2[0][0] = 2;
	m3 = m1 + m2;
	EXPECT_EQ(3, m3[0][0]);
}

TEST(TMatrix, cannot_plus_with_not_equal_size)
{
	TMatrix<int> m1(7);
	TMatrix<int> m2(8);
	ASSERT_ANY_THROW(m1 + m2);
}

TEST(TMatrix, can_subtract_matrices_with_equal_size)
{
	TMatrix<int> m1(3), m2(3), m3(3);
	m1[0][0] = 1;
	m2[0][0] = 2;
	m3 = m1 - m2;
	EXPECT_EQ(-1, m3[0][0]);
}

TEST(TMatrix, cant_subtract_matrixes_with_not_equal_size)
{
	TMatrix<int> m1(4), m2(5);
	ASSERT_ANY_THROW(TMatrix<int> res(m1 - m2));
}

TEST(TMatrix, can_mult_with_equal_size)
{
	TMatrix<int> m1(3), m2(3), m3(3);
	m1[0][0] = 1;
	m2[0][0] = 2;
	m3 = m1*m2;
	EXPECT_EQ(2, m3[0][0]);
}

TEST(TMatrix, cant_mult_with_not_equal_size)
{
	TMatrix<int> m1(1);
	TMatrix<int> m2(2);
	ASSERT_ANY_THROW(m1 * m2);
}