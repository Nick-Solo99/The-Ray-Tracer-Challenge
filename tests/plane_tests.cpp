//
// Created by Nicholas Solomon on 2026-05-14.
//

#include <catch2/catch_test_macros.hpp>
#include <shapes/planes/Plane.h>
#include <rays/Ray.h>
#include <intersections/Intersection.h>

using namespace rtc::shapes::planes;
using namespace rtc::tuples;
using namespace rtc::rays;
using namespace rtc::intersections;

SCENARIO("The normal of a plane is constant everywhere") {
    GIVEN("p <- plane()") {
        const Plane p{};
        WHEN("n1 <- p.normal_at(point(0, 0, 0)), n2 <- p.normal_at(point(10, 0, -10)), n3 <- p.normal_at(point(-5, 0, 150))") {
            const Vector n1 = p.normal_at(point(0, 0, 0), {1, &p});
            const Vector n2 = p.normal_at(point(10, 0, -10), {1, &p});
            const Vector n3 = p.normal_at(point(-5, 0, 150), {1, &p});
            THEN("n1 = vector(0, 1, 0)") {
                REQUIRE(n1 == vector(0, 1, 0));
            }

            AND_THEN("n2 = vector(0, 1, 0)") {
                REQUIRE(n2 == vector(0, 1, 0));
            }

            AND_THEN("n3 = vector(0, 1, 0)") {
                REQUIRE(n3 == vector(0, 1, 0));
            }
        }
    }
}

SCENARIO("Intersect with a ray parallel to the plane") {
    GIVEN("p <- plane(), r <- ray(point(0, 10, 0), vector(0, 0, 1))") {
        const Plane p{};
        const Ray r(point(0, 10, 0), vector(0, 0, 1));
        WHEN("xs <- p.intersect(r)") {
            const std::vector<Intersection> xs = p.intersect(r);
            THEN("xs.size() = 0") {
                REQUIRE(xs.empty());
            }
        }

    }
}

SCENARIO("Intersect with a coplanar ray") {
    GIVEN("p <- plane(), r <- ray(point(0, 0, 0), vector(0, 0, 1))") {
        const Plane p{};
        const Ray r(point(0, 0, 0), vector(0, 0, 1));
        WHEN("xs <- p.intersect(r)") {
            const auto xs = p.intersect(r);
            THEN("xs.size() = 0") {
                REQUIRE(xs.empty());
            }
        }
    }
}

SCENARIO("A ray intersecting a plane from above") {
    GIVEN("p <- plane(), r <- ray(point(0, 1, 0), vector(0, -1, 0))") {
        const Plane p{};
        const Ray r(point(0, 1, 0), vector(0, -1, 0));
        WHEN("xs <- p.intersect(r)") {
            const std::vector<Intersection> xs = p.intersect(r);
            THEN("xs.size() = 1") {
                REQUIRE(xs.size() == 1);
            }
            AND_THEN("xs[0].t = 1") {
                REQUIRE(xs[0].t == 1);
            }
            AND_THEN("xs[0].object = p") {
                REQUIRE(xs[0].object == &p);
            }
        }
    }
}

SCENARIO("A ray intersecting a plane from below") {
    GIVEN("p <- plane(), r <- ray(point(0, -1, 0), vector(0, 1, 0))") {
        const Plane p{};
        const Ray r(point(0, -1, 0), vector(0, 1, 0));
        WHEN("xs <- p.intersect(r)") {
            const std::vector<Intersection> xs = p.intersect(r);
            THEN("xs.size() = 1") {
                REQUIRE(xs.size() == 1);
            }
            AND_THEN("xs[0].t = 1") {
                REQUIRE(xs[0].t == 1);
            }
            AND_THEN("xs[0].object = p") {
                REQUIRE(xs[0].object == &p);
            }
        }
    }
}