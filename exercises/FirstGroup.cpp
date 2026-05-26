//
// Created by Nicholas Solomon on 2026-05-25.
//

#include <world/World.h>
#include <camera/Camera.h>
#include <canvas/Canvas.h>
#include <lights/point/PointLight.h>
#include <shapes/cylinders/Cylinder.h>
#include <shapes/spheres/Sphere.h>
#include <shapes/groups/Group.h>
#include <transformations/Transformations.h>
#include <iostream>
#include <fstream>
#include <chrono>
#include <numbers>
#include <memory>

using namespace rtc::world;
using namespace rtc::camera;
using namespace rtc::canvas;
using namespace rtc::lights::point;
using namespace rtc::shapes::cylinders;
using namespace rtc::shapes::spheres;
using namespace rtc::shapes::groups;
using namespace rtc::transformations;

Sphere hexagon_corner() {
    Sphere corner{};
    corner.transform = translation(0, 0, -1) * scaling(0.25, 0.25, 0.25);
    return corner;
}

Cylinder hexagon_edge() {
    Cylinder edge{};
    edge.minimum = 0;
    edge.maximum = 1;
    edge.transform = translation(0, 0, -1) * rotation_y(-std::numbers::pi_v<float> / 6.f) * rotation_z(-std::numbers::pi_v<float> / 2.f) * scaling(0.25, 1, 0.25);
    return edge;
}

std::unique_ptr<Group> hexagon_side() {
    auto side = std::make_unique<Group>();
    side->add_child(std::make_unique<Sphere>(hexagon_corner()));
    side->add_child(std::make_unique<Cylinder>(hexagon_edge()));
    return side;
}

std::unique_ptr<Group> hexagon() {
    auto hex = std::make_unique<Group>();
    for (size_t i{}; i < 6; i++) {
        auto side = hexagon_side();
        side->transform = rotation_y(i * std::numbers::pi_v<float> / 3.f);
        hex->add_child(std::move(side));
    }
    return hex;
}

int main() {

    constexpr int SCREEN_WIDTH = 256;
    constexpr int SCREEN_HEIGHT = 128;

    const auto start = std::chrono::high_resolution_clock::now();

    World w{};
    w.lights.push_back(std::make_unique<PointLight>(point(-10, 10, -10), color(1, 1, 1)));

    auto hex = hexagon();
    w.objects.push_back(std::move(hex));

    Camera cam{SCREEN_WIDTH, SCREEN_HEIGHT, std::numbers::pi_v<float> / 3.f};
    const Point from = point(-3, 3, -3);
    const Point to = point(0, 0, 0);
    const Vector up = vector(0, 1, 0);
    cam.transform = view_transform(from, to, up);

    std::ofstream file("../output/first_group.ppm");
    file << cam.render(w).canvas_to_ppm();

    const auto end = std::chrono::high_resolution_clock::now();
    std::cout << "File Created. Time Elapsed: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " ms" << std::endl;
    return 0;
}