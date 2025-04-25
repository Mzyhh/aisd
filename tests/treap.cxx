#include <algorithm>
#include <array>
#include <iostream>
#include <random>
#include <set>

#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators.hpp>
#include <catch2/generators/catch_generators_all.hpp>
#include <catch2/generators/catch_generators_adapters.hpp>

#include "catch2/matchers/catch_matchers.hpp"
#include "catch2/matchers/catch_matchers_vector.hpp"

extern "C" {
#include "treap.h"
}

std::uint_least32_t seed = 31123123;
static std::mt19937 rand_gen(seed);
static std::uniform_int_distribution distrib(0, 1000);
static auto gen = []() {
    return distrib(rand_gen);
};

static int n_max = 15;
static int iterations_count = 10;

std::vector<int> iterate_out;
auto iterate_callback = [](int v) { iterate_out.push_back(v); };

std::vector<int> get_sorted_unique(const std::vector<int>& arr) {
    std::vector res = arr;

    std::sort(res.begin(), res.end());
    auto last = std::unique(res.begin(), res.end());
    res.erase(last, res.end());
    return res;
}

TEST_CASE("Treap works", "[treap]") {
    SECTION("build works") {
        int n = GENERATE(range(0, n_max + 1));
        std::vector<int> numbers(n);
        std::ranges::generate(numbers, gen);
        std::vector to_insert = numbers;
        numbers = get_sorted_unique(numbers);

        auto treap = build_treap(to_insert.data(), to_insert.size());

        iterate_out.clear();
        iterate_treap(&treap, iterate_callback);

        REQUIRE_THAT(iterate_out, Catch::Matchers::Equals(numbers));
    }
    SECTION("build works for big array") {
        int n = GENERATE(range(10000, 10010));
        std::vector<int> numbers(n);
        std::ranges::generate(numbers, gen);
        std::vector to_insert = numbers;
        numbers = get_sorted_unique(numbers);

        auto treap = build_treap(to_insert.data(), to_insert.size());

        iterate_out.clear();
        iterate_treap(&treap, iterate_callback);

        REQUIRE_THAT(iterate_out, Catch::Matchers::Equals(numbers));
    }
    SECTION("insert works") {
        int n = GENERATE(range(0, n_max + 1));
        std::vector<int> numbers(n);
        std::ranges::generate(numbers, gen);

        std::vector<int> empty;
        std::vector to_insert = numbers;

        auto treap = build_treap(empty.data(), empty.size());
        iterate_out.clear();
        iterate_treap(&treap, iterate_callback);
        REQUIRE_THAT(iterate_out, Catch::Matchers::Equals(empty));

        for (int v: to_insert)
            add_number(&treap, v);
        iterate_out.clear();
        iterate_treap(&treap, iterate_callback);
        to_insert = get_sorted_unique(to_insert);
        REQUIRE_THAT(iterate_out, Catch::Matchers::Equals(to_insert));
    }
    SECTION("delete works") {
        int n = GENERATE(range(0, n_max + 1));
        std::vector<int> numbers(n);
        std::ranges::generate(numbers, gen);
        std::vector to_insert = numbers;

        auto treap = build_treap(to_insert.data(), to_insert.size());

        std::vector left = numbers;
        for (int v: to_insert) {
            delete_number(&treap, v);
            iterate_out.clear();
            iterate_treap(&treap, iterate_callback);

            left.erase(std::remove(left.begin(), left.end(), v), left.end());
            std::vector left_uniq = get_sorted_unique(left);

            REQUIRE_THAT(iterate_out, Catch::Matchers::Equals(left_uniq));
        }
    }

    SECTION("numbers count works") {
        int n = GENERATE(range(1, n_max + 1));
        std::vector<int> numbers(n);
        std::ranges::generate(numbers, gen);
        numbers = get_sorted_unique(numbers);

        auto treap = build_treap(numbers.data(), numbers.size());

        int l = GENERATE_REF(take(iterations_count, random(0, 1000)));
        int r = GENERATE_REF(take(iterations_count, random(0, 1000)));

        int expected = std::count_if(
            numbers.cbegin(),
            numbers.cend(),
            [l, r](int v) {return v >= l && v < r;});
        int actual = get_numbers_count(&treap, l, r);
        CHECK(actual == expected);
    }

    SECTION("statistics iteration works") {
        int n = GENERATE(range(1, n_max + 1));
        std::vector<int> numbers(n);
        std::ranges::generate(numbers, gen);
        numbers = get_sorted_unique(numbers);

        auto treap = build_treap(numbers.data(), numbers.size());

        int k = GENERATE_REF(take(iterations_count, random(0, n - 1)));
        int m = GENERATE_REF(take(iterations_count, random(1, n - k)));

        std::vector expected = std::vector(numbers.cbegin() + k, numbers.cbegin() + k + m);
        iterate_out.clear();
        iterate_statistics(&treap, k, m, iterate_callback);
        REQUIRE_THAT(iterate_out, Catch::Matchers::Equals(expected));
    }
}
