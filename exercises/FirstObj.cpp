//
// Created by Nicholas Solomon on 2026-05-27.
//

#include <scene/Scene.h>


int main() {
    constexpr int SCREEN_WIDTH = 256;
    constexpr int SCREEN_HEIGHT = 128;

    const auto start = std::chrono::high_resolution_clock::now();


    World w{};
    w.lights.push_back(std::make_unique<PointLight>(point(-99, 99, -99), color(1, 1, 1)));

    CheckerPattern checker_pattern{color(0.8, 0.8, 0.8), color(0.4, 0.4, 0.4)};
    checker_pattern.transform = scaling(0.1, 0.1, 0.1);

    Cube room{};
    room.material.pattern = std::make_unique<CheckerPattern>(checker_pattern);
    room.transform = translation(0, 100, 0) * scaling(100, 100, 100);
    w.objects.push_back(std::make_unique<Cube>(room));

    if (std::ifstream input("../input/lambo.obj"); !input) {
        std::cout << "File not found" << std::endl;
    } else {
        auto parsed_obj = parse_obj_file(input);
        auto obj = obj_to_group(parsed_obj);
        obj->transform = rotation_y(std::numbers::pi_v<float> / 2.f) * scaling(0.1, 0.1, 0.1);
        Material obj_material{};
        obj_material.color = color(0.85, 0.45, 0.1);
        obj->set_material(obj_material);
        obj->cache_bounds();
        w.objects.push_back(std::move(obj));

    }


    Camera cam{SCREEN_WIDTH, SCREEN_HEIGHT, std::numbers::pi_v<float> / 3.f};
    const Point from = point(0, 10, -60);
    const Point to = point(0, 0.2, 0);
    const Vector up = vector(0, 1, 0);
    cam.transform = view_transform(from, to, up);

    std::ofstream output("../output/first_obj.ppm");
    output << cam.render(w).canvas_to_ppm();

    const auto end = std::chrono::high_resolution_clock::now();
    std::cout << "File Created. Time Elapsed: " << std::chrono::duration_cast<std::chrono::milliseconds>(end -start).count() << " ms" << std::endl;
    return 0;
}