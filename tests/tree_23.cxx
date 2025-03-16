#include <algorithm>
#include <array>
#include <iostream>
#include <random>
#include <ranges>
#include <unordered_set>

#include "catch2/catch_test_macros.hpp"
#include "catch2/generators/catch_generators_range.hpp"
#include "catch2/matchers/catch_matchers.hpp"
#include "catch2/matchers/catch_matchers_predicate.hpp"

extern "C" {
#include "tree_23.h"
}

using namespace std;

uint_least32_t seed = 31123123;
static mt19937 rand_gen(seed);
static uniform_int_distribution distrib(-999, 999);
static auto gen = []() {
    return distrib(rand_gen);
};

static node_23 mock_node{
    .value_left = std::numeric_limits<int>::min(),
    .value_right = std::numeric_limits<int>::min()
};

constexpr int max_len = 1000;

TEST_CASE("add() and find() works", "[tree-23]") {
    SECTION("tree contain all added number") {
        auto len = GENERATE(Catch::Generators::range(1, max_len));

        vector<int> numbers(len);
        ranges::generate(numbers, gen);

        node_23 *tree = nullptr;
        for (auto value: numbers) {
            tree = add(tree, value);
        }

        auto tree_contain_all_numbers = [tree](vector<int> const &numbers2) {
            return ranges::all_of(numbers2,
                                  [tree](const int number) { return find(tree, number) != nullptr; });
        };
        REQUIRE_THAT(
            numbers,
            Catch::Matchers::Predicate<vector<int>>(
                tree_contain_all_numbers,
                "Tree contain all added numbers")
        );
    }

    SECTION("add() return not null") {
        auto len = GENERATE(Catch::Generators::range(0, max_len));

        vector<int> numbers(len);
        ranges::generate(numbers, gen);
        auto roots = vector<node_23 *>();

        node_23 *tree = nullptr;
        for (auto value: numbers) {
            tree = add(tree, value);
            roots.push_back(tree);
        }

        auto check_all_not_null = [](vector<node_23 *> const &roots2) {
            return ranges::all_of(roots2,
                                  [](const node_23 *root) { return root != nullptr; });
        };
        REQUIRE_THAT(
            roots,
            Catch::Matchers::Predicate<vector<node_23*>>(
                check_all_not_null,
                "All roots must be not null")
        );
    }
}

// TEST_CASE("print() works", "[tree-23]") {
//     SECTION("works") {
//         auto len = GENERATE(Catch::Generators::range(0, max_len));

//         vector<int> numbers_to_insert(len);
//         ranges::generate(numbers_to_insert, gen);
//         unordered_set<int> a;
//         for (int number: numbers_to_insert) {
//             a.insert(number);
//         }
//         numbers_to_insert = {};
//         for(int i:a)
//             numbers_to_insert.push_back(i);
//         len = numbers_to_insert.size();

//         node_23 *tree = nullptr;
//         for (auto value: numbers_to_insert) {
//             tree = add(tree, value);
//         }

//         // number contain 3 digits + 1 sign + 1 space
//         auto print_res_arr = array<char, max_len * 5>();
//         print(tree, print_res_arr.data());
//         string print_res(print_res_arr.data());

//         ranges::sort(numbers_to_insert);
//         string expected;
//         for (char char2: numbers_to_insert
//                          | views::transform([](auto i) { return to_string(i); })
//                          | views::join_with(' '))
//             expected += char2;

//         REQUIRE(print_res == expected);
//     }
// }

