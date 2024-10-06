#include <random>

#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_vector.hpp>
#include "catch2/generators/catch_generators.hpp"
#include "catch2/generators/catch_generators_range.hpp"

extern "C" {
#include "nth_element.h"
}

std::uint_least32_t seed = 31123123;
static std::mt19937 rand_gen(seed);
static std::uniform_int_distribution distrib(-1000, 1000);
static auto gen = [](){
    return distrib(rand_gen);
};

TEST_CASE("Quickselect works", "[nth-element]") {
    SECTION("for a sorted array") {
        auto data = std::vector{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
        int n = static_cast<int>(data.size());

        CHECK(quick_select(data.data(), n, 0) == 1);
        CHECK(quick_select(data.data(), n, 1) == 2);
        CHECK(quick_select(data.data(), n, 2) == 3);
        CHECK(quick_select(data.data(), n, 3) == 4);
        CHECK(quick_select(data.data(), n, 4) == 5);
        CHECK(quick_select(data.data(), n, 5) == 6);
        CHECK(quick_select(data.data(), n, 6) == 7);
        CHECK(quick_select(data.data(), n, 7) == 8);
        CHECK(quick_select(data.data(), n, 8) == 9);
        CHECK(quick_select(data.data(), n, 9) == 10);
    }
    SECTION("for an array sorted in reverse order") {
        auto data = std::vector{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
        std::reverse(data.begin(), data.end());
        int n = static_cast<int>(data.size());

        CHECK(quick_select(data.data(), n, 0) == 1);
        CHECK(quick_select(data.data(), n, 1) == 2);
        CHECK(quick_select(data.data(), n, 2) == 3);
        CHECK(quick_select(data.data(), n, 3) == 4);
        CHECK(quick_select(data.data(), n, 4) == 5);
        CHECK(quick_select(data.data(), n, 5) == 6);
        CHECK(quick_select(data.data(), n, 6) == 7);
        CHECK(quick_select(data.data(), n, 7) == 8);
        CHECK(quick_select(data.data(), n, 8) == 9);
        CHECK(quick_select(data.data(), n, 9) == 10);
    }
    SECTION("for the big shuffled array") {
        auto n = GENERATE(100, 1000, 10000);
        std::vector<int> data(n);
        std::generate(data.begin(), data.end(), gen);

        auto data_sorted = std::vector(data);
        std::sort(data_sorted.begin(), data_sorted.end());

        for (int k = 0; k < 10; ++k)
            CHECK(median_of_median(data.data(), n, k) == data_sorted[k]);
        for (int k = n / 2 - 5; k < n / 2 + 5; ++k)
            CHECK(median_of_median(data.data(), n, k) == data_sorted[k]);
        for (int k = n - 10; k < n; ++k)
            CHECK(median_of_median(data.data(), n, k) == data_sorted[k]);
    }
    SECTION("for the shuffled array with different length") {
        auto n = GENERATE(range(1, 20));
        std::vector<int> data(n);
        std::generate(data.begin(), data.end(), gen);

        auto data_sorted = std::vector(data);
        std::sort(data_sorted.begin(), data_sorted.end());

        for (int k = 0; k < n; ++k)
            CHECK(median_of_median(data.data(), n, k) == data_sorted[k]);
    }
}

TEST_CASE("Median-median works", "[nth-element]") {
    SECTION("for a sorted array") {
        auto data = std::vector{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
        int n = static_cast<int>(data.size());

        CHECK(median_of_median(data.data(), n, 0) == 1);
        CHECK(median_of_median(data.data(), n, 1) == 2);
        CHECK(median_of_median(data.data(), n, 2) == 3);
        CHECK(median_of_median(data.data(), n, 3) == 4);
        CHECK(median_of_median(data.data(), n, 4) == 5);
        CHECK(median_of_median(data.data(), n, 5) == 6);
        CHECK(median_of_median(data.data(), n, 6) == 7);
        CHECK(median_of_median(data.data(), n, 7) == 8);
        CHECK(median_of_median(data.data(), n, 8) == 9);
        CHECK(median_of_median(data.data(), n, 9) == 10);
    }
    SECTION("for an array sorted in reverse order") {
        auto data = std::vector{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
        std::reverse(data.begin(), data.end());
        int n = static_cast<int>(data.size());

        CHECK(median_of_median(data.data(), n, 0) == 1);
        CHECK(median_of_median(data.data(), n, 1) == 2);
        CHECK(median_of_median(data.data(), n, 2) == 3);
        CHECK(median_of_median(data.data(), n, 3) == 4);
        CHECK(median_of_median(data.data(), n, 4) == 5);
        CHECK(median_of_median(data.data(), n, 5) == 6);
        CHECK(median_of_median(data.data(), n, 6) == 7);
        CHECK(median_of_median(data.data(), n, 7) == 8);
        CHECK(median_of_median(data.data(), n, 8) == 9);
        CHECK(median_of_median(data.data(), n, 9) == 10);
    }
    SECTION("for the big shuffled array") {
        auto n = GENERATE(100, 1000, 10000);
        std::vector<int> data(n);
        std::generate(data.begin(), data.end(), gen);

        auto data_sorted = std::vector(data);
        std::sort(data_sorted.begin(), data_sorted.end());

        for (int k = 0; k < 10; ++k)
            CHECK(median_of_median(data.data(), n, k) == data_sorted[k]);
        for (int k = n / 2 - 5; k < n / 2 + 5; ++k)
            CHECK(median_of_median(data.data(), n, k) == data_sorted[k]);
        for (int k = n - 10; k < n; ++k)
            CHECK(median_of_median(data.data(), n, k) == data_sorted[k]);
    }
    SECTION("for the shuffled array with different length") {
        auto n = GENERATE(range(1, 20));
        std::vector<int> data(n);
        std::generate(data.begin(), data.end(), gen);

        auto data_sorted = std::vector(data);
        std::sort(data_sorted.begin(), data_sorted.end());

        for (int k = 0; k < n; ++k)
            CHECK(median_of_median(data.data(), n, k) == data_sorted[k]);
    }
}
