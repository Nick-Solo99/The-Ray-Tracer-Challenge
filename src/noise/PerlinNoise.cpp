//
// Created by Nicholas Solomon on 2026-05-19.
//

#include "PerlinNoise.h"
#include <cmath>

namespace rtc::noise {
    float PerlinNoise::grad(const int& hash, const float& x, const float& y, const float& z) {
        const int h = hash & 15;
        const float u = h < 8 ? x : y,
              v = h < 4 ? y : h == 12 || h == 14 ? x : z;
        return ((h&1) == 0 ? u : -u) + ((h&2) == 0 ? v : -v);
    }
    float PerlinNoise::noise(float x, float y, float z) {
        const int X = static_cast<int>(std::floorf(x)) & 255,
                  Y = static_cast<int>(std::floorf(y)) & 255,
                  Z = static_cast<int>(std::floorf(z)) & 255;
        x -= std::floorf(x);
        y -= std::floorf(y);
        z -= std::floorf(z);
        const float u = fade(x);
        const float v = fade(y);
        const float w = fade(z);
        const int A = p[X] + Y, AA = p[A] + Z, AB = p[A + 1] + Z,
                  B = p[X + 1] + Y, BA = p[B] + Z, BB = p[B + 1] + Z;

        return lerp(w,
            lerp(v,
                lerp(u,
                    grad(p[AA], x, y, z),
                    grad(p[BA], x - 1, y, z)),
                lerp(u,
                    grad(p[AB], x, y - 1, z),
                    grad(p[BB], x - 1, y - 1, z))),
            lerp(v,
                lerp(u,
                    grad(p[AA + 1], x, y, z - 1),
                    grad(p[BA + 1], x - 1, y, z - 1)),
                lerp(u,
                    grad(p[AB + 1], x, y - 1, z - 1),
                    grad(p[BB + 1], x - 1, y - 1, z - 1))));
    }
}