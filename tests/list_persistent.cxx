#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_vector.hpp>

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
    SECTION("Different insertions1") {
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
    SECTION("Set one value") {
        list_persistent list = create_empty();
        insert_at(&list, 0, 0);
        set(&list, 0, 2);
        actual.clear();
        iterate(&list, list.last_version, print_to_buffer);
        std::vector<int> expected = { 2 };
        REQUIRE_THAT(actual, Catch::Matchers::Equals(expected)); 
    }
    SECTION("Set two values in one place") {
        list_persistent list = create_empty();
        insert_at(&list, 0, 0);
        set(&list, 0, 2);
        set(&list, 0, 3);
        std::vector<int> expected1 = { 2 };
        std::vector<int> expected2 = { 3 };
        actual.clear();
        iterate(&list, list.last_version - 1, print_to_buffer);
        REQUIRE_THAT(actual, Catch::Matchers::Equals(expected1)); 
        actual.clear();
        iterate(&list, list.last_version, print_to_buffer);
        REQUIRE_THAT(actual, Catch::Matchers::Equals(expected2)); 
    }
    SECTION("Complex set") {
        list_persistent list = create_empty();
        insert_at(&list, 0, 0);
        insert_at(&list, 0, -1);
        insert_at(&list, 0, -2);
        insert_at(&list, 3, 1);
        insert_at(&list, 4, 2);
        insert_at(&list, 5, 3);
        insert_at(&list, 2, 10);
        set(&list, 1, 10);
        set(&list, 2, 52);
        set(&list, 0, 11);
        std::vector<int> expected = {11, 10, 52, 0, 1, 2, 3};
        actual.clear();
        iterate(&list, list.last_version, print_to_buffer);
        REQUIRE_THAT(actual, Catch::Matchers::Equals(expected));
    }
    
}
