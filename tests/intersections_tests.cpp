//
// Created by Nicholas Solomon on 2026-05-08.
//

#include <catch2/catch_test_macros.hpp>
#include "intersections/Intersection.h"
#include "shapes/spheres/Sphere.h"
#include <rays/Ray.h>
#include <transformations/Transformations.h>
#include "constants/Constants.h"
#include <shapes/planes/Plane.h>
#include <shapes/triangles/Triangle.h>

using namespace rtc::shapes::spheres;
using namespace rtc::intersections;
using namespace rtc::rays;
using namespace rtc::transformations;
using namespace rtc::constants;
using namespace rtc::shapes::planes;
using namespace rtc::shapes::triangles;



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

SCENARIO("Precomputing the state of an intersection") {
    GIVEN("r <- ray(point(0, 0, -5), vector(0, 0, 1)), shape <- sphere(), i <- intersection(4, shape)") {
        const Ray r{point(0, 0, -5), vector(0, 0, 1)};
        const Sphere shape{};
        const Intersection i{4, &shape};

        WHEN("comps <- i.pre_compute(r)") {
            const Components comps = i.pre_compute(r);

            THEN("comps.t = i.t") {
                REQUIRE(comps.t == i.t);
            }

            AND_THEN("comps.object = i.object") {
                REQUIRE(comps.object == i.object);
            }

            AND_THEN("comps.point = point(0, 0, -1)") {
                REQUIRE(comps.point == point(0, 0, -1));
            }

            AND_THEN("comps.eve_v = vector(0, 0, -1)") {
                REQUIRE(comps.eye_v == vector(0, 0, -1));
            }

            AND_THEN("comps.normal_v = vector(0, 0, -1)") {
                REQUIRE(comps.normal_v == vector(0, 0, -1));
            }
        }

    }
}

SCENARIO("The hit, when an intersection occurs on the outside") {
    GIVEN("r <- ray(point(0, 0, -5), vector(0, 0, 1)), shape <- sphere(), i <- intersection(4, shape)") {
        const Ray r{point(0, 0, -5), vector(0, 0, 1)};
        const Sphere shape{};
        const Intersection i{4, &shape};

        WHEN("comps <- i.pre_compute(r)") {
            const Components comps = i.pre_compute(r);
            THEN("comps.inside = false") {
                REQUIRE(!comps.inside);
            }
        }
    }
}

SCENARIO("The hit, when an intersection occurs on the inside") {
    GIVEN("r <- ray(point(0, 0, -5), vector(0, 0, 1)), shape <- sphere(), i <- intersection(4, shape)") {
        const Ray r{point(0, 0, 0), vector(0, 0, 1)};
        const Sphere shape{};
        const Intersection i{1, &shape};

        WHEN("comps <- i.pre_compute(r)") {
            const Components comps = i.pre_compute(r);
            THEN("comps.inside = true") {
                REQUIRE(comps.inside);
            }

            THEN("comps.point = point(0, 0, 1)") {
                REQUIRE(comps.point == point(0, 0, 1));
            }

            AND_THEN("comps.eye_v = vector(0, 0, -1)") {
                REQUIRE(comps.eye_v == vector(0, 0, -1));
            }

            AND_THEN("comps.normal_v = vector(0, 0, -1)") {
                REQUIRE(comps.normal_v == vector(0, 0, -1));
            }
        }
    }
}

SCENARIO("The hit should offset the point") {
    GIVEN("r <- ray(point(0, 0, -5), vector(0, 0, 1)), shape <- sphere(),"
          "s.transform <- translation(0, 0, 1), i <- intersection(5, s)") {
        const Ray r{point(0, 0, -5), vector(0, 0, 1)};
        Sphere shape{};
        shape.transform = translation(0, 0, 1);
        const Intersection i(5, &shape);
        WHEN("comps <- i.pre_compute(r)") {
            const Components comps = i.pre_compute(r);
            THEN("comps.over_point.z < -EPSILON/2") {
                REQUIRE(comps.over_point.z < -EPSILON / 2.f);
            }
            AND_THEN("comps.point.z > comps.over_point.z") {
                REQUIRE(comps.point.z > comps.over_point.z);
            }
        }
    }
}

