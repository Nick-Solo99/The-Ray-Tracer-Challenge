//
// Created by Nicholas Solomon on 2026-05-21.
//

#include <catch2/catch_test_macros.hpp>
#include <shapes/cubes/Cube.h>
#include <rays/Ray.h>
#include <intersections/Intersection.h>
#include <constants/Constants.h>

using namespace rtc::shapes::cubes;
using namespace rtc::rays;
using namespace rtc::intersections;
using namespace rtc::constants;

SCENARIO("A ray intersects a cube") {
    GIVEN("c <- cube(), r <- ray(point(5, 0.5, 0), vector(-1, 0, 0))") {
        const Cube c{};
        const Ray r{point(5, 0.5, 0), vector(-1, 0, 0)};
        WHEN("xs <- c.intersect(r)") {
            const auto xs = c.intersect(r);
            THEN("xs.count = 2") {
                REQUIRE(xs.size() == 2);
            }
            AND_THEN("xs[0].t = 4") {
                REQUIRE((xs[0].t - 4.f) < EPSILON);
            }
            AND_THEN("xs[1].t = 6") {
                REQUIRE((xs[1].t - 6.f) < EPSILON);
            }
        }
    }
    AND_GIVEN("c <- cube(), r <- ray(point(-5, 0.5, 0), vector(1, 0, 0))") {
        const Cube c{};
        const Ray r{point(-5, 0.5, 0), vector(1, 0, 0)};
        WHEN("xs <- c.intersect(r)") {
            const auto xs = c.intersect(r);
            THEN("xs.count = 2") {
                REQUIRE(xs.size() == 2);
            }
            AND_THEN("xs[0].t = 4") {
                REQUIRE((xs[0].t - 4.f) < EPSILON);
            }
            AND_THEN("xs[1].t = 6") {
                REQUIRE((xs[1].t - 6.f) < EPSILON);
            }
        }
    }
    AND_GIVEN("c <- cube(), r <- ray(point(0.5, 5, 0), vector(0, -1, 0))") {
        const Cube c{};
        const Ray r{point(0.5, 5, 0), vector(0, -1, 0)};
        WHEN("xs <- c.intersect(r)") {
            const auto xs = c.intersect(r);
            THEN("xs.count = 2") {
                REQUIRE(xs.size() == 2);
            }
            AND_THEN("xs[0].t = 4") {
                REQUIRE((xs[0].t - 4.f) < EPSILON);
            }
            AND_THEN("xs[1].t = 6") {
                REQUIRE((xs[1].t - 6.f) < EPSILON);
            }
        }
    }
    AND_GIVEN("c <- cube(), r <- ray(point(0.5, -5, 0), vector(0, 1, 0))") {
        const Cube c{};
        const Ray r{point(0.5, -5, 0), vector(0, 1, 0)};
        WHEN("xs <- c.intersect(r)") {
            const auto xs = c.intersect(r);
            THEN("xs.count = 2") {
                REQUIRE(xs.size() == 2);
            }
            AND_THEN("xs[0].t = 4") {
                REQUIRE((xs[0].t - 4.f) < EPSILON);
            }
            AND_THEN("xs[1].t = 6") {
                REQUIRE((xs[1].t - 6.f) < EPSILON);
            }
        }
    }
    AND_GIVEN("c <- cube(), r <- ray(point(0.5, 0, 5), vector(0, 0, -1))") {
        const Cube c{};
        const Ray r{point(0.5, 0, 5), vector(0, 0, -1)};
        WHEN("xs <- c.intersect(r)") {
            const auto xs = c.intersect(r);
            THEN("xs.count = 2") {
                REQUIRE(xs.size() == 2);
            }
            AND_THEN("xs[0].t = 4") {
                REQUIRE((xs[0].t - 4.f) < EPSILON);
            }
            AND_THEN("xs[1].t = 6") {
                REQUIRE((xs[1].t - 6.f) < EPSILON);
            }
        }
    }
    AND_GIVEN("c <- cube(), r <- ray(point(0.5, 0, -5), vector(0, 0, 1))") {
        const Cube c{};
        const Ray r{point(0.5, 0, -5), vector(0, 0, 1)};
        WHEN("xs <- c.intersect(r)") {
            const auto xs = c.intersect(r);
            THEN("xs.count = 2") {
                REQUIRE(xs.size() == 2);
            }
            AND_THEN("xs[0].t = 4") {
                REQUIRE((xs[0].t - 4.f) < EPSILON);
            }
            AND_THEN("xs[1].t = 6") {
                REQUIRE((xs[1].t - 6.f) < EPSILON);
            }
        }
    }
    AND_GIVEN("c <- cube(), r <- ray(point(0, 0.5, 0), vector(0, 0, 1))") {
        const Cube c{};
        const Ray r{point(0, 0.5, 0), vector(0, 0, 1)};
        WHEN("xs <- c.intersect(r)") {
            const auto xs = c.intersect(r);
            THEN("xs.count = 2") {
                REQUIRE(xs.size() == 2);
            }
            AND_THEN("xs[0].t = -1") {
                REQUIRE((xs[0].t + 1.f) < EPSILON);
            }
            AND_THEN("xs[1].t = 1") {
                REQUIRE((xs[1].t - 1.f) < EPSILON);
            }
        }
    }
}

