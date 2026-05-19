//
// Created by Nicholas Solomon on 2026-05-17.
//

#include "CheckerPattern.h"

namespace rtc::patterns::checkers {
    Color CheckerPattern::color_at(const Point &point) const {
        const Point point_a = a->transform.inverse() * point;
        const Point point_b = b->transform.inverse() * point;
        return (static_cast<int>(std::floor(point.x)) + static_cast<int>(std::floor(point.y)) + static_cast<int>(std::floor(point.z))) % 2 == 0 ? a->color_at(point_a) : b->color_at(point_b);
    }

    std::unique_ptr<Pattern> CheckerPattern::clone() const {
        return std::make_unique<CheckerPattern>(*this);
    }
}
