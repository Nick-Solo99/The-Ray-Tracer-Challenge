//
// Created by Nicholas Solomon on 2026-05-08.
//

#include "Intersection.h"
#include <span>
#include <algorithm>
#include <constants/Constants.h>

using namespace rtc::constants;

namespace rtc::intersections {

    Components Intersection::pre_compute(const rays::Ray &ray, const std::vector<Intersection>& xs) const {
        Components comps;

        comps.t = t;
        comps.object = object;

        comps.point = ray.position(comps.t);
        comps.eye_v = -ray.direction;
        comps.normal_v = comps.object->normal_at(comps.point, *this);

        if (dot(comps.normal_v, comps.eye_v) < 0.0f) {
            comps.inside = true;
            comps.normal_v = -comps.normal_v;
        } else {
            comps.inside = false;
        }

        comps.over_point = comps.point + comps.normal_v * EPSILON;
        comps.under_point = comps.point - comps.normal_v * EPSILON;

        comps.reflect_v = ray.direction.reflect(comps.normal_v);

        std::vector<const Shape*> container;

        for (const auto& i : xs) {
            if (i == *this) {
                if (container.empty()) {
                    comps.n1 = 1.0f;
                } else {
                    comps.n1 = container.back()->material.refractive_index;
                }
            }
            if (auto it = std::ranges::find(container, i.object); it != container.end()) {
                container.erase(it);
            } else {
                container.push_back(i.object);
            }
            if (i == *this) {
                if (container.empty()) {
                    comps.n2 = 1.0f;
                } else {
                    comps.n2 = container.back()->material.refractive_index;
                }
                break;
            }
        }

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

    float schlick(const Components& comps) {
        float cos = dot(comps.eye_v, comps.normal_v);
        if (comps.n1 > comps.n2) {
            const float n = comps.n1 / comps.n2;
            const float sin2_t = n * n * (1.0f - cos * cos);
            if (sin2_t > 1.0f) {
                return 1.0f;
            }
            const float cos_t = std::sqrtf(1.0f - sin2_t);
            cos = cos_t;
        }
        const float r0 = std::powf((comps.n1 - comps.n2) / (comps.n1 + comps.n2), 2);
        return r0 + (1.0f - r0) * std::powf(1.f - cos, 5);
    }
}
