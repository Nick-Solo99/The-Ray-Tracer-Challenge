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

SCENARIO("Normal vector on a cylinder") {
    auto [origin, normal] = GENERATE(table<Point, Vector>({
        {point(1, 0, 0), vector(1, 0, 0)},
        {point(0, 5, -1), vector(0, 0, -1)},
        {point(0, -2, 1), vector(0, 0, 1)},
        {point(-1, 1, 0), vector(-1, 0, 0)}
    }));
    GIVEN("cyl <- Cylinder()") {
        const Cylinder cyl{};
        WHEN("n <- cyl.normal_at(<origin>)") {
            const Vector n = cyl.normal_at(origin, {1, &cyl});
            THEN("n = <normal>") {
                REQUIRE(n == normal);
            }
        }
    }
}

SCENARIO("The default minimum and maximum for a cylinder") {
    GIVEN("cyl <- cylinder()") {
        const Cylinder cyl{};
        THEN("cyl.minimum = -INFINITY") {
            REQUIRE(cyl.minimum == -INFINITY);
        }
        AND_THEN("cyl.maximum = INFINITY") {
            REQUIRE(cyl.maximum == INFINITY);
        }
    }
}

SCENARIO("Intersecting a constrained cylinder") {
    auto [origin, direction, count] = GENERATE(table<Point, Vector, float>({
        {point(0, 1.5, 0), vector(0.1, 1, 0), 0},
        {point(0, 3, -5), vector(0, 0, 1), 0},
        {point(0, 0, -5), vector(0, 0, 1), 0},
        {point(0, 2, -5), vector(0, 0, 1), 0},
        {point(0, 1, -5), vector(0, 0, 1), 0},
        {point(0, 1.5, -2), vector(0, 0, 1), 2}
    }));
    GIVEN("cyl <- cylinder(), cyl.minimum = 1, cyl.maximum = 2, dir <- normalize(<direction>), r <- ray(<origin>, dir)") {
        Cylinder cyl{};
        cyl.minimum = 1;
        cyl.maximum = 2;
        const Vector dir = normalize(direction);
        const Ray r{origin, dir};
        WHEN("xs <- cyl.intersect(r)") {
            const auto xs = cyl.intersect(r);
            THEN("xs.count == <count>") {
                REQUIRE(xs.size() == count);
            }
        }
    }
}

SCENARIO("The default closed value for a cylinder") {
    GIVEN("cyl <- cylinder()") {
        const Cylinder cyl{};
        THEN("cyl.closed = false") {
            REQUIRE(!cyl.closed);
        }
    }
}

SCENARIO("Intersecting the caps of a closed cylinder") {
    auto [origin, direction, count] = GENERATE(table<Point, Vector, float>({
        {point(0, 3, 0), vector(0, -1, 0), 2},
        {point(0, 3, -2), vector(0, -1, 2), 2},
        {point(0, 4, -2), vector(0, -1, 1), 2},
        {point(0, 0, -2), vector(0, 1, 2), 2},
        {point(0, -1, -2), vector(0, 1, 1), 2}
    }));
    GIVEN("cyl <- cylinder(), cyl.minimum = 1, cyl.maximum = 2, cyl.closed = true, dir <- normalize(<direction>), r <- ray(<origin>, dir)") {
        Cylinder cyl{};
        cyl.minimum = 1;
        cyl.maximum = 2;
        cyl.closed = true;
        const Vector dir = normalize(direction);
        const Ray r{origin, dir};
        WHEN("xs <- cyl.intersect(r)") {
            const auto xs = cyl.intersect(r);
            THEN("xs.count == <count>") {
                REQUIRE(xs.size() == count);
            }
        }
    }
}

SCENARIO("The normal vector on a cylinders end caps") {
    auto [origin, normal] = GENERATE(table<Point, Vector>({
        {point(0, 1, 0), vector(0, -1, 0)},
        {point(0.5, 1, 0), vector(0, -1, 0)},
        {point(0, 1, 0.5), vector(0, -1, 0)},
        {point(0, 2, 0), vector(0, 1, 0)},
        {point(0.5, 2, 0), vector(0, 1, 0)},
        {point(0, 2, 0.5), vector(0, 1, 0)},
    }));
    GIVEN("cyl <- cylinder(), cyl.minimum <- 1, cyl.maximum <- 2, cyl.closed <- true") {
        Cylinder cyl{};
        cyl.minimum = 1;
        cyl.maximum = 2;
        cyl.closed = true;
        WHEN("n <- cyl.normal_at(point(" << origin.x << ", " << origin.y << ", " << origin.z << "))") {
            const auto n = cyl.normal_at(origin, {1, &cyl});
            THEN("n = vector(" << normal.x << ", " << normal.y << ", " << normal.z << ")") {
                REQUIRE(n == normal);
            }
        }
    }
}