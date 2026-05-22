//
// Created by Nicholas Solomon on 2026-05-22.
//

#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators.hpp>
#include <shapes/cylinders/Cylinder.h>
#include <rays/Ray.h>
#include <intersections/Intersection.h>
#include <constants/Constants.h>

using namespace rtc::shapes::cylinders;
using namespace rtc::constants;

SCENARIO("A ray missed a cylinder") {
    GIVEN("cyl <- cylinder(), dir <- normalize(vector(0, 1, 0)), r <- ray(point(1, 0, 0), dir)") {
        const Cylinder cyl{};
        const Vector dir = normalize(point(0, 1, 0));
        const Ray r{point(1, 0, 0), dir};
        WHEN("xs <- cyl.intersect(r)") {
            const auto xs = cyl.intersect(r);
            THEN("xs.count = 0") {
                REQUIRE(xs.empty());
            }
        }
    }
    AND_GIVEN("cyl <- cylinder(), dir <- normalize(vector(0, 1, 0)), r <- ray(point(0, 0, 0), dir)") {
        const Cylinder cyl{};
        const Vector dir = normalize(point(0, 1, 0));
        const Ray r{point(0, 0, 0), dir};
        WHEN("xs <- cyl.intersect(r)") {
            const auto xs = cyl.intersect(r);
            THEN("xs.count = 0") {
                REQUIRE(xs.empty());
            }
        }
    }
    AND_GIVEN("cyl <- cylinder(), dir <- normalize(vector(1, 1, 1)), r <- ray(point(0, 0, -5), dir)") {
        const Cylinder cyl{};
        const Vector dir = normalize(point(1, 1, 1));
        const Ray r{point(0, 0, -5), dir};
        WHEN("xs <- cyl.intersect(r)") {
            const auto xs = cyl.intersect(r);
            THEN("xs.count = 0") {
                REQUIRE(xs.empty());
            }
        }
    }
}

SCENARIO("A ray strikes a cylinder") {
    auto [origin, direction, t0, t1] = GENERATE(table<Point, Vector, float, float>({
        {point(1, 0, -5), vector(0, 0, 1), 5, 5},
        {point(0, 0, -5), vector(0, 0, 1), 4, 6},
        {point(0.5f, 0, -5), vector(0.1f, 1, 1), 6.80798f, 7.08872f}
    }));
    GIVEN("cyl <- cylinder(), dir <- normalize<direction>, r <- ray(<origin>, dir)") {
        const Cylinder cyl{};
        const Vector dir = normalize(direction);
        const Ray r{origin, dir};
        WHEN("xs <- cyl.intersect(r)") {
            const auto xs = cyl.intersect(r);
            THEN("xs.count = 2") {
                REQUIRE(xs.size() == 2);
            }
            AND_THEN("xs[0].t = t0") {
                REQUIRE((xs[0].t - t0) < EPSILON);
            }
            AND_THEN("xs[1].t = t1") {
                REQUIRE((xs[1].t - t1) < EPSILON);
            }
        }
    }
}