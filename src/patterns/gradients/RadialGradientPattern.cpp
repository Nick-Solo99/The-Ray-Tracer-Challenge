//
// Created by Nicholas Solomon on 2026-05-17.
//

#include "RadialGradientPattern.h"

namespace rtc::patterns::gradients {
    Color RadialGradientPattern::color_at(const Point& point) const {
        const Point point_a = a->transform.inverse() * point;
        const Point point_b = b->transform.inverse() * point;
        return a->color_at(point_a) + (b->color_at(point_b) - a->color_at(point_a)) * (std::hypot(point.x, point.z) - std::floor(std::hypot(point.x, point.z)));
    }

    std::unique_ptr<Pattern> RadialGradientPattern::clone() const {
        return std::make_unique<RadialGradientPattern>(*this);
    }
}