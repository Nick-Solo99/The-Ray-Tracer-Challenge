//
// Created by Nicholas Solomon on 2026-05-14.
//
#include <catch2/catch_test_macros.hpp>

#include "tuples/Tuple.h"
#include <patterns/stripes/StripePattern.h>
#include <transformations/Transformations.h>
#include <shapes/spheres/Sphere.h>
#include <patterns/Pattern.h>
#include <patterns/gradients/GradientPattern.h>

using namespace rtc::transformations;
using namespace rtc::tuples;
using namespace rtc::patterns::stripes;
using namespace rtc::shapes::spheres;
using namespace rtc::patterns::gradients;

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

SCENARIO("Stripes with an object transformation") {
    GIVEN("black <- color(0, 0, 0), white <- color(1, 1, 1), object <- sphere(), object.transform = scaling(2, 2, 2),"
          "pattern <- StripePattern(white, black)") {
        const Color black = color(0, 0, 0);
        const Color white = color(1, 1, 1);
        Sphere object{};
        object.transform = scaling(2, 2, 2);
        const StripePattern pattern{white, black};
        WHEN("c <- pattern.color_at_obj(object, point(1.5, 0, 0))") {
            const Color c = pattern.color_at_obj(object, point(1.5, 0, 0));
            THEN("c = white") {
                REQUIRE(c == white);
            }
        }

    }
}
SCENARIO("Stripes with a pattern transformation") {
    GIVEN("black <- color(0, 0, 0), white <- color(1, 1, 1), object <- sphere(), pattern <- StripePattern(white, black),"
          "pattern.transform = scaling(2, 2, 2),") {
        const Color black = color(0, 0, 0);
        const Color white = color(1, 1, 1);
        Sphere object{};
        StripePattern pattern{white, black};
        pattern.transform = scaling(2, 2, 2);
        WHEN("c <- pattern.color_at_obj(object, point(1.5, 0, 0))") {
            const Color c = pattern.color_at_obj(object, point(1.5, 0, 0));
            THEN("c = white") {
                REQUIRE(c == white);
            }
        }

    }
}
SCENARIO("Stripes with both an object and a pattern transformation") {
    GIVEN("black <- color(0, 0, 0), white <- color(1, 1, 1), object <- sphere(), object.transform = scaling(2, 2, 2),"
          "pattern <- StripePattern(white, black), pattern.transform = translation(0.5, 0, 0)") {
        const Color black = color(0, 0, 0);
        const Color white = color(1, 1, 1);
        Sphere object{};
        object.transform = scaling(2, 2, 2);
        StripePattern pattern{white, black};
        pattern.transform = translation(0.5, 0, 0);
        WHEN("c <- pattern.color_at_obj(object, point(1.5, 0, 0))") {
            const Color c = pattern.color_at_obj(object, point(2.5, 0, 0));
            THEN("c = white") {
                REQUIRE(c == white);
            }
        }

    }
}

SCENARIO("A gradient linearly interpolates between colors") {
    GIVEN("black <- color(0, 0 ,0), white <- color(1, 1, 1), pattern <- GradientPattern(white, black)") {
        const Color black = color(0, 0, 0);
        const Color white = color(1, 1, 1);
        const GradientPattern pattern{white, black};
        THEN("pattern.color_at(point(0, 0, 0)) = white") {
            REQUIRE(pattern.color_at(point(0, 0, 0)) == white);
        }
        AND_THEN("pattern.color_at(point(0.25, 0, 0)) = color(0.75, 0.75, 0.75)") {
            REQUIRE(pattern.color_at(point(0.25f, 0, 0)) == color(0.75f, 0.75f, 0.75f));
        }
        AND_THEN("pattern.color_at(point(0.5, 0, 0)) = color(0.5, 0.5, 0.5)") {
            REQUIRE(pattern.color_at(point(0.5f, 0, 0)) == color(0.5f, 0.5f, 0.5f));
        }
        AND_THEN("pattern.color_at(point(0.75, 0, 0)) = color(0.25, 0.25, 0.25)") {
            REQUIRE(pattern.color_at(point(0.75f, 0, 0)) == color(0.25f, 0.25f, 0.25f));
        }
    }
}