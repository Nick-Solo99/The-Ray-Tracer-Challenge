//
// Created by Nicholas Solomon on 2026-05-17.
//

#ifndef RTC_SOLIDPATTERN_H
#define RTC_SOLIDPATTERN_H

#include <memory>
#include <tuples/Tuple.h>

#include "patterns/Pattern.h"

using namespace rtc::tuples;

namespace rtc::patterns::solid {
    struct SolidPattern final : Pattern {
        Color color = tuples::color(1, 1, 1);
        explicit SolidPattern(const Color& color) : color(color) {}
        [[nodiscard]] Color color_at(const Point& point) const override { return color; }
        [[nodiscard]] std::unique_ptr<Pattern> clone() const override { return std::make_unique<SolidPattern>(*this); }
    };
}




#endif //RTC_SOLIDPATTERN_H