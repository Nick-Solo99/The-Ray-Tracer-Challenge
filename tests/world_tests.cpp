//
// Created by Nicholas Solomon on 2026-05-12.
//

#include <catch2/catch_test_macros.hpp>
#include <world/World.h>
#include <lights/point/PointLight.h>
#include <shapes/Shape.h>
#include <shapes/spheres/Sphere.h>
#include <transformations/Transformations.h>
#include <rays/Ray.h>
#include <intersections/Intersection.h>
#include <algorithm>

using namespace rtc::world;
using namespace rtc::lights::point;
using namespace rtc::shapes::spheres;
using namespace rtc::transformations;
using namespace rtc::rays;
using namespace rtc::shapes;
using namespace rtc::intersections;



SCENARIO("Creating a world") {
    GIVEN("w <- world()") {
        const World w{};

        THEN("w contains no objects") {
            REQUIRE(w.objects.empty());
        }

        AND_THEN("w contains no light source") {
            REQUIRE(w.lights.empty());
        }
    }
}

SCENARIO("The default world") {
    GIVEN("light <- PointLight(point(-10, 10, -10), color(1, 1, 1)), "
          "s1 <- sphere() with:"
          "material.color = (0.8, 1.0, 0.6),"
          "material.diffuse = 0.7"
          "material.specular = 0.2,"
          "s2 <- sphere() with: "
          "s2.transform = scaling(0.5, 0.5, 0.5)") {
        const PointLight light{point(-10, 10, -10), color(1, 1, 1)};
        Sphere s1{};
        s1.material.color = color(0.8, 1.0, 0.6);
        s1.material.diffuse = 0.7;
        s1.material.specular = 0.2;
        Sphere s2{};
        s2.transform = scaling(0.5, 0.5, 0.5);

        WHEN("w <- World::default_world()") {
            const World w = World::default_world();

            THEN("w.lights[0] = light") {
                REQUIRE(*w.lights[0] == light);
            }

            AND_THEN("w.objects.contains(s1)") {
                REQUIRE(*w.objects[0] == s1);
            }

            AND_THEN("w.objects.contains(s2)") {
                REQUIRE(*w.objects[1] == s2);
            }
        }
    }
}

SCENARIO("Intersect a world with a ray") {
    GIVEN("w <- default_world(), r <- ray(point(0, 0, -5), vector(0, 0, 1))") {
        const World w = World::default_world();
        const Ray r{point(0, 0, -5), vector(0, 0, 1)};

        WHEN("xs <- w.intersect(r)") {
            const auto& xs = w.intersect(r);

            THEN("xs.size() = 4") {
                REQUIRE(xs.size() == 4);
            }

            AND_THEN("xs[0].t = 4") {
                REQUIRE(xs[0].t == 4);
            }

            AND_THEN("xs[1].t = 4.5") {
                REQUIRE(xs[1].t == 4.5f);
            }

            AND_THEN("xs[2].t = 5.5") {
                REQUIRE(xs[2].t == 5.5f);
            }

            AND_THEN("xs[3].t = 6") {
                REQUIRE(xs[3].t == 6);
            }
        }
    }
}

SCENARIO("Shading an intersection") {
    GIVEN("w <- default_world(), r <- ray(point(0, 0, -5), vector(0, 0, 1)), shape <- w.objects[0], i <- intersection(4, shape)") {
        const World w = World::default_world();
        const Ray r{point(0, 0, -5), vector(0, 0, 1)};
        const Shape* shape = w.objects[0].get();
        const Intersection i{4.0f, shape};

        WHEN("comps <- i.pre_compute(r), c <- w.shade_hit(comps)") {
            const Components comps = i.pre_compute(r);
            const Color c = w.shade_hit(comps);

            THEN("c = color(0.38066, 0.47583, 0.2855)") {
                REQUIRE(c == color(0.38066, 0.47583, 0.2855));
            }
        }
    }
}

SCENARIO("Shading an intersection from the inside") {
    GIVEN("w <- default_world(), w.lights[0]->position = point(0, 0.25, 0), r <- ray(point(0, 0, 0), vector(0, 0, 1)),"
          "shape <- w.objects[1], i <- intersection(0.5, shape)") {
        World w = World::default_world();
        w.lights[0]->position = point(0, 0.25f, 0);
        const Ray r{point(0, 0, 0), vector(0, 0, 1)};
        const Shape* shape = w.objects[1].get();
        const Intersection i{0.5f, shape};
        WHEN("comps <- i.pre_compute(r), c <- w.shade_hit(comps)") {
            const Components comps = i.pre_compute(r);
            const Color c = w.shade_hit(comps);
            THEN("c = color(0.90498, 0.90498, 0.90498)") {
                REQUIRE(c == color(0.90498, 0.90498, 0.90498));
            }
        }

    }
}

