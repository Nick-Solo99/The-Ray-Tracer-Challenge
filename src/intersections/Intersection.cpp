//
// Created by xGrim on 2026-05-08.
//

#include "Intersection.h"
#include <span>
#include <algorithm>

namespace rtc::intersections {

    std::vector<Intersection> intersections(const std::initializer_list<Intersection> list) {
        std::vector<Intersection> result{list};
        std::sort(result.begin(), result.end());
        return result;
    }

    std::optional<Intersection> hit(const std::span<const Intersection> intersections) {
        for (const auto& intersection : intersections) {
            if (intersection.t >= 0) {
                return intersection;
            }
        }
        return std::nullopt;
    }
}
