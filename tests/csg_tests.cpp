//
// Created by Nicholas Solomon on 2026-05-30.
//

#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators.hpp>

#include <shapes/csg/CSG.h>
#include <shapes/spheres/Sphere.h>
#include <shapes/cubes/Cube.h>
#include <shapes/Shape.h>
#include <intersections/Intersection.h>
#include <transformations/Transformations.h>

using namespace rtc::shapes::csg;
using namespace rtc::shapes::spheres;
using namespace rtc::shapes::cubes;
using namespace rtc::shapes;
using namespace rtc::intersections;
using namespace rtc::rays;
using namespace rtc::transformations;

SCENARIO("CSG is created with an operation and two shapes") {
    GIVEN("s1 <- sphere(), s2 <- cube()") {
        auto s1 = std::make_unique<Sphere>();
        Sphere* s1_ptr = s1.get();
        auto s2 = std::make_unique<Cube>();
        Cube* s2_ptr = s2.get();
        WHEN("c <- csg('union', s1, s2)") {
            const CSG c{Operation::UNION, std::move(s1), std::move(s2)};
            THEN("c.op = UNION") {
                REQUIRE(c.op == Operation::UNION);
            }
            AND_THEN("c.left = s1") {
                REQUIRE(c.left.get() == s1_ptr);
            }
            AND_THEN("c.right = s2") {
                REQUIRE(c.right.get() == s2_ptr);
            }
            AND_THEN("s1.parent = c") {
                REQUIRE(s1_ptr->parent == &c);
            }
            AND_THEN("s2.parent = c") {
                REQUIRE(s2_ptr->parent == &c);
            }
        }
    }
}

SCENARIO("Evaluating the rule for a CSG operation") {
    const auto&[op, lhit, inl, inr, res] = GENERATE(table<Operation, bool, bool, bool, bool>({
        {Operation::UNION, true, true, true, false},
        {Operation::UNION, true, true, false,true},
        {Operation::UNION, true, false, true, false},
        {Operation::UNION, true, false, false, true},
        {Operation::UNION, false, true, true, false},
        {Operation::UNION, false, true, false, false},
        {Operation::UNION, false, false, true, true},
        {Operation::UNION, false, false, false, true},
        {Operation::INTERSECT, true, true, true, true},
        {Operation::INTERSECT, true, true, false, false},
        {Operation::INTERSECT, true, false, true, true},
        {Operation::INTERSECT, true, false, false, false},
        {Operation::INTERSECT, false, true, true, true},
        {Operation::INTERSECT, false, true, false, true},
        {Operation::INTERSECT, false, false, true, false},
        {Operation::INTERSECT, false, false, false, false},
        {Operation::DIFFERENCE, true, true, true, false},
        {Operation::DIFFERENCE, true, true, false, true},
        {Operation::DIFFERENCE, true, false, true, false},
        {Operation::DIFFERENCE, true, false, false, true},
        {Operation::DIFFERENCE, false, true, true, true},
        {Operation::DIFFERENCE, false, true, false, true},
        {Operation::DIFFERENCE, false, false, true, false},
        {Operation::DIFFERENCE, false, false, false, false},
    }));
    WHEN("result <- intersection_allowed(<op>, <lhit>, <inl>, <inr>)") {
        const bool result = intersection_allowed(op, lhit, inl, inr);
        THEN("result = <res>") {
            REQUIRE(result == res);
        }
    }
}

SCENARIO("Filtering a list of intersections") {
    const auto& [op, x0, x1] = GENERATE(table<Operation, int, int>({
        {Operation::UNION, 0, 3},
        {Operation::INTERSECT, 1, 2},
        {Operation::DIFFERENCE, 0, 1},
    }));
    GIVEN("s1 <- sphere(), s1 <- cube(), c <- csg(<op>, s1, s2), xs <- intersections(1:s1. 2:s2, 3:s1. 4:s2)") {
        auto s1 = std::make_unique<Sphere>();
        Sphere* s1_ptr = s1.get();
        auto s2 = std::make_unique<Cube>();
        Cube* s2_ptr = s2.get();
        const CSG c{op, std::move(s1), std::move(s2)};
        const auto xs = intersections({{1, s1_ptr}, {2, s2_ptr}, {3, s1_ptr}, {4, s2_ptr}});
        WHEN("result <- c.filter_intersections(xs)") {
            const auto result = c.filter_intersections(xs);
            THEN("result.count = 2") {
                REQUIRE(result.size() == 2);
            }
            AND_THEN("result[0] = xs[<x0>]") {
                REQUIRE(result[0] == xs[x0]);
            }
            AND_THEN("result[1] = xs[<x1>]") {
                REQUIRE(result[1] == xs[x1]);
            }
        }
    }
}

SCENARIO("A ray misses a CSG object") {
    GIVEN("c <- csg(union, sphere(), cube()), r <- ray(point(0, 2, -5), vector(0, 0, 1))") {
        const CSG c{Operation::UNION, std::make_unique<Sphere>(), std::make_unique<Cube>()};
        const Ray r{point(0, 2, -5), vector(0, 0, 1)};
        WHEN("xs <- c.intersect(r)") {
            const auto xs = c.intersect(r);
            THEN("xs is empty") {
                REQUIRE(xs.empty());
            }
        }
    }
}

SCENARIO("A ray hits a CSG object") {
    GIVEN("s1 <- sphere(), s2 <- sphere(), s2.transform <- translation(0, 0, 0.5), c <- csg(union, s1, s2),"
          "r <- ray(point(0, 0, -5), vector(0, 0, 1))") {
        auto s1 = std::make_unique<Sphere>();
        Sphere* s1_ptr = s1.get();
        auto s2 = std::make_unique<Sphere>();
        s2->transform = translation(0, 0, 0.5);
        Sphere* s2_ptr = s2.get();
        const CSG c{Operation::UNION, std::move(s1), std::move(s2)};
        const Ray r{point(0, 0, -5), vector(0, 0, 1)};
        WHEN("xs <- c.intersect(r)") {
            const auto xs = c.intersect(r);
            THEN("xs.count = 2") {
                REQUIRE(xs.size() == 2);
            }
            AND_THEN("xs[0].t = 4") {
                REQUIRE(xs[0].t == 4);
            }
            AND_THEN("xs[0].object = s1") {
                REQUIRE(xs[0].object == s1_ptr);
            }
            AND_THEN("xs[1].t = 6.5") {
                REQUIRE(xs[1].t == 6.5);
            }
            AND_THEN("xs[1].object = s2") {
                REQUIRE(xs[1].object == s2_ptr);
            }
        }
    }
}