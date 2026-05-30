//
// Created by Nicholas Solomon on 2026-05-21.
//

#include "Cube.h"

#include <constants/Constants.h>
#include <rays/Ray.h>
#include <algorithm>
#include <intersections/Intersection.h>

using namespace rtc::constants;

namespace rtc::shapes::cubes {
    std::array<float, 2> Cube::check_axis(const float& origin, const float& direction) const {
        const float tmin_numerator = (-1 - origin);
        const float tmax_numerator = (1 - origin);
        float tmin, tmax;
        if (std::fabs(direction) >= EPSILON) {
            tmin = tmin_numerator / direction;
            tmax = tmax_numerator / direction;
        } else {
            tmin = tmin_numerator < 0 ? -INFINITY : INFINITY;
            tmax = tmax_numerator < 0 ? -INFINITY : INFINITY;
        }
        if (tmin > tmax) {
            std::swap(tmin, tmax);
        }
        return { tmin, tmax };
    }

    std::vector<intersections::Intersection> Cube::intersect(const rays::Ray &ray) const {
        const Ray ray2 = ray.transform(transform.inverse());
        const auto [xtmin, xtmax] = check_axis(ray2.origin.x, ray2.direction.x);
        const auto [ytmin, ytmax] = check_axis(ray2.origin.y, ray2.direction.y);
        float tmin = std::max({xtmin, ytmin});
        float tmax = std::min({xtmax, ytmax});

        if (tmin > tmax) return {};

        const auto [ztmin, ztmax] = check_axis(ray2.origin.z, ray2.direction.z);

        tmin = std::max({tmin, ztmin});
        tmax = std::min({tmax, ztmax});
        if (tmin > tmax) return {};

        return {{tmin, this}, {tmax, this}};
    }

    Vector Cube::local_normal_at(const Point &p, const intersections::Intersection& i) const {
        const float max_c = std::max({std::fabs(p.x), std::fabs(p.y), std::fabs(p.z)});
        if (max_c == std::fabs(p.x)) {
            return vector(p.x, 0, 0);
        }
        if (max_c == std::fabs(p.y)) {
            return vector(0, p.y, 0);
        }
        return vector(0, 0, p.z);
    }

    const Bounds& Cube::bounds() const {
        if (cached_bounds) {
            return *cached_bounds;
        }
        cached_bounds = {{-1, -1, -1}, {1, 1, 1}};
        return *cached_bounds;
    }

    bool Cube::includes(const Shape &other) const {
        return this == &other;
    }
}


