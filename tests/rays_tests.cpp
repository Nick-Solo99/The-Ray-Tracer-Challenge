//
// Created by Nicholas Solomon on 2026-05-08.
//

#include <catch2/catch_test_macros.hpp>
#include <tuples/Tuple.h>
#include <rays/Ray.h>
#include <matrices/Matrix.h>
#include <transformations/Transformations.h>

using namespace rtc::tuples;
using namespace rtc::rays;
using namespace rtc::matrices;
using namespace rtc::transformations;

SCENARIO(" Creating and querying a ray") {
    GIVEN("origin <- point(1, 2, 3), direction <- vector(4, 5, 6)") {
        const Point origin = point(1, 2, 3);
        const Vector direction = vector(4, 5, 6);

        WHEN("r <- ray(origin, direction)") {
            const Ray r(origin, direction);
            THEN("r.origin = origin") {
                REQUIRE(r.origin == origin);
            }

            AND_THEN("r.direction = direction") {
                REQUIRE(r.direction == direction);
            }
        }
    }
}

SCENARIO("Computing a point from a distance") {
    GIVEN("r <- ray(point(2, 3, 4), vector(1, 0, 0))") {
        const Ray r(point(2, 3, 4), vector(1, 0, 0));

        THEN("r.position(0) = point(2, 3, 4)") {
            REQUIRE(r.position(0) == point(2, 3, 4));
        }

        AND_THEN("r.position(1) = point(3, 3, 4)") {
            REQUIRE(r.position(1) == point(3, 3, 4));
        }

        AND_THEN("r.position(-1) = point(1, 3, 4)") {
            REQUIRE(r.position(-1) == point(1, 3, 4));
        }

        AND_THEN("r.position(2.5) = point(4.5, 3, 4)") {
            REQUIRE(r.position(2.5f) == point(4.5f, 3, 4));
        }
    }
}

SCENARIO("Translating a ray") {
    GIVEN("r <- ray(point(1, 2, 3), vector(0, 1, 0)), m <- translation(3, 4, 5)") {
        const Ray r(point(1, 2, 3), vector(0, 1, 0));
        const Matrix m = translation(3, 4, 5);

        WHEN("r2 <- r.transform(m)") {
            const Ray r2 = r.transform(m);

            THEN("r2.origin = point(4, 6, 8)") {
                REQUIRE(r2.origin == point(4, 6, 8));
            }

            AND_THEN("r2.direction = vector(0, 1, 0)") {
                REQUIRE(r2.direction == vector(0, 1, 0));
            }
        }
    }
}

SCENARIO("Scaling a ray") {
    GIVEN("r <- ray(point(1, 2, 3), vector(0, 1, 0)), m <- scaling(2, 3, 4)") {
        const Ray r(point(1, 2, 3), vector(0, 1, 0));
        const Matrix m = scaling(2, 3, 4);

        WHEN("r2 <- r.transform(m)") {
            const Ray r2 = r.transform(m);
            THEN("r2.origin = point(2, 6, 12)") {
                REQUIRE(r2.origin == point(2, 6, 12));
            }
            AND_THEN("r2.direction = vector(0, 3, 0)") {
                REQUIRE(r2.direction == vector(0, 3, 0));
            }
        }
    }
}