//
// Created by Nicholas Solomon on 2026-05-29.
//

#ifndef RTC_SMOOTHTRIANGLE_H
#define RTC_SMOOTHTRIANGLE_H

#include <shapes/triangles/Triangle.h>

namespace rtc::shapes::triangles {
    class SmoothTriangle final : public Triangle{
        public:
        Vector n1, n2, n3;
        SmoothTriangle(const Point& p1, const Point& p2, const Point& p3, const Vector& n1, const Vector& n2, const Vector& n3) : Triangle(p1, p2, p3), n1(n1), n2(n2), n3(n3) {};
        [[nodiscard]] Vector local_normal_at(const Point& p, const intersections::Intersection& i) const override;
        [[nodiscard]] bool operator==(const Shape &other) const override;
    };
}


#endif //RTC_SMOOTHTRIANGLE_H