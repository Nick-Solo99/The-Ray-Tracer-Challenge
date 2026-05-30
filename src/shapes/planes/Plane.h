//
// Created by Nicholas Solomon on 2026-05-14.
//

#ifndef RTC_PLANE_H
#define RTC_PLANE_H

#include <shapes/Shape.h>

namespace rtc::shapes::planes {
    class Plane final : public Shape{
        public:
        [[nodiscard]] std::vector<intersections::Intersection> intersect(const Ray& ray) const override;
        [[nodiscard]] Vector local_normal_at(const Point& p, const intersections::Intersection& i) const override;
        [[nodiscard]] const Bounds& bounds() const override;
    };
}

#endif //RTC_PLANE_H