//
// Created by Nicholas Solomon on 2026-05-07.
//

#include <algorithm>
#include <iostream>
#include <fstream>
#include "tuples/Tuple.h"
#include "canvas/Canvas.h"

using namespace rtc::tuples;
using namespace rtc::canvas;

struct Environment {
    Tuple gravity, wind;
};

struct Projectile {
    Tuple position, velocity;
};


Projectile tick(const Environment &env, const Projectile &proj) {
    const Tuple pos = proj.position + proj.velocity;
    const Tuple vel = proj.velocity + env.gravity + env.wind;
    return {pos, vel};
}

int main() {
    constexpr float velocity_scale = 11.25;

    Point start = point(0, 1, 0);
    Vector velocity = normalize(vector(1, 1.8f, 0)) * velocity_scale;
    Projectile p = {start, velocity};

    Vector gravity = vector(0, -0.1f, 0);
    Vector wind = vector(-0.01f, 0, 0);

    const Environment e = {gravity, wind};

    Canvas c(900, 550);

    int ticks = 0;
    while (p.position.y > 0.0f) {
        ticks++;
        p = tick(e, p);

        int values[2] = {
            std::clamp(static_cast<int>(std::round(p.position.x)), 0, c.width - 1),
            std::clamp(static_cast<int>(std::round(p.position.y)), 0, c.height - 1)
        };

        c.write_pixel(values[0], c.height - 1 - values[1], color(0.5f, 0.0f, 0.5f));
        std::cout << "Projectile Position: [x: " << values[0] << ", y: " << values[1] << "]" << std::endl;
    }
    std::cout << "Ticks: " << ticks << std::endl;

    std::ofstream file("../output/render.ppm");
    file << c.canvas_to_ppm();
    return 0;
}