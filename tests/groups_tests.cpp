//
// Created by Nicholas Solomon on 2026-05-22.
//

#include <numbers>
#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators.hpp>
#include <shapes/groups/Group.h>
#include <shapes/spheres/Sphere.h>
#include <rays/Ray.h>
#include <intersections/Intersection.h>
#include <transformations/Transformations.h>

using namespace rtc::shapes::groups;
using namespace rtc::shapes::spheres;
using namespace rtc::rays;
using namespace rtc::intersections;
using namespace rtc::transformations;

SCENARIO("Creating a new group") {
    GIVEN("g <- group()") {
        const Group g{};
        THEN("g.transform = Matrix::identity()") {
            REQUIRE(g.transform == Matrix::identity());
        }
        AND_THEN("g is empty") {
            REQUIRE(g.empty());
        }
    }
}

SCENARIO("Adding a child to a group") {
    GIVEN("g <- group(), s <- sphere()") {
        Group g{};
        auto s = std::make_unique<Sphere>();
        Shape* s_ptr = s.get();
        WHEN("g.add_child(s)") {
            g.add_child(std::move(s));
            THEN("g is not empty") {
                REQUIRE(!g.empty());
            }
            AND_THEN("g includes s") {
                REQUIRE(g.contains(s_ptr));
            }
            AND_THEN("s.parent = g") {
                REQUIRE(s_ptr->parent == &g);
            }
        }
    }
}

SCENARIO("Intersecting a ray with an empty group") {
    GIVEN("g <- group(), r <- ray(point(0, 0, 0), vector(0, 0, 1))") {
        const Group g{};
        const Ray r{point(0, 0, 0), vector(0, 0, 1)};
        WHEN("xs <- g.intersect(r)") {
            const auto xs = g.intersect(r);
            THEN("xs is empty") {
                REQUIRE(xs.empty());
            }
        }
    }
}

SCENARIO("Intersecting a ray with a nonempty group") {
    GIVEN("g <- group(), s1 <- sphere(), s2 <- sphere(), s2.transform <- translation(0, 0, -3),"
          "s3 <- sphere(), s3.transform = translation(5, 0, 0), g.add_child(s1), g.add_child(s2), g.add_child(s3)") {
        Group g{};
        auto s1 = std::make_unique<Sphere>();
        Shape* s1_ptr = s1.get();
        auto s2 = std::make_unique<Sphere>();
        Shape* s2_ptr = s2.get();
        s2->transform = translation(0, 0, -3);
        auto s3 = std::make_unique<Sphere>();
        Shape* s3_ptr = s3.get();
        s3->transform = translation(5, 0, 0);
        g.add_child(std::move(s1));
        g.add_child(std::move(s2));
        g.add_child(std::move(s3));
        WHEN("r <- ray(point(0, 0, -5), vector(0, 0 1)), xs <- g.intersect(r)") {
            const Ray r{point(0, 0, -5), vector(0, 0, 1)};
            const auto xs = g.intersect(r);
            THEN("xs.count = 4") {
                REQUIRE(xs.size() == 4);
            }
            AND_THEN("xs[0].object = s2") {
                REQUIRE(xs[0].object == s2_ptr);
            }
            AND_THEN("xs[1].object = s2") {
                REQUIRE(xs[1].object == s2_ptr);
            }
            AND_THEN("xs[2].object = s1") {
                REQUIRE(xs[2].object == s1_ptr);
            }
            AND_THEN("xs[3].object = s1") {
                REQUIRE(xs[3].object == s1_ptr);
            }
        }
    }
}

SCENARIO("Intersecting a transformed group") {
    GIVEN("g <- group(), g.transform <- scaling(2, 2, 2), s <- sphere(), s.transform <- translation(5, 0, 0), g.add_child(s)") {
        Group g{};
        g.transform = scaling(2, 2, 2);
        Sphere s{};
        s.transform = translation(5, 0, 0);
        g.add_child(std::make_unique<Sphere>(s));
        WHEN("r <- ray(point(10, 0, -10), vector(0, 0, 1)), xs <- g.intersect(r)") {
            const Ray r{point(10, 0, -10), vector(0, 0, 1)};
            const auto xs = g.intersect(r);
            THEN("xs.count = 2") {
                REQUIRE(xs.size() == 2);
            }
        }
    }
}

