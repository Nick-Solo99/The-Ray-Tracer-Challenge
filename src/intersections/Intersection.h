//
// Created by Nicholas Solomon on 2026-05-08.
//

#ifndef RTC_INTERSECTION_H
#define RTC_INTERSECTION_H

#include <algorithm>
#include <vector>
#include <span>
#include <initializer_list>
#include <optional>

#include "rays/Ray.h"
#include "shapes/Shape.h"
#include "tuples/Tuple.h"

namespace rtc::shapes {
    class Shape;
}

namespace rtc::intersections {

    struct Components {
        const shapes::Shape* object = nullptr;
        float t{};
        Point point{};
        Vector eye_v{};
        Vector normal_v{};
        bool inside{};
        Point over_point{};
    };

    struct Intersection {
        float t = 0.0f;
        const shapes::Shape* object = nullptr;

        bool operator==(const Intersection& other) const { return object == other.object && t == other.t; }
        bool operator!=(const Intersection& other) const { return !(*this == other); }
        bool operator<(const Intersection& other) const { return t < other.t; }

        [[nodiscard]] Components pre_compute(const rays::Ray& ray) const;
    };



    std::vector<Intersection> intersections(std::initializer_list<Intersection> list);
    std::optional<Intersection> hit(std::span<const Intersection> intersections);

}

#endif //RTC_INTERSECTION_H
