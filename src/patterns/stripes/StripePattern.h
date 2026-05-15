//
// Created by Nicholas Solomon on 2026-05-14.
//

#ifndef RTC_STRIPEPATTERN_H
#define RTC_STRIPEPATTERN_H

#include <patterns/Pattern.h>

namespace rtc::patterns::stripes {
    struct StripePattern final : Pattern {
        StripePattern(const Color& a, const Color& b) { this->a = a; this->b = b; }
        [[nodiscard]] Color color_at(const Point& point) const override;
        [[nodiscard]] std::unique_ptr<Pattern> clone() const override;
    };
} // rtc

#endif //RTC_STRIPEPATTERN_H