TEST_CASE("get_nodes_with_key_between() works", "[tree-23]") {
    SECTION("works for random range") {
        auto len = GENERATE(Catch::Generators::range(1, max_len));

        vector<int> numbers_to_insert(len);
        ranges::generate(numbers_to_insert, gen);

        node_23 *tree = nullptr;
        for (auto value: numbers_to_insert) {
            tree = add(tree, value);
        }

        int key_min = numbers_to_insert[len / 3];
        int key_max = numbers_to_insert[static_cast<int>(len * 2.0 / 3)];
        if (key_min > key_max)
            swap(key_min, key_max);
        if (key_min == key_max)
            key_max += 1;

        std::vector res_nodes(max_len, mock_node);
        get_nodes_with_key_between(tree, key_min, key_max, res_nodes.data());

        auto filled_nodes_range = res_nodes
                                  | views::take_while([](auto n) {
                                      return n.value_left != std::numeric_limits<int>::min();
                                  });
        std::vector<node_23> filled_nodes{};
        ranges::copy(filled_nodes_range, std::back_inserter(filled_nodes));

        /*std::vector<int> numbers_in_tree{};
        for (auto node: filled_nodes_range) {
            switch (node.type) {
                case node_2:
                    numbers_in_tree.push_back(node.value_left);
                    break;
                case node_3:
                    numbers_in_tree.push_back(node.value_left);
                    numbers_in_tree.push_back(node.value_right);
                    break;
                default:
                    exit(20);
            }
        }
        REQUIRE(ranges::is_sorted(numbers_in_tree));*/

        auto at_least_one_value_in_range = [key_min, key_max](vector<node_23> const &nodes) {
            return ranges::all_of(nodes,
                                  [key_min, key_max](const node_23 &node) {
                                      switch (node.type) {
                                          case node_2:
                                              return node.value_left >= key_min && node.value_left < key_max;
                                          case node_3:
                                              return node.value_left >= key_min && node.value_left < key_max
                                                     || node.value_right >= key_min && node.value_right < key_max;
                                          default:
                                              exit(20);
                                      }
                                  });
        };
        REQUIRE_THAT(
            filled_nodes,
            Catch::Matchers::Predicate<vector<node_23>>(
                at_least_one_value_in_range,
                "At least one value in nodes must be in range")
        );
    }

    SECTION("works for semi-infinite range (-inf, v)") {
        auto len = GENERATE(Catch::Generators::range(1, max_len));

        vector<int> numbers_to_insert(len);
        ranges::generate(numbers_to_insert, gen);

        node_23 *tree = nullptr;
        for (auto value: numbers_to_insert) {
            tree = add(tree, value);
        }

        int key_min = std::numeric_limits<int>::min();
        int key_max = numbers_to_insert[len / 2];

        std::vector res_nodes(max_len, mock_node);
        get_nodes_with_key_between(tree, key_min, key_max, res_nodes.data());

        auto filled_nodes_range = res_nodes
                                  | views::take_while([](auto n) {
                                      return n.value_left != std::numeric_limits<int>::min();
                                  });
        std::vector<node_23> filled_nodes{};
        ranges::copy(filled_nodes_range, std::back_inserter(filled_nodes));

        /*std::vector<int> numbers_in_tree{};
        for (auto node: filled_nodes_range) {
            switch (node.type) {
                case node_2:
                    numbers_in_tree.push_back(node.value_left);
                    break;
                case node_3:
                    numbers_in_tree.push_back(node.value_left);
                    numbers_in_tree.push_back(node.value_right);
                    break;
                default:
                    exit(20);
            }
        }
        REQUIRE(ranges::is_sorted(numbers_in_tree));*/

        auto at_least_one_value_in_range = [key_min, key_max](vector<node_23> const &nodes) {
            return ranges::all_of(nodes,
                                  [key_min, key_max](const node_23 &node) {
                                      switch (node.type) {
                                          case node_2:
                                              return node.value_left >= key_min && node.value_left < key_max;
                                          case node_3:
                                              return node.value_left >= key_min && node.value_left < key_max
                                                     || node.value_right >= key_min && node.value_right < key_max;
                                          default:
                                              exit(20);
                                      }
                                  });
        };
        REQUIRE_THAT(
            filled_nodes,
            Catch::Matchers::Predicate<vector<node_23>>(
                at_least_one_value_in_range,
                "At least one value in nodes must be in range")
        );
    }

    SECTION("works for semi-infinite range (v, +inf)") {
        auto len = GENERATE(Catch::Generators::range(1, max_len));

        vector<int> numbers_to_insert(len);
        ranges::generate(numbers_to_insert, gen);

        node_23 *tree = nullptr;
        for (auto value: numbers_to_insert) {
            tree = add(tree, value);
        }

        int key_min = numbers_to_insert[len / 2];
        int key_max = std::numeric_limits<int>::max();

        std::vector res_nodes(max_len, mock_node);
        get_nodes_with_key_between(tree, key_min, key_max, res_nodes.data());

        auto filled_nodes_range = res_nodes
                                  | views::take_while([](auto n) {
                                      return n.value_left != std::numeric_limits<int>::min();
                                  });
        std::vector<node_23> filled_nodes{};
        ranges::copy(filled_nodes_range, std::back_inserter(filled_nodes));

        /*std::vector<int> numbers_in_tree{};
        for (auto node: filled_nodes_range) {
            switch (node.type) {
                case node_2:
                    numbers_in_tree.push_back(node.value_left);
                    break;
                case node_3:
                    numbers_in_tree.push_back(node.value_left);
                    numbers_in_tree.push_back(node.value_right);
                    break;
                default:
                    exit(20);
            }
        }
        REQUIRE(ranges::is_sorted(numbers_in_tree));*/

        auto at_least_one_value_in_range = [key_min, key_max](vector<node_23> const &nodes) {
            return ranges::all_of(nodes,
                                  [key_min, key_max](const node_23 &node) {
                                      switch (node.type) {
                                          case node_2:
                                              return node.value_left >= key_min && node.value_left < key_max;
                                          case node_3:
                                              return node.value_left >= key_min && node.value_left < key_max
                                                     || node.value_right >= key_min && node.value_right < key_max;
                                          default:
                                              exit(20);
                                      }
                                  });
        };
        REQUIRE_THAT(
            filled_nodes,
            Catch::Matchers::Predicate<vector<node_23>>(
                at_least_one_value_in_range,
                "At least one value in nodes must be in range")
        );
    }
}

TEST_CASE("get_shortest_longest_path() works", "[tree-23]") {
    SECTION("works for random tree") {
        auto len = GENERATE(Catch::Generators::range(1, max_len));

        vector<int> numbers_to_insert(len);
        ranges::generate(numbers_to_insert, gen);

        node_23 *tree = nullptr;
        for (auto value: numbers_to_insert) {
            tree = add(tree, value);
        }

        auto [shortest_len, longest_len] = get_shortest_longest_path(tree);
        REQUIRE(longest_len >= shortest_len);
        REQUIRE(longest_len <= len);
        REQUIRE(shortest_len <= len);

        // only for balanced tree
        // int min_integers_count = floor(pow(2, shortest_len + 1) - 1);
        // REQUIRE(len >= min_integers_count);
        int max_integers_count = ceil(pow(3, longest_len + 1) - 1);
        REQUIRE(len <= max_integers_count);
    }

    SECTION("works for linear tree") {
        auto len = GENERATE(Catch::Generators::range(1, max_len));

        vector<int> numbers_to_insert(len);
        ranges::generate(numbers_to_insert, gen);
        ranges::sort(numbers_to_insert);

        node_23 *tree = nullptr;
        for (auto value: numbers_to_insert) {
            tree = add(tree, value);
        }

        auto [shortest_len, longest_len] = get_shortest_longest_path(tree);
        auto expected_height = (len - 1) / 2; // inner nodes are 3-nodes, leaf is 2- or 3-node
        REQUIRE(shortest_len == longest_len);
        //REQUIRE(longest_len == expected_height);
    }
}
