#include "THeadRingList.h"
#include <gtest.h>

TEST(THeadRingList, can_create_THeadRingList) {
	THeadRingList<int> list;
}

TEST(THeadRingList, can_insert_element) {
	THeadRingList<int> list;
	list.insert_last(1);
	EXPECT_EQ(1, list.GetCurrent()->data);
}

TEST(THeadRingList, can_get_next_elemet)
{
	THeadRingList<int> list;
	list.insert_last(1);
	list.insert_last(2);
	list.next();
	EXPECT_EQ(2, list.GetCurrent()->data);
}

TEST(THeadRingList, can_remove_element)
{
	THeadRingList<int> list;
	list.insert_last(1);
	list.insert_last(2);
	list.insert_last(3);
	list.remove(3);
	EXPECT_EQ(2, list.GetSize());
}

TEST(THeadRingList, check_list_is_ring)
{
	THeadRingList<int> list;
	list.insert_last(1);
	list.insert_last(2);
	list.next(); list.next(); list.next();
	ASSERT_NO_THROW(list.GetCurrent()->data);
}

TEST(THeadRingList, get_next_element_in_ring)
{
	THeadRingList<int> list;
	list.insert_last(1);
	list.insert_last(2);
	list.next(); list.next(); list.next(); 
	EXPECT_EQ(2,list.GetCurrent()->data);
}

TEST(THeadRingList, can_insert_element_at_beginning)
{
	THeadRingList<int> list;
	list.insert_last(1);
	list.insert_first(2);
	EXPECT_EQ(2, list.GetCurrent()->data);
}

TEST(THeadRingList, can_insert_element_in_middle)
{
	THeadRingList<int> list;
	list.insert_last(1);
	list.insert_last(3);
	list.insert_after(2, list.GetCurrent()->data); 
	list.next(); 
	EXPECT_EQ(2, list.GetCurrent()->data);
}

//TEST(THeadRingList, can_remove_first_element)
//{
//	THeadRingList<int> list;
//	list.insert_last(1);
//	list.insert_last(2);
//	list.remove(1);
//	list.next();
//	EXPECT_EQ(2, list.GetCurrent()->data);
//}

TEST(THeadRingList, can_remove_last_element)
{
	THeadRingList<int> list;
	list.insert_last(1);
	list.insert_last(2);
	list.remove(2);
	EXPECT_EQ(1, list.GetCurrent()->data);
}

TEST(THeadRingList, can_get_size)
{
	THeadRingList<int> list;
	list.insert_last(1);
	list.insert_last(2);
	list.insert_last(3);
	EXPECT_EQ(3, list.GetSize());
}

TEST(THeadRingList, can_clear_list)
{
	THeadRingList<int> list;
	list.insert_last(1);
	list.insert_last(2);
	list.insert_last(3);
	list.clear();
	EXPECT_EQ(0, list.GetSize());
	EXPECT_EQ(nullptr, list.GetCurrent());
}

TEST(THeadRingList, can_insert_multiple_elements)
{
	THeadRingList<int> list;
	list.insert_last(1);
	list.insert_last(2);
	list.insert_last(3);
	EXPECT_EQ(3, list.GetSize());
	list.reset();
	EXPECT_EQ(1, list.GetCurrent()->data);
}

TEST(THeadRingList, can_insert_element_before_current)
{
	THeadRingList<int> list;
	list.insert_last(1);
	list.insert_last(3);
	list.insert_before(2, list.GetCurrent()->data); 
	list.reset();
	EXPECT_EQ(2, list.GetCurrent()->data);
}

TEST(THeadRingList, can_insert_element_after_current)
{
	THeadRingList<int> list;
	list.insert_last(1);
	list.insert_last(3);
	list.insert_after(2, list.GetCurrent()->data); 
	list.next();
	EXPECT_EQ(2, list.GetCurrent()->data);
}

//// “ест провер€ет вставку монома в пустой список
//TEST(THeadRingList, can_insert_to_empty_sorted_list)
//{
//	THeadRingList<TMonom> list;
//	TMonom m1(1, 2.0); // degree = 1
//
//	list.InsertToSort(m1);
//
//	EXPECT_EQ(1, list.GetSize()); // ѕровер€ем, что размер списка равен 1
//	list.Reset();
//	EXPECT_EQ(1, list.GetCurrent()->data.degree); // ѕровер€ем, что моном вставлен верно
//}
//
//// “ест провер€ет вставку монома в начало отсортированного списка
//TEST(THeadRingList, can_insert_to_beginning_of_sorted_list)
//{
//	THeadRingList<TMonom> list;
//	TMonom m1(1, 2.0); // degree = 1
//	TMonom m2(2, 3.0); // degree = 2
//	TMonom m3(3, 4.0); // degree = 3
//
//	list.InsertToSort(m3);
//	list.InsertToSort(m2);
//	list.InsertToSort(m1);
//
//	EXPECT_EQ(3, list.GetSize()); // ѕровер€ем, что размер списка равен 3
//	list.Reset();
//	EXPECT_EQ(1, list.GetCurrent()->data.degree); // ѕровер€ем, что мономы вставлены в правильном пор€дке
//	list.Next();
//	EXPECT_EQ(2, list.GetCurrent()->data.degree);
//	list.Next();
//	EXPECT_EQ(3, list.GetCurrent()->data.degree);
//}
//
//// “ест провер€ет вставку монома в середину отсортированного списка
//TEST(THeadRingList, can_insert_to_middle_of_sorted_list)
//{
//	THeadRingList<TMonom> list;
//	TMonom m1(1, 2.0); // degree = 1
//	TMonom m2(3, 3.0); // degree = 3
//	TMonom m3(5, 5.0); // degree = 5
//
//	list.InsertToSort(m3);
//	list.InsertToSort(m1);
//	list.InsertToSort(m2);
//
//	TMonom m4(4, 4.0); // degree = 4
//	list.InsertToSort(m4);
//
//	EXPECT_EQ(4, list.GetSize()); // ѕровер€ем, что размер списка равен 4
//	list.Reset();
//	EXPECT_EQ(1, list.GetCurrent()->data.degree); // ѕровер€ем, что мономы вставлены в правильном пор€дке
//	list.Next();
//	EXPECT_EQ(3, list.GetCurrent()->data.degree);
//	list.Next();
//	EXPECT_EQ(4, list.GetCurrent()->data.degree);
//	list.Next();
//	EXPECT_EQ(5, list.GetCurrent()->data.degree);
//}


//TEST(THeadRingList, can_sum_coefficients_of_equal_degrees)
//{
//	THeadRingList<int> list;
//
//	list.InsertToSort(1);
//	list.InsertToSort(5);
//	list.InsertToSort(2);
//
//	EXPECT_EQ(1, list.GetCurrent()->data); 
//	list.next();
//	EXPECT_EQ(2, list.GetCurrent()->data);
//	list.next();
//	EXPECT_EQ(5, list.GetCurrent()->data);
//}