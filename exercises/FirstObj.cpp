//
// Created by Nicholas Solomon on 2026-05-27.
//

#include <scene/Scene.h>


int main() {
    constexpr int SCREEN_WIDTH = 256;
    constexpr int SCREEN_HEIGHT = 128;

    const auto start = std::chrono::high_resolution_clock::now();


    World w{};
    w.lights.push_back(std::make_unique<PointLight>(point(-4, 4, -4), color(1, 1, 1)));

    CheckerPattern checker_pattern{color(0.8, 0.8, 0.8), color(0.4, 0.4, 0.4)};
    checker_pattern.transform = scaling(0.1, 0.1, 0.1);

    Cube room{};
    room.material.pattern = std::make_unique<CheckerPattern>(checker_pattern);
    room.transform = translation(0, 5, 0) * scaling(5, 5, 5);
    w.objects.push_back(std::make_unique<Cube>(room));

    if (std::ifstream input("../input/teapot.obj"); !input) {
        std::cout << "File not found" << std::endl;
    } else {
        auto parsed_obj = parse_obj_file(input);
        auto teapot = obj_to_group(parsed_obj);
        teapot->transform = scaling(0.3, 0.3, 0.3);
        teapot->cache_bounds();
        w.objects.push_back(std::move(teapot));

    }


    Camera cam{SCREEN_WIDTH, SCREEN_HEIGHT, std::numbers::pi_v<float> / 3.f};
    const Point from = point(0, 2, -2);
    const Point to = point(0, 0.2, 0);
    const Vector up = vector(0, 1, 0);
    cam.transform = view_transform(from, to, up);

    std::ofstream output("../output/first_obj.ppm");
    output << cam.render(w).canvas_to_ppm();

    const auto end = std::chrono::high_resolution_clock::now();
    std::cout << "File Created. Time Elapsed: " << std::chrono::duration_cast<std::chrono::milliseconds>(end -start).count() << " ms" << std::endl;
    return 0;
}