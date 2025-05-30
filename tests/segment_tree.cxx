#include <algorithm>
#include <array>
#include <iostream>
#include <random>
#include <set>

#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators.hpp>
#include <catch2/generators/catch_generators_all.hpp>
#include <catch2/generators/catch_generators_adapters.hpp>

extern "C" {
#include "segment_tree.h"
}

std::uint_least32_t seed = 31123123;
static std::mt19937 rand_gen(seed);
static std::uniform_int_distribution distrib(0, 1000);
static auto gen = []() {
    return distrib(rand_gen);
};

static int n_max = 15;
static int iterations_count = 10;

int get_max_on_interval(const std::vector<int>& arr, int l, int r) {
    auto max_value = std::numeric_limits<int>::lowest();
    for (int i = l; i <= r; ++i) {
        if (arr[i] > max_value)
            max_value = std::max(max_value, arr[i]);
    }
    return max_value;
}

TEST_CASE("Segment tree works", "[segment-tree]") {
    SECTION("all possible cases for small arrays") {
        int n = GENERATE(range(1, n_max + 1));
        std::vector<int> numbers(n);
        std::ranges::generate(numbers, gen);

        auto structure = build_segment_tree(numbers.data(), n);

        int l = GENERATE_REF(range(0, n));
        int r = GENERATE_REF(range(l, n));

        int actual = get_max(&structure, l, r);
        int expected = get_max_on_interval(numbers, l, r);

        CHECK(actual == expected);
    }

    SECTION("query works") {
        int n = GENERATE(take(iterations_count, random(1000, 10000)));
        std::vector<int> numbers(n);
        std::ranges::generate(numbers, gen);

        auto structure = build_segment_tree(numbers.data(), n);

        int l = GENERATE_REF(take(iterations_count, random(0, n - 1)));
        int r = GENERATE_REF(take(iterations_count, random(l, n - 1)));

        int actual = get_max(&structure, l, r);
        int expected = get_max_on_interval(numbers, l, r);

        CHECK(actual == expected);
    }

//  SECTION("single update work") {
//      int n = GENERATE(take(iterations_count, random(1000, 10000)));
//      std::vector<int> numbers(n);
//      std::ranges::generate(numbers, gen);

//      auto structure = build_segment_tree(numbers.data(), n);

//      int ul = GENERATE_REF(take(iterations_count, random(0, n - 1)));
//      int ur = GENERATE_REF(take(iterations_count, random(ul, n - 1)));

//      int set_min_value = numbers[ul];
//      set_min(&structure, ul, ur, set_min_value);

//      for (int i = ul; i <= ur; ++i) {
//          numbers[i] = std::min(numbers[i], set_min_value);
//      }

//      int ql = GENERATE_REF(take(iterations_count, random(0, n - 1)));
//      int qr = GENERATE_REF(take(iterations_count, random(ql, n - 1)));

//      int actual = get_max(&structure, ql, qr);
//      int expected = get_max_on_interval(numbers, ql, qr);

//      CHECK(actual == expected);
//  }

    SECTION("multiple updates work") {
        int n = GENERATE(take(iterations_count, random(1000, 6075)));
        std::vector<int> numbers(n);
        std::ranges::generate(numbers, gen);

        auto structure = build_segment_tree(numbers.data(), n);

        int ul = GENERATE_REF(take(iterations_count, random(0, n - 1)));
        int ur = GENERATE_REF(take(iterations_count, random(ul, n - 1)));

        for (int i = 0; i < 5; ++i) {
            ul = (106 * ul  + 1283) % 6075 % n;
            ur = (106 * ur  + 1283) % 6075 % n;
            if (ur < ul)
                std::swap(ul, ur);

            int set_min_value = numbers[ul];
            set_min(&structure, ul, ur, set_min_value);

            for (int j = ul; j <= ur; ++j) {
                numbers[j] = std::min(numbers[j], set_min_value);
            }
        }

        int ql = GENERATE_REF(take(iterations_count, random(0, n - 1)));
        int qr = GENERATE_REF(take(iterations_count, random(ql, n - 1)));

        int actual = get_max(&structure, ql, qr);
        int expected = get_max_on_interval(numbers, ql, qr);

        CHECK(actual == expected);
    }
}
