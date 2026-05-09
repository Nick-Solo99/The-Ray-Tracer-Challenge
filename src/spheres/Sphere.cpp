//
// Created by xGrim on 2026-05-08.
//

#include "Sphere.h"


namespace rtc::spheres {

    std::vector<float> Sphere::intersect(const Ray& ray) const {
        const Vector sphere_to_ray = ray.origin - point(0, 0, 0);

        const float a = dot(ray.direction, ray.direction);
        const float b = 2.0f * dot(ray.direction, sphere_to_ray);
        const float c = dot(sphere_to_ray, sphere_to_ray) - 1.0f;

        const float discriminant = b * b - 4.0f * a * c;

        if (discriminant < 0) {
            return std::vector<float>{};
        }

        const float t1 = (-b - sqrtf(discriminant)) / (2.0f * a);
        const float t2 = (-b + sqrtf(discriminant)) / (2.0f * a);

        return std::vector{t1, t2};
    }

}
