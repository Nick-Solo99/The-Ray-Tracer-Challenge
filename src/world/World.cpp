//
// Created by Nicholas Solomon on 2026-05-12.
//

#include "World.h"
#include "lights/point/PointLight.h"
#include <shapes/spheres/Sphere.h>
#include <transformations/Transformations.h>

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

    Color World::shade_hit(const intersections::Components &comps) const {
        Color result = color(0, 0, 0);
        const bool& shadowed = is_shadowed(comps.over_point);

        for (const auto& light : lights) {
            result += comps.object->material.lighting(*light, comps.point, comps.eye_v, comps.normal_v, shadowed);
        }

        return result;
    }

    Color World::color_at(const rays::Ray &r) const {
        const auto xs = intersect(r);
        if (const auto& h = hit(xs)) {
            return shade_hit(h->pre_compute(r));
        }
        return color(0, 0, 0);
    }

    bool World::is_shadowed(const Point& p) const {
        const Vector v = lights[0]->position - p;
        const float distance = magnitude(v);
        const Vector direction = normalize(v);

        const Ray r{p, direction};
        const auto xs = intersect(r);
        if (const auto& h = hit(xs); h && h->t < distance) {
            return true;
        }
        return false;
    }
}
