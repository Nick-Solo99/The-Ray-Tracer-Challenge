//
// Created by xGrim on 2026-05-20.
//

#include "TestPattern.h"

namespace rtc::patterns::test {
    Color TestPattern::color_at(const Point &point) const {
        return color(point.x, point.y, point.z);
    }

    std::unique_ptr<Pattern> TestPattern::clone() const {
        return std::make_unique<TestPattern>(*this);
    }
}

