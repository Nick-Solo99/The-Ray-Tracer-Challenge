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
            REQUIRE(half_quarter * p == point(0, sqrtf(2)/2, sqrtf(2)/2));
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
            REQUIRE(inv * p == point(0, sqrtf(2)/2, -sqrtf(2)/2));
        }
    }
}

SCENARIO("Rotating a point around the y axis") {
    GIVEN("p <- point(0, 0, 1), half_quarter <- rotation_y(PI / 4), full_quarter <- rotation_y(PI / 2)") {
        const Point p = point(0, 0, 1);
        const Matrix half_quarter = rotation_y(PI / 4);
        const Matrix full_quarter = rotation_y(PI / 2);

        THEN("half_quarter * p = point(sqrt(2)/2, 0, sqrt(2)/2") {
            REQUIRE(half_quarter * p == point(sqrtf(2)/2, 0, sqrtf(2)/2));
        }

        AND_THEN("full_quarter * p = point(1, 0, 0)") {
            REQUIRE(full_quarter * p == point(1, 0, 0));
        }
    }
}

SCENARIO("Rotating a point around the z axis") {
    GIVEN("p <- point(0, 1, 0), half_quarter <- rotation_z(PI/4), full_quarter <- rotation_z(PI / 2)") {
        const Point p = point(0, 1, 0);
        const Matrix half_quarter = rotation_z(PI / 4);
        const Matrix full_quarter = rotation_z(PI / 2);

        THEN("half_quarter * p = point(-sqrt(2)/2, sqrt(2)/2, 0)") {
            REQUIRE(half_quarter * p == point(-sqrt(2)/2, sqrt(2)/2, 0));
        }

        AND_THEN("full_quarter * p = point(-1, 0, 0") {
            REQUIRE(full_quarter * p == point(-1, 0, 0));
        }
    }
}

SCENARIO("A shearing transformation moves x in proportion to y") {
    GIVEN("transform <- shearing(1, 0, 0, 0, 0, 0), p <- point(2, 3, 4)") {
        const Matrix transform = shearing(1, 0, 0, 0, 0, 0);
        const Point p = point(2, 3, 4);

        THEN("transform * p = point(5, 3, 4") {
            REQUIRE(transform * p == point(5, 3, 4));
        }
    }
}

SCENARIO("A shearing transformation moves x in proportion to z") {
    GIVEN("transform <- shearing(0, 1, 0, 0, 0, 0), p <- point(2, 3, 4)") {
        const Matrix transform = shearing(0, 1, 0, 0, 0, 0);
        const Point p = point(2, 3, 4);

        THEN("transform * p = point(6, 3, 4") {
            REQUIRE(transform * p == point(6, 3, 4));
        }
    }
}

SCENARIO("A shearing transformation moves y in proportion to x") {
    GIVEN("transform <- shearing(0, 0, 1, 0, 0, 0), p <- point(2, 3, 4)") {
        const Matrix transform = shearing(0, 0, 1, 0, 0, 0);
        const Point p = point(2, 3, 4);

        THEN("transform * p = point(2, 5, 4") {
            REQUIRE(transform * p == point(2, 5, 4));
        }
    }
}

SCENARIO("A shearing transformation moves y in proportion to z") {
    GIVEN("transform <- shearing(0, 0, 0, 1, 0, 0), p <- point(2, 3, 4)") {
        const Matrix transform = shearing(0, 0, 0, 1, 0, 0);
        const Point p = point(2, 3, 4);

        THEN("transform * p = point(2, 7, 4") {
            REQUIRE(transform * p == point(2, 7, 4));
        }
    }
}

SCENARIO("A shearing transformation moves z in proportion to x") {
    GIVEN("transform <- shearing(0, 0, 0, 0, 1, 0), p <- point(2, 3, 4)") {
        const Matrix transform = shearing(0, 0, 0, 0, 1, 0);
        const Point p = point(2, 3, 4);

        THEN("transform * p = point(2, 3, 6") {
            REQUIRE(transform * p == point(2, 3, 6));
        }
    }
}

SCENARIO("A shearing transformation moves z in proportion to y") {
    GIVEN("transform <- shearing(0, 0, 0, 0, 0, 1), p <- point(2, 3, 4)") {
        const Matrix transform = shearing(0, 0, 0, 0, 0, 1);
        const Point p = point(2, 3, 4);

        THEN("transform * p = point(2, 3, 7") {
            REQUIRE(transform * p == point(2, 3, 7));
        }
    }
}

