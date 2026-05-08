//
// Created by Nicholas Solomon on 2026-05-07.
//

#include <catch2/catch_test_macros.hpp>
#include "canvas/Canvas.h"

using namespace rtc::canvas;

SCENARIO("Creating a canvas") {
    GIVEN("c <- canvas(10, 20)") {
        const Canvas c(10, 20);

        THEN("c.width = 10") {
            REQUIRE(c.width == 10);
        }

        AND_THEN("c.height = 20") {
            REQUIRE(c.height == 20);
        }

        AND_THEN("every pixel of c is color(0.0, 0.0, 0.0)") {
            bool isBlack = true;
            for (Color pixel : c.pixels) {
                if (pixel != color(0, 0, 0)) {
                    isBlack = false;
                }
            }
            REQUIRE(isBlack);
        }
    }
}

SCENARIO("Writing pixels to a canvas") {
    GIVEN("c <- canvas(10, 20), red <- color(1, 0, 0)") {
        Canvas c(10, 20);
        const Color red = color(1, 0, 0);

        WHEN("c.write_pixel(2, 3, red)") {
            c.write_pixel(2, 3, red);

            THEN("pixel_at(c, 2, 3) = red") {
                REQUIRE(c.pixel_at(2, 3) == red);
            }
        }
    }
}

