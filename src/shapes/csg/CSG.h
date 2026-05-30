//
// Created by Nicholas Solomon on 2026-05-30.
//

#ifndef RTC_CSG_H
#define RTC_CSG_H

#include <shapes/Shape.h>

namespace rtc::shapes::csg {

    enum class Operation {
        UNION,
        INTERSECT,
        DIFFERENCE
    };

    class CSG final : public Shape {
    public:
        Operation op;
        std::unique_ptr<Shape> left, right;
        CSG(const Operation& op, std::unique_ptr<Shape> left, std::unique_ptr<Shape> right) : op(op), left(std::move(left)), right(std::move(right)) {
            this->left->parent = this;
            this->right->parent = this;
        }
        [[nodiscard]] std::vector<intersections::Intersection> intersect(const Ray& ray) const override;
        [[nodiscard]] Vector local_normal_at(const Point &p, const intersections::Intersection &i) const override;
        [[nodiscard]] const Bounds& bounds() const override;
        [[nodiscard]] bool includes(const Shape& other) const override;
        [[nodiscard]] std::vector<intersections::Intersection> filter_intersections(std::vector<intersections::Intersection> xs) const;
    };

    [[nodiscard]] bool intersection_allowed(const Operation& op, const bool lhit, const bool inl, const bool inr);
}


#endif //RTC_CSG_H