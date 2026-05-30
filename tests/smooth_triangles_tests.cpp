//
// Created by Nicholas Solomon on 2026-05-29.
//

#include <catch2/catch_test_macros.hpp>
#include <shapes/triangles/SmoothTriangle.h>
#include <constants/Constants.h>

using namespace rtc::shapes::triangles;
using namespace rtc::rays;
using namespace rtc::constants;
using namespace rtc::intersections;

const Point p1 = point(0, 1, 0);
const Point p2 = point(-1, 0, 0);
const Point p3 = point(1, 0, 0);
const Vector n1 = vector(0, 1, 0);
const Vector n2 = vector(-1, 0, 0);
const Vector n3 = vector(1, 0, 0);
const SmoothTriangle tri{p1, p2, p3, n1, n2, n3};

SCENARIO("Constructing a smooth triangle") {
    REQUIRE(tri.p1 == p1);
    REQUIRE(tri.p2 == p2);
    REQUIRE(tri.p3 == p3);
    REQUIRE(tri.n1 == n1);
    REQUIRE(tri.n2 == n2);
    REQUIRE(tri.n3 == n3);
}

SCENARIO("An intersection with a smooth triangle stores u/v") {
    WHEN("r <- ray(point(-0.2, 0.3, -2), vector(0, 0, 1)), xs <- tri.intersect(r)") {
        const Ray r{point(-0.2, 0.3, -2), vector(0, 0, 1)};
        const auto xs = tri.intersect(r);
        THEN("xs[0].u = 0.45") {
            REQUIRE((xs[0].u - 0.45f) < EPSILON);
        }
        AND_THEN("xs[0].v = 0.25") {
            REQUIRE((xs[0].v - 0.25f) < EPSILON);
        }
    }
}

SCENARIO("A smooth triangle uses u/v to interpolate the normal") {
    WHEN("i <- intersection(1, tri, 0.45, 0.25), n <- tri.normal_at(point(0, 0, 0), i)") {
        const Intersection i{1, &tri, 0.45, 0.25};
        const Vector n = tri.normal_at(point(0, 0, 0), i);
        THEN("n = vector(-0.5547, 0.83205, 0)") {
            REQUIRE(n == vector(-0.5547, 0.83205, 0));
        }
    }
}

SCENARIO("Preparing the normal on a smooth triangle") {
    WHEN("i <- intersection(1, tri, 0.45, 0.25), r <- ray(point(-0.2, 0.3, -2), vector(0, 0, 1)), xs <- intersections(i),"
         "comps <- i.pre_compute(r, xs)") {
        const Intersection i{1, &tri, 0.45, 0.25};
        const Ray r{point(-0.2, 0.3, -2), vector(0, 0, 1)};
        const auto xs = intersections({i});
        const Components comps = i.pre_compute(r, xs);
        THEN("comps.normal_v = vector(-0.5547, 0.83205, 0)") {
            REQUIRE(comps.normal_v == vector(-0.5547, 0.83205, 0));
        }
    }
}