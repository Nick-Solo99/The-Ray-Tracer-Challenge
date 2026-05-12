//
// Created by Nicholas Solomon on 2026-05-08.
//

#ifndef RTC_SHAPE_H
#define RTC_SHAPE_H
#include <vector>
#include <intersections/Intersection.h>
#include <materials/Material.h>
namespace rtc::rays {
    struct Ray;
}

namespace rtc::tuples {
    struct Tuple;
    using Vector = Tuple;
    using Point = Tuple;
}

namespace rtc::shapes {
    using Intersection = intersections::Intersection;
    using Ray = rays::Ray;
    using Material = materials::Material;

    class Shape {
        public:
        Material material;
        virtual ~Shape() = default;
        [[nodiscard]] virtual std::vector<Intersection> intersect(const Ray& ray) const = 0;
        [[nodiscard]] virtual tuples::Vector normal_at(const tuples::Point& p) const = 0;
    };
}

#endif //RTC_SHAPE_H
