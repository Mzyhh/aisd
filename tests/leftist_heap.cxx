#include <algorithm>
#include <array>
#include <iostream>
#include <random>
#include <ranges>
#include <set>
#include <unordered_set>

#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators.hpp>
#include <catch2/generators/catch_generators_all.hpp>
#include <catch2/generators/catch_generators_adapters.hpp>

#include "catch2/matchers/catch_matchers.hpp"

extern "C" {
#include "leftist_heap.h"
}

int try_count = 10;

std::vector<int> iterate_out;
auto iterate_callback = [](int v) { iterate_out.push_back(v); };

std::vector<int> create_vector(const uint32_t seed, const int n, bool unique) {
    if (n == 0)
        return {};

    std::mt19937 rand_gen(seed);
    std::uniform_int_distribution distrib(0, 1000);
    auto gen = [&distrib, &rand_gen]() {
        return distrib(rand_gen);
    };

    if (!unique) {
        std::vector<int> res(n);
        std::ranges::generate(res, gen);
        return res;
    }

    for (int i = 1; i <= 10; i++) {
        std::unordered_set<int> seen;
        std::vector<int> raw(i * n);
        std::ranges::generate(raw, gen);
        std::vector<int> result;
        for (auto num : raw)
            if (seen.insert(num).second) {
                result.push_back(num);
                if (result.size() == n)
                    return result;
            }
    }
    throw std::logic_error("Too many attempts when generating a random vector");
}

std::vector<int> get_random_subset(const uint32_t seed, std::vector<int> input, int n) {
    std::mt19937 gen(seed);
    std::ranges::shuffle(input, gen);
    input.resize(n);
    return input;
}

void shuffle_vector(const uint32_t seed, std::vector<int>& input) {
    std::mt19937 gen(seed);
    std::ranges::shuffle(input, gen);
}

TEST_CASE("Leftist heap works", "[leftist-heap]") {
    SECTION("build works") {
        GENERATE(repeat(try_count, value(0)));
        const int n = GENERATE(range(1, 100, 5));
        const auto seed = Catch::Generators::Detail::getSeed();
        auto numbers = create_vector(seed, n, false);

        auto heap = leftist_build(numbers.data(), n);
        auto expected = std::ranges::max_element(numbers);
        auto actual = leftist_get_max(&heap);
        REQUIRE(actual == *expected);
    }
    SECTION("insert works") {
        GENERATE(repeat(try_count, value(0)));
        const int n = GENERATE(range(1, 100, 5));

        std::vector<int> added_numbers;
        auto heap = leftist_build(added_numbers.data(), 0);

        const auto seed = Catch::Generators::Detail::getSeed();
        auto numbers = create_vector(seed, n, false);

        for (auto num : numbers) {
            leftist_insert(&heap, num);
            added_numbers.push_back(num);
            auto expected = std::ranges::max_element(added_numbers);
            auto actual = leftist_get_max(&heap);
            REQUIRE(actual == *expected);
        }
    }
    SECTION("get_max/delete_max works") {
        GENERATE(repeat(try_count, value(0)));
        const int n = GENERATE(range(0, 100, 5));
        const auto seed = Catch::Generators::Detail::getSeed();
        auto numbers = create_vector(seed, n, false);

        auto heap = leftist_build(numbers.data(), n);

        auto sorted_numbers = std::vector(numbers.begin(), numbers.end());
        std::ranges::sort(sorted_numbers, std::ranges::greater());

        for (auto const [i, expected] : std::views::enumerate(sorted_numbers))
        {
            auto actual = leftist_get_max(&heap);
            leftist_delete_max(&heap);
            REQUIRE(actual == expected);
        }
    }
    SECTION("delete works") {
        GENERATE(repeat(try_count, value(0)));
        const int n = GENERATE(range(0, 100, 5));
        const auto seed = Catch::Generators::Detail::getSeed();
        auto numbers = create_vector(seed, n, false);
        auto heap = leftist_build(numbers.data(), n);

        shuffle_vector(seed, numbers);
        auto left_numbers = std::vector(numbers.begin(), numbers.end());
        for (auto num: numbers)
        {
            leftist_delete(&heap, num);
            auto it = std::ranges::find(left_numbers, num);
            left_numbers.erase(it);

            auto actual = leftist_get_max(&heap);
            auto expected = std::ranges::max_element(numbers);
            REQUIRE(actual == *expected);
        }
    }
}
