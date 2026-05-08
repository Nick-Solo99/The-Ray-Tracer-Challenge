//
// Created by Nicholas Solomon on 2026-05-08.
//

#include <catch2/catch_test_macros.hpp>
#include "matrices/Matrix.h"
#include <cmath>

using namespace rtc::matrices;

constexpr float EPSILON = 0.00001;

SCENARIO("Constructing and inspecting a 4x4 matrix") {
    GIVEN("M <- {{1, 2, 3, 4}, {5.5, 6.5, 7.5, 8.5}, {9, 10, 11, 12}, {13.5, 14.5, 15.5, 16.5}}") {
        Matrix M({{1, 2, 3, 4}, {5.5, 6.5, 7.5, 8.5}, {9, 10, 11, 12}, {13.5, 14.5, 15.5, 16.5}});

        THEN("M[0, 0] = 1") {
            REQUIRE(M[0, 0] == 1);
        }

        AND_THEN("M[0, 3] = 4") {
            REQUIRE(M[0, 3] == 4);
        }

        AND_THEN("M[1, 0] = 5.5") {
            REQUIRE(M[1, 0] == 5.5);
        }

        AND_THEN("M[1, 2] = 7.5") {
            REQUIRE(M[1, 2] == 7.5);
        }

        AND_THEN("M[2, 2] = 11") {
            REQUIRE(M[2, 2] == 11);
        }

        AND_THEN("M[3, 0] = 13.5") {
            REQUIRE(M[3, 0] == 13.5);
        }

        AND_THEN("M[3, 2] = 15.5") {
            REQUIRE(M[3, 2] == 15.5);
        }
    }
}

SCENARIO("A 2x2 matrix ought to be representable") {
    GIVEN("M <- {{-3, 5}, {1, -2}}") {
        Matrix M({{-3, 5}, {1, -2}});

        THEN("M[0, 0] = -3") {
            REQUIRE(M[0, 0] == -3);
        }

        AND_THEN("M[0, 1] = 5") {
            REQUIRE(M[0, 1] == 5);
        }

        AND_THEN("M[1, 0] = 1") {
            REQUIRE(M[1, 0] == 1);
        }

        AND_THEN("M[1, 1] = -2") {
            REQUIRE(M[1, 1] == -2);
        }
    }
}

SCENARIO("A 3x3 matrix ought to be representable") {
    GIVEN("M <- {{-3, 5, 0}, {1, -2, -7}, {0, 1, 1}}") {
        Matrix M({{-3, 5, 0}, {1, -2, -7}, {0, 1, 1}});

        THEN("M[0, 0] = -3") {
            REQUIRE(M[0, 0] == -3);
        }

        AND_THEN("M[1, 1] = -2") {
            REQUIRE(M[1, 1] == -2);
        }

        AND_THEN("M[2, 2] = 1") {
            REQUIRE(M[2, 2] == 1);
        }
    }
}

SCENARIO("Matrix equality with identical matrices") {
    GIVEN("A <- {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 8, 7, 6}, {5, 4, 3, 2}}"
          "B <- {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 8, 7, 6}, {5, 4, 3, 2}}") {
        Matrix A({{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 8, 7, 6}, {5, 4, 3, 2}});
        Matrix B({{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 8, 7, 6}, {5, 4, 3, 2}});

        THEN("A == B") {
            REQUIRE(A == B);
        }
    }
}

SCENARIO("Matrix equality with different matrices") {
    GIVEN("A <- {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 8, 7, 6}, {5, 4, 3, 2}}"
          "B <- {{2, 3, 4, 5}, {6, 7, 8, 9}, {8, 7, 6, 5}, {4, 3, 2, 1}}") {
        Matrix A({{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 8, 7, 6}, {5, 4, 3, 2}});
        Matrix B({{2, 3, 4, 5}, {6, 7, 8, 9}, {8, 7, 6, 5}, {4, 3, 2, 1}});

        THEN("A != B") {
            REQUIRE(A != B);
        }
    }
}