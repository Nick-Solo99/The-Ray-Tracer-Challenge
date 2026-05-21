//
// Created by Nicholas Solomon on 2026-05-21.
//

#include <world/World.h>
#include <shapes/planes/Plane.h>
#include <shapes/spheres/Sphere.h>
#include <camera/Camera.h>
#include <canvas/Canvas.h>
#include <patterns/checkers/CheckerPattern.h>
#include <lights/point/PointLight.h>
#include <transformations/Transformations.h>
#include <numbers>
#include <iostream>
#include <fstream>
#include <chrono>

using namespace rtc::world;
using namespace rtc::shapes::planes;
using namespace rtc::shapes::spheres;
using namespace rtc::camera;
using namespace rtc::canvas;
using namespace rtc::patterns::checkers;
using namespace rtc::lights::point;
using namespace rtc::transformations;

constexpr int SCREEN_WIDTH = 256;
constexpr int SCREEN_HEIGHT = 128;

int main() {
    const auto start = std::chrono::high_resolution_clock::now();

    World w{};
    w.lights.push_back(std::make_unique<PointLight>(point(-3, 3, -3), color(1, 1, 1)));

    CheckerPattern checker_pattern{color(0, 0, 0), color(1, 1, 1)};

    Plane floor{};
    floor.transform = translation(0, -1, 0);
    floor.material.reflective = 0.5;
    floor.material.pattern = std::make_unique<CheckerPattern>(checker_pattern);
    w.objects.push_back(std::make_unique<Plane>(floor));

    Plane glass{};
    glass.transform = Transform().rotate_x(std::numbers::pi_v<float> / 2.f).rotate_y(std::numbers::pi_v<float> / 2.f);
    glass.material.reflective = 0.9;
    glass.material.transparency = 0.9;
    glass.material.casts_shadows = false;
    w.objects.push_back(std::make_unique<Plane>(glass));

    Sphere ball_a{};
    ball_a.material.color = color(1, 0, 0);
    ball_a.transform = translation(-2, 0, 2);
    w.objects.push_back(std::make_unique<Sphere>(ball_a));

    Sphere ball_b{};
    ball_b.material.color = color(0, 0, 1);
    ball_b.transform = translation(2, 0, 2);
    w.objects.push_back(std::make_unique<Sphere>(ball_b));

    Camera cam{SCREEN_WIDTH, SCREEN_HEIGHT, std::numbers::pi_v<float> /2.f};
    const Point from = point(-1, 2, -3);
    const Point to = point(0, 1, 0);
    const Vector up = vector(0, 1, 0);
    cam.transform = view_transform(from, to, up);

    std::ofstream file("../output/first_refractions.ppm");

    file << cam.render(w).canvas_to_ppm();

    const auto end = std::chrono::high_resolution_clock::now();
    std::cout << "File Created. Time elapsed: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " ms" << std::endl;
    return 0;
}