SCENARIO("Precomputing the reflection vector") {
    GIVEN("shape <- plane(), r <- ray(point(0, 1, -1), vector(0, -sqrt(2)/2, sqrt(2)/2, i <- intersection(sqrt(2)/2, shape)") {
        const Plane plane{};
        const Ray r{point(0, 1, -1), vector(0, -std::sqrtf(2.f)/2.f, std::sqrtf(2.f)/2.f)};
        const Intersection i{std::sqrtf(2.f)/2.f, &plane};
        WHEN("comps <- i.pre_compute(r)") {
            const Components comps = i.pre_compute(r);
            THEN("comps.reflect_v = vector(0, sqrt(2)/2, sqrt(2)/2)") {
                REQUIRE(comps.reflect_v == vector(0, std::sqrtf(2.f)/2.f, std::sqrtf(2.f)/2.f));
            }
        }
    }
}

SCENARIO("Finding n1 and n2 at various intersections") {
    GIVEN("A <- Sphere::glass(), A.transform <- scaling(2, 2, 2), A.material.refractive_index <- 1.5,"
          "B <- Sphere::glass(), B.transform <- translation(0, 0, -0.25), B.material.refractive_index <- 2.0,"
          "C <- Sphere::glass(), C.transform <- translation(0, 0, 0.25), C.material.refractive_index <- 2.5,"
          "r <- Ray(point(0, 0, -4), vector(0, 0, 1)), xs <- intersections({2, A}, {2.75, B}, {3.25, C}, {4.75, B}, {5.25, C}, {6, A}") {
        Sphere A = Sphere::glass();
        A.transform = scaling(2, 2, 2);
        A.material.refractive_index = 1.5f;
        Sphere B = Sphere::glass();
        B.transform = translation(0, 0, -0.25f);
        B.material.refractive_index = 2.0f;
        Sphere C = Sphere::glass();
        C.transform = translation(0, 0, 0.25f);
        C.material.refractive_index = 2.5f;
        const Ray r{point(0, 0, -4), vector(0, 0, 1)};
        const auto xs = intersections({{2.f, &A}, {2.75, &B}, {3.25, &C}, {4.75, &B}, {5.25, &C}, {6, &A}});
        WHEN("comps <- xs[0].pre_compute(r)") {
            const Components comps = xs[0].pre_compute(r, xs);
            THEN("comps.n1 = 1.0") {
                REQUIRE(comps.n1 == 1.0f);
            }
            AND_THEN("comps.n2 = 1.5") {
                REQUIRE(comps.n2 == 1.5f);
            }
        }
        AND_WHEN("comps <- xs[1].pre_compute(r)") {
            const Components comps = xs[1].pre_compute(r, xs);
            THEN("comps.n1 = 1.5") {
                REQUIRE(comps.n1 == 1.5f);
            }
            AND_THEN("comps.n2 = 2.0") {
                REQUIRE(comps.n2 == 2.0f);
            }
        }
        AND_WHEN("comps <- xs[2].pre_compute(r)") {
            const Components comps = xs[2].pre_compute(r, xs);
            THEN("comps.n1 = 2.0") {
                REQUIRE(comps.n1 == 2.0f);
            }
            AND_THEN("comps.n2 = 2.5") {
                REQUIRE(comps.n2 == 2.5f);
            }
        }
        AND_WHEN("comps <- xs[3].pre_compute(r)") {
            const Components comps = xs[3].pre_compute(r, xs);
            THEN("comps.n1 = 2.5") {
                REQUIRE(comps.n1 == 2.5f);
            }
            AND_THEN("comps.n2 = 2.5") {
                REQUIRE(comps.n2 == 2.5f);
            }
        }
        AND_WHEN("comps <- xs[4].pre_compute(r)") {
            const Components comps = xs[4].pre_compute(r, xs);
            THEN("comps.n1 = 2.5") {
                REQUIRE(comps.n1 == 2.5f);
            }
            AND_THEN("comps.n2 = 1.5") {
                REQUIRE(comps.n2 == 1.5f);
            }
        }
        AND_WHEN("comps <- xs[5].pre_compute(r)") {
            const Components comps = xs[5].pre_compute(r, xs);
            THEN("comps.n1 = 1.5") {
                REQUIRE(comps.n1 == 1.5f);
            }
            AND_THEN("comps.n2 = 1.0") {
                REQUIRE(comps.n2 == 1.0f);
            }
        }
    }
}

