#include <iostream>

#include "tuples/Tuple.h"


using namespace rtc::tuples;

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
    constexpr float velocity_scale = 5.0;
    const Environment env = {vector(0, -0.1, 0), vector(-0.01, 0, 0)};
    Projectile proj = {point(0, 1, 0), normalize(vector(1, 1, 0)) * velocity_scale};
    int ticks = 0;
    while (proj.position.y > 0.0) {
        ticks++;
        proj = tick(env, proj);
        std::cout << "Projectile Position: [x: " << proj.position.x << ", y: " << proj.position.y << ", z: " << proj.position.z << "]" << std::endl;
    }
    std::cout << "Ticks: " << ticks << std::endl;

    return 0;
}