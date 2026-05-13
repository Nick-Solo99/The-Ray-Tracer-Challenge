//
// Created by Nicholas Solomon on 2026-05-08.
//

#ifndef RTC_SHAPE_H
#define RTC_SHAPE_H
#include <vector>
#include <materials/Material.h>
#include <matrices/Matrix.h>

namespace rtc::rays {
    struct Ray;
}

namespace rtc::tuples {
    struct Tuple;
    using Vector = Tuple;
    using Point = Tuple;
}

namespace rtc::intersections {
    struct Intersection;
}

namespace rtc::shapes {
    using Ray = rays::Ray;
    using Material = materials::Material;

    class Shape {
        public:
        Material material;
        matrices::Matrix transform = matrices::Matrix::identity();

        void set_transform(const matrices::Matrix& t) { transform = t; }

        bool virtual operator==(const Shape& other) const = 0;

        [[nodiscard]] virtual std::vector<intersections::Intersection> intersect(const Ray& ray) const = 0;
        [[nodiscard]] virtual Vector normal_at(const Point& p) const = 0;
        virtual ~Shape() = default;
    };
}

#endif //RTC_SHAPE_H
