//
// Created by Nicholas Solomon on 2026-05-16.
//

#include "RingPattern.h"

namespace rtc::patterns::rings {
    Color RingPattern::color_at(const Point& point) const {
        return static_cast<int>(std::floor(std::hypot(point.x, point.z))) % 2 == 0 ? a : b;
    }
    std::unique_ptr<Pattern> RingPattern::clone() const {
        return std::make_unique<RingPattern>(*this);
    }
}