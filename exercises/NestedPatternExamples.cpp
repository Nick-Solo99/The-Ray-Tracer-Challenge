//
// Created by Nicholas Solomon on 2026-05-18.
//

#include <world/World.h>
#include <lights/point/PointLight.h>
#include <shapes/planes/Plane.h>
#include <camera/Camera.h>
#include <numbers>
#include <transformations/Transformations.h>
#include <iostream>
#include <fstream>
#include <chrono>
#include <patterns/stripes/StripePattern.h>
#include <patterns/checkers/CheckerPattern.h>
#include <patterns/blended/BlendedPattern.h>


using namespace rtc::world;
using namespace rtc::lights::point;
using namespace rtc::shapes::planes;
using namespace rtc::camera;
using namespace rtc::transformations;
using namespace rtc::canvas;
using namespace rtc::patterns::checkers;
using namespace rtc::patterns::stripes;
using namespace rtc::patterns::blended;

constexpr int SCREEN_WIDTH = 256;
constexpr int SCREEN_HEIGHT = 128;

int main() {
    const auto start = std::chrono::high_resolution_clock::now();

    World w{};

    w.lights.push_back(std::make_unique<PointLight>(point(-10, 10, -10), color(1, 1, 1)));

    w.objects.push_back(std::make_unique<Plane>());

    StripePattern a{color(0.75, 0.25, 0.25), color(0.8, 0.4, 0.4)};
    a.transform = Transform().rotate_y(std::numbers::pi_v<float> / 4.f).scale(0.25, 0.25, 0.25);

    StripePattern b{color(0.75, 0.75, 0.75), color(0.4, 0.4, 0.4)};
    b.transform = Transform().rotate_y(-std::numbers::pi_v<float> / 4.f).scale(0.25, 0.25, 0.25);

    CheckerPattern c{ std::make_unique<StripePattern>(a), std::make_unique<StripePattern>(b) };

    w.objects[0]->material.pattern = std::make_unique<CheckerPattern>(c);

    w.objects.push_back(std::make_unique<Plane>());
    w.objects[1]->transform = Transform().rotate_x(std::numbers::pi_v<float>/ 2.f).translate(0, 0, 3);

    StripePattern d{color(0.5, 1, 0.5), color(0.4, 0.8, 0.4)};
    StripePattern e{color(0.5, 1, 0.5), color(0.4, 0.8, 0.4)};
    e.transform = Transform().rotate_y(std::numbers::pi_v<float> / 2.f);

    BlendedPattern f{std::make_unique<StripePattern>(d), std::make_unique<StripePattern>(e) };

    w.objects[1]->material.pattern = std::make_unique<BlendedPattern>(f);

    Camera cam{SCREEN_WIDTH, SCREEN_HEIGHT, std::numbers::pi_v<float> / 3.f};
    const Point from = point(0, 2, -5);
    const Point to = point(0, 1, 0);
    const Vector up = vector(0, 1, 0);
    cam.transform = view_transform(from, to, up);

    Canvas canvas = cam.render(w);

    std::ofstream file("../output/nested_patterns.ppm");

    file << canvas.canvas_to_ppm();

    const auto end = std::chrono::high_resolution_clock::now();

    std::cout << "File Created. Time Elapsed: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << "ms" << std::endl;

    return 0;
}