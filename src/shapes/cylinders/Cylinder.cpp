//
// Created by Nicholas Solomon on 2026-05-22.
//

#include "Cylinder.h"
#include <rays/Ray.h>
#include <constants/Constants.h>
#include <intersections/Intersection.h>

using namespace rtc::constants;

namespace rtc::shapes::cylinders {
    std::vector<intersections::Intersection> Cylinder::intersect(const Ray& ray) const {
        const Ray ray2 = ray.transform(transform.inverse());
        const float a = std::powf(ray2.direction.x, 2) + std::powf(ray2.direction.z, 2);
        if (a < EPSILON) return {};
        const float b = 2 * ray2.origin.x * ray2.direction.x + 2 * ray2.origin.z * ray2.direction.z;
        const float c = std::powf(ray2.origin.x, 2) + std::powf(ray2.origin.z, 2) - 1;
        const float disc = std::powf(b, 2) - 4 * a * c;
        if (disc < 0) return {};
        const float t0 = (-b - std::sqrtf(disc)) / (2 * a);
        const float t1 = (-b + std::sqrtf(disc)) / (2 * a);
        return {{t0, this}, {t1, this}};
    }

    Vector Cylinder::normal_at(const Point &point) const {
        const Point obj_point = transform.inverse() * point;
        return vector(obj_point.x, 0, obj_point.z);
    }
}