//
// Created by Nicholas Solomon on 2026-05-08.
//

#include <catch2/catch_test_macros.hpp>
#include <tuples/Tuple.h>
#include <rays/Ray.h>

using namespace rtc::tuples;
using namespace rtc::rays;

SCENARIO(" Creating and querying a ray") {
    GIVEN("origin <- point(1, 2, 3), direction <- vector(4, 5, 6)") {
        const Point origin = point(1, 2, 3);
        const Vector direction = vector(4, 5, 6);

        WHEN("r <- ray(origin, direction)") {
            Ray r(origin, direction);
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
        Ray r(point(2, 3, 4), vector(1, 0, 0));

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