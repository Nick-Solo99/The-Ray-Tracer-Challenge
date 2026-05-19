//
// Created by Nicholas Solomon on 2026-05-14.
//

#include "StripePattern.h"
#include <cmath>

#include "constants/Constants.h"

namespace rtc::patterns::stripes {
    Color StripePattern::color_at(const Point& point) const {
        const Point point_a = a->transform.inverse() * point;
        const Point point_b = b->transform.inverse() * point;
        return static_cast<int>(std::floor(point.x)) % 2 == 0 ? a->color_at(point_a) : b->color_at(point_b);
    }

    std::unique_ptr<Pattern> StripePattern::clone() const {
        return std::make_unique<StripePattern>(*this);
    }
} // rtc