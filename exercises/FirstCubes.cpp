//
// Created by Nicholas Solomon on 2026-05-21.
//

#include <world/World.h>
#include <camera/Camera.h>
#include <canvas/Canvas.h>
#include <lights/point/PointLight.h>
#include <shapes/cubes/Cube.h>
#include <transformations/Transformations.h>
#include <numbers>
#include <iostream>
#include <fstream>
#include <chrono>
#include <patterns/checkers/CheckerPattern.h>
#include <patterns/stripes/StripePattern.h>

using namespace rtc::world;
using namespace rtc::camera;
using namespace rtc::canvas;
using namespace rtc::lights::point;
using namespace rtc::shapes::cubes;
using namespace rtc::transformations;
using namespace rtc::patterns::checkers;
using namespace rtc::patterns::stripes;

constexpr int SCREEN_WIDTH = 256;
constexpr int SCREEN_HEIGHT = 128;

int main() {
    const auto start = std::chrono::high_resolution_clock::now();


    World w{};
    w.lights.push_back(std::make_unique<PointLight>(point(-9, 9, -9), color(1, 1, 1)));

    CheckerPattern check_pat{color(0, 0, 0), color(1, 1, 1)};
    check_pat.transform = scaling(0.1, 0.1, 0.1);

    Cube cube{};
    cube.transform = Transform().scale(11, 10, 11).translate(0, 10, 0);
    cube.material.pattern = std::make_unique<CheckerPattern>(check_pat);
    cube.material.reflective = 0.1;
    cube.material.ambient = 0.3;
    cube.material.diffuse = 0.3;
    w.objects.push_back(std::make_unique<Cube>(cube));

    StripePattern stripe_pat{color(0.75, 0.50, 0.25), color(0.5, 0.3, 0.15)};
    stripe_pat.transform = scaling(0.1, 0.1, 0.1);

    Cube walls_a{};
    walls_a.transform = Transform().scale(11, 11, 10).translate(0, 10, 0);
    walls_a.material.pattern = std::make_unique<StripePattern>(stripe_pat);
    walls_a.material.reflective = 0.1;
    walls_a.material.ambient = 0.3;
    walls_a.material.diffuse = 0.3;
    w.objects.push_back(std::make_unique<Cube>(walls_a));
    Cube walls_b{};
    walls_b.transform = Transform().scale(11, 11, 10).rotate_y(std::numbers::pi_v<float> / 2.f).translate(0, 10, 0);
    walls_b.material.pattern = std::make_unique<StripePattern>(stripe_pat);
    walls_b.material.reflective = 0.1;
    walls_b.material.ambient = 0.3;
    walls_b.material.diffuse = 0.3;
    w.objects.push_back(std::make_unique<Cube>(walls_b));

    Cube table{};
    table.transform = Transform().scale(4, 0.1, 2).translate(0, 3, 0);
    stripe_pat.transform = scaling(0.05, 0.05, 0.05);
    table.material.pattern = std::make_unique<StripePattern>(stripe_pat);
    table.material.reflective = 0.1;
    table.material.ambient = 0.3;
    table.material.diffuse = 0.3;
    w.objects.push_back(std::make_unique<Cube>(table));

    Cube leg_a{};
    leg_a.transform = Transform().scale(0.1, 3, 0.1).translate(3.8, 0, -1.8);
    leg_a.material.color = color(0.75, 0.50, 0.25);
    w.objects.push_back(std::make_unique<Cube>(leg_a));
    Cube leg_b{};
    leg_b.transform = Transform().scale(0.1, 3, 0.1).translate(3.8, 0, 1.8);
    leg_b.material.color = color(0.75, 0.50, 0.25);
    w.objects.push_back(std::make_unique<Cube>(leg_b));
    Cube leg_c{};
    leg_c.transform = Transform().scale(0.1, 3, 0.1).translate(-3.8, 0, -1.8);
    leg_c.material.color = color(0.75, 0.50, 0.25);
    w.objects.push_back(std::make_unique<Cube>(leg_c));
    Cube leg_d{};
    leg_d.transform = Transform().scale(0.1, 3, 0.1).translate(-3.8, 0, 1.8);
    leg_d.material.color = color(0.75, 0.50, 0.25);
    w.objects.push_back(std::make_unique<Cube>(leg_d));

    Camera cam{SCREEN_WIDTH, SCREEN_HEIGHT, std::numbers::pi_v<float> / 2.f};
    const Point from = point(5, 5, -5);
    const Point to = point(0, 2.5, 0);
    const Vector up = vector(0, 1, 0);
    cam.transform = view_transform(from, to, up);

    std::ofstream file("../output/first_cubes.ppm");

    file << cam.render(w).canvas_to_ppm();


    const auto end = std::chrono::high_resolution_clock::now();
    std::cout << "File Created. Time Elapsed: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " ms" << std::endl;
    return 0;
}