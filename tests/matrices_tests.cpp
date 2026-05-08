//
// Created by Nicholas Solomon on 2026-05-08.
//

#include <catch2/catch_test_macros.hpp>
#include "matrices/Matrix.h"

using namespace rtc::matrices;

constexpr float EPSILON = 0.00001;

SCENARIO("Constructing and inspecting a 4x4 matrix") {
    GIVEN("M <- {{1, 2, 3, 4}, {5.5, 6.5, 7.5, 8.5}, {9, 10, 11, 12}, {13.5, 14.5, 15.5, 16.5}}") {
        const Matrix M({{1, 2, 3, 4}, {5.5, 6.5, 7.5, 8.5}, {9, 10, 11, 12}, {13.5, 14.5, 15.5, 16.5}});

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
        const Matrix M({{-3, 5}, {1, -2}});

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
        const Matrix M({{-3, 5, 0}, {1, -2, -7}, {0, 1, 1}});

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
        const Matrix A({{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 8, 7, 6}, {5, 4, 3, 2}});
        const Matrix B({{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 8, 7, 6}, {5, 4, 3, 2}});

        THEN("A == B") {
            REQUIRE(A == B);
        }
    }
}

SCENARIO("Matrix equality with different matrices") {
    GIVEN("A <- {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 8, 7, 6}, {5, 4, 3, 2}}"
          "B <- {{2, 3, 4, 5}, {6, 7, 8, 9}, {8, 7, 6, 5}, {4, 3, 2, 1}}") {
        const Matrix A({{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 8, 7, 6}, {5, 4, 3, 2}});
        const Matrix B({{2, 3, 4, 5}, {6, 7, 8, 9}, {8, 7, 6, 5}, {4, 3, 2, 1}});

        THEN("A != B") {
            REQUIRE(A != B);
        }
    }
}

SCENARIO("Multiplying two matrices") {
    GIVEN("A <- {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 8, 7, 6}, {5, 4, 3, 2}}"
          "B <- {{-2, 1, 2, 3}, {3, 2, 1, -1}, {4, 3, 6, 5}, {1, 2, 7, 8}}") {
        const Matrix A({{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 8, 7, 6}, {5, 4, 3, 2}});
        const Matrix B({{-2, 1, 2, 3}, {3, 2, 1, -1}, {4, 3, 6, 5}, {1, 2, 7, 8}});

        THEN("A * B == Matrix({{20, 22, 50, 48}, {44, 54, 114, 108}, {40, 58, 110, 102}, {16, 26, 46, 42}})") {
            Matrix result({{20, 22, 50, 48}, {44, 54, 114, 108}, {40, 58, 110, 102}, {16, 26, 46, 42}});
            REQUIRE(A * B == result);
        }
    }
}

SCENARIO("A Matrix multiplied by a tuple") {
    GIVEN("A <- {{1, 2, 3, 4}, {2, 4, 4, 2}, {8, 6, 4, 1}, {0, 0, 0, 1}}"
          "b <- tuple(1, 2, 3, 1)") {
        const Matrix A({{1, 2, 3, 4}, {2, 4, 4, 2}, {8, 6, 4, 1}, {0, 0, 0, 1}});
        const Tuple b = tuple(1, 2, 3, 1);

        THEN("A * b = tuple(18, 24, 33, 1)") {
            REQUIRE(A * b == tuple(18, 24, 33, 1));
        }
    }
}