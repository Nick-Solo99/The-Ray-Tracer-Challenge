//
// Created by xGrim on 2026-05-08.
//

#ifndef RTC_SPHERE_H
#define RTC_SPHERE_H
#include <vector>

#include <rays/Ray.h>

using namespace rtc::rays;

namespace rtc::spheres {
    class Sphere {
        public:
        Sphere() = default;

        std::vector<float> intersect(const Ray& ray) const;
    };


}

#endif //RTC_SPHERE_H
