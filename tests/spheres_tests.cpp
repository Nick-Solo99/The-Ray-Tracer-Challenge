//
// Created by Nicholas Solomon on 2026-05-08.
//

#include <catch2/catch_test_macros.hpp>
#include <rays/Ray.h>
#include <spheres/Sphere.h>

using namespace rtc::rays;
using namespace rtc::spheres;

SCENARIO("A ray intersects a sphere at two points") {
    GIVEN("r <- ray(point(0, 0, -5), vector(0, 0, 1)), s <- sphere()") {
        const Ray r(point(0, 0, -5), vector(0, 0, 1));
        const Sphere s{};

        WHEN("xs <- s.intersects(r)") {
            const std::vector<float> xs = s.intersect(r);

            THEN("xs.size() = 2") {
                REQUIRE(xs.size() == 2);
            }

            AND_THEN("xs[0] = 4.0") {
                REQUIRE(xs[0] == 4.0f);
            }

            AND_THEN("xs[1] = 6.0") {
                REQUIRE(xs[1] == 6.0f);
            }
        }
    }
}

SCENARIO("A ray intersects a sphere at a tangent") {
    GIVEN("r <- ray(point(0, 1, -5), vector(0, 0, 1)), s <- sphere()") {
        const Ray r(point(0, 1, -5), vector(0, 0, 1));
        const Sphere s{};

        WHEN("xs <- s.intersects(r)") {
            const std::vector<float> xs = s.intersect(r);
            THEN("xs.size() = 2") {
                REQUIRE(xs.size() == 2);
            }

            AND_THEN("xs[0] = 5.0") {
                REQUIRE(xs[0] == 5.0f);
            }

            AND_THEN("xs[1] = 5.0") {
                REQUIRE(xs[1] == 5.0f);
            }
        }
    }
}

SCENARIO("A ray misses a sphere") {
    GIVEN("r <- ray(point(0, 2, -5), vector(0, 0, 1)), s <- sphere()") {
        const Ray r(point(0, 2, -5), vector(0, 0, 1));
        const Sphere s{};

        WHEN("xs <- s.intersects(r)") {
            const std::vector<float> xs = s.intersect(r);
            THEN("xs.size() = 0") {
                REQUIRE(xs.size() == 0);
            }
        }
    }
}

SCENARIO("A ray originates inside a sphere") {
    GIVEN("r <- ray(point(0, 0, 0), vector(0, 0, 1)), s <- sphere()") {
        const Ray r(point(0, 0, 0), vector(0, 0, 1));
        const Sphere s{};

        WHEN("xs <- s.intersects(r)") {
            const std::vector<float> xs = s.intersect(r);

            THEN("xs.size() = 2") {
                REQUIRE(xs.size() == 2);
            }

            AND_THEN("xs[0] = -1.0") {
                REQUIRE(xs[0] == -1.0f);
            }

            AND_THEN("xs[1] = 1.0") {
                REQUIRE(xs[1] == 1.0f);
            }
        }
    }
}

SCENARIO("A sphere behind a ray") {
    GIVEN("r <- ray(point(0, 0, 5), vector(0, 0, 1)), s <- sphere()") {
        const Ray r(point(0, 0, 5), vector(0, 0, 1));
        const Sphere s{};

        WHEN("xs <- s.intersects(r)") {
            const std::vector<float> xs = s.intersect(r);
            THEN("xs.size() = 2") {
                REQUIRE(xs.size() == 2);
            }

            AND_THEN("xs[0] = -6.0") {
                REQUIRE(xs[0] == -6.0f);
            }

            AND_THEN("xs[1] = -4.0") {
                REQUIRE(xs[1] == -4.0f);
            }
        }
    }
}