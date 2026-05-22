//
// Created by Nicholas Solomon on 2026-05-22.
//

#ifndef RTC_CYLINDER_H
#define RTC_CYLINDER_H

#include <shapes/Shape.h>

namespace rtc::shapes::cylinders {
    class Cylinder final : public Shape {
        static bool check_cap(const Ray& ray, const float& t) ;
        void intersect_caps(const Ray& ray, std::vector<intersections::Intersection>& xs) const;
    public:
        float minimum = -INFINITY;
        float maximum = INFINITY;
        bool closed = false;
        [[nodiscard]] std::vector<intersections::Intersection> intersect(const Ray& ray) const override;
        [[nodiscard]] Vector normal_at(const Point& point) const override;
    };


}


#endif //RTC_CYLINDER_H