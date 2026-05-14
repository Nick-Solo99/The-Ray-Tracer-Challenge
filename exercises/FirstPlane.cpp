//
// Created by Nicholas Solomon on 2026-05-14.
//

#include <world/World.h>
#include <camera/Camera.h>


#include <fstream>
#include <iostream>
#include <numbers>
#include <chrono>

#include "transformations/Transformations.h"
#include <shapes/spheres/Sphere.h>
#include <shapes/planes/Plane.h>

#include "lights/point/PointLight.h"


using namespace rtc::world;
using namespace rtc::camera;
using namespace rtc::canvas;
using namespace rtc::tuples;
using namespace rtc::transformations;
using namespace rtc::shapes;
using namespace rtc::shapes::spheres;
using namespace rtc::shapes::planes;
using namespace rtc::lights::point;

int main() {


    const auto start = std::chrono::high_resolution_clock::now();

    constexpr int SCREEN_WIDTH = 256;
    constexpr int SCREEN_HEIGHT = 128;

    World world = World::default_world();

    world.objects.push_back(std::make_unique<Sphere>());
    world.objects.push_back(std::make_unique<Plane>());
    world.objects.push_back(std::make_unique<Plane>());
    world.objects.push_back(std::make_unique<Plane>());
    world.objects.push_back(std::make_unique<Plane>());
    world.objects.push_back(std::make_unique<Plane>());
    world.objects.push_back(std::make_unique<Plane>());
    world.objects.push_back(std::make_unique<Plane>());
    world.objects.push_back(std::make_unique<Plane>());

    Shape* middle = world.objects[0].get();
    Shape* right = world.objects[1].get();
    Shape* left = world.objects[2].get();

    Shape* floor = world.objects[3].get();
    floor->material.color = color(1, 0.9f, 0.9f);
    floor->material.specular = 0;

    Shape* roof = world.objects[4].get();
    roof->material.color = color(1, 0.9f, 0.9f);
    roof->material.specular = 0;
    roof->transform = translation(0, 0, 10) * rotation_x(std::numbers::pi_v<float> * 2.f);

    constexpr int SIDES = 6;
    constexpr float RADIUS = 10.f;

    for (int i = 0; i < SIDES; ++i) {
        const float angle = (2.f * std::numbers::pi_v<float> / SIDES) * i;
        const float z = std::cos(angle) * RADIUS;
        const float x = std::sin(angle) * RADIUS;

        std::cout << "z: " << z << ", x: " << x << ", angle: " << angle << std::endl;

        world.objects[5 + i]->material.color = color(1.f, 0.9f, 0.9f);
        world.objects[5 + i]->material.specular = 0;
        world.objects[5 + i]->transform = translation(x, 0, z) * rotation_y(angle) * rotation_x(std::numbers::pi_v<float> / 2.f);
    }


    middle->transform = translation(-0.5f, 1.f, 0.5f);
    middle->material.color = color(0.1f, 1.f, 0.5f);
    middle->material.diffuse = 0.7f;
    middle->material.specular = 0.3f;

    right->transform = translation(1.5f, 0.5f, -0.5f) * scaling(0.5f, 0.5f, 0.5f);
    right->material.color = color(0.5f, 1.f, 0.1f);
    right->material.diffuse = 0.7f;
    right->material.specular = 0.3f;

    left->transform = translation(-1.5f, 0.33f, -0.75f) * scaling(0.33f, 0.33f, 0.33f);
    left->material.color = color(1.f, 0.8f, 0.1f);
    left->material.diffuse = 0.7f;
    left->material.specular = 0.3f;

    world.lights[0]->position = point(3, 3, -5);


    Camera camera{SCREEN_WIDTH, SCREEN_HEIGHT, std::numbers::pi_v<float> / 2.f};
    const Point from = point(0, 9, -5);
    const Point to = point(0, 1, 0);
    const Vector up = vector(0, 1, 0);
    camera.transform = view_transform(from, to, up);

    Canvas canvas = camera.render(world);

    std::ofstream file("../output/first_plane.ppm");

    file << canvas.canvas_to_ppm();

    const auto end = std::chrono::high_resolution_clock::now();
    const auto delta = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    std::cout << "File created. Elapsed time: " << delta << " ms" << std::endl;

    return 0;
}