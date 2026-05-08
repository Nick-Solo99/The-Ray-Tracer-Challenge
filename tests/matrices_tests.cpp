//
// Created by Nicholas Solomon on 2026-05-08.
//

#include <catch2/catch_test_macros.hpp>
#include "matrices/Matrix.h"

using namespace rtc::matrices;
using namespace rtc::tuples;

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

SCENARIO("Multiplying a matrix by the identity matrix") {
    GIVEN("A <- {{0, 1, 2, 4}, {1, 2, 4, 8}, {2, 4, 8, 16}, {4, 8, 16, 32}}") {
        const Matrix A({{0, 1, 2, 4}, {1, 2, 4, 8}, {2, 4, 8, 16}, {4, 8, 16, 32}});

        THEN("A * Matrix::identity() = A") {
            REQUIRE(A * Matrix::identity() == A);
        }
    }
}

SCENARIO("Multiplying the identity matrix by a tuple") {
    GIVEN("a <- tuple(1, 2, 3, 4)") {
        const Tuple a = tuple(1, 2, 3, 4);

        THEN("Matrix::identity() * a = a") {
            REQUIRE(Matrix::identity() * a == a);
        }
    }
}

SCENARIO("Transposing a matrix") {
    GIVEN("A <- {{0, 9, 3, 0}, {9, 8, 0, 8}, {1, 8, 5, 3}, {0, 0, 5, 8}}") {
        const Matrix A({{0, 9, 3, 0}, {9, 8, 0, 8}, {1, 8, 5, 3}, {0, 0, 5, 8}});

        THEN("A.transpose() = Matrix({{0, 9, 1, 0}, {9, 8, 8, 0}, {3, 0, 5, 5}, {0, 8, 3, 8}})") {
            Matrix result({{0, 9, 1, 0}, {9, 8, 8, 0}, {3, 0, 5, 5}, {0, 8, 3, 8}});

            REQUIRE(A.transpose() == result);
        }
    }
}

SCENARIO("Transposing the identity matrix") {
    GIVEN("A <- Matrix::identity().transpose()") {
        const Matrix A = Matrix::identity().transpose();
        THEN("A = Matrix::identity()") {
            REQUIRE(A == Matrix::identity());
        }
    }
}

SCENARIO("Calculating the determinant of a 2x2 matrix") {
    GIVEN(" A <- {{1, 5}, {-3, 2}}") {
        const Matrix A({{1, 5}, {-3, 2}});
        THEN("A.determinant() = 17") {
            REQUIRE(A.determinant() == 17);
        }
    }
}

SCENARIO("A submatrix of a 3x3 matrix is a 2x2 matrix") {
    GIVEN("A <- {{1, 5, 0}, {-3, 2, 7}, {0, 6, -3}}") {
        const Matrix A({{1, 5, 0}, {-3, 2, 7}, {0, 6, -3}});

        THEN("A.submatrix(0, 2) = Matrix({{-3, 2}, {0, 6}})") {
            REQUIRE(A.submatrix(0, 2) == Matrix({{-3, 2}, {0, 6}}));
        }
    }
}

SCENARIO("A submatrix of a 4x4 matrix is a 3x3 matrix") {
    GIVEN("A <- {{-6, 1, 1, 6}, {-8, 5, 8, 6}, {-1, 0, 8, 2}, {-7, 1, -1, 1}}") {
        const Matrix A({{-6, 1, 1, 6}, {-8, 5, 8, 6}, {-1, 0, 8, 2}, {-7, 1, -1, 1}});

        THEN("A.submatrix(2, 1) = Matrix({{-6, 1, 6}, {-8, 8, 6}, {-7, -1, 1}})") {
            REQUIRE(A.submatrix(2, 1) == Matrix({{-6, 1, 6}, {-8, 8, 6}, {-7, -1, 1}}));
        }
    }
}

SCENARIO("Calculating a minor of a 3x3 matrix") {
    GIVEN("A <- {{3, 5, 0}, {2, -1, -7}, {6, -1, 5}}, B <- A.submatrix(1, 0)") {
        const Matrix A({{3, 5, 0}, {2, -1, -7}, {6, -1, 5}});
        const Matrix B = A.submatrix(1, 0);

        THEN("B.determinant() = 25") {
            REQUIRE(B.determinant() == 25);
        }

        AND_THEN("A.minor(1, 0) = 25") {
            REQUIRE(A.minor(1, 0) == 25);
        }
    }
}

