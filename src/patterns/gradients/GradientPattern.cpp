//
// Created by Nicholas Solomon on 2026-05-16.
//

#include "GradientPattern.h"

namespace rtc::patterns::gradients {
    Color GradientPattern::color_at(const Point& point) const {
        return a + (b - a) * (point.x - std::floor(point.x));
    }

    std::unique_ptr<Pattern> GradientPattern::clone() const {
        return std::make_unique<GradientPattern>(*this);
    }
} // rtc