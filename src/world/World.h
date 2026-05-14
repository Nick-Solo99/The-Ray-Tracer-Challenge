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

namespace rtc::world {
    struct World {
        std::vector<std::unique_ptr<shapes::Shape>> objects;
        std::vector<std::unique_ptr<lights::Light>> lights;

        static World default_world();

        [[nodiscard]] std::vector<intersections::Intersection> intersect(const rays::Ray& r) const;
        [[nodiscard]] Color shade_hit(const intersections::Components& comps) const;
        [[nodiscard]] Color color_at(const rays::Ray& r) const;
    };
}

#endif //RTC_WORLD_H
