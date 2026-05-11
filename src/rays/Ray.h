//
// Created by xGrim on 2026-05-08.
//

#ifndef RTC_RAY_H
#define RTC_RAY_H

#include <tuples/Tuple.h>

using namespace rtc::tuples;

namespace rtc::rays {
    struct Ray {
        Tuple origin, direction;

        Ray(const Point origin, const Vector direction) : origin(origin), direction(direction) {}
        [[nodiscard]] Point position(const float& t) const { return origin + direction * t; }
    };


}

#endif //RTC_RAY_H
