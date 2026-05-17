//
// Created by Nicholas Solomon on 2026-05-16.
//

#ifndef RTC_RINGPATTERN_H
#define RTC_RINGPATTERN_H

#include <patterns/Pattern.h>

namespace rtc::patterns::rings {
    struct RingPattern final : Pattern {
        RingPattern(const Color& a, const Color& b) {this->a = a; this->b = b; transform = Matrix::identity(); }
        [[nodiscard]] Color color_at(const Point& point) const override;
        [[nodiscard]] std::unique_ptr<Pattern> clone() const override;
    };

}


#endif //RTC_RINGPATTERN_H