//
// Created by Nicholas Solomon on 2026-05-20.
//

#include <world/World.h>
#include <shapes/planes/Plane.h>
#include <shapes/spheres/Sphere.h>
#include <patterns/checkers/CheckerPattern.h>
#include <camera/Camera.h>
#include <canvas/Canvas.h>
#include <lights/point/PointLight.h>
#include <iostream>
#include <fstream>
#include <chrono>
#include <numbers>
#include <transformations/Transformations.h>
#include <patterns/stripes/StripePattern.h>

using namespace rtc::world;
using namespace rtc::shapes::planes;
using namespace rtc::shapes::spheres;
using namespace rtc::patterns::checkers;
using namespace rtc::patterns::stripes;
using namespace rtc::camera;
using namespace rtc::canvas;
using namespace rtc::lights::point;
using namespace rtc::transformations;

constexpr int SCREEN_WIDTH = 256;
constexpr int SCREEN_HEIGHT = 128;

int main() {
    const auto start = std::chrono::high_resolution_clock::now();

    World w{};
    w.lights.push_back(std::make_unique<PointLight>(point(-4, 4, -4), color(1, 1, 1)));

    CheckerPattern pattern_a{color(0, 0, 0), color(1, 1, 1)};
    StripePattern pattern_b{color(0.25, 0.25, 0.25), color(0.75, 0.75, 0.75)};
    pattern_b.transform = rotation_y(std::numbers::pi_v<float> / 2.f);

    Plane floor{};
    floor.material.pattern = std::make_unique<CheckerPattern>(pattern_a);
    floor.material.reflective = 0.5;
    floor.transform = translation(0, -1, 0);
    w.objects.push_back(std::make_unique<Plane>(floor));

    Plane wall_a{};
    wall_a.material.pattern = std::make_unique<StripePattern>(pattern_b);
    wall_a.transform = Transform().rotate_x(std::numbers::pi_v<float> / 2.f).translate(0, 0, 5);
    w.objects.push_back(std::make_unique<Plane>(wall_a));
    Plane wall_b{};
    wall_b.material.pattern = std::make_unique<StripePattern>(pattern_b);
    wall_b.transform = Transform().rotate_x(std::numbers::pi_v<float> / 2.f).rotate_y(std::numbers::pi_v<float> / 2.f).translate(-5, 0, 0);
    w.objects.push_back(std::make_unique<Plane>(wall_b));

    Sphere sphere{};
    sphere.material.color = color(0.75f, 0.25f, 0.25f);
    w.objects.push_back(std::make_unique<Sphere>(sphere));

    Camera cam{SCREEN_WIDTH, SCREEN_HEIGHT, std::numbers::pi_v<float> / 3.f};
    const Point from = point(std::hypotf(5.f, 5.f), 1.f, -std::hypotf(5.f, 5.f));
    const Point to = point(0, 0, 0);
    const Vector up = vector(0, 1, 0);
    cam.transform = view_transform(from, to, up);

    std::ofstream file("../output/first_reflection.ppm");
    file << cam.render(w).canvas_to_ppm();

    const auto end = std::chrono::high_resolution_clock::now();
    std::cout << "File Created. Time elapsed: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " ms" << std::endl;

    return 0;
}