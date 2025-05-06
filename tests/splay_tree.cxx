#include <algorithm>
#include <array>
#include <iostream>
#include <random>
#include <set>
#include <unordered_set>

#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators.hpp>
#include <catch2/generators/catch_generators_all.hpp>
#include <catch2/generators/catch_generators_adapters.hpp>

#include "catch2/matchers/catch_matchers.hpp"
#include "catch2/matchers/catch_matchers_vector.hpp"

extern "C" {
#include "splay_tree.h"
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
        for (int num : raw)
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

TEST_CASE("Splay tree works", "[splay-tree]") {
    SECTION("insert works") {
        GENERATE(repeat(try_count, value(0)));
        const int n = GENERATE(range(0, 100, 5));
        const auto seed = Catch::Generators::Detail::getSeed();
        auto unique_numbers = create_vector(seed, n, true);

        const splay_node *tree = nullptr;
        for (int num : unique_numbers)
            tree = splay_insert(tree, num);

        iterate_out.clear();
        splay_traverse(tree, iterate_callback);

        auto expected = std::vector(unique_numbers.begin(), unique_numbers.end());
        std::ranges::sort(expected);

        REQUIRE_THAT(iterate_out, Catch::Matchers::Equals(expected));
    }
    SECTION("remove works") {
        GENERATE(repeat(try_count, value(0)));
        const int n = GENERATE(range(0, 100, 5));
        const auto seed = Catch::Generators::Detail::getSeed();
        auto unique_numbers = create_vector(seed, n, true);

        const splay_node *tree = nullptr;
        for (int num : unique_numbers)
            tree = splay_insert(tree, num);

        auto expected = std::vector(unique_numbers.begin(), unique_numbers.end());
        auto to_delete = get_random_subset(seed, unique_numbers, n / 2);
        for (int num : to_delete) {
            tree = splay_remove(tree, num);
            std::erase(expected, num);
        }

        iterate_out.clear();
        splay_traverse(tree, iterate_callback);

        REQUIRE_THAT(iterate_out, Catch::Matchers::Equals(expected));
    }
}
