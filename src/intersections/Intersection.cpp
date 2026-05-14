//
// Created by Nicholas Solomon on 2026-05-08.
//

#include "Intersection.h"
#include <span>
#include <algorithm>
#include <constants/Constants.h>

using namespace rtc::constants;

namespace rtc::intersections {

    Components Intersection::pre_compute(const rays::Ray &ray) const {
        Components comps;

        comps.t = t;
        comps.object = object;

        comps.point = ray.position(comps.t);
        comps.eye_v = -ray.direction;
        comps.normal_v = comps.object->normal_at(comps.point);

        if (dot(comps.normal_v, comps.eye_v) < 0.0f) {
            comps.inside = true;
            comps.normal_v = -comps.normal_v;
        } else {
            comps.inside = false;
        }

        comps.over_point = comps.point + comps.normal_v * EPSILON;

        return comps;
    }

    std::vector<Intersection> intersections(const std::initializer_list<Intersection> list) {
        std::vector<Intersection> result{list};
        std::sort(result.begin(), result.end());
        return result;
    }

    std::optional<Intersection> hit(const std::span<const Intersection> intersections) {
        for (const auto& intersection : intersections) {
            if (intersection.t > EPSILON) {
                return intersection;
            }
        }
        return std::nullopt;
    }
}
