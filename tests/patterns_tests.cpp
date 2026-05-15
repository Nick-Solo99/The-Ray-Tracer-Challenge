//
// Created by Nicholas Solomon on 2026-05-14.
//
#include <catch2/catch_test_macros.hpp>

#include "tuples/Tuple.h"
#include <patterns/stripes/StripePattern.h>
using namespace rtc::tuples;
using namespace rtc::patterns::stripes;

SCENARIO("Creating a stripe pattern") {
    GIVEN("black <- color(0, 0, 0), white <- color(1, 1, 1), pattern <- StripePattern(white, black)") {
        const Color black = color(0, 0, 0);
        const Color white = color(1, 1, 1);
        const StripePattern pattern{white, black};
        THEN("pattern.a = white") {
           REQUIRE(pattern.a == white);
        }
        AND_THEN("pattern.b = black") {
           REQUIRE(pattern.b == black);
        }
    }
}

SCENARIO("A stripe pattern is constant in y") {
    GIVEN("black <- color(0, 0, 0), white <- color(1, 1, 1), pattern <- StripePattern(white, black)") {
        const Color black = color(0, 0, 0);
        const Color white = color(1, 1, 1);
        const StripePattern pattern{white, black};
        THEN("pattern.color_at(point(0, 0, 0)) = white") {
            REQUIRE(pattern.color_at(point(0, 0, 0)) == white);
        }
        AND_THEN("pattern.color_at(point(0, 1, 0)) = white") {
            REQUIRE(pattern.color_at(point(0, 1, 0)) == white);
        }
        AND_THEN("pattern.color_at(point(0, 2, 0)) = white") {
            REQUIRE(pattern.color_at(point(0, 2, 0)) == white);
        }
    }
}

SCENARIO("A stripe pattern is constant in z") {
    GIVEN("black <- color(0, 0, 0), white <- color(1, 1, 1), pattern <- StripePattern(white, black)") {
        const Color black = color(0, 0, 0);
        const Color white = color(1, 1, 1);
        const StripePattern pattern{white, black};
        THEN("pattern.color_at(point(0, 0, 0)) = white") {
            REQUIRE(pattern.color_at(point(0, 0, 0)) == white);
        }
        AND_THEN("pattern.color_at(point(0, 1, 0)) = white") {
            REQUIRE(pattern.color_at(point(0, 0, 1)) == white);
        }
        AND_THEN("pattern.color_at(point(0, 2, 0)) = white") {
            REQUIRE(pattern.color_at(point(0, 0, 2)) == white);
        }
    }
}

SCENARIO("A stripe pattern alternates in x") {
    GIVEN("black <- color(0, 0, 0), white <- color(1, 1, 1), pattern <- StripePattern(white, black)") {
        const Color black = color(0, 0, 0);
        const Color white = color(1, 1, 1);
        const StripePattern pattern{white, black};
        THEN("pattern.color_at(point(0, 0, 0)) = white") {
            REQUIRE(pattern.color_at(point(0, 0, 0)) == white);
        }
        AND_THEN("pattern.color_at(point(0.9, 0, 0)) = white") {
            REQUIRE(pattern.color_at(point(0.9f, 0, 0)) == white);
        }
        AND_THEN("pattern.color_at(point(1, 0, 0)) = black") {
            REQUIRE(pattern.color_at(point(1.f, 0, 0)) == black);
        }
        AND_THEN("pattern.color_at(point(-0.1, 0, 0)) = black") {
            REQUIRE(pattern.color_at(point(-0.1f, 0, 0)) == black);
        }
        AND_THEN("pattern.color_at(point(-1, 0, 0)) = black") {
            REQUIRE(pattern.color_at(point(-1.f, 0, 0)) == black);
        }
        AND_THEN("pattern.color_at(point(-1.1, 0, 0)) = white") {
            REQUIRE(pattern.color_at(point(-1.1f, 0, 0)) == white);
        }
    }
}