SCENARIO("shade_hit() is given an intersection in shadow") {
    GIVEN("w <- world(), w.lights[0] <- PointLight(point(0, 0, -10), color(1, 1, 1)),"
          "s1 <- sphere(), s1 added to w,"
          "s2 <- sphere(), s2.transform <- translation(0, 0, 10), s2 added to w,"
          "r <- ray(point(0, 0, 5), vector(0, 0, 1)), i <- intersection(4, s2),") {
        World w{};
        w.lights.push_back(std::make_unique<PointLight>(point(0, 0, -10), color(1, 1, 1)));
        w.objects.push_back(std::make_unique<Sphere>());
        w.objects.push_back(std::make_unique<Sphere>());

        const auto s1 = w.objects[0].get();
        const auto s2 = w.objects[1].get();

        s2->transform = translation(0, 0, 10);

        const Ray r{point(0, 0, 5), vector(0, 0, 1)};
        const Intersection i(4, s2);
        WHEN("comps <- i.pre_compute(r), c <- shade_hit(comps)") {
            const Components comps = i.pre_compute(r);
            const Color c = w.shade_hit(comps);
            THEN("c = color(0.1, 0.1, 0.1)") {
                REQUIRE(c == color(0.1, 0.1, 0.1));
            }
        }
    }
}

SCENARIO("The color when a ray misses") {
    GIVEN("w <- default_world(), r <- ray(point(0, 0, -5), vector(0, 1, 0)") {
        const World w = World::default_world();
        const Ray r{point(0, 0, -5), vector(0, 1, 0)};
        WHEN("c <- w.color_at(r)") {
            const Color c = w.color_at(r);
            THEN("c = color(0, 0, 0)") {
                REQUIRE(c == color(0, 0, 0));
            }
        }
    }
}

SCENARIO("The color when a ray hits") {
    GIVEN("w <- default_world(), r <- ray(point(0, 0, -5), vector(0, 0, 1)") {
        const World w = World::default_world();
        const Ray r{point(0, 0, -5), vector(0, 0, 1)};
        WHEN("c <- w.color_at(r)") {
            const Color c = w.color_at(r);
            THEN("c = color(0.38066, 0.47583, 0.2855)") {
                REQUIRE(c == color(0.38066f, 0.47583f, 0.2855f));
            }
        }
    }
}

SCENARIO("The color with an intersection behind the ray") {
    GIVEN("w <- default_world(), "
          "outer <- w.objects[0], "
          "outer.material.ambient <- 1, "
          "inner <- w.objects[1], "
          "inner.material.ambient <- 1,"
          "r <- ray(point(0, 0, 0.75), vector(0, 0, -1))") {
        const World w = World::default_world();
        Shape* outer = w.objects[0].get();
        outer->material.ambient = 1;
        Shape* inner = w.objects[1].get();
        inner->material.ambient = 1;
        const Ray r{point(0, 0, 0.75f), vector(0, 0, -1)};

        WHEN("c <- w.color_at(r)") {
            const Color c = w.color_at(r);
            THEN("c = inner->material.color") {
                REQUIRE(c == inner->material.color);
            }
        }
    }
}

SCENARIO("There is no shadow when nothing is collinear with point and light") {
    GIVEN("w <- default_world(), p <- point(0, 10, 0)") {
        const World w = World::default_world();
        const Point p = point(0, 10, 0);
        THEN("w.is_shadowed(p) is false") {
            REQUIRE(w.is_shadowed(p) == false);
        }
    }
}

SCENARIO("The shadow when an object is between the point and the light") {
    GIVEN("w <- default_world(), p <- point(10, -10, 10)") {
        const World w = World::default_world();
        const Point p = point(10, -10, 10);
        THEN("w.is_shadowed(p) is true") {
            REQUIRE(w.is_shadowed(p) == true);
        }
    }
}

SCENARIO("There is no shadow when an object is behind the light") {
    GIVEN("w <- default_world(), p <- point(-20, 20, -20)") {
        const World w = World::default_world();
        const Point p = point(-20, 20, -20);
        THEN("w.is_shadowed(p) is false") {
            REQUIRE(w.is_shadowed(p) == false);
        }
    }
}

SCENARIO("There is no shadow when an object is behind the point") {
    GIVEN("w <- default_world(), p <- point(-2, 2, -2)") {
        const World w = World::default_world();
        const Point p = point(-2, 2, -2);
        THEN("w.is_shadowed(p) is false") {
            REQUIRE(w.is_shadowed(p) == false);
        }
    }
}