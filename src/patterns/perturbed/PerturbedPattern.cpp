//
// Created by Nicholas Solomon on 2026-05-19.
//

#include "PerturbedPattern.h"
#include <noise/PerlinNoise.h>

using namespace rtc::noise;

namespace rtc::patterns::perturbed {
    Color PerturbedPattern::color_at(const Point &point) const {
        constexpr float scale = 0.2f;

        const float nx = PerlinNoise::noise(point.x, point.y, point.z);
        const float ny = PerlinNoise::noise(point.x + 31.4f, point.y + 47.2f, point.z + 11.8f);
        const float nz = PerlinNoise::noise(point.x + 73.1f, point.y + 19.6f, point.z + 52.8f);

        const Point perturbed_point = point + vector(nx, ny, nz) * scale;

        const Point child_point = pattern->transform.inverse() * perturbed_point;

        return pattern->color_at(child_point);
    }
    std::unique_ptr<Pattern> PerturbedPattern::clone() const {
        return std::make_unique<PerturbedPattern>(*this);
    }
}