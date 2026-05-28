//
// Created by Nicholas Solomon on 2026-05-22.
//

#ifndef RTC_CONE_H
#define RTC_CONE_H

#include <shapes/cylinders/Cylinder.h>

using namespace rtc::shapes::cylinders;

namespace rtc::shapes::cones {
    class Cone final : public Cylinder{
        protected:
        static bool check_cap(const Ray& ray, const float& t, const float& radius);
        void intersect_caps(const Ray& ray, std::vector<intersections::Intersection>& xs) const override;
    public:
        [[nodiscard]] std::vector<intersections::Intersection> intersect(const Ray& ray) const override;
        [[nodiscard]] Vector local_normal_at(const Point &p) const override;
        [[nodiscard]] const Bounds& bounds() const override;
    };
}


#endif //RTC_CONE_H