SCENARIO("Individual transformations are applied in sequence") {
    GIVEN("p <- point(1, 0, 1), A <- rotation_x(PI/2), B <- scaling(5, 5, 5), C <- translation(10, 5, 7)") {
        const Point p = point(1, 0, 1);
        const Matrix A = rotation_x(PI / 2);
        const Matrix B = scaling(5, 5, 5);
        const Matrix C = translation(10, 5, 7);

        WHEN("p2 <- A * p)") {
            const Point p2 = A * p;
            THEN("p2 = point(1, -1, 0)") {
                REQUIRE(p2 == point(1, -1, 0));
            }
            WHEN("p3 <- B * p2)") {
                const Point p3 = B * p2;
                THEN("p3 = point(5, -5, 0)") {
                    REQUIRE(p3 == point(5, -5, 0));
                }
                WHEN("p4 <- C * p3)") {
                    const Point p4 = C * p3;
                    THEN("p4 = point(15, 0, 7)") {
                        REQUIRE(p4 == point(15, 0, 7));
                    }
                }
            }
        }
    }
}

SCENARIO("Chained transformations must be applied in reverse order") {
    GIVEN("p <- point(1, 0, 1), A <- rotation_x(PI/2), B <- scaling(5, 5, 5), C <- translation(10, 5, 7)") {
        const Point p = point(1, 0, 1);
        const Matrix A = rotation_x(PI / 2);
        const Matrix B = scaling(5, 5, 5);
        const Matrix C = translation(10, 5, 7);
        WHEN("T <- C * B * A") {
            const Matrix T = C * B * A;
            THEN("T * p = point(15, 0, 7)") {
                REQUIRE(T * p == point(15, 0, 7));
            }
        }
    }
}

SCENARIO("Chained transformations using fluent API") {
    GIVEN("p <- point(1, 0, 1), T <- Transform().rotate_x(PI/2).scale(5, 5, 5).translate(10, 5, 7)") {
        const Point p = point(1, 0, 1);
        const Matrix T = Transform().rotate_x(PI/2).scale(5, 5, 5).translate(10, 5, 7);
        THEN("T * p = point(15, 0, 7)") {
            REQUIRE(T * p == point(15, 0, 7));
        }
    }
}

SCENARIO("The transformation matrix for the default orientation") {
    GIVEN("from <- point(0, 0, 0), to <- point(0, 0, -1), up <- vector(0, 1, 0)") {
        const Point from = point(0, 0, 0);
        const Point to = point(0, 0, -1);
        const Vector up = vector(0, 1, 0);
        WHEN("t <- view_transform(from, to, up)") {
            Matrix t = view_transform(from, to, up);
            THEN("t = identity_matrix") {
                REQUIRE(t == Matrix::identity());
            }
        }
    }
}

SCENARIO("A view transformation matrix looking in positive z direction") {
    GIVEN("from <- point(0, 0, 0), to <- point(0, 0, 1), up <- vector(0, 1, 0)") {
        const Point from = point(0, 0, 0);
        const Point to = point(0, 0, 1);
        const Vector up = vector(0, 1, 0);
        WHEN("t <- view_transform(from, to, up)") {
            Matrix t = view_transform(from, to, up);
            THEN("t = scaling(-1, 1, -1)") {
                REQUIRE(t == scaling(-1, 1, -1));
            }
        }
    }
}

SCENARIO("The view transformation moves the world") {
    GIVEN("from <- point(0, 0, 8), to <- point(0, 0, 0), up <- vector(0, 1, 0)") {
        const Point from = point(0, 0, 8);
        const Point to = point(0, 0, 0);
        const Vector up = vector(0, 1, 0);
        WHEN("t <- view_transform(from, to, up)") {
            Matrix t = view_transform(from, to, up);
            THEN("t = translation(0, 0, -8)") {
                REQUIRE(t == translation(0, 0, -8));
            }
        }
    }
}

SCENARIO("An arbitrary view transform") {
    GIVEN("from <- point(1, 3, 2), to <- point(4, -2, 8), up <- vector(1, 1, 0)") {
        const Point from = point(1, 3, 2);
        const Point to = point(4, -2, 8);
        const Vector up = vector(1, 1, 0);
        WHEN("t <- view_transform(from, to, up)") {
            Matrix t = view_transform(from, to, up);
            THEN("t = {"
                 "{-0.50709, 0.50709, 0.67612, -2.36643},"
                 "{0.76772, 0.60609, 0.12122, -2.82843},"
                 "{-0.35857, 0.59761, -0.71714, 0.00000},"
                 "{0.00000, 0.00000, 0.00000, 1.00000}}") {
                REQUIRE(t == Matrix{
                    {-0.50709, 0.50709, 0.67612, -2.36643},
                    {0.76772, 0.60609, 0.12122, -2.82843},
                    {-0.35857, 0.59761, -0.71714, 0.00000},
                    {0.00000, 0.00000, 0.00000, 1.00000}
                });
            }
        }
    }
}