SCENARIO("A ray misses a cube") {
    GIVEN("c <- cube(), r <- ray(point(-2, 0, 0), vector(0.2673, 0.5345, 0.8018))") {
        const Cube c{};
        const Ray r{point(-2, 0, 0), vector(0.2673f, 0.5345f, 0.8018f)};
        WHEN("xs <- c.intersect(r)") {
            const auto xs = c.intersect(r);
            THEN("xs.count = 0") {
                REQUIRE(xs.empty());
            }
        }
    }
    AND_GIVEN("c <- cube(), r <- ray(point(0, -2, 0), vector(0.8018, 0.5345, 0.8018))") {
        const Cube c{};
        const Ray r{point(0, -2, 0), vector(0.8010f, 0.5345f, 0.8018f)};
        WHEN("xs <- c.intersect(r)") {
            const auto xs = c.intersect(r);
            THEN("xs.count = 0") {
                REQUIRE(xs.empty());
            }
        }
    }
    AND_GIVEN("c <- cube(), r <- ray(point(0, 0, -2), vector(0.5345, 0.8018, 0.2673))") {
        const Cube c{};
        const Ray r{point(0.5, 5, 0), vector(0.5345f, 0.8018f, 0.2673f)};
        WHEN("xs <- c.intersect(r)") {
            const auto xs = c.intersect(r);
            THEN("xs.count = 0") {
                REQUIRE(xs.empty());
            }
        }
    }
    AND_GIVEN("c <- cube(), r <- ray(point(2, 0, 2), vector(0, 0, -1))") {
        const Cube c{};
        const Ray r{point(2, 0, 2), vector(0, 0, -1)};
        WHEN("xs <- c.intersect(r)") {
            const auto xs = c.intersect(r);
            THEN("xs.count = 0") {
                REQUIRE(xs.empty());
            }
        }
    }
    AND_GIVEN("c <- cube(), r <- ray(point(0, 2, 2), vector(0, -1, 0))") {
        const Cube c{};
        const Ray r{point(0, 2, 2), vector(0, -1, 0)};
        WHEN("xs <- c.intersect(r)") {
            const auto xs = c.intersect(r);
            THEN("xs.count = 0") {
                REQUIRE(xs.empty());
            }
        }
    }
    AND_GIVEN("c <- cube(), r <- ray(point(2, 2, 0), vector(-1, 0, 0))") {
        const Cube c{};
        const Ray r{point(2, 2, 0), vector(-1, 0, 0)};
        WHEN("xs <- c.intersect(r)") {
            const auto xs = c.intersect(r);
            THEN("xs.count = 0") {
                REQUIRE(xs.empty());
            }
        }
    }
}

SCENARIO("The normal on the surface of a cube") {
    GIVEN("c <- cube(), p <- point(1, 0.5, -0.8)") {
        const Cube c{};
        const Point p = point(1, 0.5f, -0.8f);
        WHEN("normal <- c.normal_at(p)") {
            const Vector normal = c.normal_at(p, {1, &c});
            THEN("normal = vector(1, 0, 0)") {
                REQUIRE(normal == vector(1, 0, 0));
            }
        }
    }
    AND_GIVEN("c <- cube(), p <- point(-1, -0.2, 0.9)") {
        const Cube c{};
        const Point p = point(-1, -0.2f, 0.9f);
        WHEN("normal <- c.normal_at(p)") {
            const Vector normal = c.normal_at(p, {1, &c});
            THEN("normal = vector(-1, 0, 0)") {
                REQUIRE(normal == vector(-1, 0, 0));
            }
        }
    }
    AND_GIVEN("c <- cube(), p <- point(-0.4, 1, -0.1)") {
        const Cube c{};
        const Point p = point(-0.4f, 1, -0.1f);
        WHEN("normal <- c.normal_at(p)") {
            const Vector normal = c.normal_at(p, {1, &c});
            THEN("normal = vector(0, 1, 0)") {
                REQUIRE(normal == vector(0, 1, 0));
            }
        }
    }
    AND_GIVEN("c <- cube(), p <- point(0.3, -1, -0.7)") {
        const Cube c{};
        const Point p = point(0.3f, -1, -0.7f);
        WHEN("normal <- c.normal_at(p)") {
            const Vector normal = c.normal_at(p, {1, &c});
            THEN("normal = vector(0, -1, 0)") {
                REQUIRE(normal == vector(0, -1, 0));
            }
        }
    }
    AND_GIVEN("c <- cube(), p <- point(-0.6, 0.3, 1)") {
        const Cube c{};
        const Point p = point(-0.6f, 0.3f, 1);
        WHEN("normal <- c.normal_at(p)") {
            const Vector normal = c.normal_at(p, {1, &c});
            THEN("normal = vector(0, 0, 1)") {
                REQUIRE(normal == vector(0, 0, 1));
            }
        }
    }
    AND_GIVEN("c <- cube(), p <- point(0.4, 0.4, -1)") {
        const Cube c{};
        const Point p = point(0.4f, 0.4f, -1);
        WHEN("normal <- c.normal_at(p)") {
            const Vector normal = c.normal_at(p, {1, &c});
            THEN("normal = vector(0, 0, -1)") {
                REQUIRE(normal == vector(0, 0, -1));
            }
        }
    }
    AND_GIVEN("c <- cube(), p <- point(1, 1, 1)") {
        const Cube c{};
        const Point p = point(1, 1, 1);
        WHEN("normal <- c.normal_at(p)") {
            const Vector normal = c.normal_at(p, {1, &c});
            THEN("normal = vector(1, 0, 0)") {
                REQUIRE(normal == vector(1, 0, 0));
            }
        }
    }
    AND_GIVEN("c <- cube(), p <- point(-1, -1, -1)") {
        const Cube c{};
        const Point p = point(-1, -1, -1);
        WHEN("normal <- c.normal_at(p)") {
            const Vector normal = c.normal_at(p, {1, &c});
            THEN("normal = vector(-1, 0, 0)") {
                REQUIRE(normal == vector(-1, 0, 0));
            }
        }
    }
}
