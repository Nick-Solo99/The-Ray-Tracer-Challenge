//
// Created by Nicholas Solomon on 2026-05-16.
//

#include "GradientPattern.h"

namespace rtc::patterns::gradients {
    Color GradientPattern::color_at(const Point& point) const {
        const Point point_a = a->transform.inverse() * point;
        const Point point_b = b->transform.inverse() * point;
        return a->color_at(point_a) + (b->color_at(point_b) - a->color_at(point_a)) * (point.x - std::floor(point.x));
    }

    std::unique_ptr<Pattern> GradientPattern::clone() const {
        return std::make_unique<GradientPattern>(*this);
    }
} // rtc