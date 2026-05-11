//
// Created by xGrim on 2026-05-08.
//

#ifndef RTC_INTERSECTION_H
#define RTC_INTERSECTION_H

#include <vector>
#include <initializer_list>

namespace rtc::shapes {
    class Shape;
}

namespace rtc::intersections {
    using Shape = shapes::Shape;

    struct Intersection {
        float t = 0.0f;
        const Shape* object = nullptr;
    };

    inline std::vector<Intersection> intersections(std::initializer_list<Intersection> list) { return {list}; }

}

#endif //RTC_INTERSECTION_H
