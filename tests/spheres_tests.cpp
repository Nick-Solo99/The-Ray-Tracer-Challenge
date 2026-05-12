//
// Created by Nicholas Solomon on 2026-05-08.
//

#include <catch2/catch_test_macros.hpp>
#include <rays/Ray.h>
#include <shapes/spheres/Sphere.h>
#include <intersections/Intersection.h>
#include <matrices/Matrix.h>
#include <transformations/Transformations.h>

using namespace rtc::rays;
using namespace rtc::shapes::spheres;
using namespace rtc::intersections;
using namespace rtc::matrices;
using namespace rtc::transformations;

SCENARIO("A ray intersects a sphere at two points") {
    GIVEN("r <- ray(point(0, 0, -5), vector(0, 0, 1)), s <- sphere()") {
        const Ray r(point(0, 0, -5), vector(0, 0, 1));
        const Sphere s{};

        WHEN("xs <- s.intersects(r)") {
            const std::vector<Intersection> xs = s.intersect(r);

            THEN("xs.size() = 2") {
                REQUIRE(xs.size() == 2);
            }

            AND_THEN("xs[0].t = 4.0") {
                REQUIRE(xs[0].t == 4.0f);
            }

            AND_THEN("xs[1] = 6.0") {
                REQUIRE(xs[1].t == 6.0f);
            }
        }
    }
}

SCENARIO("A ray intersects a sphere at a tangent") {
    GIVEN("r <- ray(point(0, 1, -5), vector(0, 0, 1)), s <- sphere()") {
        const Ray r(point(0, 1, -5), vector(0, 0, 1));
        const Sphere s{};

        WHEN("xs <- s.intersects(r)") {
            const std::vector<Intersection> xs = s.intersect(r);
            THEN("xs.size() = 2") {
                REQUIRE(xs.size() == 2);
            }

            AND_THEN("xs[0].t = 5.0") {
                REQUIRE(xs[0].t == 5.0f);
            }

            AND_THEN("xs[1].t = 5.0") {
                REQUIRE(xs[1].t == 5.0f);
            }
        }
    }
}

SCENARIO("A ray misses a sphere") {
    GIVEN("r <- ray(point(0, 2, -5), vector(0, 0, 1)), s <- sphere()") {
        const Ray r(point(0, 2, -5), vector(0, 0, 1));
        const Sphere s{};

        WHEN("xs <- s.intersects(r)") {
            const std::vector<Intersection> xs = s.intersect(r);
            THEN("xs.size() = 0") {
                REQUIRE(xs.empty());
            }
        }
    }
}

SCENARIO("A ray originates inside a sphere") {
    GIVEN("r <- ray(point(0, 0, 0), vector(0, 0, 1)), s <- sphere()") {
        const Ray r(point(0, 0, 0), vector(0, 0, 1));
        const Sphere s{};

        WHEN("xs <- s.intersects(r)") {
            const std::vector<Intersection> xs = s.intersect(r);

            THEN("xs.size() = 2") {
                REQUIRE(xs.size() == 2);
            }

            AND_THEN("xs[0].t = -1.0") {
                REQUIRE(xs[0].t == -1.0f);
            }

            AND_THEN("xs[1].t = 1.0") {
                REQUIRE(xs[1].t == 1.0f);
            }
        }
    }
}

SCENARIO("A sphere behind a ray") {
    GIVEN("r <- ray(point(0, 0, 5), vector(0, 0, 1)), s <- sphere()") {
        const Ray r(point(0, 0, 5), vector(0, 0, 1));
        const Sphere s{};

        WHEN("xs <- s.intersects(r)") {
            const std::vector<Intersection> xs = s.intersect(r);
            THEN("xs.size() = 2") {
                REQUIRE(xs.size() == 2);
            }

            AND_THEN("xs[0].t = -6.0") {
                REQUIRE(xs[0].t == -6.0f);
            }

            AND_THEN("xs[1].t = -4.0") {
                REQUIRE(xs[1].t == -4.0f);
            }
        }
    }
}

SCENARIO("Intersect sets the object on the intersection") {
    GIVEN("r <- ray(point(0, 0, -5), vector(0, 0, 1)), s <- sphere()") {
        const Ray r(point(0, 0, -5), vector(0, 0, 1));
        const Sphere s{};

        WHEN("xs <- s.intersect(r)") {
            const std::vector<Intersection> xs = s.intersect(r);

            THEN("xs.size() = 2") {
                REQUIRE(xs.size() == 2);
            }
            AND_THEN("xs[0].object = s") {
                REQUIRE(xs[0].object == &s);
            }
            AND_THEN("xs[1].object = s") {
                REQUIRE(xs[1].object == &s);
            }
        }
    }
}

