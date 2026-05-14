//
// Created by Nicholas Solomon on 2026-05-13.
//

#include <world/World.h>
#include <camera/Camera.h>


#include <fstream>
#include <iostream>
#include <numbers>
#include <chrono>

#include "transformations/Transformations.h"
#include <shapes/spheres/Sphere.h>


using namespace rtc::world;
using namespace rtc::camera;
using namespace rtc::canvas;
using namespace rtc::tuples;
using namespace rtc::transformations;
using namespace rtc::shapes;
using namespace rtc::shapes::spheres;

int main() {

    const auto start = std::chrono::high_resolution_clock::now();

    constexpr int SCREEN_WIDTH = 256;
    constexpr int SCREEN_HEIGHT = 128;

    World world = World::default_world();

    world.objects.push_back(std::make_unique<Sphere>());
    world.objects.push_back(std::make_unique<Sphere>());
    world.objects.push_back(std::make_unique<Sphere>());
    world.objects.push_back(std::make_unique<Sphere>());

    Shape* floor = world.objects[0].get();
    Shape* left_wall = world.objects[1].get();
    Shape* right_wall = world.objects[2].get();
    Shape* middle = world.objects[3].get();
    Shape* right = world.objects[4].get();
    Shape* left = world.objects[5].get();


    floor->transform = scaling(10, 0.01, 10);
    floor->material = rtc::materials::Material{};
    floor->material.color = color(1, 0.9f, 0.9f);
    floor->material.specular = 0;

    left_wall->transform = Transform()
    .scale(10, 0.01f, 10)
    .rotate_x(std::numbers::pi_v<float> / 2.f)
    .rotate_y(-std::numbers::pi_v<float> / 4.f)
    .translate(0, 0, 5);
    left_wall->material = floor->material;

    right_wall->transform = Transform()
    .scale(10, 0.01f, 10)
    .rotate_x(std::numbers::pi_v<float> / 2.f)
    .rotate_y(std::numbers::pi_v<float> / 4.f)
    .translate(0, 0, 5);
    right_wall->material = floor->material;

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



    Camera camera{SCREEN_WIDTH, SCREEN_HEIGHT, std::numbers::pi_v<float> / 3.f};
    const Point from = point(0, 1.5, -5);
    const Point to = point(0, 1, 0);
    const Vector up = vector(0, 1, 0);
    camera.transform = view_transform(from, to, up);

    Canvas canvas = camera.render(world);

    std::ofstream file("../output/first_scene.ppm");

    file << canvas.canvas_to_ppm();

    const auto end = std::chrono::high_resolution_clock::now();
    const auto delta = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    std::cout << "File created. Elapsed time: " << delta << " ms" << std::endl;

    return 0;
}