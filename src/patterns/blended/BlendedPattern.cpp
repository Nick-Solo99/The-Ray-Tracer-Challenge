//
// Created by Nicholas Solomon on 2026-05-19.
//

#include "BlendedPattern.h"

namespace rtc::patterns::blended {
    Color BlendedPattern::color_at(const Point& point) const {
        const Point point_a = a->transform.inverse() * point;
        const Point point_b = b->transform.inverse() * point;
        return (a->color_at(point_a) + b->color_at(point_b)) * .5f;
    }

    std::unique_ptr<Pattern> BlendedPattern::clone() const {
        return std::make_unique<BlendedPattern>(*this);
    }
}