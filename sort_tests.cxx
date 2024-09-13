#include "gtest/gtest.h"
#include "gmock/gmock.h"

extern "C" {
#include "sorts.h"
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

TEST(BubbleSort, DuplicateEntry) {
    int a[] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
    bubble_sort(a, 10);
    EXPECT_THAT(std::vector(a, a + 10), testing::Contains(1).Times(10));
}
