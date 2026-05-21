//
// Created by Nicholas Solomon on 2026-05-12.
//

#include "World.h"
#include "lights/point/PointLight.h"
#include <shapes/spheres/Sphere.h>
#include <transformations/Transformations.h>
#include <constants/Constants.h>

using namespace rtc::lights::point;
using namespace rtc::shapes::spheres;
using namespace rtc::rays;

namespace rtc::world {
    World World::default_world() {
        World world;
        world.lights.push_back(std::make_unique<PointLight>(point(-10, 10, -10), color(1, 1, 1)));
        world.objects.push_back(std::make_unique<Sphere>());
        world.objects.push_back(std::make_unique<Sphere>());


        world.objects[0]->material.color = color(0.8, 1.0, 0.6);
        world.objects[0]->material.diffuse = 0.7;
        world.objects[0]->material.specular = 0.2;

        world.objects[1]->transform = transformations::scaling(0.5, 0.5, 0.5);


        return world;
    }

    std::vector<intersections::Intersection> World::intersect(const rays::Ray &r) const {
        std::vector<intersections::Intersection> intersections;
        intersections.reserve(objects.size() * 4);

        for (const auto& obj: objects) {
            auto xs = obj->intersect(r);
            intersections.insert(intersections.end(), xs.begin(), xs.end());
        }

        std::sort(intersections.begin(), intersections.end());
        return intersections;
    }

    Color World::shade_hit(const intersections::Components &comps, const size_t& remaining) const {
        Color surface = color(0, 0, 0);

        for (const auto& light : lights) {
            const bool shadowed = is_shadowed(comps.over_point, *light);
            surface += comps.object->material.lighting(*comps.object, *light, comps.over_point, comps.eye_v, comps.normal_v, shadowed);
        }
        const Color reflected = reflected_color(comps, remaining);
        const Color refracted = refracted_color(comps, remaining);
        if (comps.object->material.reflective > 0.f && comps.object->material.transparency > 0.f) {
            const float reflectance = intersections::schlick(comps);
            return surface + reflected * reflectance + refracted * (1 - reflectance);
        }
        return surface + reflected + refracted;
    }

    Color World::color_at(const rays::Ray &r, const size_t& remaining) const {
        const auto xs = intersect(r);
        if (const auto& h = hit(xs)) {
            return shade_hit(h->pre_compute(r, xs), remaining);
        }
        return color(0, 0, 0);
    }

    bool World::is_shadowed(const Point& p, const lights::Light& light) const {
        const Vector v = light.position - p;
        const float distance = magnitude(v);
        const Vector direction = normalize(v);

        const Ray r{p, direction};
        const auto xs = intersect(r);
        if (const auto& h = hit(xs); h && h->object->material.casts_shadows && h->t < distance) {
            return true;
        }
        return false;
    }

    Color World::reflected_color(const intersections::Components &comps, const size_t& remaining) const {
        if (remaining < 1 || comps.object->material.reflective < constants::EPSILON) {
            return color(0, 0, 0);
        }

        const Ray reflect_ray{comps.over_point, comps.reflect_v};
        const Color c = color_at(reflect_ray, remaining - 1);

        return c * comps.object->material.reflective;
    }

    Color World::refracted_color(const intersections::Components &comps, const size_t &remaining) const {
        if (remaining == 0 || comps.object->material.transparency < EPSILON) {
            return color(0, 0, 0);
        }

        const float n_ratio = comps.n1 / comps.n2;
        const float cos_i = dot(comps.eye_v, comps.normal_v);
        const float sin2_t = n_ratio * n_ratio * (1 - cos_i * cos_i);

        if (sin2_t > 1) {
            return color(0, 0, 0);
        }

        const float cos_t = std::sqrtf(1.f - sin2_t);
        const Vector direction = comps.normal_v * (n_ratio * cos_i - cos_t) - comps.eye_v * n_ratio;
        const Ray refract_ray{comps.under_point, direction};

        return color_at(refract_ray, remaining - 1) * comps.object->material.transparency;
    }
}