SCENARIO("A sphere's default transformation") {
    GIVEN("s <- sphere()") {
        const Sphere s{};

        THEN("s.transform = Matrix::identity()") {
            REQUIRE(s.transform == Matrix::identity());
        }
    }
}

SCENARIO("Changing a sphere's transformation") {
    GIVEN("s <- sphere(), t <- translation(2, 3, 4)") {
        Sphere s{};
        const Matrix t = translation(2, 3, 4);

        WHEN("s.set_transform(t)") {
            s.set_transform(t);

            THEN("s.transform = t") {
                REQUIRE(s.transform == t);
            }
        }
    }
}

SCENARIO("Intersecting a scaled sphere with a ray") {
    GIVEN("r <- ray(point(0, 0, -5), vector(0, 0, 1)), s <- sphere()") {
        const Ray r(point(0, 0, -5), vector(0, 0, 1));
        Sphere s{};

        WHEN("s.set_transform(scaling(2, 2, 2)), xs <- intersect(s, r)") {
            s.set_transform(scaling(2, 2, 2));
            const std::vector<Intersection> xs = s.intersect(r);

            THEN("xs.size() = 2") {
                REQUIRE(xs.size() == 2);
            }

            AND_THEN("xs[0].t = 3") {
                REQUIRE(xs[0].t == 3);
            }

            AND_THEN("xs[1].t = 7") {
                REQUIRE(xs[1].t == 7);
            }
        }
    }
}

SCENARIO("Intersecting a translated sphere with a ray") {
    GIVEN("r <- ray(point(0, 0, -5), vector(0, 0, 1)), s <- sphere()") {
        const Ray r(point(0, 0, -5), vector(0, 0, 1));
        Sphere s{};

        WHEN("s.set_transform(translation(5, 0 ,0)), xs <- s.intersect(r)") {
            s.set_transform(translation(5, 0 ,0));
            const std::vector<Intersection> xs = s.intersect(r);

            THEN("xs.size() = 0") {
                REQUIRE(xs.size() == 0);
            }
        }
    }
}

SCENARIO("The normal on a sphere at a point on the x axis") {
    GIVEN("s <- sphere()") {
        const Sphere s{};

        WHEN("n <- s.normal_at(point(1, 0, 0))") {
            const Vector n = s.normal_at(point(1, 0, 0));

            THEN("n = vector(1, 0, 0)") {
                REQUIRE(n == vector(1, 0, 0));
            }
        }
    }
}

SCENARIO("The normal on a sphere at a point on the y axis") {
    GIVEN("s <- sphere()") {
        const Sphere s{};

        WHEN("n <- s.normal_at(point(0, 1, 0))") {
            const Vector n = s.normal_at(point(0, 1, 0));
            THEN("n = vector(0, 1, 0)") {
                REQUIRE(n == vector(0, 1, 0));
            }
        }
    }
}

SCENARIO("The normal on a sphere at a point on the z axis") {
    GIVEN("s <- sphere()") {
        const Sphere s{};
        WHEN("n <- s.normal_at(point(0, 0, 1))") {
            const Vector n = s.normal_at(point(0, 0, 1));
            THEN("n = vector(0, 0, 1)") {
                REQUIRE(n == vector(0, 0, 1));
            }
        }
    }
}

SCENARIO("The normal on a sphere at a nonaxial point") {
    GIVEN("s <- sphere()") {
        const Sphere s{};
        WHEN("n <- s.normal_at(point(sqrt(3)/3, sqrt(3)/3, sqrt(3)/3))") {
            const Vector n = s.normal_at(point(std::sqrtf(3.0f) / 3.0f, std::sqrtf(3.0f) / 3.0f, std::sqrtf(3.0f) / 3.0f));

            THEN("n = vector(sqrt(3)/3, sqrt(3)/3, sqrt(3)/3)") {
                REQUIRE(n == vector(std::sqrtf(3.0f) / 3.0f, std::sqrtf(3.0f) / 3.0f, std::sqrtf(3.0f) / 3.0f));
            }
        }
    }
}

SCENARIO("The normal is a normalized vector") {
    GIVEN("s <- sphere()") {
        const Sphere s{};
        WHEN("n <- s.normal_at(point(sqrt(3)/3, sqrt(3)/3, sqrt(3)/3))") {
            const Vector n = s.normal_at(point(std::sqrtf(3.0f) / 3.0f, std::sqrtf(3.0f) / 3.0f, std::sqrtf(3.0f) / 3.0f));

            THEN("n = normalize(n)") {
                REQUIRE(n == normalize(n));
            }
        }
    }
}