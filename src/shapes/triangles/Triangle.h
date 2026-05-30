//
// Created by Nicholas Solomon on 2026-05-25.
//

#ifndef RTC_TRIANGLE_H
#define RTC_TRIANGLE_H

#include <shapes/Shape.h>
#include <intersections/Intersection.h>

namespace rtc::shapes::triangles {
    class Triangle : public Shape {
        public:
        Point p1{}, p2{}, p3{};
        Vector e1{}, e2{}, normal{};
        Triangle(const Point& p1, const Point& p2, const Point& p3) : p1(p1), p2(p2), p3(p3), e1(p2 - p1), e2(p3 - p1), normal(normalize(cross(e2, e1))) {};
        [[nodiscard]] Vector local_normal_at(const Point &p, const intersections::Intersection& i) const override;
        [[nodiscard]] std::vector<intersections::Intersection> intersect(const rays::Ray& r) const override;
        [[nodiscard]] const Bounds& bounds() const override;
        [[nodiscard]] bool operator==(const Shape& other) const override;
    };
}


#endif //RTC_TRIANGLE_H