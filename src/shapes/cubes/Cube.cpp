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

    bool Cube::operator==(const Shape &other) const {
        return typeid(*this) == typeid(other) && transform == other.transform && material == other.material;
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

    Vector Cube::normal_at(const Point &p) const {
        const Point obj_point = transform.inverse() * p;
        const float max_c = std::max({std::fabs(obj_point.x), std::fabs(obj_point.y), std::fabs(obj_point.z)});
        Vector obj_normal;
        if (max_c == std::fabs(obj_point.x)) {
            obj_normal = vector(obj_point.x, 0, 0);
        }else if (max_c == std::fabs(obj_point.y)) {
            obj_normal = vector(0, obj_point.y, 0);
        } else {
            obj_normal = vector(0, 0, obj_point.z);
        }

        Vector world_normal = transform.inverse().transpose() * obj_normal;
        world_normal.w = 0;
        return normalize(world_normal);
    }
}


