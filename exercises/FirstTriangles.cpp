//
// Created by Nicholas Solomon on 2026-05-26.
//
#include <world/World.h>
#include <camera/Camera.h>
#include <canvas/Canvas.h>
#include <shapes/cubes/Cube.h>
#include <shapes/triangles/Triangle.h>
#include <patterns/checkers/CheckerPattern.h>
#include <lights/point/PointLight.h>
#include <transformations/Transformations.h>
#include <iostream>
#include <fstream>
#include <chrono>
#include <numbers>
#include <shapes/groups/Group.h>


using namespace rtc::world;
using namespace rtc::camera;
using namespace rtc::canvas;
using namespace rtc::shapes::cubes;
using namespace rtc::shapes::triangles;
using namespace rtc::patterns::checkers;
using namespace rtc::lights::point;
using namespace rtc::transformations;
using namespace rtc::shapes::groups;

int main() {
    constexpr int SCREEN_WIDTH = 256;
    constexpr int SCREEN_HEIGHT = 128;

    const auto start = std::chrono::high_resolution_clock::now();

    World w{};
    w.lights.push_back(std::make_unique<PointLight>(point(-4, 4, -4), color(1, 1, 1)));

    CheckerPattern pattern{color(0.8, 0.8, 0.8), color(0.6, 0.6, 0.6)};
    pattern.transform = scaling(0.1, 0.1, 0.1);

    Cube room{};
    room.material.pattern = std::make_unique<CheckerPattern>(pattern);
    room.transform = Transform().scale(5, 5, 5).translate(0, 5, 0);
    w.objects.push_back(std::make_unique<Cube>(room));

    const Point p1 = point(0, 1, 0);
    const Point p2 = point(-1, 0, -1);
    const Point p3 = point(1, 0, -1);
    const Point p4 = point(1, 0, 1);
    const Point p5 = point(-1, 0, 1);

    auto group = std::make_unique<Group>();
    group->add_child(std::make_unique<Triangle>(p1, p2, p3));
    group->add_child(std::make_unique<Triangle>(p1, p3, p4));
    group->add_child(std::make_unique<Triangle>(p1, p4, p5));
    group->add_child(std::make_unique<Triangle>(p1, p5, p2));
    group->add_child(std::make_unique<Triangle>(p2, p5, p4));
    group->add_child(std::make_unique<Triangle>(p2, p3, p4));

    w.objects.push_back(std::move(group));


    Camera cam{SCREEN_WIDTH, SCREEN_HEIGHT, std::numbers::pi_v<float> / 3.f};
    const Point from = point(3, 1, -3);
    const Point to = point(0, 0, 0);
    const Vector up = vector(0, 1, 0);
    cam.transform = view_transform(from, to, up);

    std::ofstream file("../output/first_triangles.ppm");
    file << cam.render(w).canvas_to_ppm();

    const auto end = std::chrono::high_resolution_clock::now();
    std::cout << "File Created. Time Elapsed: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " ms" << std::endl;
    return 0;
}