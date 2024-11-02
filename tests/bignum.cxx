#include <random>

#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_vector.hpp>
#include "catch2/generators/catch_generators.hpp"
#include "catch2/generators/catch_generators_range.hpp"

extern "C" {
#include "bignum.h"
}

std::vector<int> polynomial_multiply(const std::vector<int>& a, const std::vector<int>& b) {
    std::vector<int> res;
    for (auto k = 0; k < a.size() + b.size() - 1; ++k) {
        auto coeff = 0;
        for (auto i = 0; i < a.size(); ++i) {
            auto j = k - i;
            if (j >= 0 && j < b.size())
                coeff += a[i] * b[j];
        }
        res.push_back(coeff);
    }
    return res;
}

TEST_CASE("Karatsuba multiplication of polynomials works", "[bignum]") {
    SECTION("both zero") {
        std::vector a = {0};
        std::vector b = {0};
        std::vector expected = polynomial_multiply(a, b);

        bignum a_struct = {.digits = a.data(), .n = static_cast<int>(a.size())};
        bignum b_struct = {.digits = b.data(), .n = static_cast<int>(b.size())};
        auto [digits, n] = karatsuba_polynomial(a_struct, b_struct);
        auto actual = std::vector(digits, digits + n);

        REQUIRE_THAT(actual, Catch::Matchers::Equals(expected));
    }
    SECTION("both one") {
        std::vector a = {1};
        std::vector b = {1};
        std::vector expected = polynomial_multiply(a, b);

        bignum a_struct = {.digits = a.data(), .n = static_cast<int>(a.size())};
        bignum b_struct = {.digits = b.data(), .n = static_cast<int>(b.size())};
        auto [digits, n] = karatsuba_polynomial(a_struct, b_struct);
        auto actual = std::vector(digits, digits + n);

        REQUIRE_THAT(actual, Catch::Matchers::Equals(expected));
    }
    SECTION("two random polynomials of len 4") {
        std::vector a = {1, 2, 3, 4};
        std::vector b = {5, 6, 7, 8};
        std::vector expected = {5, 16, 34, 60, 61, 52, 32};

        bignum a_struct = {.digits = a.data(), .n = static_cast<int>(a.size())};
        bignum b_struct = {.digits = b.data(), .n = static_cast<int>(b.size())};
        auto [digits, n] = karatsuba_polynomial(a_struct, b_struct);
        auto actual = std::vector(digits, digits + n);

        REQUIRE_THAT(actual, Catch::Matchers::Equals(expected));
    }
    SECTION("two big random polynomials") {
        std::vector a = {7, 3, 7, 9, 3, 5, 8, 9, 6, 5, 4};
        std::vector b = {3, 6, 5, 4, 6, 8, 9, 6, 3, 2, 4, 7, 8, 6, 4, 3, 2, 5};
        std::vector expected = polynomial_multiply(a, b);

        bignum a_struct = {.digits = a.data(), .n = static_cast<int>(a.size())};
        bignum b_struct = {.digits = b.data(), .n = static_cast<int>(b.size())};
        auto [digits, n] = karatsuba_polynomial(a_struct, b_struct);
        auto actual = std::vector(digits, digits + n);

        REQUIRE_THAT(actual, Catch::Matchers::Equals(expected));
    }
}

TEST_CASE("Karatsuba multiplication of two binary numbers", "[bignum]") {
    SECTION("both zero") {
        std::vector a = {0};
        std::vector b = {0};
        std::vector expected = {0};

        bignum a_struct = {.digits = a.data(), .n = static_cast<int>(a.size())};
        bignum b_struct = {.digits = b.data(), .n = static_cast<int>(b.size())};
        auto [digits, n] = karatsuba_binary_numbers(a_struct, b_struct);
        auto actual = std::vector(digits, digits + n);

        REQUIRE_THAT(actual, Catch::Matchers::Equals(expected));
    }
    SECTION("both one") {
        std::vector a = {1};
        std::vector b = {1};
        std::vector expected = {1};

        bignum a_struct = {.digits = a.data(), .n = static_cast<int>(a.size())};
        bignum b_struct = {.digits = b.data(), .n = static_cast<int>(b.size())};
        auto [digits, n] = karatsuba_binary_numbers(a_struct, b_struct);
        auto actual = std::vector(digits, digits + n);

        REQUIRE_THAT(actual, Catch::Matchers::Equals(expected));
    }
    SECTION("two random numbers of len 4") {
        std::vector a = {1, 1, 0, 1};
        std::vector b = {1, 0, 1, 1};
        std::vector expected = {1, 1, 1, 1, 0, 0, 0, 1};

        bignum a_struct = {.digits = a.data(), .n = static_cast<int>(a.size())};
        bignum b_struct = {.digits = b.data(), .n = static_cast<int>(b.size())};
        auto [digits, n] = karatsuba_binary_numbers(a_struct, b_struct);
        auto actual = std::vector(digits, digits + n);

        REQUIRE_THAT(actual, Catch::Matchers::Equals(expected));
    }
    SECTION("two big random numbers") {
        // https://www.wolframalpha.com/input?i=10001010101101010*111110111010110101100011110
        std::vector n1 = {0, 1, 0, 1, 0, 1, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1};
        std::vector n2 = {0, 1, 1, 1, 1, 0, 0, 0, 1, 1, 0, 1, 0, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1};
        std::vector expected = {0, 0, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 0, 1, 0, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1};

        bignum a_struct = {.digits = n1.data(), .n = static_cast<int>(n1.size())};
        bignum b_struct = {.digits = n2.data(), .n = static_cast<int>(n2.size())};
        auto [digits, n] = karatsuba_binary_numbers(a_struct, b_struct);
        auto actual = std::vector(digits, digits + n);

        REQUIRE_THAT(actual, Catch::Matchers::Equals(expected));
    }
}

