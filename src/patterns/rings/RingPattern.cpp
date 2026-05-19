//
// Created by Nicholas Solomon on 2026-05-16.
//

#include "RingPattern.h"

namespace rtc::patterns::rings {
    Color RingPattern::color_at(const Point& point) const {
        const Point point_a = a->transform.inverse() * point;
        const Point point_b = b->transform.inverse() * point;
        return static_cast<int>(std::floor(std::hypot(point.x, point.z))) % 2 == 0 ? a->color_at(point_a) : b->color_at(point_b);
    }
    std::unique_ptr<Pattern> RingPattern::clone() const {
        return std::make_unique<RingPattern>(*this);
    }
}