//
// Created by Nicholas Solomon on 2026-05-12.
//

#ifndef RTC_WORLD_H
#define RTC_WORLD_H

#include <vector>
#include <memory>
#include <shapes/Shape.h>
#include <lights/Light.h>
#include <intersections/Intersection.h>
#include <rays/Ray.h>
#include <constants/Constants.h>

using namespace rtc::constants;

namespace rtc::world {
    struct World {
        std::vector<std::unique_ptr<shapes::Shape>> objects;
        std::vector<std::unique_ptr<lights::Light>> lights;

        static World default_world();

        [[nodiscard]] std::vector<intersections::Intersection> intersect(const rays::Ray& r) const;
        [[nodiscard]] Color shade_hit(const intersections::Components& comps, const size_t& remaining = RECURSION_DEPTH) const;
        [[nodiscard]] Color color_at(const rays::Ray& r, const size_t& remaining = RECURSION_DEPTH) const;
        [[nodiscard]] bool is_shadowed(const Point& p, const lights::Light& light) const;
        [[nodiscard]] Color reflected_color(const intersections::Components& comps, const size_t& remaining = RECURSION_DEPTH) const;
    };
}

#endif //RTC_WORLD_H