SCENARIO("The under point is offset below the surface") {
    GIVEN("r <- ray(point(0, 0, -5), vector(0, 0, 1)), shape <- Sphere::glass(), shape.transform <- translation(0, 0, 1),"
          "i <- intersection(5, shape), xs <- intersections(i)") {
        const Ray r{point(0, 0, -5), vector(0, 0, 1)};
        Sphere shape = Sphere::glass();
        shape.transform = translation(0, 0, 1);
        const Intersection i{5, &shape};
        const auto xs = intersections({i});
        WHEN("comps <- i.pre_compute(r, xs)") {
            const Components comps = i.pre_compute(r, xs);
            THEN("comps.under_point.z > EPSILON / 2") {
                REQUIRE(comps.under_point.z > EPSILON / 2.f);
            }
            AND_THEN("comps.point.z < comps.under_point.z") {
                REQUIRE(comps.point.z < comps.under_point.z);
            }
        }
    }
}

SCENARIO("The Schlick approximation under total internal reflection") {
    GIVEN("shape <- Sphere::glass(), r <- ray(point(0, 0, sqrt(2)/2), vector(0, 1, 0)), xs <- intersections({{-sqrt(2)/2, shape}, {sqrt(2)/2, shape}})") {
        const Sphere shape = Sphere::glass();
        const Ray r{point(0, 0, std::sqrtf(2.f)/2.f), vector(0, 1, 0)};
        const auto xs = intersections({{-std::sqrtf(2.f)/2.f, &shape}, {std::sqrtf(2.f)/2.f, &shape}});
        WHEN("comps <- xs[1].pre_compute(r, xs), reflectance <- schlick(comps)") {
            const Components comps = xs[1].pre_compute(r, xs);
            const auto reflectance = schlick(comps);
            THEN("reflectance = 1.0") {
                REQUIRE((reflectance - 1.0) < EPSILON);
            }
        }
    }
}

SCENARIO("The schlick approximation with a perpendicular viewing angle") {
    GIVEN("shape <- Sphere::glass(), r <- ray(point(0, 0, 0), vector(0, 1, 0)), xs <- intersections({{-1, shape}, {1, shape}})") {
        const Sphere shape = Sphere::glass();
        const Ray r{point(0, 0, 0), vector(0, 1, 0)};
        const auto xs = intersections({{-1, &shape}, {1, &shape}});
        WHEN("comps <- xs[1].pre_compute(r, xs), reflectance <- schlick(comps)") {
            const Components comps = xs[1].pre_compute(r, xs);
            const float reflectance = schlick(comps);
            THEN("reflectance = 0.04") {
                REQUIRE((reflectance - 0.04f) < EPSILON);
            }
        }
    }
}

SCENARIO("The schlick approximation with small angles and n2 > n1") {
    GIVEN("shape <- Sphere::glass(), r <- ray(point(0, 0.99, -2), vector(0, 0, 1)), xs <- intersections({{1.8589, shape}})") {
        const Sphere shape = Sphere::glass();
        const Ray r{point(0, 0.99, -2), vector(0, 0, 1)};
        const auto xs = intersections({{1.8589, &shape}});
        WHEN("comps <- xs[0].pre_compute(r, xs), reflectance <- schlick(comps)") {
            const Components comps = xs[0].pre_compute(r, xs);
            const float reflectance = schlick(comps);
            THEN("reflectance = 0.48873") {
                REQUIRE((reflectance - 0.48873f) < EPSILON);
            }
        }
    }
}

SCENARIO("An intersection can encapsulate 'u' and 'v'") {
    GIVEN("s <- triangle(point(0, 1, 0), point(-1, 0, 0), point(1, 0, 0))") {
        const Triangle s{point(0, 1, 0), point(-1, 0, 0), point(1, 0, 0)};
        WHEN("i <- intersection(3.5, s, 0.2, 0.4") {
            const Intersection i{3.5, &s, 0.2, 0.4};
            THEN("i.u = 0.2") {
                REQUIRE((i.u - 0.2f) < EPSILON);
            }
            AND_THEN("i.v = 0.4") {
                REQUIRE((i.v - 0.4f) < EPSILON);
            }
        }
    }
}