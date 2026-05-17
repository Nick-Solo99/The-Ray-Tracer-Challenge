//
// Created by Nicholas Solomon on 2026-05-16.
//
#include <world/World.h>
#include <camera/Camera.h>
#include <numbers>
#include <transformations/Transformations.h>
#include <iostream>
#include <fstream>
#include <chrono>
#include <patterns/stripes/StripePattern.h>
#include <shapes/planes/Plane.h>
#include <shapes/spheres/Sphere.h>

#include "patterns/gradients/GradientPattern.h"
#include <patterns/rings/RingPattern.h>
#include <patterns/checkers/CheckerPattern.h>

using namespace rtc::world;
using namespace rtc::camera;
using namespace rtc::transformations;
using namespace rtc::canvas;
using namespace rtc::patterns::stripes;
using namespace rtc::shapes::planes;
using namespace rtc::shapes::spheres;
using namespace rtc::patterns::gradients;
using namespace rtc::patterns::rings;
using namespace rtc::patterns::checkers;

int main() {

    const auto start_time = std::chrono::high_resolution_clock::now();

    constexpr int SCREEN_WIDTH = 256;
    constexpr int SCREEN_HEIGHT = 128;

    World world = World::default_world();

    world.objects[0]->transform = Transform().scale(2, 2, 2).translate(0, 2, 0);
    world.objects[1]->transform = Transform().scale(0.5f, 0.5f, 0.5f).translate(-4, 2, 0);


    world.objects.push_back(std::make_unique<Plane>());
    world.objects.push_back(std::make_unique<Plane>());

    world.objects[3]->transform = Transform().rotate_x(std::numbers::pi_v<float> / 2.f).translate(0, 0, 3);
    for (const auto& obj : world.objects) {
        obj->material.pattern = std::make_unique<CheckerPattern>(color(0, 0, 1), color(0, 1, 0));
    }

    world.objects.push_back(std::make_unique<Sphere>());
    world.objects[4]->transform = Transform().scale(2, 2, 2).translate(4, 2, 0);
    world.objects[4]->material.pattern = std::make_unique<GradientPattern>(color(0, 0, 1), color(0, 1, 0));
    world.objects[4]->material.pattern->transform = Transform().rotate_y(std::numbers::pi_v<float> / 2.f).scale(2.f, 2.f, 2.f);

    Camera camera{SCREEN_WIDTH, SCREEN_HEIGHT, std::numbers::pi_v<float> / 3.f};
    const Point from = point(3, 3, -10);
    const Point to = point(0, 2, 0);
    const Vector up = vector(0, 1, 0);
    camera.transform = view_transform(from, to, up);

    Canvas canvas = camera.render(world);

    std::ofstream file("../output/first_pattern.ppm");
    file << canvas.canvas_to_ppm();

    const auto end_time = std::chrono::high_resolution_clock::now();
    const auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count();

    std::cout << "File created. Time elapsed: " << ms << "ms" << std::endl;

    return 0;
}