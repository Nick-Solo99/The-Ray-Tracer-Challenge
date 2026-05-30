//
// Created by Nicholas Solomon on 2026-05-25.
//

#include "Triangle.h"
#include <constants/Constants.h>

using namespace rtc::constants;

namespace rtc::shapes::triangles {
    Vector Triangle::local_normal_at(const Point &p, const intersections::Intersection& i) const {
        return normal;
    }

    std::vector<intersections::Intersection> Triangle::intersect(const rays::Ray &r) const {
        const Ray r2 = r.transform(transform.inverse());
        const Vector dir_cross_e2 = cross(r2.direction, e2);
        const float det = dot(e1, dir_cross_e2);
        if (std::fabs(det) < EPSILON) return {};

        const float f = 1.f / det;
        const Vector p1_to_origin = r2.origin - p1;
        const float u = f * dot(p1_to_origin, dir_cross_e2);
        if (u < 0 || u > 1) return {};

        const Vector origin_cros_e1 = cross(p1_to_origin, e1);
        const float v = f * dot(r2.direction, origin_cros_e1);
        if (v < 0 || u + v > 1) return {};

        const float t = f * dot(e2, origin_cros_e1);
        return {{t, this, u, v}};
    }

    const Bounds& Triangle::bounds() const {
        if (cached_bounds) {
            return *cached_bounds;
        }
        Point min = point(0, 0, 0), max = point(0, 0, 0);
        min.x = std::min({p1.x, p2.x, p3.x});
        min.y = std::min({p1.y, p2.y, p3.y});
        min.z = std::min({p1.z, p2.z, p3.z});
        max.x = std::max({p1.x, p2.x, p3.x});
        max.y = std::max({p1.y, p2.y, p3.y});
        max.z = std::max({p1.z, p2.z, p3.z});
        cached_bounds = Bounds{min, max};
        return *cached_bounds;
    }

    bool Triangle::operator==(const Shape &other) const {
        if (!Shape::operator==(other)) return false;
        if (const auto o = dynamic_cast<const Triangle*>(&other); !o || p1 != o->p1 || p2 != o->p2 || p3 != o->p3) return false;
        return true;
    }
}
