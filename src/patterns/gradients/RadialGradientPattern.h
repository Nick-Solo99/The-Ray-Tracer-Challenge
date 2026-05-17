//
// Created by Nicholas Solomon on 2026-05-17.
//

#ifndef RTC_RADIALGRADIENTPATTERN_H
#define RTC_RADIALGRADIENTPATTERN_H

#include <patterns/Pattern.h>

namespace rtc::patterns::gradients {
    struct RadialGradientPattern final : Pattern {
        RadialGradientPattern(const Color& a, const Color& b) { this->a = a; this->b = b; transform = Matrix::identity(); }
        [[nodiscard]] Color color_at(const Point& point) const override;
        [[nodiscard]] std::unique_ptr<Pattern> clone() const override;
    };

}


#endif //RTC_RADIALGRADIENTPATTERN_H