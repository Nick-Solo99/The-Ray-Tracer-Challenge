//
// Created by Nicholas Solomon on 2026-05-22.
//

#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators.hpp>

#include <shapes/cones/Cone.h>
#include <rays/Ray.h>
#include <intersections/Intersection.h>
#include <constants/Constants.h>

using namespace rtc::shapes::cones;
using namespace rtc::rays;
using namespace rtc::constants;


SCENARIO("Intersecting a cone with a ray") {
    auto [origin, direction, t0, t1] = GENERATE(table<Point, Vector, float, float> ({
        {point(0, 0, -5), vector(0, 0, 1), 5, 5},
        {point(0, 0, -5), vector(1, 1, 1), 8.66025f, 59.66025f},
        {point(1, 1, -5), vector(-0.5, -1, 1), 4.55006f, 49.44994f}
    }));
    GIVEN("shape <- cone(), dir <- normalize(vector(" << direction.x << ", " << direction.y << ", " << direction.z <<")),"
          "r <- ray(point(" << origin.x << ", " << origin.y << ", " << origin.z << "), dir)") {
        const Cone shape{};
        const Vector dir = normalize(direction);
        const Ray r{origin, dir};
        WHEN("xs <- shape.intersect(r)") {
            const auto xs = shape.intersect(r);
            THEN("xs.count = 2") {
                REQUIRE(xs.size() == 2);
            }
            AND_THEN("xs[0].t = " << t0 << "") {
                REQUIRE((xs[0].t - t0) < EPSILON);
            }
            AND_THEN("xs[1].t = " << t1 << "") {
                REQUIRE((xs[1].t - t1) < EPSILON);
            }
        }
    }
}

SCENARIO("Intersecting a cone with a ray parallel to one of its halves") {
    GIVEN("shape <- cone(), direction <- normalize(vector(0, 1, 1)), r <- ray(point(0, 0, -1), direction)") {
        const Cone shape{};
        const Vector direction = normalize(vector(0, 1, 1));
        const Ray r{point(0, 0, -1), direction};
        WHEN("xs <- shape.intersect(r)") {
            const auto xs = shape.intersect(r);
            THEN("xs.count = 1") {
                REQUIRE(xs.size() == 1);
            }
            AND_THEN("xs[0].t = 0.35355") {
                REQUIRE((xs[0].t - 0.35355f) < EPSILON);
            }
        }
    }
}

SCENARIO("Intersecting a cones end caps") {
    auto [origin, direction, count] = GENERATE(table<Point, Vector, float>({
        {point(0, 0, -5), vector(0, 1, 0), 0},
        {point(0, 0, -0.25), vector(0, 1, 1), 2},
        {point(0, 0, -0.25), vector(0, 1, 0), 4},
    }));
    GIVEN("shape <- cone(), shape.minimum <- -0.5, shape.maximum <- 0.5, shape.closed <- true,"
          "dir <- normalize(vector(" << direction.x << ", " << direction.y << ", " << direction.z <<")),"
          "r <- ray(point(" << origin.x << ", " << origin.y << ", " << origin.z << "), dir)") {
        Cone shape{};
        shape.minimum = -0.5;
        shape.maximum = 0.5;
        shape.closed = true;
        const Vector dir = normalize(direction);
        const Ray r{origin, dir};
        WHEN("xs <- shape.intersect(r)") {
            const auto xs = shape.intersect(r);
            THEN("xs.count = " << count << "") {
                REQUIRE(xs.size() == count);
            }
        }
    }
}

SCENARIO("Computing the normal vector on a cone") {
    auto [origin, normal] = GENERATE(table<Point, Vector>({
        {point(0, 0, 0), vector(0, 0, 0)},
        {point(1, 1, 1), vector(1, -std::sqrtf(2.f), 1)},
        {point(-1, -1, 0), vector(-1, 1, 0)},
    }));
    GIVEN("shape <- cone()") {
        const Cone shape{};
        WHEN("n <- shape.normal_at(point(" << origin.x << ", " << origin.y << ", " << origin.z << "))") {
            const Vector n = shape.normal_at(origin);
            THEN("n = vector(" << normal.x << ", " << normal.y << ", " << normal.z << ")") {
                REQUIRE(n == normal);
            }
        }
    }
}