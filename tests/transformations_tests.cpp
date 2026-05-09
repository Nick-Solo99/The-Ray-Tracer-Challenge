//
// Created by Nicholas Solomon on 2026-05-08.
//

#include <catch2/catch_test_macros.hpp>

#include "matrices/Matrix.h"
#include "transformations/Transformations.h"
#include <numbers>

using namespace rtc::transformations;
using namespace rtc::matrices;
using namespace rtc::tuples;

constexpr float PI = std::numbers::pi_v<float>;

SCENARIO("Multiplying by a translation matrix") {
    GIVEN("transform <- translation(5, -3, 2), p <- point(-3, 4, 5)") {
        const Matrix transform = translation(5, -3, 2);
        const Point p = point(-3, 4, 5);
        THEN("transform * p = point(2, 1, 7)") {
            REQUIRE(transform * p == point(2, 1, 7));
        }
    }
}

SCENARIO("Multiplying by the inverse of a translation matrix") {
    GIVEN("transform <- translation(5, -3, 2), inv <- transform.inverse(), p <- point(-3, 4, 5)") {
        const Matrix transform = translation(5, -3, 2);
        const Matrix inverse = transform.inverse();
        const Point p = point(-3, 4, 5);
        THEN("inv * p = point(-8, 7, 3)") {
            REQUIRE(inverse * p == point(-8, 7, 3));
        }
    }
}

SCENARIO("Translation does not affect vectors") {
    GIVEN("transform <- translation(5, -3, 2), v <- vector(-3, 4, 5)") {
        const Matrix transform = translation(5, -3, 2);
        const Vector v = vector(-3, 4, 5);

        THEN("transform * v = v") {
            REQUIRE(transform * v == v);
        }
    }
}

SCENARIO("A Scaling matrix applied to a point") {
    GIVEN("transform <- scaling(2, 3, 4), p <- point(-4, 6, 8)") {
        const Matrix transform = scaling(2, 3, 4);
        const Point p = point(-4, 6, 8);
        THEN("transform * p = point(-8, 18, 32)") {
            REQUIRE(transform * p == point(-8, 18, 32));
        }
    }
}

SCENARIO("A Scaling matrix applied to a vector") {
    GIVEN("transform <- scaling(2, 3, 4), v <- vector(-4, 6, 8)") {
        const Matrix transform = scaling(2, 3, 4);
        const Vector v = vector(-4, 6, 8);
        THEN("transform * v = vector(-8, 18, 32)") {
            REQUIRE(transform * v == vector(-8, 18, 32));
        }
    }
}

SCENARIO("Multiplying by the inverse of a scaling matrix") {
    GIVEN("transform <- scaling(2, 3, 4), inv <- transform.inverse(), v <- vector(-4, 6, 8)") {
        const Matrix transform = scaling(2, 3, 4);
        const Matrix inv = transform.inverse();
        const Vector v = vector(-4, 6, 8);

        THEN("inv * v = vector(-2, 2, 2)") {
            REQUIRE(inv * v == vector(-2, 2, 2));
        }
    }
}

SCENARIO("Reflection is scaling by a negative value") {
    GIVEN("transform <- scaling(-1, 1, 1), p <- point(2, 3, 4)") {
        const Matrix transform = scaling(-1, 1, 1);
        const Point p = point(2, 3, 4);

        THEN("transform * p = point(-2, 3, 4)") {
            REQUIRE(transform * p == point(-2, 3, 4));
        }
    }
}

SCENARIO("Rotating a point around the x axis") {
    GIVEN("p <- point(0, 1, 0), half_quarter <- rotation_x(PI / 4), full_quarter <- rotation_x(PI / 2)") {
        const Point p = point(0, 1, 0);
        const Matrix half_quarter = rotation_x(PI / 4);
        const Matrix full_quarter = rotation_x(PI / 2);

        THEN("half_quarter * p = point(0, sqrt(2)/2, sqrt(2)/2)") {
            REQUIRE(half_quarter * p == point(0, sqrt(2)/2, sqrt(2)/2));
        }

        AND_THEN("full_quarter * p = point(0, 0, 1") {
            REQUIRE(full_quarter * p == point(0, 0, 1));
        }
    }
}

SCENARIO("The inverse of an x rotation rotates in the opposite direction") {
    GIVEN("p <- point(0, 1, 0), half_quarter <- rotation_x(PI / 4), inv <- half_quarter.inverse()") {
        const Point p = point(0, 1, 0);
        const Matrix half_quarter = rotation_x(PI / 4);
        const Matrix inv = half_quarter.inverse();

        THEN("inv * p = point(0, sqrt(2)/2, -sqrt(2)/2)") {
            REQUIRE(inv * p == point(0, sqrt(2)/2, -sqrt(2)/2));
        }
    }
}