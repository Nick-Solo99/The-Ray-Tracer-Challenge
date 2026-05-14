//
// Created by Nicholas Solomon on 2026-05-13.
//

#include <numbers>
#include <catch2/catch_test_macros.hpp>

#include <camera/Camera.h>
#include <matrices/Matrix.h>
#include <rays/Ray.h>
#include <tuples/Tuple.h>
#include <transformations/Transformations.h>
#include <world/World.h>
#include <canvas/Canvas.h>

using namespace rtc::transformations;
using namespace rtc::world;
using namespace rtc::camera;

SCENARIO("Constructing a camera") {
    GIVEN("hsize <- 160, vsize <- 120, fov <- pi/2") {
        const float hsize = 160;
        const float vsize = 120;
        const float fov = std::numbers::pi_v<float> / 2.0f;

        WHEN("c <- camera(hsize, vsize, fov)") {
            const rtc::camera::Camera c{hsize, vsize, fov};
            THEN("c.hsize = 160") {
                REQUIRE(c.hsize == 160);
            }
            AND_THEN("c.vsize = 120") {
                REQUIRE(c.vsize == 120);
            }
            AND_THEN("c.fov = pi/2") {
                REQUIRE(c.fov == std::numbers::pi_v<float> / 2.0f);
            }
            AND_THEN("c.transform = Matrix::identity()") {
                REQUIRE(c.transform == rtc::matrices::Matrix::identity());
            }
        }
    }
}

SCENARIO("The pixel size for a horizontal canvas") {
    GIVEN("c <- camera(200, 125, pi/2)") {
        const Camera c{200, 125, std::numbers::pi_v<float> / 2.0f};
        THEN("c.pixel_size = 0.01") {
            REQUIRE(c.pixel_size() == 0.01f);
        }
    }
}

SCENARIO("The pixel size for a vertical canvas") {
    GIVEN("c <- camera(125, 200, pi/2)") {
        const Camera c{125, 200, std::numbers::pi_v<float> / 2.0f};
        THEN("c.pixel_size = 0.01") {
            REQUIRE(c.pixel_size() == 0.01f);
        }
    }
}

SCENARIO("Constructing a ray through the center of the canvas") {
    GIVEN("c <- camera(201, 101, pi/2)") {
        const Camera c{201, 101, std::numbers::pi_v<float> / 2.f};
        WHEN("r <- c.ray_for_pixel(100, 50)") {
            const rtc::rays::Ray r = c.ray_for_pixel(100, 50);
            THEN("r.origin = point(0, 0, 0)") {
                REQUIRE(r.origin == point(0, 0, 0));
            }
            AND_THEN("r.direction = vector(0, 0, -1)") {
                REQUIRE(r.direction == vector(0, 0, -1));
            }
        }
    }
}

SCENARIO("Constructing a ray through a corner of the canvas") {
    GIVEN("c <- camera(201, 101, pi/2)") {
        const Camera c{201, 101, std::numbers::pi_v<float> / 2.f};
        WHEN("r <- c.ray_for_pixel(0, 0)") {
            const rtc::rays::Ray r = c.ray_for_pixel(0, 0);
            THEN("r.origin = point(0, 0, 0)") {
                REQUIRE(r.origin == point(0, 0, 0));
            }
            AND_THEN("r.direction = vector(0.66519, 0.33259, -0.66851)") {
                REQUIRE(r.direction == vector(0.66519f, 0.33259f, -0.66851f));
            }
        }
    }
}

SCENARIO("Constructing a ray when the camera is transformed") {
    GIVEN("c <- camera(201, 101, pi/2)") {
        Camera c{201, 101, std::numbers::pi_v<float> / 2.f};
        WHEN("c.transform <- rotation_y(pi / 4) * translation(0, -2, 5), r <- c.ray_for_pixel(100, 50)") {
            c.transform = rotation_y(std::numbers::pi_v<float> / 4.f) * translation(0, -2, 5);
            const rtc::rays::Ray r = c.ray_for_pixel(100, 50);
            THEN("r.origin = point(0, 2, -5)") {
                REQUIRE(r.origin == point(0, 2, -5));
            }
            AND_THEN("r.direction = vector(sqrt(2)/2, 0, -sqrt(2)/2)") {
                REQUIRE(r.direction == vector(std::sqrtf(2.f) / 2.f, 0, -std::sqrtf(2.f) / 2.f));
            }
        }
    }
}

SCENARIO("Rendering a world with a camera") {
    GIVEN("w <- default_world(), "
          "c <- camera(11, 11, pi/2), "
          "from <- point(0, 0, -5), "
          "to <- point(0, 0, 0), "
          "up <- vector(0, 1, 0),"
          "c.transform <- view_transform(from, to, up)") {
        const World w = World::default_world();
        Camera c{11, 11, std::numbers::pi_v<float> / 2.f};
        const Point from = point(0, 0, -5);
        const Point to = point(0, 0, 0);
        const Vector up = vector(0, 1, 0);
        c.transform = view_transform(from, to, up);

        WHEN("image <- c.render(w)") {
            const rtc::canvas::Canvas image = c.render(w);
            THEN("image.pixel_at(5, 5) = color(0.38066, 0.47583, 0.2855)") {
                REQUIRE(image.pixel_at(5, 5) == color(0.38066f, 0.47583f, 0.2855f));
            }
        }
    }
}