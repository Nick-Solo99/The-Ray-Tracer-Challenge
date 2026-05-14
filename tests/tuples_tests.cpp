//
// Created by Nicholas Solomon on 2026-05-07.
//

#include <catch2/catch_test_macros.hpp>
#include <cmath>
#include "tuples/Tuple.h"
#include <constants/Constants.h>

using namespace rtc::tuples;
using namespace rtc::constants;


SCENARIO("A tuple with w=1.0 is a point") {
    GIVEN("a <- tuple(4.3, -4.2, 3.1, 1.0)") {
        Tuple a = tuple(4.3f, -4.2f, 3.1f, 1.0f);

        THEN("it has correct components") {
            REQUIRE(a.x == 4.3f);
            REQUIRE(a.y == -4.2f);
            REQUIRE(a.z == 3.1f);
            REQUIRE(a.w == 1.0f);
        }

        AND_THEN("it is a point") {
            REQUIRE(a.isPoint() == true);
        }

        AND_THEN("it is not a vector") {
            REQUIRE(a.isVector() == false);
        }
    }
}

SCENARIO("A tuple with w=0 is a vector") {
    GIVEN("a <- tuple(4.3, -4.2, 3.1, 1.0)") {
        Tuple a = tuple(4.3f, -4.2f, 3.1f, 0.0f);

        THEN("it has correct components") {
            REQUIRE(a.x == 4.3f);
            REQUIRE(a.y == -4.2f);
            REQUIRE(a.z == 3.1f);
            REQUIRE(a.w == 0.0f);
        }

        AND_THEN("it is a point") {
            REQUIRE(a.isPoint() == false);
        }

        AND_THEN("it is not a vector") {
            REQUIRE(a.isVector() == true);
        }
    }
}

SCENARIO("point() creates a tuple with w=1.0") {
    GIVEN("p <- point(4, -4, 3)") {
        Point p = point(4, -4, 3);

        THEN("p = tuple(4, -4, 3, 1") {
            REQUIRE(p == tuple(4, -4, 3, 1));
        }
    }
}

SCENARIO("vector() creates a tuple with w=0.0") {
    GIVEN("v <- vector(4, -4, 3)") {
        Vector v = vector(4, -4, 3);

        THEN("v = tuple(4, -4, 3, 0") {
            REQUIRE(v == tuple(4, -4, 3, 0));
        }
    }
}

SCENARIO("Adding two tuples") {
    GIVEN("a1 <- tuple(3, -2, 5, 1), a2 <- tuple(-2, 3, 1, 0)") {
        const Tuple a1 = tuple(3, -2, 5, 1);
        const Tuple a2 = tuple(-2, 3, 1, 0);

        THEN("a1 + a2 = tuple(1, 1, 6, 1)") {
            REQUIRE(a1 + a2 == tuple(1, 1, 6, 1));
        }
    }
}

SCENARIO("Adding two tuples using assignment operator") {
    GIVEN("a1 <- tuple(3, -2, 5, 1), a2 <- tuple(-2, 3, 1, 0)") {
        Tuple a1 = tuple(3, -2, 5, 1);
        const Tuple a2 = tuple(-2, 3, 1, 0);

        THEN("a1 += a2 = tuple(1, 1, 6, 1)") {
            a1 += a2;
            REQUIRE(a1 == tuple(1, 1, 6, 1));
        }
    }
}

SCENARIO("Subtracting two points") {
    GIVEN("p1 <- point(3, 2, 1), p2 <- point(5, 6, 7)") {
        const Point p1 = point(3, 2, 1);
        const Point p2 = point(5, 6, 7);

        THEN("p1 - p2 = vector(-2, -4, -6)") {
            REQUIRE(p1 - p2 == vector(-2, -4, -6));
        }
    }
}

SCENARIO("Subtracting two points using assignment operator") {
    GIVEN("p1 <- point(3, 2, 1), p2 <- point(5, 6, 7)") {
        Point p1 = point(3, 2, 1);
        const Point p2 = point(5, 6, 7);

        THEN("p1 -= p2 = vector(-2, -4, -6)") {
            p1 -= p2;
            REQUIRE(p1 == vector(-2, -4, -6));
        }
    }
}

SCENARIO("Subtracting two vectors") {
    GIVEN("v1 <- vector(3, 2, 1), v2 <- vector(5, 6, 7)") {
        const Vector v1 = vector(3, 2, 1);
        const Vector v2 = vector(5, 6, 7);

        THEN("v1 - v2 = vector(-2, -4, -6)") {
            REQUIRE(v1 - v2 == vector(-2, -4, -6));
        }
    }
}

