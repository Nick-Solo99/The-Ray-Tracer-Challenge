//
// Created by Nicholas Solomon on 2026-05-08.
//

#ifndef RTC_SHAPE_H
#define RTC_SHAPE_H
#include <vector>
#include <intersections/Intersection.h>

namespace rtc::rays {
    struct Ray;
}

namespace rtc::shapes {
    using Intersection = intersections::Intersection;
    using Ray = rays::Ray;

    class Shape {
        public:
        virtual ~Shape() = default;
        [[nodiscard]] virtual std::vector<Intersection> intersect(const Ray& ray) const = 0;
    };
}

#endif //RTC_SHAPE_H
