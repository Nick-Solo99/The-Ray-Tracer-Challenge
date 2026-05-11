//
// Created by Nicholas Solomon on 2026-05-08.
//

#include <catch2/catch_test_macros.hpp>
#include <rays/Ray.h>
#include <shapes/spheres/Sphere.h>
#include "intersections/Intersection.h"

using namespace rtc::rays;
using namespace rtc::shapes::spheres;
using namespace rtc::intersections;

SCENARIO("A ray intersects a sphere at two points") {
    GIVEN("r <- ray(point(0, 0, -5), vector(0, 0, 1)), s <- sphere()") {
        const Ray r(point(0, 0, -5), vector(0, 0, 1));
        const Sphere s{};

        WHEN("xs <- s.intersects(r)") {
            const std::vector<Intersection> xs = s.intersect(r);

            THEN("xs.size() = 2") {
                REQUIRE(xs.size() == 2);
            }

            AND_THEN("xs[0].t = 4.0") {
                REQUIRE(xs[0].t == 4.0f);
            }

            AND_THEN("xs[1] = 6.0") {
                REQUIRE(xs[1].t == 6.0f);
            }
        }
    }
}

SCENARIO("A ray intersects a sphere at a tangent") {
    GIVEN("r <- ray(point(0, 1, -5), vector(0, 0, 1)), s <- sphere()") {
        const Ray r(point(0, 1, -5), vector(0, 0, 1));
        const Sphere s{};

        WHEN("xs <- s.intersects(r)") {
            const std::vector<Intersection> xs = s.intersect(r);
            THEN("xs.size() = 2") {
                REQUIRE(xs.size() == 2);
            }

            AND_THEN("xs[0].t = 5.0") {
                REQUIRE(xs[0].t == 5.0f);
            }

            AND_THEN("xs[1].t = 5.0") {
                REQUIRE(xs[1].t == 5.0f);
            }
        }
    }
}

SCENARIO("A ray misses a sphere") {
    GIVEN("r <- ray(point(0, 2, -5), vector(0, 0, 1)), s <- sphere()") {
        const Ray r(point(0, 2, -5), vector(0, 0, 1));
        const Sphere s{};

        WHEN("xs <- s.intersects(r)") {
            const std::vector<Intersection> xs = s.intersect(r);
            THEN("xs.size() = 0") {
                REQUIRE(xs.empty());
            }
        }
    }
}

SCENARIO("A ray originates inside a sphere") {
    GIVEN("r <- ray(point(0, 0, 0), vector(0, 0, 1)), s <- sphere()") {
        const Ray r(point(0, 0, 0), vector(0, 0, 1));
        const Sphere s{};

        WHEN("xs <- s.intersects(r)") {
            const std::vector<Intersection> xs = s.intersect(r);

            THEN("xs.size() = 2") {
                REQUIRE(xs.size() == 2);
            }

            AND_THEN("xs[0].t = -1.0") {
                REQUIRE(xs[0].t == -1.0f);
            }

            AND_THEN("xs[1].t = 1.0") {
                REQUIRE(xs[1].t == 1.0f);
            }
        }
    }
}

SCENARIO("A sphere behind a ray") {
    GIVEN("r <- ray(point(0, 0, 5), vector(0, 0, 1)), s <- sphere()") {
        const Ray r(point(0, 0, 5), vector(0, 0, 1));
        const Sphere s{};

        WHEN("xs <- s.intersects(r)") {
            const std::vector<Intersection> xs = s.intersect(r);
            THEN("xs.size() = 2") {
                REQUIRE(xs.size() == 2);
            }

            AND_THEN("xs[0].t = -6.0") {
                REQUIRE(xs[0].t == -6.0f);
            }

            AND_THEN("xs[1].t = -4.0") {
                REQUIRE(xs[1].t == -4.0f);
            }
        }
    }
}

SCENARIO("Intersect sets the object on the intersection") {
    GIVEN("r <- ray(point(0, 0, -5), vector(0, 0, 1)), s <- sphere()") {
        const Ray r(point(0, 0, -5), vector(0, 0, 1));
        const Sphere s{};

        WHEN("xs <- s.intersect(r)") {
            const std::vector<Intersection> xs = s.intersect(r);

            THEN("xs.size() = 2") {
                REQUIRE(xs.size() == 2);
            }
            AND_THEN("xs[0].object = s") {
                REQUIRE(xs[0].object == &s);
            }
            AND_THEN("xs[1].object = s") {
                REQUIRE(xs[1].object == &s);
            }
        }
    }
}