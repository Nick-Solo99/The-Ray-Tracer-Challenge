//
// Created by Nicholas Solomon on 2026-05-22.
//

#include "Cylinder.h"
#include <rays/Ray.h>
#include <constants/Constants.h>
#include <intersections/Intersection.h>

using namespace rtc::constants;

namespace rtc::shapes::cylinders {
    bool Cylinder::check_cap(const Ray &ray, const float &t) {
        const float x = ray.origin.x + t * ray.direction.x;
        const float z = ray.origin.z + t * ray.direction.z;
        return (x * x + z * z) - 1 < EPSILON;
    }

    void Cylinder::intersect_caps(const Ray &ray, std::vector<intersections::Intersection> &xs) const {
        if (!closed || std::fabs(ray.direction.y) < EPSILON) return;
        float t = (minimum - ray.origin.y) / ray.direction.y;
        if (check_cap(ray, t)) xs.push_back({t, this});
        t = (maximum - ray.origin.y) / ray.direction.y;
        if (check_cap(ray, t)) xs.push_back({t, this});
    }

    std::vector<intersections::Intersection> Cylinder::intersect(const Ray& ray) const {
        const Ray ray2 = ray.transform(transform.inverse());
        std::vector<intersections::Intersection> xs;
        const float a = std::powf(ray2.direction.x, 2) + std::powf(ray2.direction.z, 2);
        if (a == 0) {
            intersect_caps(ray2, xs);
            return xs;
        }
        const float b = 2 * ray2.origin.x * ray2.direction.x + 2 * ray2.origin.z * ray2.direction.z;
        const float c = std::powf(ray2.origin.x, 2) + std::powf(ray2.origin.z, 2) - 1;
        const float disc = std::powf(b, 2) - 4 * a * c;
        if (disc < 0) return {};
        float t0 = (-b - std::sqrtf(disc)) / (2 * a);
        float t1 = (-b + std::sqrtf(disc)) / (2 * a);
        if (t0 > t1) std::swap(t0, t1);
        const float y0 = ray2.origin.y + t0 * ray2.direction.y;
        if (minimum < y0 && y0 < maximum) xs.push_back({t0, this});
        const float y1 = ray2.origin.y + t1 * ray2.direction.y;
        if (minimum < y1 && y1 < maximum) xs.push_back({t1, this});

        intersect_caps(ray2, xs);

        return xs;
    }

    Vector Cylinder::normal_at(const Point &point) const {
        const Point obj_point = transform.inverse() * point;
        const float dist = std::powf(obj_point.x, 2) + std::powf(obj_point.z, 2);
        if (dist < 1 && obj_point.y >= maximum - EPSILON) return vector(0, 1, 0);
        if (dist < 1 && obj_point.y <= minimum + EPSILON) return vector(0, -1, 0);
        return vector(obj_point.x, 0, obj_point.z);
    }
}