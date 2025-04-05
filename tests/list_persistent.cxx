#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_vector.hpp>
#include "catch2/benchmark/catch_benchmark.hpp"

extern "C" {
#include "list_persistent.h"
}

std::vector<int> actual = {};

void print_to_buffer(int value) {
    actual.push_back(value);
}

TEST_CASE("insert_at()", "[persistent_list]") {
    SECTION("Insertion in empty list") {
        list_persistent list = create_empty();
        insert_at(&list, 0, 1);
        actual.clear();
        iterate(&list, 1, print_to_buffer);
        std::vector<int> expected = { 1 };
        REQUIRE_THAT(actual, Catch::Matchers::Equals(expected)); 
    }
    SECTION("Insertion in front") {
        list_persistent list = create_empty();
        insert_at(&list, 0, 1);
        insert_at(&list, 0, 0);
        actual.clear();
        iterate(&list, list.last_version, print_to_buffer);
        std::vector<int> expected = { 0, 1 };
        REQUIRE_THAT(actual, Catch::Matchers::Equals(expected)); 
    }
    SECTION("Insertion in end") {
        list_persistent list = create_empty();
        insert_at(&list, 0, 1);
        insert_at(&list, 1, 0);
        actual.clear();
        iterate(&list, list.last_version, print_to_buffer);
        std::vector<int> expected = { 1, 0 };
        REQUIRE_THAT(actual, Catch::Matchers::Equals(expected)); 
    }
    SECTION("Different insertions") {
        list_persistent list = create_empty();
        insert_at(&list, 0, 0);
        insert_at(&list, 0, -1);
        insert_at(&list, 0, -2);
        insert_at(&list, 3, 1);
        insert_at(&list, 4, 2);
        insert_at(&list, 5, 3);
        insert_at(&list, 2, 10);
        actual.clear();
        iterate(&list, list.last_version, print_to_buffer);
        std::vector<int> expected = {-2, -1, 10, 0, 1, 2, 3};
        REQUIRE_THAT(actual, Catch::Matchers::Equals(expected));
    }
    SECTION("Persistence") {
        list_persistent list = create_empty();
        insert_at(&list, 0, 0);
        insert_at(&list, 0, -1);
        insert_at(&list, 0, -2);

        actual.clear();
        iterate(&list, 0, print_to_buffer);
        std::vector<int> expected = { };
        REQUIRE_THAT(actual, Catch::Matchers::Equals(expected));
        
        actual.clear();
        iterate(&list, 1, print_to_buffer);
        expected = { 0 };
        REQUIRE_THAT(actual, Catch::Matchers::Equals(expected));

        actual.clear();
        iterate(&list, 2, print_to_buffer);
        expected = { -1, 0 };
        REQUIRE_THAT(actual, Catch::Matchers::Equals(expected));

        actual.clear();
        iterate(&list, 3, print_to_buffer);
        expected = { -2, -1, 0 };
        REQUIRE_THAT(actual, Catch::Matchers::Equals(expected));
    }
}

TEST_CASE("set()", "[list_persistent]") {

}
