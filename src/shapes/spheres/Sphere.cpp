//
// Created by Nicholas Solomon on 2026-05-08.
//

#include "Sphere.h"
#include <intersections/Intersection.h>
#include <tuples/Tuple.h>
#include <rays/Ray.h>
#include <typeinfo>

using namespace rtc::tuples;

namespace rtc::shapes::spheres {
    std::vector<intersections::Intersection> Sphere::intersect(const Ray& ray) const {
        const Ray ray2 = ray.transform(transform.inverse());

        const Vector sphere_to_ray = ray2.origin - point(0, 0, 0);

        const float a = dot(ray2.direction, ray2.direction);
        const float b = 2.0f * dot(ray2.direction, sphere_to_ray);
        const float c = dot(sphere_to_ray, sphere_to_ray) - 1.0f;

        const float discriminant = b * b - 4.0f * a * c;


        if (discriminant < 0) {
            return std::vector<intersections::Intersection>{};
        }

        const float t1 = (-b - std::sqrtf(discriminant)) / (2.0f * a);
        const float t2 = (-b + std::sqrtf(discriminant)) / (2.0f * a);

        return intersections::intersections({{t1, this},{t2, this}});
    }

    Vector Sphere::normal_at(const Point& p) const {
        const Point object_point = transform.inverse() * p;
        const Vector object_normal = object_point - point(0, 0, 0);
        Vector world_normal =  transform.inverse().transpose() * object_normal;
        world_normal.w = 0;
        return normalize(world_normal);
    }

    Sphere Sphere::glass() {
        Sphere sphere;
        sphere.material.transparency = 1.0;
        sphere.material.refractive_index = 1.5;
        return sphere;
    }
}
