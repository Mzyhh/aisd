#include "gtest/gtest.h"
#include "gmock/gmock.h"

extern "C" {
#include "sort.h"
}

TEST(BubbleSort, EmptyArray) {
    int a[] = {};
    bubble_sort(a, 0);
    EXPECT_THAT(std::vector(a, a + 0), testing::IsEmpty());
}

TEST(BubbleSort, SingleElement) {
    int a[] = {10};
    bubble_sort(a, 1);
    EXPECT_THAT(std::vector(a, a + 1), testing::ElementsAre(10));
}

TEST(BubbleSort, AlreadySorted) {
    int a[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    bubble_sort(a, 10);
    EXPECT_THAT(std::vector(a, a + 10), testing::ElementsAre(1, 2, 3, 4, 5, 6, 7, 8, 9, 10));
}

TEST(BubbleSort, AlreadyDescSorted) {
    int a[] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
    bubble_sort(a, 10);
    EXPECT_THAT(std::vector(a, a + 10), testing::ElementsAre(1, 2, 3, 4, 5, 6, 7, 8, 9, 10));
}

TEST(BubbleSort, Shuffled1) {
    int a[] = {1, 10, 5, 9, 6, 7, 4, 8, 2, 3};
    bubble_sort(a, 10);
    EXPECT_THAT(std::vector(a, a + 10), testing::ElementsAre(1, 2, 3, 4, 5, 6, 7, 8, 9, 10));
}

TEST(BubbleSort, Shuffled2) {
    int a[] = {5, 7, 2, 9, 6, 10, 8, 1, 4, 3};
    bubble_sort(a, 10);
    EXPECT_THAT(std::vector(a, a + 10), testing::ElementsAre(1, 2, 3, 4, 5, 6, 7, 8, 9, 10));
}

TEST(BubbleSort, Repeat) {
    int a[] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
    bubble_sort(a, 10);
    EXPECT_THAT(std::vector(a, a + 10), testing::Contains(1).Times(10));
}

TEST(BubbleSort, WithCollisions) {
    int a[] = {1, 5, 5, 5, 5, 7, 4, 8, 2, 3};
    bubble_sort(a, 10);
    EXPECT_THAT(std::vector(a, a + 10), testing::ElementsAre(1, 2, 3, 4, 5, 5, 5, 5, 7, 8));
}


TEST(InsertionSort, EmptyArray) {
    int a[] = {};
    insertion_sort(a, 0);
    EXPECT_THAT(std::vector(a, a + 0), testing::IsEmpty());
}

TEST(InsertionSort, SingleElement) {
    int a[] = {10};
    insertion_sort(a, 1);
    EXPECT_THAT(std::vector(a, a + 1), testing::ElementsAre(10));
}

TEST(InsertionSort, AlreadySorted) {
    int a[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    insertion_sort(a, 10);
    EXPECT_THAT(std::vector(a, a + 10), testing::ElementsAre(1, 2, 3, 4, 5, 6, 7, 8, 9, 10));
}

TEST(InsertionSort, AlreadyDescSorted) {
    int a[] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
    insertion_sort(a, 10);
    EXPECT_THAT(std::vector(a, a + 10), testing::ElementsAre(1, 2, 3, 4, 5, 6, 7, 8, 9, 10));
}

TEST(InsertionSort, Shuffled1) {
    int a[] = {1, 10, 5, 9, 6, 7, 4, 8, 2, 3};
    insertion_sort(a, 10);
    EXPECT_THAT(std::vector(a, a + 10), testing::ElementsAre(1, 2, 3, 4, 5, 6, 7, 8, 9, 10));
}

TEST(InsertionSort, Shuffled2) {
    int a[] = {5, 7, 2, 9, 6, 10, 8, 1, 4, 3};
    insertion_sort(a, 10);
    EXPECT_THAT(std::vector(a, a + 10), testing::ElementsAre(1, 2, 3, 4, 5, 6, 7, 8, 9, 10));
}

TEST(InsertionSort, Repeat) {
    int a[] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
    insertion_sort(a, 10);
    EXPECT_THAT(std::vector(a, a + 10), testing::Contains(1).Times(10));
}

TEST(InsertionSort, WithCollisions) {
    int a[] = {1, 5, 5, 5, 5, 7, 4, 8, 2, 3};
    insertion_sort(a, 10);
    EXPECT_THAT(std::vector(a, a + 10), testing::ElementsAre(1, 2, 3, 4, 5, 5, 5, 5, 7, 8));
}


TEST(SelectionSort, EmptyArray) {
    int a[] = {};
    selection_sort(a, 0);
    EXPECT_THAT(std::vector(a, a + 0), testing::IsEmpty());
}

TEST(SelectionSort, SingleElement) {
    int a[] = {10};
    selection_sort(a, 1);
    EXPECT_THAT(std::vector(a, a + 1), testing::ElementsAre(10));
}

TEST(SelectionSort, AlreadySorted) {
    int a[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    selection_sort(a, 10);
    EXPECT_THAT(std::vector(a, a + 10), testing::ElementsAre(1, 2, 3, 4, 5, 6, 7, 8, 9, 10));
}

TEST(SelectionSort, AlreadyDescSorted) {
    int a[] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
    selection_sort(a, 10);
    EXPECT_THAT(std::vector(a, a + 10), testing::ElementsAre(1, 2, 3, 4, 5, 6, 7, 8, 9, 10));
}

TEST(SelectionSort, Shuffled1) {
    int a[] = {1, 10, 5, 9, 6, 7, 4, 8, 2, 3};
    selection_sort(a, 10);
    EXPECT_THAT(std::vector(a, a + 10), testing::ElementsAre(1, 2, 3, 4, 5, 6, 7, 8, 9, 10));
}

TEST(SelectionSort, Shuffled2) {
    int a[] = {5, 7, 2, 9, 6, 10, 8, 1, 4, 3};
    selection_sort(a, 10);
    EXPECT_THAT(std::vector(a, a + 10), testing::ElementsAre(1, 2, 3, 4, 5, 6, 7, 8, 9, 10));
}

TEST(SelectionSort, Repeat) {
    int a[] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
    selection_sort(a, 10);
    EXPECT_THAT(std::vector(a, a + 10), testing::Contains(1).Times(10));
}

TEST(SelectionSort, WithCollisions) {
    int a[] = {1, 5, 5, 5, 5, 7, 4, 8, 2, 3};
    selection_sort(a, 10);
    EXPECT_THAT(std::vector(a, a + 10), testing::ElementsAre(1, 2, 3, 4, 5, 5, 5, 5, 7, 8));
}


TEST(MergeSort, EmptyArray) {
    int a[] = {};
    int* res = merge_sort(a, 0);
    EXPECT_THAT(std::vector(res, res + 0), testing::IsEmpty());
}

TEST(MergeSort, SingleElement) {
    int a[] = {10};
    int* res = merge_sort(a, 1);
    EXPECT_THAT(std::vector(res, res + 1), testing::ElementsAre(10));
}

TEST(MergeSort, AlreadySorted) {
    int a[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int* res = merge_sort(a, 10);
    EXPECT_THAT(std::vector(res, res + 10), testing::ElementsAre(1, 2, 3, 4, 5, 6, 7, 8, 9, 10));
}

TEST(MergeSort, AlreadyDescSorted) {
    int a[] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
    int* res = merge_sort(a, 10);
    EXPECT_THAT(std::vector(res, res + 10), testing::ElementsAre(1, 2, 3, 4, 5, 6, 7, 8, 9, 10));
}

TEST(MergeSort, Shuffled1) {
    int a[] = {1, 10, 5, 9, 6, 7, 4, 8, 2, 3};
    int* res = merge_sort(a, 10);
    EXPECT_THAT(std::vector(res, res + 10), testing::ElementsAre(1, 2, 3, 4, 5, 6, 7, 8, 9, 10));
}

TEST(MergeSort, Shuffled2) {
    int a[] = {5, 7, 2, 9, 6, 10, 8, 1, 4, 3};
    int* res = merge_sort(a, 10);
    EXPECT_THAT(std::vector(res, res + 10), testing::ElementsAre(1, 2, 3, 4, 5, 6, 7, 8, 9, 10));
}

TEST(MergeSort, Repeat) {
    int a[] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
    int* res = merge_sort(a, 10);
    EXPECT_THAT(std::vector(res, res + 10), testing::Contains(1).Times(10));
}

TEST(MergeSort, WithCollisions) {
    int a[] = {1, 5, 5, 5, 5, 7, 4, 8, 2, 3};
    int* res = merge_sort(a, 10);
    EXPECT_THAT(std::vector(res, res + 10), testing::ElementsAre(1, 2, 3, 4, 5, 5, 5, 5, 7, 8));
}
