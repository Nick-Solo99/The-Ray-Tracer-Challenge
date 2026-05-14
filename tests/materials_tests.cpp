//
// Created by Nicholas Solomon on 2026-05-11.
//

#include <catch2/catch_test_macros.hpp>
#include <tuples/Tuple.h>
#include <materials/Material.h>
#include <lights/point/PointLight.h>

using namespace rtc::tuples;
using namespace rtc::materials;
using namespace rtc::lights::point;

SCENARIO("The default material") {
    GIVEN("m <- material()") {
        const Material m;

        THEN("m.color = color(1, 1, 1)") {
            REQUIRE(m.color == color(1, 1, 1));
        }

        AND_THEN("m.ambient = 0.1") {
            REQUIRE(m.ambient == 0.1f);
        }

        AND_THEN("m.diffuse = 0.9") {
            REQUIRE(m.diffuse == 0.9f);
        }

        AND_THEN("m.specular = 0.9") {
            REQUIRE(m.specular == 0.9f);
        }

        AND_THEN("m.shininess = 200.0") {
            REQUIRE(m.shininess == 200.0f);
        }
    }
}

SCENARIO("Lighting with the eye between the light and the surface") {
    GIVEN("m <- material(), pos <- point(0, 0, 0), "
          "eye_v <- vector(0, 0, -1), normal_v <- vector(0, 0, -1), "
          "light <- PointLight(point(0, 0, -10), color(1, 1, 1))") {
        Material m;
        const Point pos = point(0, 0, 0);
        const Vector eye_v = vector(0, 0, -1);
        const Vector normal_v = vector(0, 0, -1);
        const PointLight light{point(0, 0, -10), color(1, 1, 1)};

        WHEN("result <- m.lighting(light, pos, eye_v, normal_v)") {
            Color result = m.lighting(light, pos, eye_v, normal_v);

            THEN("result = color(1.9, 1.9, 1.9)") {
                REQUIRE(result == color(1.9f, 1.9f, 1.9f));
            }
        }
    }
}

SCENARIO("Lighting with the eye between the light and the surface, eye offset 45 deg") {
    GIVEN("m <- material(), pos <- point(0, 0, 0), "
          "eye_v <- vector(0, sqrt(2)/2, -sqrt(2)/2), normal_v <- vector(0, 0, -1), "
          "light <- PointLight(point(0, 0, -10), color(1, 1, 1))") {
        Material m;
        const Point pos = point(0, 0, 0);
        const Vector eye_v = vector(0, std::sqrtf(2.0f)/2, -std::sqrtf(2.0f)/2.0f);
        const Vector normal_v = vector(0, 0, -1);
        const PointLight light{point(0, 0, -10), color(1, 1, 1)};

        WHEN("result <- m.lighting(light, pos, eye_v, normal_v)") {
            Color result = m.lighting(light, pos, eye_v, normal_v);

            THEN("result = color(1.0, 1.0, 1.0)") {
                REQUIRE(result == color(1.0f, 1.0f, 1.0f));
            }
        }
    }
}

SCENARIO("Lighting with the eye opposite the surface, light offset 45 deg") {
    GIVEN("m <- material(), pos <- point(0, 0, 0), "
          "eye_v <- vector(0, 0, -1), normal_v <- vector(0, 0, -1), "
          "light <- PointLight(point(0, 10, -10), color(1, 1, 1))") {
        Material m;
        const Point pos = point(0, 0, 0);
        const Vector eye_v = vector(0, 0, -1);
        const Vector normal_v = vector(0, 0, -1);
        const PointLight light{point(0, 10, -10), color(1, 1, 1)};

        WHEN("result <- m.lighting(light, pos, eye_v, normal_v)") {
            Color result = m.lighting(light, pos, eye_v, normal_v);

            THEN("result = color(0.7364, 0.7364, 0.7364)") {
                REQUIRE(result == color(0.7364f, 0.7364f, 0.7364f));
            }
        }
    }
}

SCENARIO("Lighting with the eye in the path of the reflection vector") {
    GIVEN("m <- material(), pos <- point(0, 0, 0), "
          "eye_v <- vector(0, -sqrt(2)/2, -sqrt(2)/2), normal_v <- vector(0, 0, -1), "
          "light <- PointLight(point(0, 10, -10), color(1, 1, 1))") {
        Material m;
        const Point pos = point(0, 0, 0);
        const Vector eye_v = vector(0, -std::sqrtf(2.0f)/2.0f, -std::sqrtf(2.0f)/2.0f);
        const Vector normal_v = vector(0, 0, -1);
        const PointLight light{point(0, 10, -10), color(1, 1, 1)};

        WHEN("result <- m.lighting(light, pos, eye_v, normal_v)") {
            Color result = m.lighting(light, pos, eye_v, normal_v);

            THEN("result = color(1.6364, 1.6364, 1.6364)") {
                REQUIRE(result == color(1.6364f, 1.6364f, 1.6364f));
            }
        }
    }
}

SCENARIO("Lighting with the light behind the surface") {
    GIVEN("m <- material(), pos <- point(0, 0, 0), "
          "eye_v <- vector(0, 0, -1, normal_v <- vector(0, 0, -1), "
          "light <- PointLight(point(0, 0, 10), color(1, 1, 1))") {
        Material m;
        const Point pos = point(0, 0, 0);
        const Vector eye_v = vector(0, 0, -1);
        const Vector normal_v = vector(0, 0, -1);
        const PointLight light{point(0, 0, 10), color(1, 1, 1)};

        WHEN("result <- m.lighting(light, pos, eye_v, normal_v)") {
            Color result = m.lighting(light, pos, eye_v, normal_v);

            THEN("result = color(0.1, 0.1, 0.1)") {
                REQUIRE(result == color(0.1f, 0.1f, 0.1f));
            }
        }
    }
}

SCENARIO("Lighting with the surface in shadow") {
    GIVEN("m <- material(), pos <- point(0, 0, 0), "
          "eye_v <- vector(0, 0, -1), "
          "normal_v <- vector(0, 0, -1), "
          "light <- PointLight(point(0, 0, -10), color(1, 1, 1)),"
          "in_shadow <- true") {
        Material m;
        const Point pos = point(0, 0, 0);
        const Vector eye_v = vector(0, 0, -1);
        const Vector normal_v = vector(0, 0, -1);
        const PointLight light{point(0, 0, -10), color(1, 1, 1)};

        WHEN("result <- m.lighting(light, pos, eye_v, normal_v, in_shadow)") {
            const Color result = m.lighting(light, pos, eye_v, normal_v, true);
            THEN("result = color(0.1, 0.1, 0.1)") {
                REQUIRE(result == color(0.1f, 0.1f, 0.1f));
            }
        }
    }
}