SCENARIO("Subtracting a vector from the zero vector") {
    GIVEN("zero <- vector(0, 0, 0), v <- vector(1, 2, 3)") {
        const Vector zero = vector(0, 0, 0);
        const Vector v = vector(1, 2, 3);

        THEN("zero - v = vector(-1, -2, -3") {
            REQUIRE(zero - v == vector(-1, -2, -3));
        }
    }
}

SCENARIO("Negating a tuple") {
    GIVEN("a <- tuple(1, -2, 3, -4)") {
        const Tuple a = tuple(1, -2, 3, -4);

        THEN("-a = tuple(-1, 2, -3, 4)") {
            REQUIRE(-a == tuple(-1, 2, -3, 4));
        }
    }
}

SCENARIO("Multiplying a tuple by a scalar") {
    GIVEN("a <- tuple(1, -2, 3, -4)") {
        const Tuple a = tuple(1, -2, 3, -4);

        THEN("a * 3.5 = tuple(0.5, -1, 1.5, -2") {
            REQUIRE(a * 3.5 == tuple(3.5, -7, 10.5, -14));
        }
    }
}

SCENARIO("Multiplying a scalar by a tuple") {
    GIVEN("a <- tuple(1, -2, 3, -4)") {
        const Tuple a = tuple(1, -2, 3, -4);

        THEN("3.5 * a = tuple(0.5, -1, 1.5, -2") {
            REQUIRE(3.5 * a == tuple(3.5, -7, 10.5, -14));
        }
    }
}

SCENARIO("Multiplying a tuple by a fraction") {
    GIVEN("a <- tuple(1, -2, 3, -4)") {
        const Tuple a = tuple(1, -2, 3, -4);

        THEN("a * 0.5 = tuple(0.5, -1, 1.5, -2") {
            REQUIRE(a * 0.5 == tuple(0.5, -1, 1.5, -2));
        }
    }
}

SCENARIO("Dividing a tuple by a scalar") {
    GIVEN("a <- tuple(1, -2, 3, -4)") {
        const Tuple a = tuple(1, -2, 3, -4);

        THEN("a / 2 = tuple(0.5, -1, 1.5, -2") {
            REQUIRE(a / 2 == tuple(0.5, -1, 1.5, -2));
        }
    }
}

SCENARIO("Computing the magnitude of vector(1, 0, 0)") {
    GIVEN("v <- vector(1, 0, 0)") {
        const Vector v = vector(1, 0, 0);

        THEN("magnitude(v) = 1") {
            REQUIRE(magnitude(v) == 1);
        }
    }
}

SCENARIO("Computing the magnitude of vector(0, 1, 0)") {
    GIVEN("v <- vector(0, 1, 0)") {
        const Vector v = vector(0, 1, 0);

        THEN("magnitude(v) = 1") {
            REQUIRE(magnitude(v) == 1);
        }
    }
}

SCENARIO("Computing the magnitude of vector(0, 0, 1)") {
    GIVEN("v <- vector(0, 0, 1)") {
        const Vector v = vector(0, 0, 1);

        THEN("magnitude(v) = 1") {
            REQUIRE(magnitude(v) == 1);
        }
    }
}

SCENARIO("Computing the magnitude of vector(1, 2, 3)") {
    GIVEN("v <- vector(1, 2, 3)") {
        const Vector v = vector(1, 2, 3);

        THEN("magnitude(v) = sqrt(14)") {
            REQUIRE(std::fabs(magnitude(v) - sqrt(14)) < EPSILON);
        }
    }
}

SCENARIO("Computing the magnitude of vector(-1, -2, -3)") {
    GIVEN("v <- vector(-1, -2, -3)") {
        const Vector v = vector(-1, -2, -3);

        THEN("magnitude(v) = sqrt(14)") {
            REQUIRE(std::fabs(magnitude(v) - sqrt(14)) < EPSILON);
        }
    }
}

SCENARIO("Normalizing vector(4, 0, 0) gives (1, 0, 0)") {
    GIVEN("v <- vector(4, 0, 0)") {
        const Vector v = vector(4, 0, 0);
        THEN("normalize(v) = vector(1, 0, 0)") {
            REQUIRE(normalize(v) == vector(1, 0, 0));
        }
    }
}

SCENARIO("Normalizing vector(1, 2, 3)") {
    GIVEN("v <- vector(1, 2, 3)") {
        const Vector v = vector(1, 2, 3);
        THEN("normalize(v) = vector(1 / sqrt(14), 2 / sqrt(14), 3 / sqrt(14))") {
            REQUIRE(normalize(v) == vector(1 / sqrt(14), 2 / sqrt(14), 3 / sqrt(14)));
        }
    }
}

