//
// Created by xGrim on 2026-05-08.
//

#ifndef RTC_SPHERE_H
#define RTC_SPHERE_H
#include <shapes/Shape.h>

namespace rtc::shapes::spheres {
    class Sphere final : public Shape {
        public:
        [[nodiscard]] std::vector<Intersection> intersect(const Ray& ray) const override;
    };


}

#endif //RTC_SPHERE_H
