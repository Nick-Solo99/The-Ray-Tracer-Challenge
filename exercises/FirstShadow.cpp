//
// Created by Nicholas Solomon on 2026-05-11.
//

#include <canvas/Canvas.h>
#include <tuples/Tuple.h>
#include <shapes/spheres/Sphere.h>
#include <rays/Ray.h>
#include <intersections/Intersection.h>
#include <transformations/Transformations.h>
#include <iostream>
#include <fstream>
#include <numbers>

using namespace rtc::canvas;
using namespace rtc::tuples;
using namespace rtc::shapes::spheres;
using namespace rtc::rays;
using namespace rtc::intersections;
using namespace rtc::transformations;

int main() {
    constexpr int CANVAS_SIZE = 256;

    constexpr int CAM_DISTANCE = 5;

    Canvas canvas{CANVAS_SIZE, CANVAS_SIZE};

    const Point ray_origin = point(0, 0, -CAM_DISTANCE);
    constexpr float WALL_Z{10.0f};
    constexpr float WALL_SIZE{(WALL_Z / CAM_DISTANCE + 1.0f) * 2.0f + 1.0f};
    constexpr float PIXEL_SIZE = WALL_SIZE / CANVAS_SIZE;
    constexpr float HALF = WALL_SIZE / 2.0f;

    Sphere s{};

    //s.set_transform(scaling(1, 0.5, 1));
    //s.set_transform(scaling(0.5, 1, 1));
    //s.set_transform( rotation_z(std::numbers::pi_v<float> / 4) * scaling(0.5, 1, 1));
    //s.set_transform( shearing(1, 0, 0, 0, 0, 0) * scaling(0.5, 1, 1));



    for (size_t y{}; y < CANVAS_SIZE; ++y) {
        const float world_y = HALF - PIXEL_SIZE * y;
        for (size_t x{}; x < CANVAS_SIZE; ++x) {
            const float world_x = -HALF + PIXEL_SIZE * x;
            const Point position = point(world_x, world_y, WALL_Z);
            const Ray r(ray_origin, normalize(position - ray_origin));
            const auto& xs = s.intersect(r);
            if (hit(xs) != std::nullopt) {
                canvas.write_pixel(x, y, color(0.5f, 0.0, 0.5f));
            }
        }
    }

    std::ofstream file("../output/first_shadow.ppm");

    file << canvas.canvas_to_ppm();
    std::cout << "File created." << std::endl;


    return 0;
}