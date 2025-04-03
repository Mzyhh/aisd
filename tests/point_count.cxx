#include <algorithm>
#include <array>
#include <iostream>
#include <random>
#include <ranges>
#include <set>

#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators.hpp>
#include <catch2/generators/catch_generators_all.hpp>
#include <catch2/generators/catch_generators_adapters.hpp>

extern "C" {
#include "point_count.h"
}

static int n_max = 1000;
static int aka_m_max = 5;
static double coord_min = -100;
static double coord_max = -100;

std::uint_least32_t seed = 31123123;
static std::mt19937 rand_gen(seed);
static std::uniform_real_distribution distrib(coord_min, coord_max);
static auto gen = []() {
    double x = distrib(rand_gen);
    double y = distrib(rand_gen);
    return point2d(x, y);
};

int inner_point_count(const std::vector<point2d>& points, point2d bl, point2d tr) {
    int count = 0;
    for (auto [x, y]: points) {
        if (x > bl.x && x < tr.x && y > bl.y && y < tr.y)
            count += 1;
    }
    return count;
}

TEST_CASE("structure works", "[point-count]") {
    SECTION("random points ad rectangles") {
        std::vector<point2d> points(n_max);
        std::ranges::generate(points, gen);

        auto structure = build_structure(points.data(), points.size());

        // (aka_m_max * aka_m_max * aka_m_max * aka_m_max) rectangles
        int v1 = GENERATE(take(aka_m_max, random(coord_min, coord_max)));
        int v2 = GENERATE(take(aka_m_max, random(coord_min, coord_max)));
        int v3 = GENERATE(take(aka_m_max, random(coord_min, coord_max)));
        int v4 = GENERATE(take(aka_m_max, random(coord_min, coord_max)));

        auto bl = point2d(v1, v2);
        auto tr = point2d(v3, v4);

        int actual = get_inner_point_count(&structure, bl,tr);
        int expected = inner_point_count(points, bl, tr);

        CHECK(actual == expected);
    }

    SECTION("vertices of the rectangle are the points") {
        std::vector<point2d> points(n_max);
        std::ranges::generate(points, gen);

        auto structure = build_structure(points.data(), points.size());

        // (aka_m_max * aka_m_max) rectangles
        int bl_i = GENERATE(range(0, aka_m_max));
        auto bl = points[bl_i];
        int tr_i = GENERATE(range(0, aka_m_max));
        auto tr = points[tr_i];

        int actual = get_inner_point_count(&structure, bl,tr);
        int expected = inner_point_count(points, bl, tr);

        CHECK(actual == expected);
    }

    SECTION("some coordinates are the same") {
        std::vector<point2d> points(n_max);
        std::ranges::generate(points, gen);

        auto structure = build_structure(points.data(), points.size());

        // (aka_m_max * aka_m_max) rectangles
        int bl_i = GENERATE(range(0, aka_m_max));
        auto bl = point2d(points[bl_i].x, points[bl_i + 1].x);
        int tr_i = GENERATE(range(0, aka_m_max));
        auto tr = point2d(points[tr_i].x, points[tr_i + 1].x);

        int actual = get_inner_point_count(&structure, bl,tr);
        int expected = inner_point_count(points, bl, tr);

        CHECK(actual == expected);
    }
}
