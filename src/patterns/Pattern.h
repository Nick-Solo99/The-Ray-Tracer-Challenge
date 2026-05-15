//
// Created by Nicholas Solomon on 2026-05-14.
//

#ifndef RTC_PATTERN_H
#define RTC_PATTERN_H

#include <tuples/Tuple.h>
#include <memory>

using namespace rtc::tuples;

namespace rtc::patterns {
    struct Pattern {
        Color a = color(0, 0, 0);
        Color b = color(1, 1, 1);
        [[nodiscard]] virtual Color color_at(const Point& point) const = 0;
        [[nodiscard]] virtual std::unique_ptr<Pattern> clone() const = 0;
        virtual ~Pattern() = default;
    };
} // rtc

#endif //RTC_PATTERN_H