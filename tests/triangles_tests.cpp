//
// Created by Nicholas Solomon on 2026-05-25.
//

#include <catch2/catch_test_macros.hpp>
#include <shapes/triangles/Triangle.h>
#include <constants/Constants.h>

using namespace rtc::shapes::triangles;
using namespace rtc::constants;

SCENARIO("Constructing a triangle") {
    GIVEN("p1 <- point(0, 1, 0), p2 <- point(-1, 0, 0), p3 <- point(1, 0, 0), t <- triangle(p1, p2, p3)") {
        const Point p1 = point(0, 1, 0), p2 = point(-1, 0, 0), p3 = point(1, 0, 0);
        const Triangle t{p1, p2, p3};
        THEN("t.p1 = p1") {
            REQUIRE(t.p1 == p1);
        }
        AND_THEN("t.p2 = p2") {
            REQUIRE(t.p2 == p2);
        }
        AND_THEN("t.p3 = p3") {
            REQUIRE(t.p3 == p3);
        }
        AND_THEN("t.e1 = vector(-1, -1, 0)") {
            REQUIRE(t.e1 == vector(-1, -1, 0));
        }
        AND_THEN("t.e2 = vector(1, -1, 0)") {
            REQUIRE(t.e2 == vector(1, -1, 0));
        }
        AND_THEN("t.normal = vector(0, 0, -1)") {
            REQUIRE(t.normal == vector(0, 0, -1));
        }
    }
}

SCENARIO("Finding the normal on a triangle") {
    GIVEN("t <- triangle(point(0, 1, 0), point(-1, 0, 0), point(1, 0, 0))") {
        const Triangle t{point(0, 1, 0), point(-1, 0, 0), point(1, 0, 0)};
        WHEN("n1 <- t.normal_at(point(0, 0.5, 0)), n2 <- t.normal_at(point(-0.5, 0.75, 0)), n3 <- t.normal_at(point(0.5, 0.25, 0))") {
            const Vector n1 = t.normal_at(point(0, 0.5, 0), {1, &t});
            const Vector n2 = t.normal_at(point(-0.5, 0.75, 0), {1, &t});
            const Vector n3 = t.normal_at(point(0.5, 0.25, 0), {1, &t});
            THEN("n1 = t.normal") {
                REQUIRE(n1 == t.normal);
            }
            AND_THEN("n2 = t.normal") {
                REQUIRE(n2 == t.normal);
            }
            AND_THEN("n3 = t.normal") {
                REQUIRE(n3 == t.normal);
            }
        }
    }
}

SCENARIO("Intersecting a ray parallel to the triangle") {
    GIVEN("t <- triangle(point(0, 1, 0), point(-1, 0, 0), point(1, 0, 0)), r <- ray(point(0, -1, -2), vector(0, 1, 0))") {
        const Triangle t{point(0, 1, 0), point(-1, 0, 0), point(1, 0, 0)};
        const Ray r{point(0, -1, -1), vector(0, 1, 0)};
        WHEN("xs <- t.intersect(r)") {
            const auto xs = t.intersect(r);
            THEN("xs is empty") {
                REQUIRE(xs.empty());
            }
        }
    }
}

SCENARIO("A ray misses the p1 - p3 edge") {
    GIVEN("t <- triangle(point(0, 1, 0), point(-1, 0, 0), point(1, 0, 0)), r <- ray(point(1, 1, -2), vector(0, 0, 1))") {
        const Triangle t{point(0, 1, 0), point(-1, 0, 0), point(1, 0, 0)};
        const Ray r{point(1, 1, -2), vector(0, 0, 1)};
        WHEN("xs <- t.intersect(r)") {
            const auto xs = t.intersect(r);
            THEN("xs is empty") {
                REQUIRE(xs.empty());
            }
        }
    }
}

SCENARIO("A ray misses the p1 - p2 edge") {
    GIVEN("t <- triangle(point(0, 1, 0), point(-1, 0, 0), point(1, 0, 0)), r <- ray(point(-1, 1, -2), vector(0, 0, 1))") {
        const Triangle t{point(0, 1, 0), point(-1, 0, 0), point(1, 0, 0)};
        const Ray r{point(-1, 1, -2), vector(0, 0, 1)};
        WHEN("xs <- t.intersect(r)") {
            const auto xs = t.intersect(r);
            THEN("xs is empty") {
                REQUIRE(xs.empty());
            }
        }
    }
}

SCENARIO("A ray misses the p2 - p3 edge") {
    GIVEN("t <- triangle(point(0, 1, 0), point(-1, 0, 0), point(1, 0, 0)), r <- ray(point(0, -1, -2), vector(0, 0, 1))") {
        const Triangle t{point(0, 1, 0), point(-1, 0, 0), point(1, 0, 0)};
        const Ray r{point(0, -1, -2), vector(0, 0, 1)};
        WHEN("xs <- t.intersect(r)") {
            const auto xs = t.intersect(r);
            THEN("xs is empty") {
                REQUIRE(xs.empty());
            }
        }
    }
}

SCENARIO("A ray strikes a triangle") {
    GIVEN("t <- triangle(point(0, 1, 0), point(-1, 0, 0), point(1, 0, 0)), r <- ray(point(0, 0.5, -2), vector(0, 0, 1))") {
        const Triangle t{point(0, 1, 0), point(-1, 0, 0), point(1, 0, 0)};
        const Ray r{point(0, 0.5, -2), vector(0, 0, 1)};
        WHEN("xs <- t.intersect(r)") {
            const auto xs = t.intersect(r);
            THEN("xs.size = 1") {
                REQUIRE(xs.size() == 1);
            }
            AND_THEN("xs[0].t = 2") {
                REQUIRE((xs[0].t - 2) < EPSILON);
            }
        }
    }
}