SCENARIO("Calculating a cofactor of a 3x3 matrix") {
    GIVEN("A <- {{3, 5, 0}, {2, -1, -7}, {6, -1, 5}}") {
        const Matrix A({{3, 5, 0}, {2, -1, -7}, {6, -1, 5}});

        THEN("A.minor(0, 0) = -12") {
            REQUIRE(A.minor(0, 0) == -12);
        }

        AND_THEN("A.cofactor(0, 0) = -12") {
            REQUIRE(A.cofactor(0, 0) == -12);
        }

        AND_THEN("A.minor(1, 0) = 25") {
            REQUIRE(A.minor(1, 0) == 25);
        }

        AND_THEN("A.cofactor(1, 0) = -25") {
            REQUIRE(A.cofactor(1, 0) == -25);
        }
    }
}

SCENARIO("Calculating the determinant of a 3x3 matrix") {
    GIVEN("A <- {{1, 2, 6}, {-5, 8, -4}, {2, 6, 4}}") {
        const Matrix A({{1, 2, 6}, {-5, 8, -4}, {2, 6, 4}});

        THEN("A.cofactor(0, 0) = 56") {
            REQUIRE(A.cofactor(0, 0) == 56);
        }

        AND_THEN("A.cofactor(0, 1) = 12") {
            REQUIRE(A.cofactor(0, 1) == 12);
        }

        AND_THEN("A.cofactor(0, 2) = -46") {
            REQUIRE(A.cofactor(0, 2) == -46);
        }

        AND_THEN("A.determinant() = -196") {
            REQUIRE(A.determinant() == -196);
        }
    }
}

SCENARIO("Calculating the determinant of a 4x4 matrix") {
    GIVEN("A <- {{-2, -8, 3, 5}, {-3, 1, 7, 3}, {1, 2, -9, 6}, {-6, 7, 7, -9}}") {
        const Matrix A({{-2, -8, 3, 5}, {-3, 1, 7, 3}, {1, 2, -9, 6}, {-6, 7, 7, -9}});

        THEN("A.cofactor(0, 0) = 690") {
            REQUIRE(A.cofactor(0, 0) == 690);
        }

        AND_THEN("A.cofactor(0, 1) = 447") {
            REQUIRE(A.cofactor(0, 1) == 447);
        }

        AND_THEN("A.cofactor(0, 2) = 210") {
            REQUIRE(A.cofactor(0, 2) == 210);
        }

        AND_THEN("A.cofactor(0, 3) = 51") {
            REQUIRE(A.cofactor(0, 3) == 51);
        }

        AND_THEN("A.determinant() = -4071") {
            REQUIRE(A.determinant() == -4071);
        }
    }
}

SCENARIO("Testing an invertible matrix for invertibility") {
    GIVEN("A <- {{6, 4, 4, 4}, {5, 5, 7, 6}, {4, -9, 3, -7}, {9, 1, 7, -6}}") {
        const Matrix A( {{6, 4, 4, 4}, {5, 5, 7, 6}, {4, -9, 3, -7}, {9, 1, 7, -6}});

        THEN("A.determinant() = -2120") {
            REQUIRE(A.determinant() == -2120);
        }

        AND_THEN("A is invertible") {
            REQUIRE(A.invertible());
        }
    }
}

SCENARIO("Testing a noninvertible matrix for invertibility") {
    GIVEN("A <- {{-4, 2, -2, -3}, {9, 6, 2, 6}, {0, -5, 1, -5}, {0, 0, 0, 0}}") {
        const Matrix A( {{-4, 2, -2, -3}, {9, 6, 2, 6}, {0, -5, 1, -5}, {0, 0, 0, 0}});

        THEN("A.determinant() = 0") {
            REQUIRE(A.determinant() == 0);
        }

        AND_THEN("A is not invertible") {
            REQUIRE(!A.invertible());
        }
    }
}

