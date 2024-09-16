#include <random>

#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_vector.hpp>
#include "catch2/benchmark/catch_benchmark.hpp"

extern "C" {
#include "sort.h"
}

TEST_CASE("Works for an empty array", "[sort]") {
    int n = 0;
    int data[] = {};

    SECTION("bubble sort") {
        bubble_sort(data, n);
    }
    SECTION("insertion sort") {
        insertion_sort(data, n);
    }
    SECTION("selection sort") {
        selection_sort(data, n);
    }
    SECTION("merge sort") {
        merge_sort(data, n);
    }
    SECTION("bottom up merge sort") {
        merge_bottom_up_sort(data, n);
    }

    auto actual = std::vector(data, data + n);
    std::vector<int> expected = { };
    REQUIRE_THAT(actual, Catch::Matchers::Equals(expected));
}

TEST_CASE("Works for an array with one element", "[sort]") {
    int n = 1;
    int data[] = {10};

    SECTION("bubble sort") {
        bubble_sort(data, n);
    }
    SECTION("insertion sort") {
        insertion_sort(data, n);
    }
    SECTION("selection sort") {
        selection_sort(data, n);
    }
    SECTION("merge sort") {
        merge_sort(data, n);
    }
    SECTION("bottom up merge sort") {
        merge_bottom_up_sort(data, n);
    }

    auto actual = std::vector(data, data + n);
    std::vector expected = {10};
    REQUIRE_THAT(actual, Catch::Matchers::Equals(expected));
}

TEST_CASE("Works for an already sorted array", "[sort]") {
    int n = 10;
    int data[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    SECTION("bubble sort") {
        bubble_sort(data, n);
    }
    SECTION("insertion sort") {
        insertion_sort(data, n);
    }
    SECTION("selection sort") {
        selection_sort(data, n);
    }
    SECTION("merge sort") {
        merge_sort(data, n);
    }
    SECTION("bottom up merge sort") {
        merge_bottom_up_sort(data, n);
    }

    auto actual = std::vector(data, data + n);
    std::vector expected = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    REQUIRE_THAT(actual, Catch::Matchers::Equals(expected));
}

TEST_CASE("Works for an array already sorted in reverse order", "[sort]") {
    int n = 10;
    int data[] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};

    SECTION("bubble sort") {
        bubble_sort(data, n);
    }
    SECTION("insertion sort") {
        insertion_sort(data, n);
    }
    SECTION("selection sort") {
        selection_sort(data, n);
    }
    SECTION("merge sort") {
        merge_sort(data, n);
    }
    SECTION("bottom up merge sort") {
        merge_bottom_up_sort(data, n);
    }

    auto actual = std::vector(data, data + n);
    std::vector expected = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    REQUIRE_THAT(actual, Catch::Matchers::Equals(expected));
}

TEST_CASE("Works for the shuffled array #1", "[sort]") {
    int n = 10;
    int data[] = {1, 10, 5, 9, 6, 7, 4, 8, 2, 3};

    SECTION("bubble sort") {
        bubble_sort(data, n);
    }
    SECTION("insertion sort") {
        insertion_sort(data, n);
    }
    SECTION("selection sort") {
        selection_sort(data, n);
    }
    SECTION("merge sort") {
        merge_sort(data, n);
    }
    SECTION("bottom up merge sort") {
        merge_bottom_up_sort(data, n);
    }

    auto actual = std::vector(data, data + n);
    std::vector expected = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    REQUIRE_THAT(actual, Catch::Matchers::Equals(expected));
}


TEST_CASE("Works for the shuffled array #2", "[sort]") {
    int n = 10;
    int data[] = {5, 7, 2, 9, 6, 10, 8, 1, 4, 3};

    SECTION("bubble sort") {
        bubble_sort(data, n);
    }
    SECTION("insertion sort") {
        insertion_sort(data, n);
    }
    SECTION("selection sort") {
        selection_sort(data, n);
    }
    SECTION("merge sort") {
        merge_sort(data, n);
    }
    SECTION("bottom up merge sort") {
        merge_bottom_up_sort(data, n);
    }

    auto actual = std::vector(data, data + n);
    std::vector expected = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    REQUIRE_THAT(actual, Catch::Matchers::Equals(expected));
}

