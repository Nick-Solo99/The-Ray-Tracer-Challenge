//
// Created by Nicholas Solomon on 2026-05-08.
//

#include <catch2/catch_test_macros.hpp>

#include "intersections/Intersection.h"
#include "shapes/spheres/Sphere.h"

using namespace rtc::shapes::spheres;
using namespace rtc::intersections;

SCENARIO("An intersection encapsulates t and object") {
    GIVEN("s <- sphere()") {
        Sphere s{};

        WHEN("i <- Intersection(3.5, s)") {
            const Intersection i{3.5f, &s};

            THEN("i.t = 3.5") {
                REQUIRE(i.t == 3.5f);
            }

            AND_THEN("i.object = s") {
                REQUIRE(i.object == &s);
            }
        }
    }
}

SCENARIO("Aggregating intersections") {
    GIVEN("s <- sphere(), i1 <- intersection(1, s), i2 <- intersection(2, s)") {
        const Sphere s{};
        const Intersection i1(1.0f, &s);
        const Intersection i2(2.0f, &s);

        WHEN("xs <- intersections(i1, i2)") {
            const std::vector<Intersection> xs = intersections({i1, i2});

            THEN("xs.size() = 2") {
                REQUIRE(xs.size() == 2);
            }
            AND_THEN("xs[0].t = 1") {
                REQUIRE(xs[0].t == 1.0f);
            }
            AND_THEN("xs[1].t = 2") {
                REQUIRE(xs[1].t == 2.0f);
            }
        }
    }
}

SCENARIO("The hit, when all intersections have positive t") {
    GIVEN("s <- sphere(), i1 <- intersection(1, s), i2 <- intersection(2, s), xs <- intersections(i2, i1)") {
        const Sphere s{};
        const Intersection i1(1.0f, &s);
        const Intersection i2(2.0f, &s);
        const std::vector<Intersection> xs = intersections({i2, i1});
        WHEN("i <- hit(xs)") {
            const std::optional<Intersection> i = hit(xs);
            THEN("i = i1") {
                REQUIRE(i == i1);
            }
        }
    }
}

SCENARIO("The hit, when some intersections have negative t") {
    GIVEN("s <- sphere(), i1 <- intersection(-1, s), i2 <- intersection(1, s), xs <- intersections(i2, i1)") {
        const Sphere s{};
        const Intersection i1(-1.0f, &s);
        const Intersection i2(1.0f, &s);
        const std::vector<Intersection> xs = intersections({i2, i1});
        WHEN("i <- hit(xs)") {
            const std::optional<Intersection> i = hit(xs);
            THEN("i = i2") {
                REQUIRE(i == i2);
            }
        }
    }
}

SCENARIO("The hit, when all intersections have negative t") {
    GIVEN("s <- sphere(), i1 <- intersection(-1, s), i2 <- intersection(1, s), xs <- intersections(i2, i1)") {
        const Sphere s{};
        const Intersection i1(-2.0f, &s);
        const Intersection i2(-1.0f, &s);
        const std::vector<Intersection> xs = intersections({i2, i1});
        WHEN("i <- hit(xs)") {
            const std::optional<Intersection> i = hit(xs);
            THEN("i is nothing") {
                REQUIRE(i == std::nullopt);
            }
        }
    }
}

SCENARIO("The hit is always the lowest nonnegative intersection") {
    GIVEN("s <- sphere(), "
          "i1 <- intersection(5, s), "
          "i2 <- intersection(7, s), "
          "i3 <- intersection(-3, s), "
          "i4 <- intersection(2, s), "
          "xs <- intersections(i1, i2, i3, i4)") {
        const Sphere s{};
        const Intersection i1(5, &s);
        const Intersection i2(7, &s);
        const Intersection i3(-3, &s);
        const Intersection i4(2, &s);
        const auto xs = intersections({i1, i2, i3, i4});

        WHEN("i <- hit(xs)") {
            const std::optional<Intersection> i = hit(xs);

            THEN("i = i4") {
                REQUIRE(i == i4);
            }
        }
    }
}