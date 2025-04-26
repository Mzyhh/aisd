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
#include "distinct_numbers.h"
}

std::uint_least32_t seed = 31123123;
static std::mt19937 rand_gen(seed);
static std::uniform_int_distribution distrib1(0, 10);
static std::uniform_int_distribution distrib2(0, 1000);
static auto gen1 = []() {
    return distrib1(rand_gen);
};
static auto gen2 = []() {
    return distrib2(rand_gen);
};

static int n_max = 20;
static int iterations_count = 10;

int count_distinct(const std::vector<int> &numbers, int l, int r) {
    std::set<int> distinct_numbers;
    std::copy(
        numbers.begin() + l,
        numbers.begin() + r,
        std::inserter(distinct_numbers, distinct_numbers.begin()));

    return distinct_numbers.size();
}

TEST_CASE("structure works", "[distinct-numbers]") {
    SECTION("all possible cases for small arrays") {
        int n = GENERATE(range(1, n_max + 1));
        std::vector<int> numbers(n);
        std::ranges::generate(numbers, gen1);

        auto structure = build_structure(numbers.data(), n);

        int l = GENERATE_REF(range(0, n));
        int r = GENERATE_REF(range(l + 1, n + 1));
        // std::cout << "n=" << n << ", l=" << l << ", r=" << r << std::endl;

        int actual = get_distinct_number_count(&structure, l, r);
        int expected = count_distinct(numbers, l, r);

        CHECK(actual == expected);
    }

    SECTION("some random cases for big arrays") {
        int n = GENERATE(take(iterations_count, random(1000, 10000)));
        std::vector<int> numbers(n);
        std::ranges::generate(numbers, gen2);

        auto structure = build_structure(numbers.data(), n);

        auto l = GENERATE_REF(take(iterations_count, random(0, n - 1)));
        auto r = GENERATE_REF(take(iterations_count, random(l + 1, n)));
        // std::cout << "n=" << n << ", l=" << l << ", r=" << r << std::endl;

        int actual = get_distinct_number_count(&structure, l, r);
        int expected = count_distinct(numbers, l, r);

        CHECK(actual == expected);
    }
}
