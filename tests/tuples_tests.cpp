//
// Created by xGrim on 2026-05-07.
//

#include <catch2/catch_test_macros.hpp>
#include <cmath>
#include "tuples/Tuple.h"

using namespace rtc::tuples;

constexpr float EPSILON = 0.00001f;

SCENARIO("A tuple with w=1.0 is a point") {
    GIVEN("a <- tuple(4.3, -4.2, 3.1, 1.0)") {
        Tuple a(4.3f, -4.2f, 3.1f, 1.0f);

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
        Tuple a(4.3f, -4.2f, 3.1f, 0.0f);

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
        Tuple p = point(4, -4, 3);

        THEN("p = tuple(4, -4, 3, 1") {
            REQUIRE(p == tuple(4, -4, 3, 1));
        }
    }
}

SCENARIO("vector() creates a tuple with w=0.0") {
    GIVEN("v <- vector(4, -4, 3)") {
        Tuple v = vector(4, -4, 3);

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
        const Tuple p1 = point(3, 2, 1);
        const Tuple p2 = point(5, 6, 7);

        THEN("p1 - p2 = vector(-2, -4, -6)") {
            REQUIRE(p1 - p2 == vector(-2, -4, -6));
        }
    }
}

SCENARIO("Subtracting two points using assignment operator") {
    GIVEN("p1 <- point(3, 2, 1), p2 <- point(5, 6, 7)") {
        Tuple p1 = point(3, 2, 1);
        const Tuple p2 = point(5, 6, 7);

        THEN("p1 -= p2 = vector(-2, -4, -6)") {
            p1 -= p2;
            REQUIRE(p1 == vector(-2, -4, -6));
        }
    }
}

SCENARIO("Subtracting two vectors") {
    GIVEN("v1 <- vector(3, 2, 1), v2 <- vector(5, 6, 7)") {
        const Tuple v1 = vector(3, 2, 1);
        const Tuple v2 = vector(5, 6, 7);

        THEN("v1 - v2 = vector(-2, -4, -6)") {
            REQUIRE(v1 - v2 == vector(-2, -4, -6));
        }
    }
}

SCENARIO("Subtracting a vector from the zero vector") {
    GIVEN("zero <- vector(0, 0, 0), v <- vector(1, 2, 3)") {
        const Tuple zero = vector(0, 0, 0);
        const Tuple v = vector(1, 2, 3);

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
        const Tuple v = vector(1, 0, 0);

        THEN("magnitude(v) = 1") {
            REQUIRE(magnitude(v) == 1);
        }
    }
}

SCENARIO("Computing the magnitude of vector(0, 1, 0)") {
    GIVEN("v <- vector(0, 1, 0)") {
        const Tuple v = vector(0, 1, 0);

        THEN("magnitude(v) = 1") {
            REQUIRE(magnitude(v) == 1);
        }
    }
}

SCENARIO("Computing the magnitude of vector(0, 0, 1)") {
    GIVEN("v <- vector(0, 0, 1)") {
        const Tuple v = vector(0, 0, 1);

        THEN("magnitude(v) = 1") {
            REQUIRE(magnitude(v) == 1);
        }
    }
}

SCENARIO("Computing the magnitude of vector(1, 2, 3)") {
    GIVEN("v <- vector(1, 2, 3)") {
        const Tuple v = vector(1, 2, 3);

        THEN("magnitude(v) = sqrt(14)") {
            REQUIRE(std::fabs(magnitude(v) - sqrt(14)) < EPSILON);
        }
    }
}

SCENARIO("Computing the magnitude of vector(-1, -2, -3)") {
    GIVEN("v <- vector(-1, -2, -3)") {
        const Tuple v = vector(-1, -2, -3);

        THEN("magnitude(v) = sqrt(14)") {
            REQUIRE(std::fabs(magnitude(v) - sqrt(14)) < EPSILON);
        }
    }
}

SCENARIO("Normalizing vector(4, 0, 0) gives (1, 0, 0)") {
    GIVEN("v <- vector(4, 0, 0)") {
        const Tuple v = vector(4, 0, 0);
        THEN("normalize(v) = vector(1, 0, 0)") {
            REQUIRE(normalize(v) == vector(1, 0, 0));
        }
    }
}

SCENARIO("Normalizing vector(1, 2, 3)") {
    GIVEN("v <- vector(1, 2, 3)") {
        const Tuple v = vector(1, 2, 3);
        THEN("normalize(v) = vector(1 / sqrt(14), 2 / sqrt(14), 3 / sqrt(14))") {
            REQUIRE(normalize(v) == vector(1 / sqrt(14), 2 / sqrt(14), 3 / sqrt(14)));
        }
    }
}

SCENARIO("The magnitude of a normalized vector") {
    GIVEN("v <- vector(1, 2, 3)") {
        const Tuple v = vector(1, 2, 3);

        WHEN("norm <- normalize(v)") {
            const Tuple norm = normalize(v);

            THEN("magnitude(norm) = 1") {
                REQUIRE(std::fabs(magnitude(norm) - 1) < EPSILON);
            }
        }
    }
}

SCENARIO("The dot product of two tuples") {
    GIVEN("a <- vector(1, 2, 3), b <- vector(2, 3, 4)") {
        const Tuple a = vector(1, 2, 3);
        const Tuple b = vector(2, 3, 4);

        THEN("dot(a, b) = 20") {
            REQUIRE(std::fabs(dot(a, b) - 20) < EPSILON);
        }
    }
}

SCENARIO("The cross product of two vectors") {
    GIVEN("a <- vector(1, 2, 3), b <- vector(2, 3, 4)") {
        const Tuple a = vector(1, 2, 3);
        const Tuple b = vector(2, 3, 4);

        THEN("cross(a, b) = vector(-1, 2, -1)") {
            REQUIRE(cross(a, b) == vector(-1, 2, -1));
        }

        AND_THEN("cross(b, a) = vector(1, -2, 1)") {
            REQUIRE(cross(b, a) == vector(1, -2, 1));
        }
    }
}