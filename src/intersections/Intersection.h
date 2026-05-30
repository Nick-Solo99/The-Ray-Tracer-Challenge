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
        const Shape* object = nullptr;
        float t{};
        Point point{};
        Vector eye_v{};
        Vector normal_v{};
        bool inside{};
        Point over_point{};
        Vector reflect_v{};
        float n1{};
        float n2{};
        Point under_point{};
    };

    struct Intersection {
        float t = 0.0f;
        const Shape* object = nullptr;
        float u, v;

        bool operator==(const Intersection& other) const { return object == other.object && t == other.t; }
        bool operator!=(const Intersection& other) const { return !(*this == other); }
        bool operator<(const Intersection& other) const { return t < other.t; }

        [[nodiscard]] Components pre_compute(const rays::Ray& ray, const std::vector<Intersection>& xs) const;
        [[nodiscard]] Components pre_compute(const rays::Ray& ray) const { return pre_compute(ray, {*this}); }
    };

    std::vector<Intersection> intersections(std::initializer_list<Intersection> list);
    std::optional<Intersection> hit(std::span<const Intersection> intersections);
    float schlick(const Components& comps);

}

#endif //RTC_INTERSECTION_H
