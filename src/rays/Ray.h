//
// Created by Nicholas Solomon on 2026-05-08.
//

#ifndef RTC_RAY_H
#define RTC_RAY_H

#include <tuples/Tuple.h>
#include <matrices/Matrix.h>

using namespace rtc::tuples;

namespace rtc::rays {
    struct Ray {
        Tuple origin, direction;

        Ray(const Point origin, const Vector direction) : origin(origin), direction(direction) {}
        [[nodiscard]] Point position(const float& t) const { return origin + direction * t; }
        [[nodiscard]] Ray transform(const matrices::Matrix& m) const { return Ray{m * origin, m * direction}; }
    };


}

#endif //RTC_RAY_H
