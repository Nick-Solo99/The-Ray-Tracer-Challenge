//
// Created by Nicholas Solomon on 2026-05-08.
//

#ifndef RTC_SHAPE_H
#define RTC_SHAPE_H
#include <vector>
#include <materials/Material.h>
#include <matrices/Matrix.h>
#include <optional>

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

    struct Bounds {
        Point min;
        Point max;
    };

    class Shape {
        public:
        Material material;
        Matrix transform = Matrix::identity();
        Shape* parent = nullptr;
        mutable std::optional<Bounds> cached_bounds;

        void set_transform(const Matrix& t) { transform = t; }
        [[nodiscard]] Point world_to_obj(Point p) const;
        [[nodiscard]] Vector normal_to_world(Vector normal) const;

        bool virtual operator==(const Shape& other) const;

        [[nodiscard]] virtual std::vector<intersections::Intersection> intersect(const Ray& ray) const = 0;
        [[nodiscard]] virtual Vector local_normal_at(const Point& p) const = 0;
        [[nodiscard]] Vector normal_at(const Point& p) const;
        [[nodiscard]] virtual const Bounds& bounds() const = 0;
        virtual ~Shape() = default;
    };
}

#endif //RTC_SHAPE_H