TEST_CASE("Works for an array of equal numbers", "[sort]") {
    int n = 10;
    int data[] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1};

    SECTION("bubble sort") {
        bubble_sort(data, n);
    }
    SECTION("insertion sort") {
        insertion_sort(data, n);
    }
    SECTION("selection sort") {
        selection_sort(data, n);
    }
    SECTION("merge sort") {
        merge_sort(data, n);
    }
    SECTION("bottom up merge sort") {
        merge_bottom_up_sort(data, n);
    }

    auto actual = std::vector(data, data + n);
    auto expected = std::vector(10, 1);
    REQUIRE_THAT(actual, Catch::Matchers::Equals(expected));
}

TEST_CASE("Works for an array with some equal numbers", "[sort]") {
    int n = 10;
    int data[] = {1, 5, 5, 5, 5, 7, 4, 8, 5, 3};

    SECTION("bubble sort") {
        bubble_sort(data, n);
    }
    SECTION("insertion sort") {
        insertion_sort(data, n);
    }
    SECTION("selection sort") {
        selection_sort(data, n);
    }
    SECTION("merge sort") {
        merge_sort(data, n);
    }
    SECTION("bottom up merge sort") {
        merge_bottom_up_sort(data, n);
    }

    auto actual = std::vector(data, data + n);
    std::vector expected = {1, 3, 4, 5, 5, 5, 5, 5, 7, 8};
    REQUIRE_THAT(actual, Catch::Matchers::Equals(expected));
}

TEST_CASE("Works for big random vector", "[sort]") {
    constexpr size_t vec_size = 1000;

    std::random_device rd;
    std::mt19937 mersenne_engine {rd()};
    std::uniform_int_distribution distrib(-1000, 1000);
    auto gen = [&](){
        return distrib(mersenne_engine);
    };
    std::vector<int> vec(vec_size);
    std::generate(vec.begin(), vec.end(), gen);

    auto expected = vec;
    std::sort(expected.begin(), expected.end());

    SECTION("bubble sort") {
        bubble_sort(vec.data(), static_cast<int>(vec.size()));
    }
    SECTION("insertion sort") {
        insertion_sort(vec.data(), static_cast<int>(vec.size()));
    }
    SECTION("selection sort") {
        selection_sort(vec.data(), static_cast<int>(vec.size()));
    }
    SECTION("merge sort") {
        merge_sort(vec.data(), static_cast<int>(vec.size()));
    }
    SECTION("bottom up merge sort") {
        merge_bottom_up_sort(vec.data(), static_cast<int>(vec.size()));
    }

    auto actual = vec;
    REQUIRE_THAT(actual, Catch::Matchers::Equals(expected));
}

TEST_CASE("Benchmarks", "[sort][.benchmark]") {
    constexpr size_t vec_size = 10000;

    std::random_device rd;
    std::mt19937 mersenne_engine {rd()};
    std::uniform_int_distribution distrib(-1000, 1000);
    auto gen = [&](){
        return distrib(mersenne_engine);
    };

    BENCHMARK_ADVANCED("bubble sort")(Catch::Benchmark::Chronometer meter) {
        std::vector<int> vec(vec_size);
        std::generate(vec.begin(), vec.end(), gen);
        meter.measure([&vec] {
            bubble_sort(vec.data(), static_cast<int>(vec.size()));
            return vec;
        });
    };
    BENCHMARK_ADVANCED("insertion sort")(Catch::Benchmark::Chronometer meter) {
        std::vector<int> vec(vec_size);
        std::generate(vec.begin(), vec.end(), gen);
        meter.measure([&vec] {
            insertion_sort(vec.data(), static_cast<int>(vec.size()));
            return vec;
        });
    };
    BENCHMARK_ADVANCED("selection sort")(Catch::Benchmark::Chronometer meter) {
        std::vector<int> vec(vec_size);
        std::generate(vec.begin(), vec.end(), gen);
        meter.measure([&vec] {
            selection_sort(vec.data(), static_cast<int>(vec.size()));
            return vec;
        });
    };
    BENCHMARK_ADVANCED("merge sort")(Catch::Benchmark::Chronometer meter) {
        std::vector<int> vec(vec_size);
        std::generate(vec.begin(), vec.end(), gen);
        meter.measure([&vec] {
            merge_sort(vec.data(), static_cast<int>(vec.size()));
            return vec;
        });
    };
    BENCHMARK_ADVANCED("bottom up merge sort")(Catch::Benchmark::Chronometer meter) {
        std::vector<int> vec(vec_size);
        std::generate(vec.begin(), vec.end(), gen);
        meter.measure([&vec] {
            merge_bottom_up_sort(vec.data(), static_cast<int>(vec.size()));
            return vec;
        });
    };
}
