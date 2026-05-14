//
// Created by Nicholas Solomon on 2026-05-14.
//

#include "Plane.h"
#include <intersections/Intersection.h>
#include <typeinfo>

constexpr float EPSILON = 0.005f;

namespace rtc::shapes::planes {
    bool Plane::operator==(const Shape &other) const {
        if (typeid(*this) != typeid(other) || material != other.material || transform != other.transform) {
            return false;
        }
        return true;
    }

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

    Vector Plane::normal_at(const Point &p) const {
        return vector(0, 1, 0);
    }
}
