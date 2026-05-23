//
// Created by Nicholas Solomon on 2026-05-21.
//

#include <world/World.h>
#include <camera/Camera.h>
#include <shapes/cubes/Cube.h>
#include <shapes/spheres/Sphere.h>
#include <shapes/planes/Plane.h>
#include <lights/point/PointLight.h>
#include <transformations/Transformations.h>
#include <numbers>
#include <iostream>
#include <fstream>
#include <chrono>

using namespace rtc::world;
using namespace rtc::camera;
using namespace rtc::canvas;
using namespace rtc::lights::point;
using namespace rtc::shapes::cubes;
using namespace rtc::shapes::spheres;
using namespace rtc::shapes::planes;
using namespace rtc::transformations;

int main() {
    const auto start = std::chrono::high_resolution_clock::now();

    World w{};

    Camera cam{1000, 1000, 0.785};
    const Point from = point(-6, 6, -10);
    const Point to = point(6, 0, 6);
    const Vector up = vector(-0.45, 1, 0);
    cam.transform = view_transform(from, to, up);

    w.lights.push_back(std::make_unique<PointLight>(point(50, 100, -50), color(1, 1, 1)));
    w.lights.push_back(std::make_unique<PointLight>(point(-400, 50, -10), color(0.2, 0.2, 0.2)));

    Material white_mat;
    white_mat.color = color(1, 1, 1);
    white_mat.diffuse = 0.7;
    white_mat.ambient = 0.1;
    white_mat.specular = 0.0;
    white_mat.reflective = 0.1;

    Material blue_mat = white_mat;
    blue_mat.color = color(0.537, 0.831, 0.914);

    Material red_mat = white_mat;
    red_mat.color = color(0.941, 0.322, 0.388);

    Material purple_mat = white_mat;
    purple_mat.color = color(0.373, 0.404, 0.550);

    const Matrix standard_transform = scaling(0.5, 0.5, 0.5) * translation(1, -1, 1);
    const Matrix large_obj = scaling(3.5, 3.5, 3.5) * standard_transform;
    const Matrix med_obj = scaling(3, 3, 3) * standard_transform;
    const Matrix small_obj = scaling(2, 2, 2) * standard_transform;

    Plane backdrop{};
    backdrop.material.color = color(1, 1, 1);
    backdrop.material.ambient = 1;
    backdrop.material.diffuse = 0;
    backdrop.material.specular = 0;
    backdrop.transform = Transform().rotate_x(std::numbers::pi_v<float> / 2.f).translate(0, 0, 500);
    w.objects.push_back(std::make_unique<Plane>(backdrop));

    Sphere s01{};
    s01.material.color = color(0.373, 0.404, 0.550);
    s01.material.diffuse = 0.2;
    s01.material.ambient = 0.0;
    s01.material.specular = 1.0;
    s01.material.shininess = 200;
    s01.material.reflective = 0.7;
    s01.material.transparency = 0.7;
    s01.material.refractive_index = 1.5;
    s01.transform = large_obj;
    w.objects.push_back(std::make_unique<Sphere>(s01));

    Cube c01{};
    c01.material = white_mat;
    c01.transform = translation(4, 0, 0) * med_obj;
    w.objects.push_back(std::make_unique<Cube>(c01));

    Cube c02{};
    c02.material = blue_mat;
    c02.transform = translation(8.5, 1.5, -0.5) * large_obj;
    w.objects.push_back(std::make_unique<Cube>(c02));

    Cube c03{};
    c03.material = red_mat;
    c03.transform = translation(0, 0, 4) * large_obj;
    w.objects.push_back(std::make_unique<Cube>(c03));

    Cube c04{};
    c04.material = white_mat;
    c04.transform = translation(4, 0, 4) * small_obj;
    w.objects.push_back(std::make_unique<Cube>(c04));

    Cube c05{};
    c05.material = purple_mat;
    c05.transform = translation(7.5, 0.5, 4) * med_obj;
    w.objects.push_back(std::make_unique<Cube>(c05));

    Cube c06{};
    c06.material = white_mat;
    c06.transform = translation(-0.25, 0.25, 8) * med_obj;
    w.objects.push_back(std::make_unique<Cube>(c06));

    Cube c07{};
    c07.material = blue_mat;
    c07.transform = translation(4, 1, 7.5) * large_obj;
    w.objects.push_back(std::make_unique<Cube>(c07));

    Cube c08{};
    c08.material = red_mat;
    c08.transform = translation(10, 2, 7.5) * med_obj;
    w.objects.push_back(std::make_unique<Cube>(c08));

    Cube c09{};
    c09.material = white_mat;
    c09.transform = translation(8, 2, 12) * small_obj;
    w.objects.push_back(std::make_unique<Cube>(c09));

    Cube c10{};
    c10.material = white_mat;
    c10.transform = translation(20, 1, 9) * small_obj;
    w.objects.push_back(std::make_unique<Cube>(c10));

    Cube c11{};
    c11.material = blue_mat;
    c11.transform = translation(-0.5, -5, 0.25) * large_obj;
    w.objects.push_back(std::make_unique<Cube>(c11));

    Cube c12{};
    c12.material = red_mat;
    c12.transform = translation(4, -4, 0) * large_obj;
    w.objects.push_back(std::make_unique<Cube>(c12));

    Cube c13{};
    c13.material = white_mat;
    c13.transform = translation(8.5, -4, 0) * large_obj;
    w.objects.push_back(std::make_unique<Cube>(c13));

    Cube c14{};
    c14.material = white_mat;
    c14.transform = translation(0, -4, 4) * large_obj;
    w.objects.push_back(std::make_unique<Cube>(c14));

    Cube c15{};
    c15.material = purple_mat;
    c15.transform = translation(-0.5, -4.5, 8) * large_obj;
    w.objects.push_back(std::make_unique<Cube>(c15));

    Cube c16{};
    c16.material = white_mat;
    c16.transform = translation(0, -8, 4) * large_obj;
    w.objects.push_back(std::make_unique<Cube>(c16));

    Cube c17{};
    c17.material = white_mat;
    c17.transform = translation(-0.5, -8.5, 8) * large_obj;
    w.objects.push_back(std::make_unique<Cube>(c17));


    std::ofstream file("../output/cover_image.ppm");
    file << cam.render(w).canvas_to_ppm();
    const auto end = std::chrono::high_resolution_clock::now();
    std::cout << "File Created. Time Elapsed: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " ms" << std::endl;
    return 0;
}
