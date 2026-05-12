//
// Created by Nicholas Solomon on 2026-05-11.
//

#include <catch2/catch_test_macros.hpp>
#include <tuples/Tuple.h>
#include <lights/point/PointLight.h>

using namespace rtc::tuples;
using namespace rtc::lights::point;

SCENARIO("A point light has a position and an intensity") {
    GIVEN("intensity <- color(1, 1, 1), position <- point(0, 0, 0)") {
        const Color intensity = color(1, 1, 1);
        const Point position = point(0, 0, 0);

        WHEN("light <- PointLight(position, intensity)") {
            PointLight light{position, intensity};

            THEN("light.position = position") {
                REQUIRE(light.position == position);
            }

            AND_THEN("light.intensity = intensity") {
                REQUIRE(light.intensity == intensity);
            }
        }

    }
}