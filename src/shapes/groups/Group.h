//
// Created by Nicholas Solomon on 2026-05-22.
//

#ifndef RTC_GROUP_H
#define RTC_GROUP_H

#include <shapes/Shape.h>

namespace rtc::shapes::groups {
    class Group final : public Shape {
        std::vector<std::unique_ptr<Shape>> shapes{};
        mutable std::vector<Bounds> child_bounds{};
        [[nodiscard]] std::array<float, 2> check_axis(const float& origin, const float& direction, const float& min, const float& max) const;

        public:
        [[nodiscard]] bool empty() const { return shapes.empty(); }
        [[nodiscard]] bool intersects_bounds(const Ray& r, const Bounds& b) const;
        [[nodiscard]] std::vector<intersections::Intersection> intersect(const Ray& ray) const override;
        [[nodiscard]] Vector local_normal_at(const Point &p) const override;
        [[nodiscard]] const Bounds& bounds() const override;
        void add_child(std::unique_ptr<Shape> shape);
        void cache_bounds() const;
        bool contains(const Shape* shape) const;
        [[nodiscard]] size_t size() const { return shapes.size(); }

        Shape& operator[](const size_t i) { return *shapes[i]; }
        const Shape& operator[](const size_t i) const { return *shapes[i]; }
        bool operator==(const Shape& shape) const override;
        bool operator!=(const Shape& shape) const { return !(*this == shape); }
    };
}



#endif //RTC_GROUP_H