SCENARIO("Converting a point from world to object space") {
    GIVEN("g1 <- group(), g1.transform <- rotation_y(pi / 2),"
          "g2 <- group(), g2.transform <- scaling(2, 2, 2),"
          "g1.add_child(g2), s <- sphere(), s.transform <- translation(5, 0, 0), g2.add_child(s)") {
        auto g1 = std::make_unique<Group>();
        g1->transform = rotation_y(std::numbers::pi_v<float> / 2.f);
        auto g2 = std::make_unique<Group>();
        Group* g2_ptr = g2.get();
        g2->transform = scaling(2, 2, 2);
        g1->add_child(std::move(g2));
        auto s = std::make_unique<Sphere>();
        Sphere* s_ptr = s.get();
        s->transform = translation(5, 0, 0);
        g2_ptr->add_child(std::move(s));
        WHEN("p <- s.world_to_obj(point(-2, 0, -10))") {
            const Point p = s_ptr->world_to_obj(point(-2, 0, -10));
            THEN("p = point(0, 0, -1)") {
                REQUIRE(p == point(0, 0, -1));
            }
        }
    }
}

SCENARIO("Converting a normal from object to world space") {
    GIVEN("g1 <- group(), g1.transform <- rotation_y(pi / 2),"
          "g2 <- group(), g2.transform <- scaling(1, 2, 3),"
          "g1.add_child(g2), s <- sphere(), s.transform <- translation(5, 0, 0), g2.add_child(s)") {
        auto g1 = std::make_unique<Group>();
        g1->transform = rotation_y(std::numbers::pi_v<float> / 2.f);
        auto g2 = std::make_unique<Group>();
        Group* g2_ptr = g2.get();
        g2->transform = scaling(1, 2, 3);
        g1->add_child(std::move(g2));
        auto s = std::make_unique<Sphere>();
        Sphere* s_ptr = s.get();
        s->transform = translation(5, 0, 0);
        g2_ptr->add_child(std::move(s));
        WHEN("n <- s.normal_to_world(vector(sqrt(3)/3, sqrt(3)/3, sqrt(3)/3))") {
            const Vector n = s_ptr->normal_to_world(vector(std::sqrtf(3.f)/3.f, std::sqrtf(3.f)/3.f, std::sqrtf(3.f)/3.f));
            THEN("n = vector(0.2857, 0.4286, -0.8571)") {
                REQUIRE(n == vector(0.2857f, 0.4286f, -0.8571f));
            }
        }
    }
}

SCENARIO("Finding the normal on a child object") {
    GIVEN("g1 <- group(), g1.transform <- rotation_y(pi / 2),"
          "g2 <- group(), g2.transform <- scaling(1, 2, 3),"
          "g1.add_child(g2), s <- sphere(), s.transform <- translation(5, 0, 0), g2.add_child(s)") {
        auto g1 = std::make_unique<Group>();
        g1->transform = rotation_y(std::numbers::pi_v<float> / 2.f);
        auto g2 = std::make_unique<Group>();
        Group* g2_ptr = g2.get();
        g2->transform = scaling(1, 2, 3);
        g1->add_child(std::move(g2));
        auto s = std::make_unique<Sphere>();
        Sphere* s_ptr = s.get();
        s->transform = translation(5, 0, 0);
        g2_ptr->add_child(std::move(s));
        WHEN("n <- s.normal_at(point(1.7321, 1.1547, -5.5774))") {
            const Vector n = s_ptr->normal_at(point(1.7321f, 1.1547f, -5.5774f), {1, g1.get()});
            THEN("n = vector(0.2857, 0.4286, -0.8571)") {
                REQUIRE(n == vector(0.2857f, 0.4286f, -0.8571f));
            }
        }
    }
}

SCENARIO("applying a material to a group applies it to all of its children") {
    GIVEN("g <- group(), s1 <- sphere(), s2 <- sphere(), g.add_child(s1), g.add_child(s2)") {
        auto g = std::make_unique<Group>();
        auto s1 = std::make_unique<Sphere>();
        Sphere* s1_ptr = s1.get();
        auto s2 = std::make_unique<Sphere>();
        Sphere* s2_ptr = s2.get();
        g->add_child(std::move(s1));
        g->add_child(std::move(s2));
        WHEN("m <- Material(), m.color <- color(1, 0, 0), g.set_material(m)") {
            Material m;
            m.color = color(1, 0, 0);
            g->set_material(m);
            THEN("s1.material.color = color(1, 0, 0)") {
                REQUIRE(s1_ptr->material.color == color(1, 0, 0));
            }
            AND_THEN("s2.material.color = color(1, 0, 0)") {
                REQUIRE(s2_ptr->material.color == color(1, 0, 0));
            }
        }
    }
}