SCENARIO("Calculating the inverse of a matrix") {
    GIVEN("A <- {{-5, 2, 6, -8}, {1, -5, 1, 8}, {7, 7, -6, -7}, {1, -3, 7, 4}}"
          "B <- A.inverse()") {
        const Matrix A({{-5, 2, 6, -8}, {1, -5, 1, 8}, {7, 7, -6, -7}, {1, -3, 7, 4}});
        const Matrix B = A.inverse();

        THEN("A.determinant() = 532") {
            REQUIRE(A.determinant() == 532);
        }

        AND_THEN("A.cofactor(2, 3) = -160") {
            REQUIRE(A.cofactor(2, 3) == -160);
        }

        AND_THEN("B[3, 2] = -160/532") {
            REQUIRE(B[3, 2] == -160.0f/532.0f);
        }

        AND_THEN("A.cofactor(3, 2) = 105") {
            REQUIRE(A.cofactor(3, 2) == 105);
        }

        AND_THEN("B[2, 3] = 105/532") {
            REQUIRE(B[2, 3] == 105.0f/532.0f);
        }

        AND_THEN("B = {"
                 "{0.21805, 0.45113, 0.24060, -0.04511},"
                 "{-0.80827, -1.45677, -0.44361, 0.52068},"
                 "{-0.07895, -0.22368, -0.05263, 0.19737},"
                 "{-0.52256, -0.81391, -0.30075, 0.30639}"
                 "}") {
            const Matrix result({
                 {0.21805f, 0.45113f, 0.24060f, -0.04511f},
                 {-0.80827f, -1.45677f, -0.44361f, 0.52068f},
                 {-0.07895f, -0.22368f, -0.05263f, 0.19737f},
                 {-0.52256f, -0.81391f, -0.30075f, 0.30639f}
                 });

            REQUIRE(B == result);
        }
    }
}

SCENARIO("Calculating the inverse of another matrix") {
    GIVEN("A <- {{8, -5, 9, 2}, {7, 5, 6, 1}, {-6, 0, 9, 6}, {-3, 0, -9, -4}}") {
        const Matrix A({{8, -5, 9, 2}, {7, 5, 6, 1}, {-6, 0, 9, 6}, {-3, 0, -9, -4}});

        AND_THEN("A.inverse() = {"
                 "{-0.15385, -0.15385, -0.28205, -0.53846},"
                 "{-0.07692, 0.12308, 0.02564, 0.03077},"
                 "{0.35897, 0.35897, 0.43590, 0.92308},"
                 "{-0.69231, -0.69231, -0.76923, -1.92308}"
                 "}") {
            const Matrix result({
                 {-0.15385f, -0.15385f, -0.28205f, -0.53846f},
                 {-0.07692f, 0.12308f, 0.02564f, 0.03077f},
                 {0.35897f, 0.35897f, 0.43590f, 0.92308f},
                 {-0.69231f, -0.69231f, -0.76923f, -1.92308f}
                 });
            REQUIRE(A.inverse() == result);
        }
    }
}

SCENARIO("Calculating the inverse of a third matrix") {
    GIVEN("A <- {{9, 3, 0, 9}, {-5, -2, -6, -3}, {-4, 9, 6, 4}, {-7, 6, 6, 2}}") {
        const Matrix A({{9, 3, 0, 9}, {-5, -2, -6, -3}, {-4, 9, 6, 4}, {-7, 6, 6, 2}});

        AND_THEN("A.inverse() = {"
                 "{-0.04074, -0.07778, 0.14444, -0.22222},"
                 "{-0.07778, 0.03333, 0.36667, -0.33333},"
                 "{-0.02901, -0.14630, -0.10926, 0.12963},"
                 "{0.17778, 0.06667, -0.26667, 0.33333}"
                 "}") {
            const Matrix result({
                 {-0.04074f, -0.07778f, 0.14444f, -0.22222f},
                 {-0.07778f, 0.03333f, 0.36667f, -0.33333f},
                 {-0.02901f, -0.14630f, -0.10926f, 0.12963f},
                 {0.17778f, 0.06667f, -0.26667f, 0.33333f}
                 });
            REQUIRE(A.inverse() == result);
        }
    }
}

SCENARIO("Multiplying a product by its inverse") {
    GIVEN("A <- {{3, -9, 7, 3}, {3, -8, 2, -9}, {-4, 4, 4, 1}, {-6, 5, -1, 1}}"
          "B <- {{8, 2, 2, 2}, {3, -1, 7, 0}, {7, 0, 5, 4}, {6, -2, 0, 5}}"
          "C <- A * B") {
        const Matrix A({{3, -9, 7, 3}, {3, -8, 2, -9}, {-4, 4, 4, 1}, {-6, 5, -1, 1}});
        const Matrix B({{8, 2, 2, 2}, {3, -1, 7, 0}, {7, 0, 5, 4}, {6, -2, 0, 5}});
        const Matrix C = A * B;

        THEN("C * B.inverse() = A") {
            REQUIRE(C * B.inverse() == A);
        }
    }
}