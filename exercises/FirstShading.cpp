//
// Created by Nicholas Solomon on 2026-05-12.
//

#include <canvas/Canvas.h>
#include <tuples/Tuple.h>
#include <shapes/spheres/Sphere.h>
#include <rays/Ray.h>
#include <intersections/Intersection.h>
#include <transformations/Transformations.h>
#include <lights/point/PointLight.h>
#include <iostream>
#include <fstream>
#include <numbers>

using namespace rtc::canvas;
using namespace rtc::tuples;
using namespace rtc::shapes::spheres;
using namespace rtc::rays;
using namespace rtc::intersections;
using namespace rtc::transformations;
using namespace rtc::lights::point;

int main() {
    constexpr int CANVAS_SIZE = 256;
    constexpr float CAM_DISTANCE = 10.0f;
    const Point ray_origin = point(0, 0, -CAM_DISTANCE);
    constexpr float WALL_Z = 15.0f;
    constexpr float WALL_SIZE = (WALL_Z / CAM_DISTANCE + 1) * 2 + 1;
    constexpr float PIXEL_SIZE = WALL_SIZE / CANVAS_SIZE;
    constexpr float HALF = WALL_SIZE / 2;

    Canvas canvas(CANVAS_SIZE, CANVAS_SIZE);
    Sphere s{};
    s.material.color = color(1.0f, 0.2f, 1.0f);

    const Point light_pos = point(-10, 10, -10);
    const Color light_color = color(1, 1, 1);
    const PointLight light{light_pos, light_color};

    //s.set_transform(scaling(1, 0.5, 1));
    //s.set_transform(scaling(0.5, 1, 1));
    //s.set_transform(rotation_z(std::numbers::pi_v<float> / 4) * scaling(0.5, 1, 1));
    s.set_transform(shearing(1, 0, 0, 0, 0, 0) * scaling(0.5, 1, 1));

    for (size_t y{}; y < CANVAS_SIZE; ++y) {
        const float world_y = HALF - y * PIXEL_SIZE;
        for (size_t x{}; x < CANVAS_SIZE; ++x) {
            const float world_x = -HALF + x * PIXEL_SIZE;
            const Point position = point(world_x, world_y, WALL_Z);
            const Ray r{ray_origin, normalize(position - ray_origin)};
            const auto& xs = s.intersect(r);
            if (const auto& h = hit(xs)) {
                const Point hit_pos = r.position(h->t);
                const Vector hit_norm = h->object->normal_at(hit_pos);
                const Vector eye = -r.direction;
                const Color pixel_color = s.material.lighting(*h->object, light, position, eye, hit_norm);
                canvas.write_pixel(x, y, pixel_color);
            }
        }
    }

    std::ofstream file("../output/first_shading.ppm");

    file << canvas.canvas_to_ppm();

    std::cout << "File created." << std::endl;

    return 0;
}