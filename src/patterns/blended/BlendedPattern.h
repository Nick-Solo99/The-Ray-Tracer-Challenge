//
// Created by Nicholas Solomon on 2026-05-19.
//

#ifndef RTC_BLENDEDPATTERN_H
#define RTC_BLENDEDPATTERN_H

#include <patterns/binary/BinaryPattern.h>

using namespace rtc::patterns::binary;

namespace rtc::patterns::blended {
    struct BlendedPattern final : BinaryPattern {
        using BinaryPattern::BinaryPattern;
        [[nodiscard]] Color color_at(const Point& point) const override;
        [[nodiscard]] std::unique_ptr<Pattern> clone() const override;
    };
}

#endif //RTC_BLENDEDPATTERN_H