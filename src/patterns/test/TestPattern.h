//
// Created by Nicholas Solomon on 2026-05-20.
//

#ifndef RTC_TESTPATTERN_H
#define RTC_TESTPATTERN_H

#include <patterns/Pattern.h>

namespace rtc::patterns::test {
    struct TestPattern final : Pattern {
        [[nodiscard]] Color color_at(const Point &point) const override;
        [[nodiscard]] std::unique_ptr<Pattern> clone() const override;
    };
}

#endif //RTC_TESTPATTERN_H