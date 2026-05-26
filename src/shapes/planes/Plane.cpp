//
// Created by Nicholas Solomon on 2026-05-14.
//

#include "Plane.h"
#include <intersections/Intersection.h>
#include <typeinfo>
#include <constants/Constants.h>

using namespace rtc::constants;


namespace rtc::shapes::planes {
    std::vector<intersections::Intersection> Plane::intersect(const Ray &ray) const {
        const Ray ray2 = ray.transform(transform.inverse());
        std::vector<intersections::Intersection> intersections;

        if (std::fabs(ray2.direction.y) < EPSILON) {
            return intersections;
        }

        const float t = - ray2.origin.y / ray2.direction.y;
        intersections.push_back(intersections::Intersection{t, this});

        return intersections;
    }

    Vector Plane::local_normal_at(const Point &p) const {
        return vector(0, 1, 0);
    }

    Bounds Plane::bounds() const {
        return {{-INFINITY, 0, -INFINITY}, {INFINITY, 0, INFINITY}};
    }
}
