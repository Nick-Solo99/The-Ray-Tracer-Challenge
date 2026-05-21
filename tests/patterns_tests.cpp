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
#include <patterns/rings/RingPattern.h>
#include <patterns/checkers/CheckerPattern.h>
#include <patterns/test/TestPattern.h>

using namespace rtc::transformations;
using namespace rtc::tuples;
using namespace rtc::patterns::stripes;
using namespace rtc::shapes::spheres;
using namespace rtc::patterns::gradients;
using namespace rtc::patterns::rings;
using namespace rtc::patterns::checkers;
using namespace rtc::patterns::test;

SCENARIO("Creating a stripe pattern") {
    GIVEN("black <- color(0, 0, 0), white <- color(1, 1, 1), pattern <- StripePattern(white, black)") {
        const Color black = color(0, 0, 0);
        const Color white = color(1, 1, 1);
        const StripePattern pattern{white, black};
        THEN("pattern.a = white") {
           REQUIRE(pattern.a->color_at(point(0, 0, 0)) == white);
        }
        AND_THEN("pattern.b = black") {
           REQUIRE(pattern.b->color_at(point(0, 0, 0)) == black);
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

SCENARIO("A ring should extend in both x and z") {
    GIVEN("black <- color(0, 0 ,0), white <- color(1, 1, 1), pattern <- RingPattern(white, black)") {
        const Color black = color(0, 0, 0);
        const Color white = color(1, 1, 1);
        const RingPattern pattern{white, black};
        THEN("pattern.color_at(point(0, 0, 0)) = white") {
            REQUIRE(pattern.color_at(point(0, 0, 0)) == white);
        }
        AND_THEN("pattern.color_at(point(1, 0, 0)) = black") {
            REQUIRE(pattern.color_at(point(1, 0, 0)) == black);
        }
        AND_THEN("pattern.color_at(point(0, 0, 1)) = black") {
            REQUIRE(pattern.color_at(point(0, 0, 1)) == black);
        }
        AND_THEN("pattern.color_at(point(0.708, 0, 0.708)) = black") {
            REQUIRE(pattern.color_at(point(0.708f, 0, 0.708f)) == black);
        }
    }
}

SCENARIO("Checkers should repeat in x") {
    GIVEN("black <- color(0, 0, 0), white <- color(1, 1, 1), pattern <- CheckerPattern(white, black)") {
        const Color black = color(0, 0, 0);
        const Color white = color(1, 1, 1);
        const CheckerPattern pattern{white, black};
        THEN("pattern.color_at(point(0, 0, 0)) = white") {
            REQUIRE(pattern.color_at(point(0, 0, 0)) == white);
        }
        AND_THEN("pattern.color_at(point(0.99, 0, 0)) = white") {
            REQUIRE(pattern.color_at(point(0.99f, 0, 0)) == white);
        }
        AND_THEN("pattern.color_at(point(1.01, 0, 0)) = black") {
            REQUIRE(pattern.color_at(point(1.01f, 0, 0)) == black);
        }
    }
}
SCENARIO("Checkers should repeat in y") {
    GIVEN("black <- color(0, 0, 0), white <- color(1, 1, 1), pattern <- CheckerPattern(white, black)") {
        const Color black = color(0, 0, 0);
        const Color white = color(1, 1, 1);
        const CheckerPattern pattern{white, black};
        THEN("pattern.color_at(point(0, 0, 0)) = white") {
            REQUIRE(pattern.color_at(point(0, 0, 0)) == white);
        }
        AND_THEN("pattern.color_at(point(0, 0.99, 0)) = white") {
            REQUIRE(pattern.color_at(point(0, 0.99f, 0)) == white);
        }
        AND_THEN("pattern.color_at(point(0, 1.01, 0)) = black") {
            REQUIRE(pattern.color_at(point(0, 1.01f, 0)) == black);
        }
    }
}
SCENARIO("Checkers should repeat in z") {
    GIVEN("black <- color(0, 0, 0), white <- color(1, 1, 1), pattern <- CheckerPattern(white, black)") {
        const Color black = color(0, 0, 0);
        const Color white = color(1, 1, 1);
        const CheckerPattern pattern{white, black};
        THEN("pattern.color_at(point(0, 0, 0)) = white") {
            REQUIRE(pattern.color_at(point(0, 0, 0)) == white);
        }
        AND_THEN("pattern.color_at(point(0, 0, 0.99)) = white") {
            REQUIRE(pattern.color_at(point(0, 0, 0.99f)) == white);
        }
        AND_THEN("pattern.color_at(point(0, 0, 1.01)) = black") {
            REQUIRE(pattern.color_at(point(0, 0, 1.01f)) == black);
        }
    }
}

SCENARIO("The default pattern transformation") {
    GIVEN("pattern <- TestPattern()") {
        const TestPattern pattern{};
        THEN("pattern.transform = Matrix::identity()") {
            REQUIRE(pattern.transform == Matrix::identity());
        }
    }
}

SCENARIO("Assigning a transformation") {
    GIVEN("pattern <- TestPattern()") {
        TestPattern pattern{};
        WHEN("pattern.transform <- translation(1, 2, 3)") {
            pattern.transform = translation(1, 2, 3);
            THEN("pattern.transform = translation(1, 2, 3)") {
                REQUIRE(pattern.transform == translation(1, 2, 3));
            }
        }
    }
}

SCENARIO("A pattern with an object transformation") {
    GIVEN("shape <- sphere(), sphere.transform <- scaling(2, 2, 2), pattern <- TestPattern()") {
        Sphere shape{};
        shape.transform = scaling(2, 2, 2);
        const TestPattern pattern{};
        WHEN("c <- pattern.color_at_obj(shape, point(2, 3, 4))") {
            const Color c = pattern.color_at_obj(shape, point(2, 3, 4));
            THEN("c = color(1, 1.5, 2)") {
                REQUIRE(c == color(1, 1.5, 2));
            }
        }
    }
}

SCENARIO("A pattern with a pattern transformation") {
    GIVEN("shape <- sphere(), pattern <- TestPattern(), pattern.transform <- scaling(2, 2, 2)") {
        const Sphere shape{};
        TestPattern pattern{};
        pattern.transform = scaling(2, 2, 2);
        WHEN("c <- pattern.color_at_obj(shape, point(2, 3, 4))") {
            const Color c = pattern.color_at_obj(shape, point(2, 3, 4));
            THEN("c = color(1, 1.5, 2)") {
                REQUIRE(c == color(1, 1.5, 2));
            }
        }
    }
}

SCENARIO("A pattern with both an object and a pattern transformation") {
    GIVEN("shape <- sphere(), shape.transform <- scaling(2, 2, 2), pattern <- TestPattern(), pattern.transform <- translation(0.5, 1, 1.5)") {
        Sphere shape{};
        shape.transform = scaling(2, 2, 2);
        TestPattern pattern{};
        pattern.transform = translation(0.5, 1, 1.5);
        WHEN("c <- pattern.color_at_obj(shape, point(2.5, 3, 3.5))") {
            const Color c = pattern.color_at_obj(shape, point(2.5, 3, 3.5));
            THEN("c = color(0.75, 0.5, 0.25)") {
                REQUIRE(c == color(0.75, 0.5, 0.25));
            }
        }
    }
}
