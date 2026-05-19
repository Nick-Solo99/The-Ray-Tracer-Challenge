//
// Created by Nicholas Solomon on 2026-05-17.
//

#ifndef RTC_CHECKERPATTERN_H
#define RTC_CHECKERPATTERN_H

#include <patterns/binary/BinaryPattern.h>
#include <patterns/solid/SolidPattern.h>

using namespace rtc::patterns::binary;
using namespace rtc::patterns::solid;

namespace rtc::patterns::checkers {
    struct CheckerPattern final : BinaryPattern {
        using BinaryPattern::BinaryPattern;
        CheckerPattern(const Color& a, const Color& b) : BinaryPattern(std::make_unique<SolidPattern>(a), std::make_unique<SolidPattern>(b)) {}
        [[nodiscard]] Color color_at(const Point& point) const override;
        [[nodiscard]] std::unique_ptr<Pattern> clone() const override;
    };
}


#endif //RTC_CHECKERPATTERN_H