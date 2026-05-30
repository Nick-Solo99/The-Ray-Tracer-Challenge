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
        [[nodiscard]] static std::array<float, 2> check_axis(const float& origin, const float& direction, const float& min, const float& max);

        public:
        [[nodiscard]] bool empty() const { return shapes.empty(); }
        [[nodiscard]] static bool intersects_bounds(const Ray& r, const Bounds& b);
        [[nodiscard]] std::vector<intersections::Intersection> intersect(const Ray& ray) const override;
        [[nodiscard]] Vector local_normal_at(const Point &p, const intersections::Intersection& i) const override;
        [[nodiscard]] const Bounds& bounds() const override;
        void add_child(std::unique_ptr<Shape> shape);
        void cache_bounds() const;
        bool contains(const Shape* shape) const;
        [[nodiscard]] size_t size() const { return shapes.size(); }
        void set_material(const Material& material) const;

        Shape& operator[](const size_t i) { return *shapes[i]; }
        const Shape& operator[](const size_t i) const { return *shapes[i]; }
        bool operator==(const Shape& shape) const override;
        bool operator!=(const Shape& shape) const { return !(*this == shape); }
    };
}



#endif //RTC_GROUP_H