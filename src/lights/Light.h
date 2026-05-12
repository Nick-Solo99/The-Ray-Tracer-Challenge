//
// Created by Nicholas Solomon on 2026-05-11.
//

#ifndef RTC_LIGHT_H
#define RTC_LIGHT_H

#include "tuples/Tuple.h"

namespace rtc::lights {
    using namespace rtc::tuples;

    struct Light {
        Point position = point(0, 0, 0);
        Color intensity = color(1, 1, 1);
    };
}

#endif //RTC_LIGHT_H