SCENARIO("The magnitude of a normalized vector") {
    GIVEN("v <- vector(1, 2, 3)") {
        const Vector v = vector(1, 2, 3);

        WHEN("norm <- normalize(v)") {
            const Vector norm = normalize(v);

            THEN("magnitude(norm) = 1") {
                REQUIRE(std::fabs(magnitude(norm) - 1) < EPSILON);
            }
        }
    }
}

SCENARIO("The dot product of two tuples") {
    GIVEN("a <- vector(1, 2, 3), b <- vector(2, 3, 4)") {
        const Vector a = vector(1, 2, 3);
        const Vector b = vector(2, 3, 4);

        THEN("dot(a, b) = 20") {
            REQUIRE(std::fabs(dot(a, b) - 20) < EPSILON);
        }
    }
}

SCENARIO("The cross product of two vectors") {
    GIVEN("a <- vector(1, 2, 3), b <- vector(2, 3, 4)") {
        const Vector a = vector(1, 2, 3);
        const Vector b = vector(2, 3, 4);

        THEN("cross(a, b) = vector(-1, 2, -1)") {
            REQUIRE(cross(a, b) == vector(-1, 2, -1));
        }

        AND_THEN("cross(b, a) = vector(1, -2, 1)") {
            REQUIRE(cross(b, a) == vector(1, -2, 1));
        }
    }
}

SCENARIO("Colors are (red, green, blue) tuples") {
    GIVEN("c <- color(-0.5, 0.4, 1.7)") {
        const Color c = color(-0.5, 0.4, 1.7);

        THEN("c.r = -0.5, c.g = 0.4, c.b = 1.7") {
            REQUIRE(std::fabs(c.r + 0.5) < EPSILON);
            REQUIRE(std::fabs(c.g - 0.4) < EPSILON);
            REQUIRE(std::fabs(c.b - 1.7) < EPSILON);
        }
    }
}

SCENARIO("Adding colors") {
    GIVEN("c1 <- color(0.9, 0.6, 0.75), c2 <- color(0.7, 0.1, 0.25") {
        const Color c1 = color(0.9, 0.6, 0.75);
        const Color c2 = color(0.7, 0.1, 0.25);

        THEN("c1 + c2 = color(1.6, 0.7, 1.0)") {
            REQUIRE(c1 + c2 == color(1.6, 0.7, 1.0));
        }
    }
}

SCENARIO("Subtracting colors") {
    GIVEN("c1 <- color(0.9, 0.6, 0.75), c2 <- color(0.7, 0.1, 0.25") {
        const Color c1 = color(0.9, 0.6, 0.75);
        const Color c2 = color(0.7, 0.1, 0.25);

        THEN("c1 - c2 = color(0.2, 0,5, 0.5)") {
            REQUIRE(c1 - c2 == color(0.2, 0.5, 0.5));
        }
    }
}

SCENARIO("Multiplying a color by a scalar") {
    GIVEN("c <- color(0.2, 0.3, 0.4)") {
        const Color c = color(0.2, 0.3, 0.4);

        THEN("c * 2 = color(0.4, 0.6, 0.8)") {
            REQUIRE(c * 2 == color(0.4, 0.6, 0.8));
        }

        AND_THEN("2 * c = color(0.4, 0.6, 0.8)") {
            REQUIRE(2 * c == color(0.4, 0.6, 0.8));
        }
    }
}

SCENARIO("Multiplying colors") {
    GIVEN("c1 <- color(1, 0.2, 0.4), c2 <- color(0.9, 1, 0.1)") {
        const Color c1 = color(1, 0.2, 0.4);
        const Color c2 = color(0.9, 1, 0.1);

        THEN("c1 * c2 = color(0.9, 0.2, 0.04)") {
            REQUIRE(c1 * c2 == color(0.9, 0.2, 0.04));
        }
    }
}

SCENARIO("Reflecting a vector approaching at 45 deg") {
    GIVEN("v <- vector(1, -1, 0), n <- vector(0, 1, 0)") {
        const Vector v = vector(1, -1, 0);
        const Vector n = vector(0, 1, 0);

        WHEN("r <- v.reflect(n)") {
            const Vector r = v.reflect(n);

            THEN("r = vector(1, 1, 0)") {
                REQUIRE(r == vector(1, 1, 0));
            }
        }
    }
}

SCENARIO("Reflecting a vector off a slanted surface") {
    GIVEN("v <- vector(0, -1, 0), n <- vector(sqrt(2)/2, sqrt(2)/2, 0)") {
        const Vector v = vector(0, -1, 0);
        const Vector n = vector(std::sqrtf(2.0f)/2.0f, std::sqrtf(2.0f)/2.0f, 0.0f);

        WHEN("r <- v.reflect(n)") {
            const Vector r = v.reflect(n);

            THEN("r = vector(1, 0, 0)") {
                REQUIRE(r == vector(1, 0, 0));
            }
        }
    }
}