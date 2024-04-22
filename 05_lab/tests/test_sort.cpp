#include <gtest.h>
#include "sort.h"

class SortingTest : public ::testing::Test {};


TEST(SortingTest, SimpleSortTest) {
    int arr[] = { 4, 2, 7, 1, 5 };
    int expected[] = { 1, 2, 4, 5, 7 };
    simple_sort(arr, 5);
    EXPECT_TRUE(std::equal(std::begin(arr), std::end(arr), std::begin(expected)));
}

TEST(SortingTest, ChooseSortTest) {
    int arr[] = { 4, 2, 7, 1, 5 };
    int expected[] = { 1, 2, 4, 5, 7 };
    choose_sort(arr, 5);
    EXPECT_TRUE(std::equal(std::begin(arr), std::end(arr), std::begin(expected)));
}

TEST(SortingTest, InsertionSortTest) {
    int arr[] = { 4, 2, 7, 1, 5 };
    int expected[] = { 1, 2, 4, 5, 7 };
    insertion_sort(arr, 5);
    EXPECT_TRUE(std::equal(std::begin(arr), std::end(arr), std::begin(expected)));
}

TEST(SortingTest, BubbleSortTest) {
    int arr[] = { 4, 2, 7, 1, 5 };
    int expected[] = { 1, 2, 4, 5, 7 };
    Bubble_sort(arr, 5);
    EXPECT_TRUE(std::equal(std::begin(arr), std::end(arr), std::begin(expected)));
}

TEST(SortingTest, MergeSortTest) {
    int arr[] = { 4, 2, 7, 1, 5 };
    int expected[] = { 1, 2, 4, 5, 7 };
    merge_sort(arr, 0, 4);
    EXPECT_TRUE(std::equal(std::begin(arr), std::end(arr), std::begin(expected)));
}

TEST(SortingTest, QuickSortTest) {
    int arr[] = { 4, 2, 7, 1, 5 };
    int expected[] = { 1, 2, 4, 5, 7 };
    QuickSort(arr, 5);
    EXPECT_TRUE(std::equal(std::begin(arr), std::end(arr), std::begin(expected)));
}

TEST(SortingTest, CountingSortTest) {
    int arr[] = { 4, 2, 7, 1, 5 };
    int expected[] = { 1, 2, 4, 5, 7 };
    CountingSort(arr, 5);
    EXPECT_TRUE(std::equal(std::begin(arr), std::end(arr), std::begin(expected)));
}
