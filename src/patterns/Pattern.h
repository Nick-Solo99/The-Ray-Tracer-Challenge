//
// Created by Nicholas Solomon on 2026-05-14.
//

#ifndef RTC_PATTERN_H
#define RTC_PATTERN_H

#include <tuples/Tuple.h>
#include <memory>
#include <matrices/Matrix.h>

namespace rtc::shapes {
    class Shape;
}

using namespace rtc::tuples;
using namespace rtc::matrices;
using namespace rtc::shapes;

namespace rtc::patterns {
    struct Pattern {
        Matrix transform = Matrix::identity();
        [[nodiscard]] virtual Color color_at(const Point& point) const = 0;
        [[nodiscard]] Color color_at_obj(const Shape& obj, const Point& point) const;
        [[nodiscard]] virtual std::unique_ptr<Pattern> clone() const = 0;
        virtual ~Pattern() = default;
    };
} // rtc

#endif //RTC_PATTERN_H